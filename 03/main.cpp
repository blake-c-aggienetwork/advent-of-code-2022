// libs
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <queue>

// file imports
#include "utils.cpp"

using namespace std;

// hard coding this because not familiar with ascii values 
// in cpp
int getPriority(char item){
  if( islower(item )){
    return int(item)-int('a')+1;
  }else{
    return int(item)-int('A')+27;
  }
}

void part1(){
  ifstream indata;
  indata.open("input.txt");

  string line = "";
  int totalValue = 0;

  while(getline(indata,line)){
    // cout << line.substr(0,line.size()/2) << " | ";
    // cout << line.substr(line.size()/2, line.size()/2) << endl;
    
    // charFreqMap of compartment 1
    map<char,int> compartment1; 
    for(char item : line.substr(0,line.size()/2) ){
      compartment1[item] != NULL ? compartment1[item]++ : compartment1[item] = 1;
    }
    
    // iterate through chars of compartment 2
    for(char item: line.substr(line.size()/2,line.size()/2)){
      if(compartment1[item] > 0 ){
        printf("found %c with value: %i\n", item, getPriority(item));
        totalValue += getPriority(item);
        break;
      }
    }

  }
  printf("total value: %i\n", totalValue);
}

void Part2(){
  ifstream indata;
  indata.open("input.txt");

  string line = "";
  int totalValue = 0;

  while(getline(indata,line)){
    string firstBag = line;
    getline(indata,line);
    string secondBag = line;
    getline(indata,line);
    string thirdBag = line;
    
    map<char,int> compartment1; 
    for(char item : firstBag){
      compartment1[item] != NULL ? compartment1[item]++ : compartment1[item] = 1;
    }

    map<char,int> compartment2; 
    for(char item : secondBag){
      compartment2[item] != NULL ? compartment2[item]++ : compartment2[item] = 1;
    }

    for(char item: thirdBag){
      if(compartment1[item] > 0 && compartment2[item] > 0 ){
        printf("found %c with value: %i\n", item, getPriority(item));
        totalValue += getPriority(item);
        break;
      }
    }
  }
  printf("total value: %i\n", totalValue);

}

int main(){
  // part1();
  Part2();

  return 0;
}
