// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// SteppingAction

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEISteppingAction.hh"
#include <iomanip>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEISteppingAction::TEISteppingAction(TEIEventAction* inEventAction)
  : G4UserSteppingAction(),
  eventAction(inEventAction)
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEISteppingAction::~TEISteppingAction()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEISteppingAction::UserSteppingAction(const G4Step*)
{
  // G4cout << G4endl << "Parent ID: " << step->GetTrack()->GetParentID() 
  //   << "Particle: " << step->GetTrack()->GetDefinition()->GetParticleName() << G4endl << G4endl;
}
