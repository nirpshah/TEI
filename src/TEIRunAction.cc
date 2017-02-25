// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// RunAction

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIRunAction::TEIRunAction(TEIEventAction* inEventAction) 
  : G4UserRunAction(),
  eventAction(inEventAction)
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIRunAction::~TEIRunAction()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIRunAction::BeginOfRunAction(const G4Run*)
{
  // Inform the runManager to save the random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIRunAction::EndOfRunAction(const G4Run*)
{ ;}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  

