// Niral Shah 
// TEI
// PhysicsList

#ifndef TEIPhysicsList_h 
#define TEIPhysicsList_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4VUserPhysicsList.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIPhysicsList : public G4VUserPhysicsList
{
  public:
    TEIPhysicsList(G4int inVerboseLevel);
    virtual ~TEIPhysicsList();
    
  protected:
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    virtual void SetCuts();
    
  private:
    G4double  defaultProductionRangeCut;
    G4bool    gammaCreated;
    G4bool    electronCreated;
    G4bool    positronCreated;
    G4bool    protonCreated;
    G4bool    neutronCreated;
    G4bool    genericIonCreated;
    
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
