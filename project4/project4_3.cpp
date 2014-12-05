#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

//adapted from windows.h

struct BITMAPFILEHEADER             // File header
{ 
  char bfType[2];                   // File type: should be BM ( 0x42 0x4D ) 
  int bfSize;                       // File size in bytes
  short bfReserved1;                // Reserved - for what i have no idea :P 
  short bfReserved2;                // -||-
  int bfOffBits;                    // Offset, adress of the beginning of the information about image (pixels )
};

//adapted from windows.h

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

void generate(string fileName,int x,int y,int threshold,int filter)
{
    int templates[25] = { 1, 4, 7, 4, 1,   
                          4, 16, 26, 16, 4,   
                          7, 26, 41, 26, 7,  
                          4, 16, 26, 16, 4,   
                          1, 4, 7, 4, 1 };
  int index=0;
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
              int r[x][y],g[x][y],b[x][y],h[x][y],s[x][y],in[x][y];
              int r2[x][y],g2[x][y],b2[x][y],h2[x][y],s2[x][y],in2[x][y];
              int diff[x][y];
              int i=0;
              for (int row=0;row<y;row++)
		{
		  for (int col=0;col<x;col++)
		    {
		        r[col][row]=image[14+40+i*3];
                        g[col][row]=image[14+40+i*3+1];
                        b[col][row]=image[14+40+i*3+2];

            if(filter==1)
            {
            index=0;
                        r2[col][row]=0;
                        g2[col][row]=0;
                        b2[col][row]=0;
            for ( int m=col-2; m<col+3; m++)  
            {  
                for (int n=row-2; n<row+3; n++)  
                {  
                    if(m>=0&&m<x&&n>=0&&n<y)
                    {
                        r2[col][row]+=r[m][n]*templates[index];
                        g2[col][row]+=g[m][n]*templates[index];
                        b2[col][row]+=b[m][n]*templates[index];
                    }
                    index++;
                }  
            }
            r2[col][row]/=273;
            g2[col][row]/=273;
            b2[col][row]/=273;
            if(r2[col][row]>255)r2[col][row]=255;
            if(g2[col][row]>255)g2[col][row]=255;
            if(b2[col][row]>255)b2[col][row]=255;
            }
            else
            {
                        r2[col][row]=r[col][row];
                        g2[col][row]=g[col][row];
                        b2[col][row]=b[col][row];
            }

  if(row==0||col==0)diff[col][row]=0;
  else
  {
    //diff[col][row]=abs(r2[col][row]+g2[col][row]+b2[col][row]-r2[col-1][row]-g2[col-1][row]-b2[col-1][row])-abs(r2[col][row-1]+g2[col][row-1]+b2[col][row-1]-r2[col-1][row-1]-g2[col-1][row-1]-b2[col-1][row-1]);
    diff[col][row]=abs(r2[col][row]*2+g2[col][row]*2+b2[col][row]*2-r2[col-1][row]-g2[col-1][row]-b2[col-1][row]-r2[col][row-1]-g2[col][row-1]-b2[col][row-1]);
  }
  if(diff[col][row]>threshold)
  {
    r2[col][row] = 0;
    g2[col][row] = 0;
    b2[col][row] = 0;
  }
  else
  {
    r2[col][row] = 255;
    g2[col][row] = 255;
    b2[col][row] = 255;
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
  string bmpName;
  int x,y,threshold,filter;
  char char1;
  cout<<"Welcome to Edge-detection System!"<<endl;
  cout<<"Please input the file name (.BMP): ";
  cin>>bmpName;
  cout<<"Width: ";
  cin>>x;
  cout<<"Height: ";
  cin>>y;
  cout<<"Detection threshold (0~1530 recommended): ";
  cin>>threshold;
  cout<<"Apply Gaussian filter? (Y/N)"<<endl;
  cin>>char1;
  if(char1=='Y'||char1=='y')filter=1;
  else filter=0;
  generate(bmpName,x,y,threshold,filter);
  return 0;
}