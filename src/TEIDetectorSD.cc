// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// TEIDetectorSD

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIDetectorSD.hh"
#include "TEIDetectorHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIDetectorSD::TEIDetectorSD(const G4String inName)
  : G4VSensitiveDetector(inName), 
    hitsCollection(NULL),
    HCID(-1)
{
  collectionName.insert("detectorColl");
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIDetectorSD::~TEIDetectorSD()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIDetectorSD::Initialize(G4HCofThisEvent* inHCE)
{
  // G4cout << "In TEIDetectorSD::Initialize" << endl;
  hitsCollection = new TEIDetectorHitsCollection
                       (SensitiveDetectorName, collectionName[0]);
  if (HCID == -1)
  {
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  }
  inHCE->AddHitsCollection(HCID, hitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TEIDetectorSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  G4double eDep = step->GetTotalEnergyDeposit();
  // If there's no energy depositied, bounce out
  if (eDep == 0.) return true;

  TEIDetectorHit* newHit = new TEIDetectorHit();

  newHit->SetParticleName(step->GetTrack()->GetDefinition()->GetParticleName());
  newHit->SetTrackID(step->GetTrack()->GetTrackID());
  newHit->SetParentID(step->GetTrack()->GetParentID());
  newHit->SetEDep(eDep);
  newHit->SetPrePos(step->GetPreStepPoint()->GetPosition());
  // newHit->SetPostPos(step->GetPostStepPoint()->GetPosition());
  newHit->SetTime(step->GetPreStepPoint()->GetGlobalTime());

  hitsCollection->insert(newHit);

  return true;
}

