// libs
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <map>

// file imports
#include "utils.cpp"

using namespace std;

int findMessageStart(int markerLength){
  ifstream f("input.txt");
  string line = "";
  getline(f,line);

  map<char,bool> seenMap;

  int left = 0, right = 0;
  while(right-left < markerLength){
    if(seenMap[line[right]] == false){
      seenMap[line[right]] = true;
    }else{
      // printf("Seen duplicate of %c at %i\n",line[right], right);
      while(line[left] != line[right]){
        seenMap.erase(line[left]);
        left++;
      }
      left++;
    }
    right++;
  }
  return right;
}


int main(){
  printf("silver: %i\n", findMessageStart(4));
  printf("gold %i\n", findMessageStart(14));

  return 0;
}
