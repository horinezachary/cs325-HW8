#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

struct Bin{
  int capacity;
  int availableCapacity;
  Vector<Item> items;
  Bin(int cap){capacity = cap; availableCapacity = capacity;}
};
struct Item{
  int weight;
};

int main(){

  string filename = "bin.txt";
  ifstream inFile;  //set up the file reader and attempt to read the file
  inFile.open(filename);
  if (!inFile) {  //make sure the file exists
    cout << "Unable to open " << filename << endl;
    exit(1);   // EXIT PROGRAM
  }

  int numCases;
  int caseCount = 1;
  int currentCaseBinCapacity;
  int currentCaseNumItems;

  string line;
  int linecount = -1;
  string fileout = "";
  while(getline(inFile,line)){ //gets one line
    linecount++;
    stringstream lineStream(line);
    string cell;
    vector<string> parsedRow;
    while(getline(lineStream,cell,' ')){  //parses line and puts numbers into string vector
      parsedRow.push_back(cell);
    }
    if (linecount == 0){  //number of cases
      numCases = stoi(parsedRow.at(0));
    }
    else if (linecount%3 == 1){ //capacity of bins
      currentCaseBinCapacity = stoi(parsedRow.at(0));
    }
    else if (linecount%3 == 2){ //number of items
      currentCaseNumItems = stoi(parsedRow.at(0));
    }
    else if (linecount%3 == 0){ //list of items
      Vector<Items> caseItems;
      for (int i = 0; i < currentCaseNumItems; i++){
        Item temp = new Item;
        temp.weight = stoi(parsedRow.at(i));
        caseItems.push_back(temp);
      }
      binPack(currentCaseBinCapacity, caseItems);
    }
  }
}
