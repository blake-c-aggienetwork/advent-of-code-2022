// includes

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <string>

using namespace std;

string getAbsolutePath(vector<string> curPath){
  string absolute = "";
  for(auto path : curPath){
    absolute.append(path);
  }
  return absolute;
}

struct Dir{
  set<string> subDirs;
  map<string,long long> files;
  long long totalSize;

  // constructor 
  Dir():totalSize(-1){};

  void addFile(string fn, long long fs){
    files[fn] = fs;
  }

  void addSubDir(string dn){
    subDirs.insert(dn);
  }

  void printInfo(map<string,Dir> &dirMap){
    cout << "\tSubDirs:\n";
    for(auto &dir : subDirs){
      printf("\t\t%s : %lli\n",dir.c_str(), dirMap[dir].getSize(dirMap));
    }
    cout << "\tFiles:\n";
    for(auto &file : files){
      printf("\t\t%s: %lli\n",file.first.c_str(),file.second);
    }
    printf("\tTotal Size: %lli\n",totalSize);
  }

  long long getSize(map<string, Dir> &dirMap){
    if(totalSize != -1){ return totalSize; }
    else{
      totalSize = 0;
      for(auto &subDir : subDirs){
        totalSize += dirMap[subDir].getSize(dirMap);
      }
      for(auto &file : files){ // Add all files in cur dir to dir size
        totalSize += file.second;
      }
      return totalSize;
    }
  }

};
typedef struct Dir Dir_t;

int main(){
  map<string, Dir_t> dirMap;

  ifstream f("input.txt", ios::in);
  string line;

  vector<string> curPath;

  while(getline(f,line)){
    if(line.substr(0,4) == "$ cd"){ // Change dir
      string dir = line.substr(5,line.size()-5);
      if(dir == ".."){
        curPath.pop_back();
      }else{
        curPath.push_back(dir);
      }
    }
    else if(line.substr(0,4) == "$ ls"){ // ls case
      // dirMap[getAbsolutePath(curPath)];
    }
    else if(line.substr(0,4) == "dir "){ // dir case
      string ds = line.substr(4,line.size()-4);
      ds = getAbsolutePath(curPath).append(ds);
      // printf("Found dir %s in %s\n",ds.c_str(),curPath.back().c_str());
      dirMap[getAbsolutePath(curPath)].addSubDir(ds);
    }
    else{ // file case
      long long fs = stol(line.substr(0,line.find(' ')));
      string fn = line.substr(line.find(' ')+1, line.size()-line.find(' ')+5);
      // printf("Found file %s with size %lli\n",fn.c_str(),fs);
      dirMap[getAbsolutePath(curPath).c_str()].addFile(fn,fs);
    }
  }

  dirMap["/"].getSize(dirMap);

  // for(auto &dir: dirMap){
  //   cout << dir.first << endl;
  //   dir.second.printInfo(dirMap);
  // }

  long long silver = 0;
  
  for(auto &dir : dirMap){
    long long fs = dir.second.getSize(dirMap);
    if(fs <= 100000){
      silver += fs;
    }
  }
  long long gold = dirMap["/"].getSize(dirMap);
  long long unused = 70000000-gold;

  for(auto &dir : dirMap){
    long long fs = dir.second.getSize(dirMap);
    if(fs <= gold && fs+unused >= 30000000){
      gold = fs;
    }

  }


  printf("Total of files < 100000: %lli\n",silver);
  printf("Deleted dir size: %lli\n",gold);

  f.close();
  return 0;
}