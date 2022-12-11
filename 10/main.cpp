// libs
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// file imports
#include "utils.cpp"

using namespace std;

void renderPixel(int x, int cycle){
  int pixelPos = cycle % 40;

  if(x == pixelPos || (x+1)== pixelPos || (x+2) == pixelPos){
    cout << "#";
  }else{
    cout << ".";
  }
  
  if(cycle % 40 == 0){
    cout << endl;
  }

}

int main(){
  ifstream f("input.txt",ios::in);
  string line;

  vector<int> instructionQueue;
  instructionQueue.push_back(0);

  while(getline(f,line)){
    if(line == "noop"){
      instructionQueue.push_back(0);
      // cout << "noop" << endl;
    }else{
      int toAdd;
      sscanf(line.c_str(),"addx %i",&toAdd);
      instructionQueue.push_back(0);
      instructionQueue.push_back(toAdd);
    }
  }
  
  int x = 1;
  int CYCLE = 0;
  int signalStrengthSum = 0;

  for(auto item : instructionQueue){
    // BEGIN CYCLE
    renderPixel(x, CYCLE);
    CYCLE++;
    // DURING CYCLE
    // FINISH CYCLE
    x += item;
    // printf("CYCLE: %i -- X: %i\n", CYCLE, x);
    if(CYCLE == 20 || (CYCLE-20) % 40 == 0){
      // cout << "Signal Strength: " << x*CYCLE << endl;
      signalStrengthSum += x*CYCLE;
    }
    
  }

  printf("\nSilver: %i\n", signalStrengthSum);


  return 0;
}
