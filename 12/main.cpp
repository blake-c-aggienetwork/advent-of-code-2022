// includes
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;
  // auto comp = [](tile &a, tile &b){
  //   if(a.letter == 'S'){
  //     return false;
  //   }
  //   if(a.letter == 'E'){
  //     return true;
  //   }
  //   return int(a.letter) > int(b.letter);
  // };
  // priority_queue<tile,vector<tile>,decltype(comp)> pq(comp);

struct tile{
  int row;
  int col;
  char letter;
  int stepsTo;

  tile(int row, int col, int stepsTo, vector<vector<char>> &elevationMap):row(row),col(col),stepsTo(stepsTo){
    this->letter = elevationMap[row][col];
  }

  bool canClimbTo(int row, int col, vector<vector<char>> &elevationMap){
    if(row < 0 || col < 0 || row >= (int)elevationMap.size() || col >= (int)elevationMap[0].size()){
      return false;
    }
    if(elevationMap[row][col] == 'S'){
      return false;
    }
    if(elevationMap[row][col] == 'E'){
      return int(this->letter)+1 >= int('z');
    }
    if(this->letter == 'S'){
      return int('a')+1 >= int(elevationMap[row][col]);
    }

    return int(this->letter)+1 >= int(elevationMap[row][col]);
  }
};

string makeKey(int row, int col){
  return to_string(row).append(",").append(to_string(col));
}

int bfs(int row, int col, vector<vector<char>> &elevationMap){
  queue<tile> q;
  q.push(tile(row,col,0,elevationMap));
  vector<vector<int>> seenMap(elevationMap.size(), vector<int> (elevationMap[0].size(),0));

  while(!q.empty()){

    // process
    tile curTile = q.front();
    // printf("visiting: %c at %i,%i\n",curTile.letter,curTile.row,curTile.col);
    seenMap[row][col] = 2;

    if(curTile.letter == 'E'){
      return curTile.stepsTo;
    }

    q.pop();
    
    // add to queue
    vector<pair<int,int>> offsets = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    for(pair<int,int> &offset : offsets){
      int row = offset.first+curTile.row;
      int col = offset.second+curTile.col;
      if(curTile.canClimbTo(row,col,elevationMap) && seenMap[row][col] == 0){
        int stepsTo = curTile.stepsTo+1;
        q.push(tile(row,col,stepsTo,elevationMap));
        seenMap[row][col] = 1;
      }
      
    }
  }
  return INT_MAX;
}


int main(){
  ifstream f("input.txt",ios::in);
  string line;

  vector<vector<char>> elevationMap(1);

  while(getline(f,line)){
    for(char &curChar : line){
      elevationMap.back().push_back(curChar);
    }
    if(f.eof()){
      break;
    }
    vector<char> newRow;
    elevationMap.push_back(newRow);
  }

  // cout << "starting at " << elevationMap[0][0] << endl;

  printf("Silver: %i\n", bfs(20,0,elevationMap));

  int minSteps = INT_MAX;

  for(int row = 0; row < (int)elevationMap.size();row++){
    for(int col = 0; col < (int)elevationMap[0].size();col++){
      if(elevationMap[row][col] == 'S' || elevationMap[row][col] == 'a' ){
        minSteps = min(bfs(row,col,elevationMap),minSteps);
      }
    }
  }
  printf("Gold: %i\n",minSteps);

  return 0;
}
