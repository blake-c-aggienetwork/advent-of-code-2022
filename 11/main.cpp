// libs
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
// file imports
#include "utils.cpp"

using namespace std;

struct monkey{
  vector<int> items;
  string operation;
  int operationNum;
  int test;
  int inspectionCnt = 0;

  int trueMonkey;
  int falseMonkey;

  monkey(vector<int> items, string operation, int operationNum, int test, int trueMonkey, int falseMonkey){
    this->items = items;
    this-> operation = operation;
    this-> operationNum = operationNum;
    this-> test = test;
    this-> trueMonkey = trueMonkey;
    this-> falseMonkey = falseMonkey;
    this->inspectionCnt = 0;
  }

  void printMonkeyInfo(){
    printf("Items: \n");
    for(int &item :items){
      cout << "\t" << item;
    }
    cout << "\n" << endl;
  }

};

struct big_monkey{
  vector<long long int> items;
  string operation;
  int operationNum;
  int test;
  long long int inspectionCnt = 0;

  int trueMonkey;
  int falseMonkey;

  big_monkey(vector<long long int> items, string operation, int operationNum, int test, int trueMonkey, int falseMonkey){
    this->items = items;
    this-> operation = operation;
    this-> operationNum = operationNum;
    this-> test = test;
    this-> trueMonkey = trueMonkey;
    this-> falseMonkey = falseMonkey;
    this->inspectionCnt = 0;
  }

  void printMonkeyInfo(){
    printf("Items: \n");
    for(auto &item :items){
      cout << "\t" << item;
    }
    cout << "\n" << endl;
  }

};

void doRound(vector<monkey> &monkeys){
    // iterate through each monkey
    for(monkey &curMonkey : monkeys){
      // go through  each item in each monkey
      for(auto &item : curMonkey.items){
        curMonkey.inspectionCnt++;
        if(curMonkey.operation == "add"){
          item += curMonkey.operationNum;
        }else if(curMonkey.operation == "multiply"){
          item *= curMonkey.operationNum;
        }else if(curMonkey.operation == "power"){
          item *= item;
        }else{
          cout << "error" << endl;
        }

        item = (int)floor(item/3);

      }

      // iterate through each item and throw them
      for(auto item : curMonkey.items){
        if(item % curMonkey.test == 0){
          monkeys[curMonkey.trueMonkey].items.push_back(item);
        }else{
          monkeys[curMonkey.falseMonkey].items.push_back(item);
        }
      }
      // remove all items from current monkey, since they have been thrown
      curMonkey.items.clear();
    }
    
}

void doRound2(vector<big_monkey> &monkeys){
    long long int lcm = 1;
    for(auto monkey : monkeys){
      lcm *= monkey.test;
    }
    // iterate through each monkey
    for(big_monkey &curMonkey : monkeys){
      // go through  each item in each monkey
      for(auto &item : curMonkey.items){
        curMonkey.inspectionCnt++;
        if(curMonkey.operation == "add"){
          item += curMonkey.operationNum;
        }else if(curMonkey.operation == "multiply"){
          item *= curMonkey.operationNum;
        }else if(curMonkey.operation == "power"){
          item *= item;
        }else{
          cout << "error" << endl;
        }
        // item = (long long int)floor(item/3);
        item = (long long int)floor(item % lcm );
      }

      // iterate through each item and throw them
      for(auto item : curMonkey.items){
        if(item % curMonkey.test == 0){
          monkeys[curMonkey.trueMonkey].items.push_back(item);
        }else{
          monkeys[curMonkey.falseMonkey].items.push_back(item);
        }
      }
      // remove all items from current monkey, since they have been thrown
      curMonkey.items.clear();
    }
}

void part1(){

  vector<monkey> monkeys;
  monkey monkey0 = monkey({77,69,76,77,50,58},"multiply",11,5,1,5);
  monkey monkey1 = monkey({75,70,82,83,96,64,62},"add",8,17,5,6);
  monkey monkey2 = monkey({53},"multiply",3,2,0,7);
  monkey monkey3 = monkey({85,64,93,64,99},"add",4,7,7,2);
  monkey monkey4 = monkey({61,92,71},"power",0,3,2,3);
  monkey monkey5 = monkey({79,73,50,90},"add",2,11,4,6);
  monkey monkey6 = monkey({50,89},"add",3,13,4,3);
  monkey monkey7 = monkey({83,56,64,58,93,91,56,65},"add",5,19,1,0);
  monkeys.push_back(monkey0);
  monkeys.push_back(monkey1);
  monkeys.push_back(monkey2);
  monkeys.push_back(monkey3);
  monkeys.push_back(monkey4);
  monkeys.push_back(monkey5);
  monkeys.push_back(monkey6);
  monkeys.push_back(monkey7);

  for(int i=0;i<20;i++){
    doRound(monkeys);
  }
  
  int max1 = -1;
  int max2 = -1;
  for(monkey curMonkey : monkeys){
    cout << curMonkey.inspectionCnt << endl;
    if(curMonkey.inspectionCnt > max1){
      max2 = max1;
      max1 = curMonkey.inspectionCnt;
    }
  }

  printf("Silver: %i\n", max1*max2);

}

void part2(){
  vector<big_monkey> monkeys;
  big_monkey monkey0 = big_monkey({77,69,76,77,50,58},"multiply",11,5,1,5);
  big_monkey monkey1 = big_monkey({75,70,82,83,96,64,62},"add",8,17,5,6);
  big_monkey monkey2 = big_monkey({53},"multiply",3,2,0,7);
  big_monkey monkey3 = big_monkey({85,64,93,64,99},"add",4,7,7,2);
  big_monkey monkey4 = big_monkey({61,92,71},"power",0,3,2,3);
  big_monkey monkey5 = big_monkey({79,73,50,90},"add",2,11,4,6);
  big_monkey monkey6 = big_monkey({50,89},"add",3,13,4,3);
  big_monkey monkey7 = big_monkey({83,56,64,58,93,91,56,65},"add",5,19,1,0);
  monkeys.push_back(monkey0);
  monkeys.push_back(monkey1);
  monkeys.push_back(monkey2);
  monkeys.push_back(monkey3);
  monkeys.push_back(monkey4);
  monkeys.push_back(monkey5);
  monkeys.push_back(monkey6);
  monkeys.push_back(monkey7);

  // big_monkey monkey0 = big_monkey({79,98},"multiply",19,23,2,3);
  // big_monkey monkey1 = big_monkey({54,65,75,74},"add",6,19,2,0);
  // big_monkey monkey2 = big_monkey({79,60,97},"power",0,13,1,3);
  // big_monkey monkey3 = big_monkey({74},"add",3,17,0,1);
  // monkeys.push_back(monkey0);
  // monkeys.push_back(monkey1);
  // monkeys.push_back(monkey2);
  // monkeys.push_back(monkey3);

  for(int i=0;i<10000;i++){
    doRound2(monkeys);
  }
  
  long long int max1 = 0;
  long long int max2 = 0;
  for(big_monkey curMonkey : monkeys){
    cout << curMonkey.inspectionCnt << endl;
    if(curMonkey.inspectionCnt > max1){
      max2 = max1;
      max1 = curMonkey.inspectionCnt;
    }
    if(curMonkey.inspectionCnt > max2 && curMonkey.inspectionCnt != max1){
      max2 = curMonkey.inspectionCnt;
    }
  }
  cout << endl;
  cout << max1 << " " << max2 << endl;

  printf("Gold: %lli\n", max1*max2);

}


int main(){
  // monkey monkey0 = monkey({79,98},"multiply",19,23,2,3);
  // monkey monkey1 = monkey({54,65,75,74},"add",6,19,2,0);
  // monkey monkey2 = monkey({79,60,97},"power",0,13,1,3);
  // monkey monkey3 = monkey({74},"add",3,17,0,1);
  // monkeys.push_back(monkey0);
  // monkeys.push_back(monkey1);
  // monkeys.push_back(monkey2);
  // monkeys.push_back(monkey3);

  // part1();
  part2();
  
  
  return 0;
}
