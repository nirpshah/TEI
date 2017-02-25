// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// EventDataMember
// This class will hold the thread local data from each event and then get copied over to 
// the DataCollector at the end of each event

#include "TEIEventDataMember.hh"
#include "TEIDetectorHit.hh"
#include "TEIDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4ios.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"
#include "TEIConstants.hh"

#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIEventDataMember::TEIEventDataMember()
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIEventDataMember::TEIEventDataMember(const G4Event* event, G4int detectorHCID)
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
  // G4cout << "***** In TEIEventDataMember::TEIEventDataMember(G4Event*, G4int) *****" << std::flush << G4endl << std::flush;
  
  G4HCofThisEvent* hce = event->GetHCofThisEvent(); 
  // Ya I mean it needs to be cast into the right type 
  TEIDetectorHitsCollection* detectorHC = 
        static_cast<TEIDetectorHitsCollection*>(hce->GetHC(detectorHCID));
  
  // Gathering the useful info
  G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
  G4PrimaryParticle* primary = primaryVertex->GetPrimary(0);

  G4String emissionParticleName = primary->GetG4code()->GetParticleName();
  G4int tempEmissionParticle = 0;
  G4ThreeVector tempEmissionMomentum;
  G4double      tempEmissionEnergy;
  
  if (emissionParticleName == "gamma")
  {
    tempEmissionParticle = 1;
    tempEmissionMomentum = primary->GetMomentum();
    tempEmissionEnergy = sqrt(tempEmissionMomentum*tempEmissionMomentum);
  }
  else if (emissionParticleName == "neutron")
  {
    tempEmissionParticle = 5;
    tempEmissionMomentum = primary->GetMomentum();
    tempEmissionEnergy = (tempEmissionMomentum*tempEmissionMomentum)/primary->GetMass()/2;
  }
  
   
  G4int tempEventID = event->GetEventID();
  G4ThreeVector tempEmissionPos = primaryVertex->GetPosition();
  
  // G4double tempEmissionTime = primaryVertex->GetT0();
  
  G4String tempParticleName;
  G4int nHit = detectorHC->entries();
  for (G4int i = 0; i < nHit; i++)
  {
    TEIDetectorHit* hit = (*detectorHC)[i];
    
    eventID.push_back(tempEventID);
    emissionParticle.push_back(tempEmissionParticle);
    emissionMomentum.push_back(tempEmissionMomentum);
    emissionEnergy.push_back(tempEmissionEnergy);
    emissionPos.push_back(tempEmissionPos);
    // emissionTime.push_back(tempEmissionTime);
    
    tempParticleName = hit->GetParticleName();
    if (tempParticleName == "gamma")
    {
      particle.push_back(GAMMA);
    }
    else if (tempParticleName == "e-")
    {
      particle.push_back(ELECTRON);
    }
    else if (tempParticleName == "e+")
    {
      particle.push_back(POSITRON);
    }
    else if (tempParticleName == "proton")
    {
      particle.push_back(PROTON);
    }
    else if (tempParticleName == "neutron")
    {
      particle.push_back(NEUTRON);
    }
    else if (tempParticleName == "GenericIon")
    {
      particle.push_back(GENERIC_ION);
    }
    else if (tempParticleName == "C12")
    {
      particle.push_back(C12);
    }
    else if (tempParticleName == "C13")
    {
      particle.push_back(C13);
    }
    else
    {
      particle.push_back(UNKNOWN);
      // cout << tempParticleName << endl;
    }
   
    trackID.push_back(hit->GetTrackID());
    parentID.push_back(hit->GetParentID());
    // preMomentum.push_back(hit->GetPreMomentum());
    prePos.push_back(hit->GetPrePos());
    // postPos.push_back(hit->GetPostPos());
    time.push_back(hit->GetTime());
    eDep.push_back(hit->GetEDep());   
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIEventDataMember::TEIEventDataMember(const TEIEventDataMember &right)
{
  // G4cout << G4endl << G4endl << "***** TEIEventDataMember::TEIEventDataMember(TEIEventDataMember& ) *****" << G4endl << G4endl << G4endl;
  eventID = right.eventID;
  emissionParticle = right.emissionParticle;
  emissionMomentum = right.emissionMomentum;
  emissionEnergy = right.emissionEnergy;
  emissionPos = right.emissionPos;
  // emissionTime = right.emissionTime;
  
  particle = right.particle;
  trackID = right.trackID;
  parentID = right.parentID;
  // preMomentum = right.preMomentum;
  prePos = right.prePos;
  // postPos = right.postPos;
  time = right.time;
  eDep = right.eDep;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIEventDataMember::~TEIEventDataMember()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const TEIEventDataMember& TEIEventDataMember::operator=(const TEIEventDataMember &right)
{
  eventID = right.eventID;
  emissionParticle = right.emissionParticle;
  emissionMomentum = right.emissionMomentum;
  emissionEnergy = right.emissionEnergy;
  emissionPos = right.emissionPos;
  // emissionTime = right.emissionTime;
  
  particle = right.particle;
  trackID = right.trackID;
  parentID = right.parentID;
  // preMomentum = right.preMomentum;
  prePos = right.prePos;
  // postPos = right.postPos;
  time = right.time; 
  eDep = right.eDep; 

  return(*this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIEventDataMember::PrintData(G4String outputFileName)
{
  // G4cout << G4endl << G4endl << "***** In TEIEventDataMember::PrintData(G4String ) *****" << G4endl << G4endl << G4endl;
  G4int size = eventID.size();
  ofstream outputFile;
  outputFile.open(outputFileName, std::ios_base::app);
  
  outputFile << setprecision(3) << fixed << left;
  
  for (G4int i = 0; i < size; i++)
  {
    outputFile << setw(10) << eventID.front()
               << setw(6)  << emissionParticle.front()
               << setw(15) << emissionMomentum.front().getX()/keV
               << setw(15) << emissionMomentum.front().getY()/keV
               << setw(15) << emissionMomentum.front().getZ()/keV
               << setw(11) << emissionEnergy.front()/keV
               << setw(11) << emissionPos.front().getX()/cm
               << setw(11) << emissionPos.front().getY()/cm
               << setw(11) << emissionPos.front().getZ()/cm
               // << setw(10) << emissionTime.front()/ns
               ;
           
    outputFile << setw(6)  << particle.front()
               << setw(7)  << trackID.front()
               << setw(7)  << parentID.front()
               // << setw(11) << preMomentum.front().getX()/keV
               // << setw(11) << preMomentum.front().getY()/keV
               // << setw(11) << preMomentum.front().getZ()/keV
               << setw(11) << prePos.front().getX()/cm
               << setw(11) << prePos.front().getY()/cm
               << setw(11) << prePos.front().getZ()/cm
               // << setw(11) << postPos.front().getX()/cm
               // << setw(11) << postPos.front().getY()/cm
               // << setw(11) << postPos.front().getZ()/cm
               << setw(10) << time.front()/ns 
               << setw(0)  << eDep.front()/keV
               << G4endl;     
               
    eventID.pop_front();      
    emissionParticle.pop_front();
    emissionMomentum.pop_front();
    emissionEnergy.pop_front();
    emissionPos.pop_front();
    // emissionTime.pop_front();
    
    particle.pop_front();
    trackID.pop_front();
    parentID.pop_front();
    // preMomentum.pop_front();
    prePos.pop_front();
    // postPos.pop_front();
    time.pop_front(); 
    eDep.pop_front();
  }
  outputFile.close();
}

void TEIEventDataMember::PrintHeader(G4String headerFileName)
{

  ofstream headerFile;
  headerFile.open(headerFileName, std::ios_base::app);
  
  headerFile << setprecision(3) << fixed << left;
  headerFile << setw(19) << " "
             << setw(32) << "Initial Momentum: [keV/c]"
             << setw(49) << "Emission Position: [cm]";
  
  headerFile // << setw(33) << "Pre-Momentum: [keV]"
             << setw(33)  << "Pre-Position: [cm]"
             // << setw(0)  << "Post-Position: [cm]"
             ; 

  headerFile << G4endl
             << setw(10) << "Event" 
             << setw(6)  << "Par"
             << setw(15) << "P0_X"
             << setw(15) << "P0_Y"
             << setw(15) << "P0_Z"
             << setw(11) << "E"
             << setw(11) << "r0_X"
             << setw(11) << "r0_Y"
             << setw(11) << "r0_Z"
             // << setw(10) << "T_0 [ns]"
             ;
       
  headerFile << setw(6)  << "Par"
             << setw(7)  << "T_ID"
             << setw(7)  << "P_ID"
             // << setw(11) << "E1_X"
             // << setw(11) << "E1_Y"
             // << setw(11) << "E1_Z"
             << setw(11) << "r1_X"
             << setw(11) << "r1_Y"
             << setw(11) << "r1_Z"
             // << setw(11) << "r2_X"
             // << setw(11) << "r2_Y"
             // << setw(11) << "r2_Z"
             << setw(10) << "T [ns]"
             << setw(0) << "E_Dep [kev]"
             << G4endl;
  headerFile.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
