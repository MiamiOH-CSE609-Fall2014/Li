#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "scoreSequence.h"
#include "findHighScore.h"
using namespace std;

tuple<int,int,string> findHighScore(string haystack,vector<string> needle,vector< vector<int> > scoring_m)
{
  tuple<int,int,string> high_scorer;
  pair<int,int> score;
  for(int i=0;i<needle.size();i++)
    {
    score=scoreSequence(haystack,needle[i],scoring_m);
    if(score.second > get<1>(high_scorer))
      {
	get<0>(high_scorer)=score.first;
	get<1>(high_scorer)=score.second;
	get<2>(high_scorer)=needle[i];
      }
    }
  return high_scorer;
}
