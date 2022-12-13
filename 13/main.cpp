// includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool compareNext(string l, string r){
  if(l.size() == 0 && r.size() == 0){
    return false;
  }
  // printf("comparing\n\t%s\n\t%s\n",l.c_str(),r.c_str());
  // Different length cases
  if(l[0] == '[' && isdigit(r[0])){ // L is a list, r is num -> build r list -> recurse
    string rList = "[";
    int i=0;
    while(isdigit(r[i])){ // preserve numbers with more than 1 digit
      rList += r[i];
      i++;
    }
    rList += ']'; // close list
    rList += r.substr(i); // Add remaining lists in string
    return compareNext(l,rList); // Compare next
  }
  if(isdigit(l[0]) && r[0] == '['){ // r is a list, l is num -> build l list -> recurse
    string lList = "[";
    int i=0;
    while(isdigit(l[i])){ // preserve nums with multiple digits
      lList += l[i];
      i++;
    }
    lList += ']';
    lList += l.substr(i);
    return compareNext(lList,r);
  }
  // Both are digits
  if(isdigit(l[0]) && isdigit(r[0])){ 
    int lVal = 0; 
    int i = 0;
    while(isdigit(l[i])){ // Convert from chars to number
      lVal *= 10;
      lVal += (l[i] -'0');
      i++;
    }
    int rVal = 0; 
    int j = 0;
    while(isdigit(r[j])){ // Convert from chars to number
      rVal *= 10;
      rVal += (r[j] -'0');
      j++;
    }
    if(lVal == rVal){ // Values are equal
      return compareNext(l.substr(i),r.substr(j)); // compare remaining packets
    }else{
      return lVal < rVal; // Values are not equal, simply compare if l is < r 
    }
  }
  
  if(l[0] == r[0]){ // go to next char to compare, includes periods && brackets
    return compareNext(l.substr(1),r.substr(1));
  }
  if(l[0] == ']'){ // L is shorter than right -> correct order
    return true;
  }
  if(r[0] == ']'){ // R is shorter than L -> wrong order
    return false;
  }
  cout << 'here' << endl;
  return l[0] < r[0]; // L is < R -> correct order
}


class Comparator{
  public:
    bool operator() (string l, string r){
      // printf("comparing\n\t%s\n\t%s\n",l.c_str(),r.c_str());
      // Different length cases
      if(l[0] == '[' && isdigit(r[0])){ // L is a list, r is num -> build r list -> recurse
        string rList = "[";
        int i=0;
        while(isdigit(r[i])){ // preserve numbers with more than 1 digit
          rList += r[i];
          i++;
        }
        rList += ']'; // close list
        rList += r.substr(i); // Add remaining lists in string
        return compareNext(l,rList); // Compare next
      }
      if(isdigit(l[0]) && r[0] == '['){ // r is a list, l is num -> build l list -> recurse
        string lList = "[";
        int i=0;
        while(isdigit(l[i])){ // preserve nums with multiple digits
          lList += l[i];
          i++;
        }
        lList += ']';
        lList += l.substr(i);
        return compareNext(lList,r);
      }
      // Both are digits
      if(isdigit(l[0]) && isdigit(r[0])){ 
        int lVal = 0; 
        int i = 0;
        while(isdigit(l[i])){ // Convert from chars to number
          lVal *= 10;
          lVal += (l[i] -'0');
          i++;
        }
        int rVal = 0; 
        int j = 0;
        while(isdigit(r[j])){ // Convert from chars to number
          rVal *= 10;
          rVal += (r[j] -'0');
          j++;
        }
        if(lVal == rVal){ // Values are equal
          return compareNext(l.substr(i),r.substr(j)); // compare remaining packets
        }else{
          return lVal < rVal; // Values are not equal, simply compare if l is < r 
        }
      }
      
      if(l[0] == r[0]){ // go to next char to compare, includes periods && brackets
        return compareNext(l.substr(1),r.substr(1));
      }
      if(l[0] == ']'){ // L is shorter than right -> correct order
        return true;
      }
      if(r[0] == ']'){ // R is shorter than L -> wrong order
        return false;
      }
      cout << 'here' << endl;
      return l[0] < r[0]; // L is < R -> correct order
        }
} comparator;

int main(){
  ifstream f("input.txt",ios::in);
  string packet2;
  string packet1;
  
  vector<string> packets;

  int sum = 0;
  int curIndex = 1;

  while(getline(f,packet1)){
    getline(f,packet2);
    sum += compareNext(packet1,packet2) ? curIndex : 0;

    // Add packets to vector for pt2
    packets.push_back(packet1);
    packets.push_back(packet2);

    curIndex++;
    getline(f,packet1); // empty line
  }

  printf("silver: %i\n",sum);
  
  // part 2
  packets.push_back("[[2]]");
  packets.push_back("[[6]]");
  sort(packets.begin(),packets.end(),comparator);

  int twoIndex = find(packets.begin(),packets.end(),"[[2]]")-packets.begin()+1;
  int sixIndex = find(packets.begin(),packets.end(),"[[6]]")-packets.begin()+1;

  printf("Gold: %i\n",twoIndex*sixIndex);

  return 0;
}