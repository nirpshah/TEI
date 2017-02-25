// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// EventDataMember
// This class will hold the thread local data from each event and then get copied over to 
// the DataCollector at the end of each event

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIEventDataMember_h
#define TEIEventDataMember_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIEventDataMember.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "TEIDetectorHit.hh"
#include "TEIDetectorSD.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include <iostream>
#include <iomanip>
#include <deque>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<TEIDetectorHit> TEIDetectorHitsCollection;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIEventDataMember
{
  public:
    TEIEventDataMember();
    TEIEventDataMember(const G4Event* event, G4int detectorHCID);
    TEIEventDataMember(const TEIEventDataMember &right);
    ~TEIEventDataMember();
    
    const TEIEventDataMember& operator=(const TEIEventDataMember &right);
    
    // The print data just needs the outputFileName and it will open it and print out.
    void PrintData(G4String outputFileName);
    void PrintHeader(G4String outputFileName);
  
  private:
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    // All the data I want to collect. It's all deques because then I can indefinitely add to it and easily access the front of it
    deque<G4int>          eventID;
    deque<G4int>          emissionParticle;
    deque<G4ThreeVector>  emissionMomentum;
    deque<G4double>       emissionEnergy;
    deque<G4ThreeVector>  emissionPos;
    // deque<G4double>       emissionTime;
    
    deque<G4int>          particle;
    deque<G4int>          trackID;
    deque<G4int>          parentID;
    // deque<G4ThreeVector>  preMomentum;
    deque<G4ThreeVector>  prePos;
    // deque<G4ThreeVector>  postPos;
    deque<G4double>       time;
    deque<G4double>       eDep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
