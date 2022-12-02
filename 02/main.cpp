// libs
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <array>
#include <queue>

// file imports
#include "utils.cpp"

using namespace std;

int calculatePoints(string opponent, string you){
  if(opponent == "A"){ // rock
    if(you == "X"){ // Rock
      return 3+1;
    }else if(you == "Y"){ // paper
      return 6+2;
    }else if(you == "Z"){ // scissors
      return 0+3;
    }
  }else if(opponent == "B"){ // Paper
    if(you == "X"){ // Rock
      return 0+1;
    }else if(you == "Y"){ // paper
      return 3+2;
    }else if(you == "Z"){ // scissors
      return 6+3;
    }
  }else if(opponent == "C"){ // scissors
    if(you == "X"){ // Rock
      return 6+1;
    }else if(you == "Y"){ // paper
      return 0+2;
    }else if(you == "Z"){ // scissors
      return 3+3;
    }
  }
  return 0;
}


int calculatePointsWithOutcome(string opponent, string outcome){
  if(opponent == "A"){ // ROCK
    if(outcome == "X"){ // lose
      return 0+3;
    }else if(outcome == "Y"){ // draw
      return 3+1;
    }else if(outcome == "Z"){ // win
      return 6+2;
    }
  }else if(opponent == "B"){ // PAPER
    if(outcome == "X"){ // lose
      return 0+1;
    }else if(outcome == "Y"){ // draw
      return 3+2;
    }else if(outcome == "Z"){ // win
      return 6+3;
    }
  }else if(opponent == "C"){ // SCISSORS
    if(outcome == "X"){ // lose
      return 0+2;
    }else if(outcome == "Y"){ // draw
      return 3+3;
    }else if(outcome == "Z"){ // win
      return 6+1;
    }
  }
  return 0;
}

int main(){
  
  ifstream indata;
  indata.open("input.txt");

  string line = "";
  int totalPoints = 0;

  while(getline(indata,line)){
    string opponent = line.substr(0,1);
    string you = line.substr(2,1);
    // cout << opponent << you << endl;
    // break;
    totalPoints += calculatePointsWithOutcome(opponent, you);
  }

  cout << totalPoints << endl;
  return 0;
}
