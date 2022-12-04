// libs
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <set>
#include <fstream>
#include <string>
#include <queue>

// file imports
#include "utils.cpp"

using namespace std;

bool checkForOverlap(array<int,2> range1, array<int,2> range2){
  if(range1[0] <= range2[0] && range1[1] >= range2[1]){
    return true;
  }
  if(range2[0] <= range1[0] && range2[1] >= range1[1]){
    return true;
  }
  return false;
}

void Part1(){
  ifstream indata;
  indata.open("input.txt");

  string line = "";
  int overlapCnt = 0;

  while(getline(indata,line)){
    array<int,2> elf1;
    array<int,2> elf2;
    elf1 = { stoi(line.substr(0,line.find('-'))) ,
              stoi(line.substr(line.find('-')+1, line.find(',')) ) };
    int middle = line.find(',');
    elf2 = { stoi( line.substr(middle+1,line.find('-',middle)) ),
        stoi( line.substr( line.find('-', middle+1)+1,line.size()-line.find('-', middle)) )
     };

    // cout << elf2[0] << " - " << elf2[1] << endl;

    checkForOverlap(elf1,elf2) ? overlapCnt++ : NULL;
  }
  printf("Overlap count: %i\n", overlapCnt);
}

bool checkForOverlapAtAll(array<int,2> range1, array<int,2> range2){
  set<int> range1Set;

  for(int i=range1[0] ; i<= range1[1] ; i++){
    range1Set.insert(i);
  }

  for(int i=range2[0]; i<=range2[1]; i++){
    if(range1Set.find(i) != range1Set.end()){
      return true;
    }
  }

  return false;
}

void Part2(){
  ifstream indata;
  indata.open("input.txt");

  string line = "";
  int overlapCnt = 0;

  while(getline(indata,line)){
    array<int,2> elf1;
    array<int,2> elf2;
    elf1 = { stoi(line.substr(0,line.find('-'))) ,
              stoi(line.substr(line.find('-')+1, line.find(',')) ) };
    int middle = line.find(',');
    elf2 = { stoi( line.substr(middle+1,line.find('-',middle)) ),
        stoi( line.substr( line.find('-', middle+1)+1,line.size()-line.find('-', middle)) )
     };

    // cout << elf2[0] << " - " << elf2[1] << endl;

    checkForOverlapAtAll(elf1,elf2) ? overlapCnt++ : NULL;
  }
  printf("Overlap count: %i\n", overlapCnt);
}

int main(){
  Part1();
  Part2();
}
