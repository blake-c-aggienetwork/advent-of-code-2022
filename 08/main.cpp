// libs
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

// file imports
#include "utils.cpp"

using namespace std;

string buildKey(int row, int col){
  string tree = "";
  tree.append(to_string(row));
  tree.append(" row,col ");
  tree.append(to_string(col));
  return tree;
}


void seeTrees(int row, int col, vector<vector<int>> &treeGrid, set<string> &seenTrees, int lastHeight, string direction){
  if(row < 0 || col < 0 || row > (int)treeGrid.size()-1 || col > (int)treeGrid[0].size()-1){
    return;
  }
  if(lastHeight < treeGrid[row][col]){
    seenTrees.insert(buildKey(row,col));
  }
  int newHeight = max(lastHeight,treeGrid[row][col]);

  if(direction=="down"){
    seeTrees(row+1,col,treeGrid,seenTrees,newHeight,direction);
  }else if(direction == "up"){
    seeTrees(row-1,col,treeGrid,seenTrees,newHeight,direction);
  }else if (direction == "left"){
    seeTrees(row,col-1,treeGrid,seenTrees,newHeight,direction);
  }else if (direction == "right"){
    seeTrees(row,col+1,treeGrid,seenTrees,newHeight,direction);
  }
  return;
}

int scenic(int row, int col, vector<vector<int>> &treeGrid, int lastHeight, int maxHeight, string direction){
  if(row < 0 || col < 0 || row > (int)treeGrid.size()-1 || col > (int)treeGrid[0].size()-1){
    return 0;
  }

  // cout << "checking " << treeGrid[row][col] << endl;

  if(treeGrid[row][col] >= maxHeight){
    return 1;
  }
  if(lastHeight == treeGrid[row][col]){
    return 0;
  }

  maxHeight = max(maxHeight,treeGrid[row][col]);

  if(direction == "up"){
    return 1+scenic(row-1,col,treeGrid,lastHeight, maxHeight,"up");
  }
  else if(direction == "down"){
    return 1+scenic(row+1,col,treeGrid,lastHeight, maxHeight,"down");
  }
  else if(direction == "left"){
    return 1+scenic(row,col-1,treeGrid,lastHeight, maxHeight,"left");
  }
  else if(direction == "right"){
    return 1+scenic(row,col+1,treeGrid,lastHeight, maxHeight,"right");
  }
  return 0;
}

int calcScenic(int row,int col,vector<vector<int>> &treeGrid){
  int score = 1;
  int height = treeGrid[row][col];
  score *= scenic(row,col-1,treeGrid,height,height,"left");
  score *= scenic(row,col+1,treeGrid,height,height,"right");
  score *= scenic(row+1,col,treeGrid,height,height,"down");
  score *= scenic(row-1,col,treeGrid,height,height,"up");

  // cout << score << endl;
  return score;
}

int main(){
  vector<vector<int>> treeGrid;
  vector<int> treeline;
  treeGrid.push_back(treeline);

  ifstream f("input.txt",ios::in);
  string line;

  int curRow = 0;
  while(getline(f,line)){
    for(unsigned long i=0;i<line.size();i++){
      int tree = (int)line[i]-48;
      treeGrid[curRow].push_back(tree);
    }
    if(f.eof()){
      break;
    }
    vector<int> treeline;
    treeGrid.push_back(treeline);
    curRow++;
  }

  set<string> seenTrees;

  // check top and bottom
  for(unsigned long i=0; i<treeGrid[0].size();i++){
    seeTrees(0,i,treeGrid,seenTrees,-1,"down");
    seeTrees(treeGrid[0].size()-1,i,treeGrid,seenTrees,-1,"up");
  }

  // check left and right
  for(unsigned long i=0; i<treeGrid[0].size();i++){
    seeTrees(i,0,treeGrid,seenTrees,-1,"right");
    seeTrees(i,treeGrid.size()-1,treeGrid,seenTrees,-1,"left");
  }

  int gold = -1;
  for(unsigned long row=0;row<treeGrid.size();row++){
    for(unsigned long col=0;col<treeGrid[0].size();col++){
      gold = max(gold, calcScenic(row,col,treeGrid));
      // printf("%i,%i has: %i\n",row,col,calcScenic(row,col,treeGrid));
    }
  }

  calcScenic(3,3,treeGrid);

  int silver = 0;
  for(auto item : seenTrees){
    silver++;
  }

  printf("silver: %i\n",silver);
  printf("gold: %i\n",gold);

  f.close();
  return 0;
}
