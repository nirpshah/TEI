// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// Source

#ifndef TEISource_h
#define TEISource_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEISpectrumInfo.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "TEIConstants.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"

using namespace CLHEP;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEISource
{
  public:
    TEISource(G4String inName);
    ~TEISource();  
    
    void ReadParameters(G4int i);
    deque<G4double> Normalize(deque<G4double> inDeque);
    void GenerateRotationMatrix();
    
    void SetName(G4String inName) {name = inName;}
    G4String GetName() const {return name;}
    
    void SetShape(G4double inShape) {shape = inShape;}
    G4double GetShape() const {return shape;}
    
    void SetProbability(G4double inProbability) {probability = inProbability;}
    G4double GetProbability() const {return probability;}
    
    void SetPosition(G4ThreeVector inPosition) {position = inPosition;}
    G4ThreeVector GetPosition() const {return position;}
    
    void SetRadius1(G4double inRadius1) {radius1 = inRadius1;}
    G4double GetRadius1() const {return radius1;}
    
    void SetRadius2(G4double inRadius2) {radius2 = inRadius2;}
    G4double GetRadius2() const {return radius2;}
    
    void SetConeAperture(G4double inConeAperture) {coneAperture = inConeAperture;}
    G4double GetConeAperture() const {return coneAperture;}
    
    void SetDirectionRandom(G4bool inDirectionRandom) {directionRandom = inDirectionRandom;}
    G4bool GetDirectionRandom() const {return directionRandom;}
    
    void SetDirection(G4ThreeVector inDirection) {direction = inDirection;}
    G4ThreeVector GetDirection() const {return direction;}
    
    G4double** GetRotationMatrix() const {return rotationMatrix;}
    
    void SetParticle(G4int inParticle); 
    G4ParticleDefinition* GetParticle() const {return particle;}
    
    // Recall that custom is created line by line. SetLineEnergy will only be called for custom builds
    void SetLineEnergy(G4double inLineEnergy) {lineEnergy.push_back(inLineEnergy);}
    deque<G4double> GetLineEnergy() const {return lineEnergy;}
    G4double GetLineEnergy(G4int i) const {return lineEnergy[i];}
    
    void SetLineProbability(G4double inLineProbability) {lineProbability.push_back(inLineProbability);}
    deque<G4double> GetLineProbability() const {return lineProbability;}
    G4double GetLineProbability(G4int i) const {return lineProbability[i];}
    
    void SetSpectrumInfo(SpectrumInfo inSpectrumInfo) {spectrumInfo = inSpectrumInfo;}
    SpectrumInfo* GetSpectrumInfo() {return &spectrumInfo;}    
    
    void SetEnergyRandom(G4bool inEnergyRandom) {energyRandom = inEnergyRandom;}
    G4bool GetEnergyRandom() const {return energyRandom;}
    
    /*void SetZ(G4int inZ) {Z = inZ;}
    G4int GetZ() const {return Z;}
    
    void SetA(G4int inA) {A = inA;}
    G4int GetA() const {return A;}
    
    void SetIonCharge(G4double inIonCharge) {ionCharge = inIonCharge;}
    G4double GetIonCharge() const {return ionCharge;}
    
    void SetExcitationEnergy(G4double inExcitationEnergy) {excitationEnergy = inExcitationEnergy;}
    G4double GetExcitationEnergy() const {return excitationEnergy;}
    */
  private:
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    
    G4String              name;
    G4double              shape;
    G4double              probability;
    G4ThreeVector         position;
    G4double              radius1;
    G4double              radius2;
    G4double              coneAperture;
    G4bool                directionRandom;
    G4ThreeVector         direction;
    G4double**            rotationMatrix;
    G4ParticleDefinition* particle;
    deque<G4double>       lineEnergy;
    deque<G4double>       lineProbability;
    G4bool                energyRandom;
    SpectrumInfo          spectrumInfo;
    
    G4String              tempString;
    G4String              message;
    
    
    // G4int                 Z;
    // G4int                 A;
    // G4double              ionCharge;
    // G4double              excitationEnergy;

    G4int size;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
