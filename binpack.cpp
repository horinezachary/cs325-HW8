#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

void binPack(int caseNumber, int binCapacity, vector<int> caseItems);
int firstFit(int binCapacity, vector<int> caseItems);
int firstFitDecreasing(int binCapacity, vector<int> caseItems);
int bestFit(int binCapacity, vector<int> caseItems);

struct Bin{
  int capacity;
  int availableCapacity;
  vector<int> items;
};
Bin newBin(int binCapacity){
  Bin temp;
  temp.capacity = binCapacity;
  temp.availableCapacity = binCapacity;
  return temp;
}

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
      vector<int> caseItems;
      for (int i = 0; i < currentCaseNumItems; i++){
        caseItems.push_back(stoi(parsedRow.at(i)));
      }
      binPack(caseCount, currentCaseBinCapacity, caseItems);
      caseCount++;
    }
  }
}

void binPack(int caseNumber, int binCapacity, vector<int> caseItems){
  int ffBins  = firstFit(binCapacity, caseItems);
  int ffdBins = firstFitDecreasing(binCapacity, caseItems);
  int bfBins  = bestFit(binCapacity, caseItems);

  cout << "Test Case " << caseNumber
       << "| First Fit: " << ffdBins
       << "| First Fit Decreasing: " << ffdBins
       << "| Best Fit: " << bfBins << endl;
}


int firstFit(int binCapacity, vector<int> caseItems){
  vector<Bin> bins;

  bins.push_back(newBin(binCapacity));

  for (int i = 0; i < caseItems.size(); i++){
    bool placed = false;
    int item = caseItems.at(i);
    for (int j = 0; !placed && j < bins.size(); j++){
      if (item <= bins.at(j).availableCapacity){
        bins.at(j).availableCapacity -= item;
        bins.at(j).items.push_back(item);
        placed = true;
      }
    }
    if (!placed){
      bins.push_back(newBin(binCapacity));
      bins.back().items.push_back(item);
    }
  }
  return bins.size();
}

int firstFitDecreasing(int binCapacity, vector<int> caseItems){
  int i = 1;
  while (i < caseItems.size()){  //step through array and sort each value
    int j = i;
    while (j > 0 && caseItems.at(j-1) > caseItems.at(j)){ //walk through array with one value and move it down into place
      int temp = caseItems.at(j-1);
      caseItems.at(j-1) = caseItems.at(j);
      caseItems.at(j) = temp;
      j--;
    }
    i++;
  }
  for (int i = 0; i < caseItems.size(); i++){
    cout << caseItems.at(i) << " ";
  }
  cout << endl;
  return firstFit(binCapacity, caseItems);
}

int bestFit(int binCapacity, vector<int> caseItems){

  return 0;
}
