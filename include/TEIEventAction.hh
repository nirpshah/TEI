// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// TEIEventAction

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIEventAction_h
#define TEIEventAction_h 1

#include "TEIDataCollector.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"
// #include <vector>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class TEIRunAction;

class TEIEventAction : public G4UserEventAction
{
  public:
    TEIEventAction();
    TEIEventAction(TEIDataCollector* inDataCollector);
    virtual ~TEIEventAction();
    
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event* event);
    void CreateBar();
    
  private:
    TEIDataCollector* dataCollector;  
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    
    G4int detectorHCID;
      
    G4double updateEventNumber; // The progress bar is a event driven update. The next update point is predicted based on when a new bar should show up.
    G4int numberOfBars; // Number of bars to show this time. It's used to index into message
    G4int numberOfEvents; // The total number of events in the simulation
    G4int barSize; // This is the maximum size of the bar. It is based on the size of the window minus some offsets
    G4int colSize; // The size of the window
    G4bool progressBar; // Whether or not to make a progress bar. For no threading, don't make a bar if ui. For threading, don't make bar unless thread 0.
    time_t startTime; // raw start time for the events. 
    time_t currentTime; // obvi
    G4int timeElapsed; // the time elapsed. The units change as the value is used.
    G4int endTime; // Projected end time.
    G4int seconds[2]; // Holds the two digits for the seconds time. The first is the tens place, the second the ones place
    G4int minutes[2];
    G4int hours[2];
    G4int i; // some counter
    char* message; // the message we will display. It gets created at the start and is modified when necessary
    char digits[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'}; // Because changing ints to char is impossibly difficult.
    G4int offset; // The offset due to threading
    G4bool createBar; // whether or not the initial bar needs to be made.
};

#endif
