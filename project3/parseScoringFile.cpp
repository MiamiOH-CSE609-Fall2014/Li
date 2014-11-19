#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<map>
#include"parseScoringFile.h"
using namespace std;

vector< vector<int> >parseScoringFile(string filePath)
{
  fstream input;
  input.open(filePath,fstream::in);
  vector<int>vector1;
  vector< vector<int> > score_matrix;
  char buff[200];
  while(input.getline(buff,200,','))
    {
      vector1.push_back(stoi(buff));
      input.getline(buff,200,',');
      vector1.push_back(stoi(buff));
      input.getline(buff,200,',');
      vector1.push_back(stoi(buff));
      input.getline(buff,200);
      vector1.push_back(stoi(buff));
      score_matrix.push_back(vector1);
      vector1.clear();
    }
  return score_matrix;
}
