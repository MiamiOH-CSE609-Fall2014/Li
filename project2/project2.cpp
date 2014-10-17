#include <iostream>
#include <iomanip>
#include <string.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdexcept>
using namespace std;

int main()
{
  int peopleNum=0;
  vector<string> names;
  vector<double> points;
  vector<char> grades;
  string name="init";
  double point=0;
  char grade;
  double pointSum=0;
  double pointMean=0;
  double variance=0;
  while(name!="none"&&!name.empty())
    {
      try
	{
	  cout<<"Student No. "<<(peopleNum+1)<<":"<<endl;
	  cout<<"Name: ";
	  getline(cin,name);
	  if(name!="none"&&!name.empty())
	    {
	    cout<<"Point: (0 to 100)";
	    cin>>point;
	    if(cin.fail())
	      {
		cin.clear();
		cin.ignore();
		throw out_of_range("Invalid input");
	      }
	    cin.ignore();
	    if(point<0||point>100)
	      throw out_of_range("Points range error");
	  names.push_back(name);
	  points.push_back(point);
	  peopleNum++;
	    }
	}
      catch(out_of_range)
	{
	  cout<<"Please re-enter:"<<endl;
	}
    }

  for(int i=0;i<peopleNum;i++)
    {
      pointSum+=points.at(i);
    }
  pointMean=pointSum/peopleNum;
  for(int i=0;i<peopleNum;i++)
    {
      variance+=pow(points.at(i)-pointMean,2);
    }
  variance=sqrt(variance);
  cout<<"Grade scale"<<endl;
  cout<<"A  Above "<<showpoint<<min(100.00,pointMean+1.5*variance)<<"%"<<endl;
  cout<<"B  "<<showpoint<<min(100.00,pointMean+0.5*variance)<<"% - "<<min(100.00,pointMean+1.5*variance)<<"%"<<endl;
  cout<<"C  "<<showpoint<<max(0.00,pointMean-0.5*variance)<<"% - "<<min(100.00,pointMean+0.5*variance)<<"%"<<endl;
  cout<<"D  "<<showpoint<<max(0.00,pointMean-1.5*variance)<<"% - "<<max(0.00,pointMean-0.5*variance)<<"%"<<endl;
  cout<<"F  Below "<<showpoint<<max(0.00,pointMean-1.5*variance)<<"%"<<endl;
  cout<<endl<<"Name                Score     Grade"<<endl;
  for(int i=0;i<peopleNum;i++)
    {
      cout<<noshowpoint<<right<<setw(2)<<(i+1)<<". "<<left<<setw(16)<<names.at(i)<<setw(10)<<showpoint<<points.at(i);
      if(points.at(i)<max(0.00,pointMean-1.5*variance))
	grades.push_back('F');
      else if(points.at(i)<max(0.00,pointMean-0.5*variance))
	grades.push_back('D');
      else if(points.at(i)<min(100.00,pointMean+0.5*variance))
        grades.push_back('C');
      else if(points.at(i)<min(100.00,pointMean+1.5*variance))
        grades.push_back('B');
      else
	grades.push_back('A');
      cout<<grades.at(i)<<endl;
    }
  cout<<endl<<"Class average = "<<pointMean<<endl;
  cout<<"Standard Deviation = "<<variance<<endl;
}
