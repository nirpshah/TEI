// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// Detector construction

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef TEIDetectorConstruction_h
#define TEIDetectorConstruction_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"
#include "G4VUserDetectorConstruction.hh"
// #include "tls.hh"
#include "globals.hh"

// #include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIInputFileReader;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    TEIDetectorConstruction();
    virtual ~TEIDetectorConstruction();
    
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    
  private:
    void DefineMaterials();
    // Makes the materials, plain and simple
    G4Material* BuildMaterial(G4String materialName, G4int i);
    G4VPhysicalVolume* DefineVolumes();
    
    TEIInputFileReader* inputFileReader;
    TEITimingCollector* timingCollector;
    
    // The logical volume of every detector must be available
    G4LogicalVolume* logicDetector;
    
    // The materials I need to save
    G4Material*   worldMaterial;
    G4Material*   detectorMaterial;
    G4Material**  maskMaterial;
    
//    G4Element* H = nistManager->FindOrBuildElement(z = 1,  isotopes = true);
//    G4Element* Li = nistManager->FindOrBuildElement(z = 3,  isotopes = true);
//    G4Element* B = nistManager->FindOrBuildElement(z = 5,  isotopes = true);
//    G4Element* C = nistManager->FindOrBuildElement(z = 6,  isotopes = true);
//    G4Element* N = nistManager->FindOrBuildElement(z = 7,  isotopes = true);
//    G4Element* O = nistManager->FindOrBuildElement(z = 8,  isotopes = true);
//    G4Element* Al = nistManager->FindOrBuildElement(z = 13,  isotopes = true);
//    G4Element* Cl = nistManager->FindOrBuildElement(z = 17,  isotopes = true);
//    G4Element* Ar = nistManager->FindOrBuildElement(z = 18,  isotopes = true);
//    G4Element* Fe = nistManager->FindOrBuildElement(z = 26,  isotopes = true);
//    G4Element* Br = nistManager->FindOrBuildElement(z = 35,  isotopes = true);
//    G4Element* Y = nistManager->FindOrBuildElement(z = 39,  isotopes = true);
//    G4Element* Cd = nistManager->FindOrBuildElement(z = 48,  isotopes = true);
//    G4Element* Cs = nistManager->FindOrBuildElement(z = 55,  isotopes = true);
//    G4Element* La = nistManager->FindOrBuildElement(z = 57,  isotopes = true);
//    G4Element* Ce = nistManager->FindOrBuildElement(z = 58,  isotopes = true);
//    G4Element* W = nistManager->FindOrBuildElement(z = 74,  isotopes = true);
//    G4Element* Pb = nistManager->FindOrBuildElement(z = 82,  isotopes = true);
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 

