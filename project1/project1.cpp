//CSE609 Porject1 Tuo Li
#include <iostream>
using namespace std;

int main()
{
	int x1,y1,x2,y2,x3,y3;
	cin>>y1;
	cin>>x1;
	cin>>y2;
	cin>>x2;
	if(x1<=0||y1<=0||x2<=0||y2<=0||x1!=y2)
	{
		cout<<"Invalid matrix."<<endl;
		return -1;
	}
	int a[y1][x1];
	int b[y2][x2];
	x3=x2;
	y3=y1;
	int c[y3][x3];
	//cout<<"a:"<<endl;
	for(int i=0;i<y1;i++)
	{
		for(int j=0;j<x1;j++)
		{
			cin>>a[i][j];
		}
	}
	//cout<<"b:"<<endl;
	for(int i=0;i<y2;i++)
	{
		for(int j=0;j<x2;j++)
		{
			cin>>b[i][j];
		}
	}
	//cout<<"c:"<<endl; 
	for(int i=0;i<y3;i++)
	{
		for(int j=0;j<x3;j++)
		{
			c[i][j]=0;
			for(int k=0;k<y2;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	//cout<<"result:"<<endl;
	for(int i=0;i<y1;i++)
	{
		for(int j=0;j<x1;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<y2;i++)
	{
		for(int j=0;j<x2;j++)
		{
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<y3;i++)
	{
		for(int j=0;j<x3;j++)
		{
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
