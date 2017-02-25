// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// ActionInitialization

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIActionInitialization_h
#define TEIActionInitialization_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIDataCollector.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4VUserActionInitialization.hh"
#include "G4String.hh"
#include <iostream>
using namespace std;

class G4String;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIActionInitialization : public G4VUserActionInitialization
{
  public:
    TEIActionInitialization();
    // I pass in the dataCollector as a pointer because I want it to be shared by threads
    TEIActionInitialization(TEIDataCollector* inDataCollector);
    virtual ~TEIActionInitialization();
    
    virtual void BuildForMaster() const;
    virtual void Build() const;
    
    TEIDataCollector* dataCollector;
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
