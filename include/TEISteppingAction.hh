// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// SteppingAction

#ifndef TEISteppingAction_h 
#define TEISteppingAction_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIDataCollector.hh"
#include "TEIEventAction.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4UserSteppingAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEISteppingAction : public G4UserSteppingAction
{
  public: 
    TEISteppingAction(TEIEventAction* inEventAction);
    virtual ~TEISteppingAction();
    
    virtual void UserSteppingAction(const G4Step*);
    
  private:
    TEIEventAction* eventAction;
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
