#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "scoreSequence.h"
using namespace std;

pair<int,int> scoreSequence(string haystack, string needle, vector< vector<int> > scoring_m)
{
  pair<int,int> max_score={0,0};
  map<char,int> index={ {'A',0},{'G',1},{'C',2},{'T',3} };
  string str1;
  for(int i=1;i<haystack.length();i++)
    {
      int score=0;
      str1=haystack.substr(i,needle.length());
      for(int i=0;i<needle.length();i++)
	{
	  score=score+scoring_m[index[str1[i]]][index[needle[i]]];
	}
      if(score>max_score.second)
	{
	  max_score.first=i;
	  max_score.second=score;
	}
    }
  return max_score;
}
