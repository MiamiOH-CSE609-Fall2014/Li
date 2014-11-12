#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "digramFreqMatrix.h"

using namespace std;

vector< vector<int> > digramFreqMatrix(map<string, int> freqMap)
{
  vector< vector<int> > freqMatrix;
  vector<int> AVector;
  vector<int> GVector;
  vector<int> CVector;
  vector<int> TVector;
  AVector.push_back(freqMap["AA"]);
  AVector.push_back(freqMap["AG"]);
  AVector.push_back(freqMap["AC"]);
  AVector.push_back(freqMap["AT"]);
  freqMatrix.push_back(AVector);
  GVector.push_back(freqMap["GA"]);
  GVector.push_back(freqMap["GG"]);
  GVector.push_back(freqMap["GC"]);
  GVector.push_back(freqMap["GT"]);
  freqMatrix.push_back(GVector);
  CVector.push_back(freqMap["CA"]);
  CVector.push_back(freqMap["CG"]);
  CVector.push_back(freqMap["CC"]);
  CVector.push_back(freqMap["CT"]);
  freqMatrix.push_back(CVector);
  TVector.push_back(freqMap["TA"]);
  TVector.push_back(freqMap["TG"]);
  TVector.push_back(freqMap["TC"]);
  TVector.push_back(freqMap["TT"]);
  freqMatrix.push_back(TVector);
  return freqMatrix;
}
