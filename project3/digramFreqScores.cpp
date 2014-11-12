#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <stdlib.h>
#include <cstdlib>
#include "digramFreqScores.h"
using namespace std;

map<string,int> digramFreqScores(string str)
{
  map<string,int> freqMap=
    {
      {"AA",0},{"AC",0},{"GT",0},{"AG",0},{"CC",0},{"CA",0},{"CG",0},{"TT",0},
      {"GG",0},{"GC",0},{"AT",0},{"GA",0},{"TG",0},{"TA",0},{"TC",0},{"CT",0}
    };
  for(int i=0;i<str.size()-1;i++)
    {
      freqMap[str.substr(i,2)]+=1;
    }
  return freqMap;
}
