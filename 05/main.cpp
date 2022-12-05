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

void moveCrates(int amount, int from, int to, vector<vector<char>> &stacks){
  from -= 1;
  to -= 1;

  vector<char> cratesToMove = {};
  
  for(int i=0;i<amount && stacks[from].size() != 0;i++){
    auto crate = stacks[from].back();
    cratesToMove.push_back(crate);
    // printf("moving %c\n",crate);
    stacks[from].pop_back();
  }

  for(auto crate : cratesToMove){
    stacks[to].push_back(crate);
  }

}

void moveCrates9001(int amount, int from, int to, vector<vector<char>> &stacks){
  from -= 1;
  to -= 1;

  vector<char> cratesToMove = {};
  
  for(int i=0;i<amount && stacks[from].size() != 0;i++){
    auto crate = stacks[from].back();
    cratesToMove.insert(cratesToMove.begin(),crate);
    // printf("moving %c\n",crate);
    stacks[from].pop_back();
  }

  for(auto crate : cratesToMove){
    stacks[to].push_back(crate);
  }

}

int main(){
  ifstream indata;
  indata.open("input.txt");
  string line = "";
  // getline(indata,line);

  // Lol idk how to parse this
  vector<vector<char>> stacks;
  stacks.push_back({'S','M','R','N','W','J','V','T'});
  stacks.push_back({'B','W','D','J','Q','P','C','V'});
  stacks.push_back({'B','J','F','H','D','R','P'});
  stacks.push_back({'F','R','P','B','M','N','D'});
  stacks.push_back({'H','V','R','P','T','B'});
  stacks.push_back({'C','B','P','T'});
  stacks.push_back({'B','J','R','P','L'});
  stacks.push_back({'N','C','S','L','T','Z','B','W'});
  stacks.push_back({'L','S','G'});
  
  while(getline(indata,line)){
    int amount, from, to;
    sscanf(line.c_str(), "move %i from %i to %i", &amount, &from, &to);
    moveCrates9001(amount,from,to,stacks);
  }
  
  for(auto item : stacks){
    printf("%c", item.back());
  }
  cout << endl;


}
