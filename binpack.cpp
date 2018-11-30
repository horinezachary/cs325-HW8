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

void binPack(int binCapacity, Vector<Items> caseItems){
  int ffBins  = firstFit(binCapacity, caseItems);
  int ffdBins = firstFitDecreasing(binCapacity, caseItems);
  int bfBins  = bestFit(binCapacity, caseItems);

  cout << "Test Case " << caseCount
       << "| First Fit: " << ffdBins
       << "| First Fit Decreasing: " << ffdBins
       << "| Best Fit: " << bfBins << endl;
}


int firstFit(int binCapacity, Vector<Items> caseItems){
  Vector<Bins> = bins;
  bins.push_back(new Bin(binCapacity));

  for (int i = 0; i < caseItems.size(); i++){
    bool placed = false;
    for (int j = 0; !placed && j < bins.size(); j++){
      Item item = caseItems.at(i);
      if (item.weight <= bins.at(j).availableCapacity){
        bins.at(j).availableCapacity -= item.weight;
        bins.at(j).items.push_back(item);
        placed = true;
      }
    }
    if (!placed){
      bins.push_back(new Bin(binCapacity));
      bins.back().items.push_back(item);
    }
  }
  return bins.size();
}
}
