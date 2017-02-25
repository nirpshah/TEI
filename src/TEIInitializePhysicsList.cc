// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// InitializePhysicsList

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIInitializePhysicsList.hh"
#include "TEITimingCollector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Pretty self explanatory. Take the list you want.
#ifdef G4MULTITHREADED
void InitializePhysicsList(G4MTRunManager* runManager)
{
  G4int verboseLevel = 0;
  TEIInputFileReader* inputFileReader = TEIInputFileReader::Instance();
  G4String tempString = inputFileReader->GetPhysicsList();
  if (tempString == "custom")
  {
    TEIPhysicsList* customPhysicsList = new TEIPhysicsList(verboseLevel);
    runManager->SetUserInitialization(customPhysicsList);
  }
  else if (tempString == "QBBC")
  {
    G4VModularPhysicsList* qbbc = new QBBC(verboseLevel);
    runManager->SetUserInitialization(qbbc);
  }
  else if (tempString == "QGSP_BERT")
  {
    G4VModularPhysicsList* qgsp_bert = new QGSP_BERT(verboseLevel);
    runManager->SetUserInitialization(qgsp_bert);
  }
  else if (tempString == "QGSP_BERT_HP")
  {
    G4VModularPhysicsList* qgsp_bert_hp = new QGSP_BERT_HP(verboseLevel);
    runManager->SetUserInitialization(qgsp_bert_hp);
  }
  else if (tempString == "QGSP_BIC_HP")
  {
    G4VModularPhysicsList* qgsp_bic_hp = new QGSP_BIC_HP(verboseLevel);
    runManager->SetUserInitialization(qgsp_bic_hp);
  }
  else if (tempString == "QGSP_INCLXX")
  {
    G4VModularPhysicsList* qgsp_inclxx = new QGSP_INCLXX(verboseLevel);
    runManager->SetUserInitialization(qgsp_inclxx);
  }
  else if (tempString == "Shielding")
  {
    G4VModularPhysicsList* shielding = new Shielding(verboseLevel);
    runManager->SetUserInitialization(shielding);
  }
  else
  {
    G4cout << "Exception Needed." << G4endl;
  }
}
#else
void InitializePhysicsList(G4RunManager* runManager)
{
  G4int verboseLevel = 0;
  TEIInputFileReader* inputFileReader = TEIInputFileReader::Instance();
  TEITimingCollector* timingCollector = TEITimingCollector::Instance();
  
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Initializing physics list");
  }
  
  G4String tempString = inputFileReader->GetPhysicsList();
  if (tempString == "custom")
  {
    TEIPhysicsList* customPhysicsList = new TEIPhysicsList(verboseLevel);
    runManager->SetUserInitialization(customPhysicsList);
  }
  else if (tempString == "QBBC")
  {
    G4cout << "QBBC" << G4endl << std::flush;
    G4VModularPhysicsList* qbbc = new QBBC(verboseLevel);
    runManager->SetUserInitialization(qbbc);
  }
  else if (tempString == "QGSP_BERT")
  {
    G4cout << "QGSP_BERT" << G4endl << std::flush;
    G4VModularPhysicsList* qgsp_bert = new QGSP_BERT(verboseLevel);
    runManager->SetUserInitialization(qgsp_bert);
  }
  else if (tempString == "QGSP_BERT_HP")
  {
    G4cout << "QGSP_BERT_HP" << G4endl << std::flush;
    G4VModularPhysicsList* qgsp_bert_hp = new QGSP_BERT_HP(verboseLevel);
    runManager->SetUserInitialization(qgsp_bert_hp);
  }
  else if (tempString == "QGSP_BIC_HP")
  {
    G4cout << "QGSP_BIC_HP" << G4endl << std::flush;
    G4VModularPhysicsList* qgsp_bic_hp = new QGSP_BIC_HP(verboseLevel);
    runManager->SetUserInitialization(qgsp_bic_hp);
  }
  else if (tempString == "QGSP_INCLXX")
  {
    G4cout << "QGSP_INCLXX" << G4endl << std::flush;
    G4VModularPhysicsList* qgsp_inclxx = new QGSP_INCLXX(verboseLevel);
    runManager->SetUserInitialization(qgsp_inclxx);
  }
  else if (tempString == "Shielding")
  {
    G4cout << "Shielding" << G4endl << std::flush;
    G4VModularPhysicsList* shielding = new Shielding(verboseLevel);
    runManager->SetUserInitialization(shielding);
  }
  else
  {
    G4String message = (tempString) + " is not a valid choice for a physics list.";
    G4Exception("TEIInitializePhysicsList", "TEIInitializePhysicsList", FatalException, message);
  }
  
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Done initializing physics list");
  }
}
#endif
  

