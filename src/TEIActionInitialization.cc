// Niral Shah 
// TEI
// ActionInitialization. I'm not sure exactly what this does but I think this creates the steps G4 will take.
// Refer to a G4 example. I used example B1, B2, and B5

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIActionInitialization.hh"
#include "TEIPrimaryGeneratorAction.hh"
#include "TEIRunAction.hh"
#include "TEIEventAction.hh"
#include "TEISteppingAction.hh"

#include <iostream>
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class TEIDataCollector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIActionInitialization::TEIActionInitialization() : G4VUserActionInitialization() 
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIActionInitialization::TEIActionInitialization(TEIDataCollector* inDataCollector) : G4VUserActionInitialization() 
{ 
  dataCollector = inDataCollector;
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIActionInitialization::~TEIActionInitialization()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIActionInitialization::BuildForMaster() const
{
  TEIEventAction* eventAction = 0;
  SetUserAction(new TEIRunAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIActionInitialization::Build() const
{
  SetUserAction(new TEIPrimaryGeneratorAction);
  
  TEIEventAction* eventAction = new TEIEventAction(dataCollector);
  // TEIEventAction* eventAction = new TEIEventAction();
  SetUserAction(eventAction);
  
  SetUserAction(new TEIRunAction(eventAction));
  
  // SetUserAction(new TEISteppingAction(eventAction));
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
