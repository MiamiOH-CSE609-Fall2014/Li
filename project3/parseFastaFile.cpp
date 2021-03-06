#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cstdlib>
using namespace std;

tuple<string,vector<string>,string> parseFastaFile(string fName)
{
  string header;
  vector<string>comments;
  string sequence;
  fstream input;
  input.open(fName, fstream::in);
  char buf[300];
  while(input.getline(buf,300))
    {
      if(buf[0]=='>')
      {
	header=buf;
      }
      else if(buf[0]==';')
      {
	comments.push_back(buf);
      }
      else
      {
	sequence=sequence+buf;
      }
    }
  tuple<string,vector<string>,string> DNAdata {header,comments,sequence};
  return DNAdata;
}
