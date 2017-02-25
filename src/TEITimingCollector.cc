// Niral Shah
// TEI
// TimingCollector
// Collects times

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEITimingCollector.hh"

#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEITimingCollector* TEITimingCollector::instance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEITimingCollector::TEITimingCollector()
{ 
  instance = this;
  MarkTime("I am born!");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEITimingCollector::~TEITimingCollector()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEITimingCollector* TEITimingCollector::Instance()
{
  if (instance == 0)
  {
    static TEITimingCollector timingCollector;
    instance = &timingCollector;
  }
  return instance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEITimingCollector::SetTime()
{
  // clock_settime(localTime, &ts);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEITimingCollector::MarkTime(G4String inLocation)
{
  locations.push_back(inLocation);
  clock_gettime(CLOCK_MONOTONIC, &ts);
  sTime.push_back(ts.tv_sec);
  nsTime.push_back(ts.tv_nsec);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEITimingCollector::PrintTime(G4String outputFileName)
{
  ofstream outputFile;
  outputFile.open(outputFileName);
  while (!locations.empty())
  {
    // outputFile << locations.front() << " :" << sTime.front() << "." << nsTime.front() << G4endl;
    outputFile << sTime.front() << "." << nsTime.front() << G4endl;
    locations.pop_front();
    sTime.pop_front();
    nsTime.pop_front();
  }
  outputFile.close();
}
