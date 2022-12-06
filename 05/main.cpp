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

  getline(indata,line);
  vector<vector<char>> stacks((line.size()+1)/4);
  indata.clear();
  indata.seekg(0);

  for(string line=""; getline(indata,line) && !line.empty(); ){
    unsigned long i = 1;
    while(i < line.size()){
      if(line[i] == '1'){
        break;
      }
      if(line[i] != ' '){
        stacks[(i-1)/4].push_back(line[i]);
      }
      i += 4;
    }
  }

  for(vector<char> &stack : stacks){
    reverse(stack.begin(), stack.end());
  }

  vector<vector<char>> stacks2(stacks);

  while(getline(indata,line)){
    int amount, from, to;
    sscanf(line.c_str(), "move %i from %i to %i", &amount, &from, &to);
    moveCrates(amount,from,to,stacks);
    moveCrates9001(amount,from,to,stacks2);
  }

  cout << "Silver: " << endl;
  for(auto item: stacks){
    cout << item.back();
  }
  cout << endl;

  cout << "Gold: " << endl;
  for(auto item: stacks2){
    cout << item.back();
  }
  cout << endl;

  return 0;
}
