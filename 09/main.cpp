// libs
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>
#include <vector>

// file imports
#include "utils.cpp"

using namespace std;

class position{
  public:
  position(): x(0), y(0){};
  int x;
  int y;

  string getPosKey(){
    string output = "x:";
    output.append(to_string(x));
    output.append(" y:");
    output.append(to_string(y));
    output.append("\n");
    return output;
  }

  void move(int x, int y){
    this->x += x;
    this->y += y;
    return;
  }

  void setPos(int x, int y){
    this->x = x;
    this->y = y;
    return;
  }

};

void updateTailPosition(position &head, position &tail){
  if(abs(head.x - tail.x) > 1 || abs(head.y-tail.y) > 1){
    if(abs(head.x-tail.x) > 0){
      tail.x += head.x > tail.x ? 1 : -1;
    }
    if(abs(head.y-tail.y) > 0){
      tail.y += head.y > tail.y ? 1 : -1;
    }
  }
  return;
}

void simulation(position &head, position &tail,char direction,int magnitude,set<string> &tailPositions){
  if(magnitude == 0){
    return;
  }
  switch (direction)
  {
  case 'R':
    head.move(1,0);
    updateTailPosition(head,tail);
    break;
  case 'L':
    head.move(-1,0);
    updateTailPosition(head,tail);
    break;
  case 'U':
    head.move(0,1);
    updateTailPosition(head,tail);
    break;
  case 'D':
    head.move(0,-1);
    updateTailPosition(head,tail);
    break;
  default:
    break;
  }
  tailPositions.insert(tail.getPosKey());
  simulation(head,tail,direction,magnitude-1,tailPositions);
}

void simulateRope(position &head, vector<position> &knots, char direction, int magnitude, set<string> &lastKnotPositions){
  if(magnitude == 0){
    return;
  }

  switch (direction)
  {
  case 'R':
    head.move(1,0);
    break;
  case 'L':
    head.move(-1,0);
    break;
  case 'U':
    head.move(0,1);
    break;
  case 'D':
    head.move(0,-1);
    break;
  default:
    break;
  }
  updateTailPosition(head,knots[0]);
  for(int i=1;i<(int)knots.size();i++){
    updateTailPosition(knots[i-1],knots[i]);
  }

  lastKnotPositions.insert(knots[8].getPosKey());
  simulateRope(head,knots,direction,magnitude-1, lastKnotPositions);
}

int main(){
  fstream f("input.txt",ios::in);
  string line;

  set<string> tailPositions;
  set<string> lastKnotPositions;
  position head;
  position tail;
  vector<position> knots(9);

  tailPositions.insert(tail.getPosKey());
  
  while(getline(f,line)){
    char direction = ' ';
    int magnitude;
    sscanf(line.c_str(), "%c %i", &direction, &magnitude);

    // simulation(head,tail, direction, magnitude, tailPositions); // Silver
    simulateRope(head,knots,direction,magnitude, lastKnotPositions);
  }

  // printf("silver: %i\n",(int)tailPositions.size());
  printf("gold: %i\n",(int)lastKnotPositions.size());

  return 0;
}
