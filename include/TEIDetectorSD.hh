// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// TEIDetectorSD

#ifndef TEIDetectorSD_h
#define TEIDetectorSD_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIDetectorHit.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4VSensitiveDetector.hh"

// #include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIDetectorSD : public G4VSensitiveDetector
{
  public: 
    TEIDetectorSD(const G4String inName);
    virtual ~TEIDetectorSD();
    
    virtual void   Initialize(G4HCofThisEvent* inHCE);
    virtual G4bool ProcessHits(G4Step* inStep, G4TouchableHistory* inHistory);
    
  private:
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    TEIDetectorHitsCollection* hitsCollection;
    // The hit collection ID, its useful for finding the hits collection
    G4int HCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
