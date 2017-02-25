// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// TEIDetectorHit

#ifndef TEIDetectorHit_h
#define TEIDetectorHit_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

using namespace std;

// #include "G4LogicalVolume.hh"
// #include "G4Transform3D.hh"
// #include "G4RotationMatrix.hh"
// #include "tls.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// class G4AttDef;
// class G4AttValue;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIDetectorHit : public G4VHit
{
  public:
    TEIDetectorHit();
    TEIDetectorHit(const TEIDetectorHit &right);
    virtual ~TEIDetectorHit();
    
    const TEIDetectorHit& operator=(const TEIDetectorHit &right);
    int operator==(const TEIDetectorHit &right) const;
    inline void *operator new(size_t);
    inline void operator delete(void *hit);
    
    virtual void Draw();
    
    // I don't really understand why this is necessary. So we'll see.
    // virtual const std::map<G4String, G4AttDef>* GetAttDefs() const;
    // virtual std::vector<G4AttValue>* Create AttValues() const;
    
    void SetParticleName(G4String inParticleName) {particleName = inParticleName;}
    G4String GetParticleName() const {return particleName;}
    
    void SetTrackID(G4int inTrackID) {trackID = inTrackID;}
    G4int GetTrackID() const {return trackID;}
    
    void SetParentID(G4int inParentID) {parentID = inParentID;}
    G4int GetParentID() const {return parentID;}
    
    
    
    void SetPrePos(G4ThreeVector inPos) {prePos = inPos;}
    G4ThreeVector GetPrePos() const {return prePos;}
    
    // void SetPostPos(G4ThreeVector inPos) {postPos = inPos;}
    // G4ThreeVector GetPostPos() const {return postPos;}
    
    void SetTime(G4double inTime) {time = inTime;}
    G4double GetTime() const {return time;}
    
    void SetEDep(G4double inEDep) {eDep = inEDep;}
    G4double GetEDep() const {return eDep;}
    
    // void SetLogicVol(G4LogicalVolume* inLogicVol) {logicVol = inLogicVol;}
    // const G4LogicalVolume* GetLogicVol() const {return logicVol;}
    
    
    
  private:
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    // The hits hold only the data related to the detector. I end up collecting more data later but it isn't recorded in the hit
    G4String particleName;
    G4int trackID;
    G4int parentID;
    
    G4ThreeVector prePos;
    // G4ThreeVector postPos;
    G4double time;
    G4double eDep;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// A typedef is just like an alias
typedef G4THitsCollection<TEIDetectorHit> TEIDetectorHitsCollection;

// Don't really know what extern is
extern G4ThreadLocal G4Allocator<TEIDetectorHit>* TEIDetectorHitAllocator;

inline void* TEIDetectorHit::operator new(size_t)
{
  if (!TEIDetectorHitAllocator)
  {
    TEIDetectorHitAllocator = new G4Allocator<TEIDetectorHit>;
  }
  return (void*)TEIDetectorHitAllocator->MallocSingle();
}

inline void TEIDetectorHit::operator delete(void* hit)
{
  TEIDetectorHitAllocator->FreeSingle((TEIDetectorHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
  












