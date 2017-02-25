// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// InitializePhysicsList

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIInitializePhysicsList_h 
#define TEIInitializePhysicsList_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"              // The multithreaded manager
#else
#include "G4RunManager.hh"                // The normal manager
#endif
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"
#include "TEIPhysicsList.hh"
#include "QBBC.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_INCLXX.hh"
#include "Shielding.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
void InitializePhysicsList(G4MTRunManager* runManager);
#else
void InitializePhysicsList(G4RunManager* runManager);
#endif



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
