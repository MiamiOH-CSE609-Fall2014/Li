#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>

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
  long size1=14+40+x*y*3;
  char* image=new char[size1];
  char* image2=new char[size1];
  if(fileName=="")
    cout<<"No File Name Input"<<endl;
  else
    {
      if (x<=0||y<=0)
	cout<<"Illegal Value Input"<<endl;
      else
	{
	      string fname,fname2;
              fname=fileName+".bmp";
              fname2=fileName+"_test.bmp";
	      ifstream myFile(fname.c_str(),ios::binary);
              myFile.read(image,size1);
	      myFile.close();
              //int* r=new int[x*y];
              //int* g=new int[x*y];
              //int* b=new int[x*y];
              int r[x][y],g[x][y],b[x][y],h[x][y],s[x][y],in[x][y];
              int r2[x][y],g2[x][y],b2[x][y],h2[x][y],s2[x][y],in2[x][y];
              int i=0;
              for (int row=0;row<y;row++)
		{
		  for (int col=0;col<x;col++)
		    {
		        r[col][row]=image[14+40+i*3];
                        g[col][row]=image[14+40+i*3+1];
                        b[col][row]=image[14+40+i*3+2];

                        double h1,s1,in1=(r[col][row]+g[col][row]+b[col][row])/3,h0,s0,in0;

   if (r[col][row]+g[col][row]+b[col][row]==765)
   {
      s1=0;
      h1=0;
   }
  double minimum = min(r[col][row], min(g[col][row],b[col][row]));

  if (in1>0)s1= 1 - minimum/in1;
  else if (in1==0)s1=0;

  double temp=(r[col][row]-(g[col][row]/2)-(b[col][row]/2))/(sqrt((r[col][row]*r[col][row])+(g[col][row]*g[col][row])+(b[col][row]*b[col][row])-(r[col][row]*g[col][row])-(r[col][row]*b[col][row])-(g[col][row]*b[col][row])));
  if(g[col][row]>=b[col][row])h1=acos(temp); 
  else if(b[col][row]>g[col][row])h1=360-acos(temp);

  h[col][row] = (int) h1;
  s[col][row] = s1;
  in[col][row] = (int) in1; 
                        
  h2[col][row]=h[col][row];
  s2[col][row]=s[col][row];//tempor
  in2[col][row]=in[col][row];

h0=h2[col][row];
s0=s2[col][row];
in0=in2[col][row];

if (h0 == 0){
   r2[col][row] = (int) (in0 + (2 * in0 * s0));
   g2[col][row] = (int) (in0 - (in0 * s0));
   b2[col][row] = (int) (in0 - (in0 * s0));
  }

else if ((0 < h0) && (h0 < 120)) {
   r2[col][row] = (int) (in0 + (in0 * s0) * cos(h0) / cos(60-h0));
   g2[col][row] = (int) (in0 + (in0 * s0) * (1 - cos(h0) / cos(60-h0)));
   b2[col][row] = (int) (in0 - (in0 * s0));
  }

else if ( h0 == 120 ){
   r2[col][row] = (int) (in0 - (in0 * s0));
   g2[col][row] = (int) (in0 + (2 * in0 * s0));
   b2[col][row] = (int) (in0 - (in0 * s0));
  }

else if ((120 < h0) && (h0 < 240)) {
   r2[col][row] = (int) (in0 - (in0 * s0));
   g2[col][row] = (int) (in0 + (in0 * s0) * cos(h0-120) / cos(180-h0));
   b2[col][row] = (int) (in0 + (in0 * s0) * (1 - cos(h0-120) / cos(180-h0)));
  }

else if (h0 == 240) {
   r2[col][row] = (int) (in0 - (in0 * s0));
   g2[col][row] = (int) (in0 - (in0 * s0));
   b2[col][row] = (int) (in0 + (2 * in0 * s0));
  }

else if ((240 < h0) && (h0 < 360)) {
   r2[col][row] = (int) (in0 + (in0 * s0) * (1 - cos(h0-240) / cos(300-h0)));
   g2[col][row] = (int) (in0 - (in0 * s0));
   b2[col][row] = (int) (in0 + (in0 * s0) * cos(h0-240) / cos(300-h0));
  }

                        i++;
		    }
		}

              

              for(int i=0;i<14+40;i++)image2[i]=image[i];//temporary
	      i=0;
              for (int row=0;row<y;row++)
		{
		  for (int col=0;col<x;col++)
		    {
		        image2[14+40+i*3]=r2[col][row];
                        image2[14+40+i*3+1]=g2[col][row];
                        image2[14+40+i*3+2]=b2[col][row];
                        i++;
		    }
		}
              ofstream myFile2(fname2.c_str(),ios::binary);
              for(int i=0;i<size1;image2++,i++)
              {
                myFile2.write(image2,1);
              }
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