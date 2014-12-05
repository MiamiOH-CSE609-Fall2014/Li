#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

#ifndef DWORD
#define WINAPI
typedef unsigned long DWORD;
typedef short WCHAR;
typedef void * HANDLE;
#define MAX_PATH PATH_MAX
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int BOOL;
#endif

/*
typedef struct tagBITMAPFILEHEADER
{
    //WORD bfType;//λͼ�ļ������ͣ�����ΪBM(1-2�ֽڣ�
    char bfType[2];
    //DWORD bfSize;//λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ��3-6�ֽڣ���λ��ǰ��
    int bfSize;
    WORD bfReserved1;//λͼ�ļ������֣�����Ϊ0(7-8�ֽڣ�
    WORD bfReserved2;//λͼ�ļ������֣�����Ϊ0(9-10�ֽڣ�
    //DWORD bfOffBits;//λͼ���ݵ���ʼλ�ã��������λͼ��11-14�ֽڣ���λ��ǰ��
    int bfOffBits;
    //�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
      DWORD  biSize;//���ṹ��ռ���ֽ�����15-18�ֽڣ�
      DWORD  biWidth;//λͼ�Ŀ�ȣ�������Ϊ��λ��19-22�ֽڣ�
      DWORD  biHeight;//λͼ�ĸ߶ȣ�������Ϊ��λ��23-26�ֽڣ�
      WORD   biPlanes;//Ŀ���豸�ļ��𣬱���Ϊ1(27-28�ֽڣ�
      WORD   biBitCount;
//ÿ�����������λ����������1��˫ɫ������29-30�ֽڣ�4(16ɫ����8(256ɫ��16(�߲�ɫ)��24�����ɫ��֮һ
      DWORD  biCompression;
//λͼѹ�����ͣ�������0����ѹ��������31-34�ֽڣ�1(BI_RLE8ѹ�����ͣ���2(BI_RLE4ѹ�����ͣ�֮һ
      DWORD  biSizeImage;//λͼ�Ĵ�С(���а�����Ϊ�˲���������4�ı�������ӵĿ��ֽ�)�����ֽ�Ϊ��λ��35-38�ֽڣ�
      //DWORD  biXPelsPerMeter;//λͼˮƽ�ֱ��ʣ�ÿ����������39-42�ֽڣ�
      signed int biXPelsPerMeter;
      //DWORD  biYPelsPerMeter;//λͼ��ֱ�ֱ��ʣ�ÿ����������43-46�ֽ�)
      signed int biYPelsPerMeter;
      DWORD  biClrUsed;//λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ�
      DWORD  biClrImportant;//λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ�
   } BITMAPINFOHEADER;
*/

struct BITMAPFILEHEADER             // File header
{ 
  char bfType[2];                   // File type: should be BM ( 0x42 0x4D ) 
  int bfSize;                       // File size in bytes
  short bfReserved1;                // Reserved - for what i have no idea :P 
  short bfReserved2;                // -||-
  int bfOffBits;                    // Offset, adress of the beginning of the information about image (pixels )
};

struct BITMAPINFOHEADER             // Bitmap header
{
  unsigned int biSize;              // Size of this header
  unsigned int biWidth;             // Width of image ( in pixels)
  unsigned int biHeight;            // Height of this image ( in pixels )
  unsigned short biPlanes;          // Numer of color planes, always 1
  unsigned short biBitCount;        // Number of bytes for pixel. Possibility values :1,4,8,16, 24 and 32
  unsigned int biCompression;       // Used compression (0 -none)
  unsigned int biSizeImage;         // Size of image 
  signed int biXPelsPerMeter;       // Horizontal resolution of the image (pixel per meter)
  signed int biYPelsPerMeter;       // Vertical resolution of the image (pixel per meter)
  unsigned int biClrUsed;           // Number of colors in the color palette, or 0 to default to 2^n ( 0- no palette)
  unsigned int biClrImportant;      // Number of important colors used
};

struct Pixel{
    unsigned int blue;
    unsigned int green;
    unsigned int red;
    //unsigned char reserved;
};

void writeHeader(ostream& out, int width, int height)
{
	BITMAPFILEHEADER tWBFH;
	//tWBFH.bfType = 0x4d42;
        tWBFH.bfType[0]='B';
        tWBFH.bfType[1]='W';
	tWBFH.bfSize = 14 + 40 + (width*height*3);
	tWBFH.bfReserved1 = 0;
	tWBFH.bfReserved2 = 0;
	tWBFH.bfOffBits = 14 + 40;

	BITMAPINFOHEADER tW2BH;
	//memset(&tW2BH,0,40);
	tW2BH.biSize = 40;
	tW2BH.biWidth = width;
	tW2BH.biHeight = height;
	tW2BH.biPlanes = 1;
	tW2BH.biBitCount = 24;
	tW2BH.biCompression = 0;

	out.write((char*)(&tWBFH),14);
	out.write((char*)(&tW2BH),40);
}

//Information on BMP format was provided by www.fileformat.info/format/bmp/egff.htm
void readHeader(istream& in, int& width, int& height){
	BITMAPFILEHEADER tWBFH;
	BITMAPINFOHEADER tW2BH;
	in.read((char*)(&tWBFH),14);
	in.read((char*)(&tW2BH),40);
	width = tW2BH.biWidth;
	height = tW2BH.biHeight;
}


void makeCheckerboardBMP(string fileName, int x, int y)
{
  char r,g,b;
  char* fileHeader=new char[sizeof(BITMAPFILEHEADER)];
  char* infoHeader=new char[sizeof(BITMAPINFOHEADER)];
  char* image=new char[x*y*3];

  if(fileName=="")
    cout<<"No File Name Input"<<endl;
  else
    {
      if (x<=0||y<=0)
	cout<<"Illegal Value Input"<<endl;
      else
	{
	      string fname,fname2;
              //fname=filename;
              fname=fileName+".bmp";
              fname2=fileName+"_test.bmp";
	      ifstream myFile(fname.c_str(),ios::binary);

              readHeader(myFile,x,y);

              /*myFile.read(fileHeader,sizeof(BITMAPFILEHEADER));
              myFile.read(infoHeader,sizeof(BITMAPINFOHEADER));
              myFile.read(image,x*y*3);
              
              BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)(fileHeader);
              cout << "\n FILHEADER\n";
              cout << "\n File type: " << bfh->bfType[0] << bfh->bfType[1] << endl;
              cout << " File size: " << bfh->bfSize << endl;
              cout << " Offset(adress of beggining of the image information): " << bfh->bfOffBits << endl;

              BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(infoHeader);
              cout << "\n INFOHEADER\n";
              cout << "\n Header size: " << bih->biSize << endl;
              cout << " Image width: " << bih->biWidth << endl;
              cout << " Image height: " << bih->biHeight << endl;
              cout << " Number of bytes for pixel: " << bih->biBitCount << endl;
              cout << " Used compression: " << bih->biCompression << endl;
              cout << " Image size: " << bih->biSizeImage<< endl;
              cout << " Horizontal resolution: " << bih->biXPelsPerMeter << endl;
              cout << " Vertical resolution: " << bih->biYPelsPerMeter << endl;
              cout << " Number of colors in the color palette: " << bih->biClrUsed << endl;
              cout << " Number of important colors used: " << bih->biClrImportant << endl;

              for(int i=0;i<sizeof(BITMAPFILEHEADER);i++)
                            {
                cout << fileHeader[i] << endl;
                            }
                            cout<<sizeof(BITMAPFILEHEADER)<<"&"<<sizeof(BITMAPINFOHEADER)<<endl;
                            for(int i=0;i<sizeof(BITMAPINFOHEADER);i++)
                            {
                                cout << infoHeader[i] << endl;
                            }*/

                            myFile.read(image,x*y*3);
                            for(int i=0;i<x*y*3;i++)
                            {
                                cout <<"No."<<i<<":"<<(int)image[i] << endl;
                            }
cout<<"x:"<<x<<endl;
cout<<"y:"<<y<<endl;
cout<<"size of image:"<<sizeof(image)<<endl;
                  
              /*for (int row=0;row<y;row++)
		{
		  for (int col=0;col<x;col++)
		    {
		      
		    }
		}*/
	      myFile.close();
	      
              ofstream myFile2(fname2.c_str(),ios::binary);
              writeHeader(myFile2,x,y);
              for(int i=0;i<x*y*3;image++,i++)
              {
                myFile2.write(image,1);
              }

	      /*for (int row=0;row<squaresize*n;row++)
		{
		  for (int col=0;col<squaresize*n;col++)
		    {
		      if ((row/squaresize+col/squaresize)%2==1)
			r=0,g=0,b=0;
		      else
			{
			  r=255,g=255,b=255;
			}
		      myFile.write(&r,1);
		      myFile.write(&g,1);
		      myFile.write(&b,1);
		    }
		}*/
	      myFile2.close(); 
	}
    }
}

int main()
{
  makeCheckerboardBMP("Yao_24bit",100,100);
  //makeCheckerboardBMP("lena512",512,512);
  return 0;
}