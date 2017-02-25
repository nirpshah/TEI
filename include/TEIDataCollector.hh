// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// DataCollector
// DataCollector holds a deque that holds TEIEventDataMember objects that hold all the data from each event. 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIDataCollector_h
#define TEIDataCollector_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIDetectorHit.hh"
#include "TEIEventDataMember.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
#include <list>
#include <vector>
#include <ctime>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Event;
class G4String;
class TEIEventDataMember;

class TEIDataCollector
{
  public:
    TEIDataCollector();
    ~TEIDataCollector();
    
    void SetOutputFileName(G4String inOutputFileName);
    G4String GetOutputFileName();
    
    void SetHeaderFileName(G4String inHeaderFileName);
    G4String GetHeaderFileName();
    
    void SetStartTime();
    G4double GetRawStartTime() {return rawStartTime;}
    G4String GetStartTime() {return startTime;}
    
    void SetEndTime();
    G4String GetEndTime() {return endTime;}
    
    // void OpenOutputFile();
    // void CloseOutputFile(); 
    void CollectData(TEIEventDataMember* inEventDataMember);
    void PrintData();
    void PrintHeader();
    
  
  private:
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    
    // This is all of the data from the simulation
    deque<TEIEventDataMember*> simData;
    G4String outputFileName;
    G4String headerFileName;
    time_t   rawStartTime;
    G4String startTime;
    G4String endTime;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
