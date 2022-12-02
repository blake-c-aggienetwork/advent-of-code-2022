// libs
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <queue>

// file imports
#include "utils.cpp"

using namespace std;

int main(){
  
  ifstream indata;
  indata.open("input.txt");

  string line = "";
  vector<int> calories;

  int curCalorieCnt = 0;
  while(getline(indata,line)){
    if(line.empty()){
      calories.push_back(curCalorieCnt);
      curCalorieCnt = 0;
    }else{
      curCalorieCnt += stoi(line);
    }
  }
  calories.push_back(curCalorieCnt);
  
  priority_queue<int> maxHeap;
  for(auto element : calories){
    maxHeap.push(element);
  }
  int total = 0;

  for(int i=0;i<3;i++){
    total += maxHeap.top();
    maxHeap.pop();
  }

  cout << total << endl;

  return 0;
}
