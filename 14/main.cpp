// includes
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
 
void drawRocks(int row, int col, pair<int,int> prevRock, vector<vector<char>> &caveMap){
  // printf("drawing: %i %i to %i %i\n", prevRock.first, prevRock.second, row, col);
  if(prevRock == pair<int,int>({-1,-1})){
    return;
  }
  
  if(row == prevRock.first){ // rows are equal, iterate across columns
    if(prevRock.second <= col){
      for(int j=prevRock.second;j<=col;j++){
        caveMap[row][j] = '#';
      }
    }else{
      for(int j=col;j<=prevRock.second;j++){
        caveMap[row][j] = '#';
      }
    }
  }else{ // cols are equal, iterate down rows
    if(prevRock.first <= row){
      for(int i=prevRock.first;i<=row;i++){
        caveMap[i][col] = '#';
      }
    }else{
      for(int i=row;i<=prevRock.first;i++){
        caveMap[i][col] = '#';
      }
    }
  }
}

int parsePath(string line, vector<vector<char>> &caveMap){
  string delimiter = " -> ";
  
  int maxRow = 0;
  size_t pos;
  string token;
  pair<int,int> prevRock = {-1,-1};

  while((pos = line.find(delimiter)) != string::npos ){
    token = line.substr(0,pos);

    int row = stoi(token.substr( token.find(',')+1, token.size()-token.find(',')-1));
    int col = stoi(token.substr(0,token.find(',')));
    maxRow = max(row,maxRow);

    drawRocks(row, col, prevRock,caveMap);

    prevRock = {row, col};
    line.erase(0,pos+delimiter.length());
  }

  // process last token
  int row = stoi(line.substr( line.find(',')+1, line.size()-line.find(',')-1));
  int col = stoi(line.substr(0,line.find(',')));
  maxRow = max(row,maxRow);
  drawRocks(row,col,prevRock,caveMap);

  return maxRow;
}

bool simulateSand(int row, int col, vector<vector<char>> &caveMap){

  // Case 0: we are about to fall through the bottom
  if(row >= (int)caveMap.size()-1){
    return true;
  }
  // Case 1: empty space below
  if(caveMap[row+1][col] == '.'){
    return simulateSand(row+1,col,caveMap); 
  }
  // Case 2: Down and left is empty
  if(caveMap[row+1][col-1] == '.'){
    return simulateSand(row+1,col-1,caveMap);
  }
  // case 3: down and right is empty
  if(caveMap[row+1][col+1] == '.'){
    return simulateSand(row+1,col+1,caveMap);
  }
  // Case 4: none of those are true, the sand must rest
  caveMap[row][col] = 'O';
  // for(int i=0;i<10;i++){
  //   for(int j=490;j<505;j++){
  //     cout << caveMap[i][j];
  //   }
  //   cout << endl;
  // }
  return false;
}

bool simulateSandWithFloor(int row, int col, vector<vector<char>> &caveMap){
  // Case 1: empty space below
  if(caveMap[row+1][col] == '.'){
    return simulateSand(row+1,col,caveMap); 
  }
  // Case 2: Down and left is empty
  if(caveMap[row+1][col-1] == '.'){
    return simulateSand(row+1,col-1,caveMap);
  }
  // case 3: down and right is empty
  if(caveMap[row+1][col+1] == '.'){
    return simulateSand(row+1,col+1,caveMap);
  }
  // Case 4: none of those are true, the sand must rest
  caveMap[row][col] = 'O';

  if(row == 0 && col == 500){
    return true;
  }

  return false;
}

int main(){
  fstream f("input.txt",ios::in);
  string line;

  vector<vector<char>> caveMap(200,vector<char>(1000,'.'));

  int highestScan = 0;
  while(getline(f,line)){
    highestScan = max(parsePath(line, caveMap),highestScan);
  }
  vector<vector<char>> caveMap2(caveMap);

  int silver = 0;
  while(simulateSand(0,500,caveMap) == false){
    silver++;
  }
  printf("Silver: %i\n", silver);

  for(size_t j=0;j<caveMap2[0].size();j++){
    caveMap2[highestScan+2][j] = '#';
  }

  int gold = 0;
  while(simulateSandWithFloor(0,500,caveMap2) == false){
    gold++;
  }
  printf("Gold: %i\n",gold+1);
  

  f.close();
  return 0;
}