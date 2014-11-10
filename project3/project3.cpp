#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "parseFastaFile.h"
using namespace std;

int main(int argc, char** argv)
{
  tuple<string,vector<string>,string> DNA= parseFastaFile(argv[1]); 
  cout<<get<0>(DNA)<<endl;
  for (int i=0; i<get<1>(DNA).size();i++)
    {
      cout<<get<1>(DNA)[i]<<endl;
    }
  cout<<get<2>(DNA)<<endl;
  return 0;
}
