// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// PrimaryGeneratorAction
// The purpose of this fuction is to generate the primary particles. First the 
// function extracts the useful information from the inputFileReader and then 
// creates the source based on user specifications. A rotation matrix is created 
// to move the source to the preferred direction.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIPrimaryGeneratorAction_h
#define TEIPrimaryGeneratorAction_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIConstants.hh"
#include "TEISource.hh"
#include "TEISpectrumInfo.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4IonTable.hh"
#include "globals.hh"
#include <deque>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4ParticleGun;
class G4Event;
// class G4Box;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    TEIPrimaryGeneratorAction();
    virtual ~TEIPrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event*);
    const G4ParticleGun* GetParticleGun() const {return particleGun;}
    
    // Creates the sources and ties it alltogether into one major array system.
    void GenerateSource();

    deque<G4double> Normalize(deque<G4double> inDeque);
    deque<G4double> PDFToCDF(deque<G4double> inPDF);
    G4double* Normalize(G4double* inArray);
    G4double* PDFToCDF(G4double* inPDF);
    
  private:
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    
    G4ParticleGun* particleGun;
    G4ParticleDefinition* gamma;
    G4ParticleDefinition* neutron;
    
    G4bool*         sourceDirectionRandom;    // A random source or not
    G4ThreeVector*  sourceDirection;
    G4double*       cosThetaLimit;            // The limits of sampling for the cone
    G4double***     rotationMatrix; 
    
    G4double*       sourceLineEnergy;
    G4bool          sourceEnergyRandom;
    G4double*       sourceLineProbability;
    
    G4double*       sourceShape;
    G4ThreeVector*  sourcePosition;
    G4double*       sourceRadius1;
    G4double*       sourceRadius2;
    G4ParticleDefinition** sourceParticle;
    // G4int*          sourceZ;
    // G4int*          sourceA;
    // G4double*       sourceIonCharge;
    // G4double*       sourceExcitationEnergy;
    
    SpectrumInfo**  sourceSpectrumInfo;
    
    G4ThreeVector   particleDirection;          // A particular particles direction
    G4double        particleDirectionArray[3];  // A particular particles direction in array form
    G4double        particleDeviation[3];       // A particular particles deviation from 0 0 1
    
    G4ThreeVector   particlePosition;
    G4double        particlePositionArray[3];
    G4double        particlePositionDeviation[3];
    
    G4double        cosTheta;                   // Randomly generated cosTheta deviation
    G4double        sinTheta;                   // Randomly generated sinTheta deviation
    G4double        phi;                        // Randomly generated phi deviation

    G4double        tempDouble;
    G4double        tempEnergy;
    G4double        tempHeight;
    G4bool          foundEnergy;
    
    // This is just cause shitty coding idk
    int i;
    int j;
    int size;
    int totalLineSize;
    int lineIndex;
    
    
};

#endif 
