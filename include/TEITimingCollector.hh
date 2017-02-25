// Niral Shah
// TEI
// TimingCollector
// This class is just to get timing data

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEITimingCollector_h
#define TEITimingCollector_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIInputFileReader.hh"

#include <ctime>
#include <sys/time.h>
#include <deque>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEITimingCollector
{
  public:
    TEITimingCollector();
    ~TEITimingCollector();
    
    static TEITimingCollector* Instance();
    
    void SetTime();
    void MarkTime(G4String inLocation);
    void PrintTime(G4String outputFileName);
    
  private:
    static TEITimingCollector* instance;
    timespec ts;
    
    deque<G4String> locations;
    deque<G4int>    sTime;
    deque<G4int>    nsTime;
};

#endif
