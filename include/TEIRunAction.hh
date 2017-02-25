// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// RunAction

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIRunAction_h
#define TEIRunAction_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIEventAction;

class G4Run;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIRunAction : public G4UserRunAction
{
  public: 
    TEIRunAction(TEIEventAction* inEventAction);
    virtual ~TEIRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
    
  private: 
    TEIEventAction* eventAction;
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
