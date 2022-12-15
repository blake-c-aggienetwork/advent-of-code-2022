// includes
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_set>
#include <vector>

using namespace std;

int manhattanDist(int x1,int y1,int x2,int y2){
  return abs(x1-x2)+abs(y1-y2);
}

string keyGen(int x,int y){
  return to_string(x).append(",").append(to_string(y));
}

void genPoints(int sx,int sy,int bx,int by, unordered_set<string> &scannedSet){
  int manDist = manhattanDist(sx,sy,bx,by);
  int rowToSearch = 2000000;

  // will this reach y=10?
  if( sy+manDist >= rowToSearch && sy-manDist <= rowToSearch){
    // cout << "\ttouches y=10\n";
    
    int minOffset = -1*(manDist-abs(sy-rowToSearch));
    // cout << "\t" << minOffset << endl;

    for(int offset=minOffset ; offset <=-1*minOffset ; offset++){
      // cout << "\t\t" << sx+offset << " " << rowToSearch << endl;
      scannedSet.insert(keyGen(sx+offset, rowToSearch));
    }

  }

}

struct sensor{
  int x;
  int y;
  int d;
  sensor(int sx, int sy, int bx, int by):x(sx), y(sy){
    this->d = manhattanDist(sx,sy,bx,by);
  }
};

void part1(){
  ifstream f("input.txt",ios::in);
  string line;
  unordered_set<string> scannedSet;
  while(getline(f,line)){
    cout << line << endl;
    int sx; int sy;
    int bx; int by;
    sscanf(line.c_str(),"Sensor at x=%i, y=%i: closest beacon is at x=%i, y=%i",&sx,&sy,&bx,&by);
    // printf("\tmanhattan dist: %i\n",manhattanDist(sx,sy,bx,by));
    genPoints(sx,sy,bx,by,scannedSet);
    if( scannedSet.count(keyGen(bx,by)) == 1){
      scannedSet.erase(keyGen(bx,by));
    }
  }
  
  // for(auto keys : scannedSet){
  //   cout << keys << endl;
  // }
  printf("Silver: %i\n",(int)scannedSet.size());
  f.close();
}

int searchCeiling = 4000000;

void part2(){
  ifstream f("input.txt",ios::in);
  string line;
  vector<sensor> sensors;

  while(getline(f,line)){
    // cout << line << endl;
    int sx; int sy;
    int bx; int by;
    sscanf(line.c_str(),"Sensor at x=%i, y=%i: closest beacon is at x=%i, y=%i",&sx,&sy,&bx,&by);
    sensors.push_back(sensor(sx,sy,bx,by));
  }

  vector<vector<pair<int,int>>> ranges(searchCeiling); // range[0] -> set of ranges -> xmin, xmax at y = 0

  for(sensor &s : sensors){
    // 
    int yspan = s.d;
    for(int yOffset=-1*yspan; yOffset <= yspan ; yOffset++){
      int xspan = s.d-abs(yOffset);
      
      int xmin = max(s.x-xspan,0);
      int xmax = min(s.x+xspan,searchCeiling);

      // cout << "Becon at " << s.x << ","  << s.y << " covers " << xmin << " to " << xmax << " at " << s.y+yOffset << endl;

      s.y+yOffset >= 0 && s.y+yOffset <= searchCeiling ? ranges[s.y+yOffset].push_back({xmin,xmax}) : void();
    }
  }

  // for(int y=0;y<=(int)ranges.size(); y++){
  //   cout << "Y: " << y << endl;
  //   sort(ranges[y].begin(), ranges[y].end());
  //   for(auto p : ranges[y]){
  //     cout << "\t" << p.first << " " << p.second << endl;
  //   }
  // }

  for( int y=0; y<(int)ranges.size(); y++){
    sort(ranges[y].begin(), ranges[y].end());
    
    int curMax = ranges[y][0].second;
    for(auto p : ranges[y]){
      if(p.first > curMax +1){
        printf("x: %i y: %i\n",curMax+1,y);
        long long gold = ((long long)curMax+1)*4000000+y;
        cout << gold << endl;
        return;
      }else{
        curMax = max(curMax, p.second);
      }
    }
  }

  f.close();
}

int main(){
  part1();
  part2();

  return 0;
}