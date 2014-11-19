#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <list>
#include <iterator>
#include <cstdlib>
#include <stdlib.h>
#include "parseFastaFile.h"
#include "digramFreqScores.h"
#include "digramFreqMatrix.h"
#include"parseScoringFile.h"
#include"scoreSequence.h"
#include"findHighScore.h"
using namespace std;

int main(int argc, char** argv)
{
  string name1=argv[1];
  string name2=argv[2];
  tuple<string,vector<string>,string> DNA= parseFastaFile(name1); 
  cout<<get<0>(DNA)<<endl;
  for (int i=0; i<get<1>(DNA).size();i++)
    {
      cout<<get<1>(DNA)[i]<<endl;
    }
  cout<<get<2>(DNA)<<endl;
  string DNAString=get<2>(DNA);
  map<string,int> freqMap=digramFreqScores(DNAString);
  vector< vector<int> > freqMatrix = digramFreqMatrix(freqMap);  
  cout<<"       A    G    C    T"<<endl;
  for(int i=1,j=0;j<4;i++,j++)
    {
      switch(i)
	{
	case 1:cout<<"  A  ";break;
	case 2:cout<<"  G  ";break;
	case 3:cout<<"  C  ";break;
	case 4:cout<<"  T  ";break;
	}
      for(int k=0;k<4;k++)
	{
	  //cout<<" "<<freqMatrix[j][k]<<" ";
	  printf("%5d",freqMatrix[j][k]);
	}
      cout<<endl;
    }

  //============//

  cout<<"Please input the sequence number:";
  int sequenceNum;
  cin>>sequenceNum;
  vector<string> sequence;
  for(int i=0;i<sequenceNum;i++)
    {
      string str1="";
      cout<<"Please input the sequence No. "<<(i+1)<<":";
      cin>>str1;
      sequence.push_back(str1);
    }
  
  vector< vector<int> > score_Matrix;
  score_Matrix=parseScoringFile(name2);
  cout<<"       A    G    C    T"<<endl;
  for(int i=1,j=0;j<4;i++,j++)
    {
      switch(i)
        {
        case 1:cout<<"  A  ";break;
        case 2:cout<<"  G  ";break;
        case 3:cout<<"  C  ";break;
        case 4:cout<<"  T  ";break;
        }
      for(int k=0;k<4;k++)
        {
          //cout<<" "<<freqMatrix[j][k]<<" ";
          printf("%5d",score_Matrix[j][k]);
        }
      cout<<endl;
    }
  
  tuple<int,int,string> highscore;
  highscore=findHighScore(get<2>(DNA),sequence,score_Matrix);
  cout<<"The Max Sequence is "<<get<2>(highscore)<<endl;
  cout<<"The Max Score is "<<get<1>(highscore)<<endl;
  cout<<"The position is "<<get<0>(highscore)<<endl;
  
  return 0;
}
