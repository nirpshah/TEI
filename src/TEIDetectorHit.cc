// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// TEIDetectorHit

#include "TEIDetectorHit.hh"

#include "G4ThreeVector.hh"
#include "G4VisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
// #include "G4AttDefStore.hh"
// #include "G4AttDef.hh"
// #include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

using namespace std;
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// No clue what this is or what it does
G4ThreadLocal G4Allocator<TEIDetectorHit>* TEIDetectorHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIDetectorHit::TEIDetectorHit() : G4VHit(),
  particleName(),
  trackID(-1),
  parentID(-1),
  time(-1),
  prePos(G4ThreeVector()),
  // postPos(G4ThreeVector()),
  eDep(-1)
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIDetectorHit::~TEIDetectorHit()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIDetectorHit::TEIDetectorHit(const TEIDetectorHit &right) : G4VHit()
{
  particleName = right.particleName;
  trackID = right.trackID;
  parentID = right.parentID;
  time = right.time;
  prePos = right.prePos;
  // postPos = right.postPos;
  eDep = right.eDep;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const TEIDetectorHit& TEIDetectorHit::operator=(const TEIDetectorHit &right)
{
  particleName = right.particleName;
  trackID = right.trackID;
  parentID = right.parentID;
  time = right.time;
  prePos = right.prePos;
  // postPos = right.postPos;
  eDep = right.eDep;

  return(*this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int TEIDetectorHit::operator==(const TEIDetectorHit& right) const
{
  // return 0;
  // No clue how this works or even if its right or wrong.
  return (this == &right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIDetectorHit::Draw()
{
  G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();
  if (visManager)
  {
    G4Circle circle(prePos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1., 1., 0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    visManager->Draw(circle);
  }
}













