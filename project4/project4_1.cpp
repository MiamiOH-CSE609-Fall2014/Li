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
         cout<<"[x="<<width<<"]"<<endl;
                  cout<<"[y="<<height<<"]"<<endl;
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
              myFile.read(image,x*y*3);
              /*for(int i=0;i<x*y*3;i++)
              {
                  cout <<"No."<<i<<":"<<(int)image[i] << endl;
              }
              cout<<"x:"<<x<<endl;
              cout<<"y:"<<y<<endl;
              cout<<"size of image:"<<sizeof(image)<<endl;*/
                  
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
	     myFile2.close(); 
	}
    }
}

int main()
{
  makeCheckerboardBMP("Yao_8bit",100,100);
  //makeCheckerboardBMP("lena512",512,512);
  return 0;
}