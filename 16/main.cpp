// includes
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <cmath>
#include <queue>

using namespace std;

struct valve{
  string id;
  int flowRate;
  set<string> tunnels;
  set<pair<string,int>> weighted_tunnels;

  valve(string id, int flowRate, set<string> tunnels):id(id),flowRate(flowRate), tunnels(tunnels){};

  valve(){};

  void reduceTunnels(set<string> &requiredValves, map<string,valve> &valves){
    // perform a BFS starting from current valve and see how long to it takes to get to all required tunnels
    queue<pair<string,int>> bfsQueue; // queue<pair<valve id, travel time>>
    bfsQueue.push({this->id, 0});
    set<string> seenValves;

    while(bfsQueue.size() != 0){
      pair<string, int> curV = bfsQueue.front();
      seenValves.insert(curV.first);
      if(curV.first != this->id && requiredValves.count(curV.first) != 0 ){
        weighted_tunnels.insert(curV);
      }

      for(auto tunnel : valves[curV.first].tunnels){
        if(seenValves.count(tunnel) == 0){
          bfsQueue.push({tunnel, curV.second+1});
        }
      }

      bfsQueue.pop();
    }

  }

};


int dfs(string id, set<string> visitedValves, map<string,valve> &valves, int timeLeft){
  if(timeLeft <= 0){
    return 0;
  }

  if(valves[id].id != "AA"){
    timeLeft--;
  }

  visitedValves.insert(id);

  int maxP = valves[id].flowRate*timeLeft;

  for(auto p : valves[id].weighted_tunnels){
    if(visitedValves.count(p.first) == 0){
      maxP = max(maxP,valves[id].flowRate*timeLeft + dfs(p.first,visitedValves,valves,timeLeft-p.second));
    }
  }
  
  return maxP;
}

int dfs2(string id, string elephant, set<string> visitedValves, map<string,valve> &valves, int timeLeft, int timeLeftEle){
  if(timeLeft <= 0 && timeLeftEle <= 0){
    return 0;
  }

  if(valves[id].id != "AA"){
    timeLeft--;
    timeLeftEle--;
  }

  visitedValves.insert(id);
  visitedValves.insert(elephant);
  
  int valveOpening = valves[id].flowRate*timeLeft + valves[elephant].flowRate*timeLeftEle;
  int maxP = valveOpening;

  // combo.append("1 at ").append(id).append(" ").append(to_string(timeLeft)).append(" 2 at ").append(elephant).append(" ").append(to_string(timeLeftEle)).append("\n\t");
  // if(visitedValves.size() >= 5){
  //   cout << combo << endl;
  // }
  

  // if(visitedValves.size() == 6){
  //   return 0;
  // }

  for(auto p : valves[id].weighted_tunnels){
    for(auto p2 : valves[elephant].weighted_tunnels){
      if(visitedValves.count(p.first) == 0 && visitedValves.count(p2.first) == 0 && p.first != p2.first){
        maxP = max(maxP, dfs2(p.first,p2.first,visitedValves,valves,timeLeft-p.second,timeLeftEle-p2.second)+ valveOpening);
      }else if(visitedValves.size() == 15 && visitedValves.count(p.first) == 0){
        maxP = max(maxP, (p.second-1)*valves[p.first].flowRate);
      }
    }
  }

  return maxP;
}

int main(){

  map<string,valve> valves;
  set<string> requiredValves;

  ifstream f("input.txt",ios::in);
  string line;
  while(getline(f,line,';')){
    string id; int flowRate;
    sscanf(line.c_str(),"Valve %s has flow rate=%i\n  ", &id, &flowRate);
    id = line.substr(6,2);
    getline(f,line);

    set<string> tunnels;
    stringstream s(line);
    string word;
    s >> word >> word >> word >> word;
    while(s >> word){
      if(word.size() == 3){
        tunnels.insert(word.substr(0,2));
      }else{
        tunnels.insert(word);
      }
    }
    valves[id] = valve(id,flowRate,tunnels);
    if(flowRate != 0){
      requiredValves.insert(id);
    }
  }
  requiredValves.insert("AA");

  for(auto s : requiredValves){
    valves[s].reduceTunnels(requiredValves, valves);
  }

  // print weighted graph
  // for(string v : requiredValves){
    // cout << "Valve " << v << endl;
    // for(auto s : valves[v].weighted_tunnels){
    //   cout << s.first << " " << s.second << endl;
    // }
  // }

  cout << requiredValves.size() << endl;

  set<string> visitedValves;
  // cout << dfs("AA",visitedValves,valves,30) << endl;
  cout << dfs2("AA", "AA", visitedValves,valves,26,26) << endl;

  return 0;
}