// Niral Shah 
// TEI
// Detector construction. Makes the materials, the geometry, and the sensitive detector

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIDetectorConstruction.hh"
#include "TEIDetectorSD.hh"
#include "TEIInputFileReader.hh"
#include "TEITimingCollector.hh"

#include "G4RunManager.hh"                // The essential run manager
#include "G4AutoDelete.hh"

#include "G4NistManager.hh"               // Nist Manager aka the material manager
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4MaterialTable.hh"

// #include "G4GeometryManager"
#include "G4LogicalVolume.hh"             // The volume that controls the material in the object
#include "G4UserLimits.hh"
#include "G4PVPlacement.hh"               // The linker between the volume's universe and another universe
#include "G4RotationMatrix.hh"
#include "G4Box.hh"                       // A box. Uses half widths for x,y,z
#include "G4Tubs.hh"                      // A cylinder. Name, innRad, outRad, halfZ, startangle, stopangle.

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"             // Units


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIDetectorConstruction::TEIDetectorConstruction() 
: G4VUserDetectorConstruction(),
  logicDetector(NULL),
  worldMaterial(NULL),
  detectorMaterial(NULL),
  maskMaterial(NULL)
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Detector construction constructor");
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIDetectorConstruction::~TEIDetectorConstruction()
{
  // delete detRot; // Do I delete this here? 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* TEIDetectorConstruction::Construct()
{
  DefineMaterials();
  G4VPhysicalVolume* universe = DefineVolumes();
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Finished detector Ccnstruction");
  }
  return universe;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIDetectorConstruction::DefineMaterials()
{
  // Building materials.
  worldMaterial         = BuildMaterial("worldMaterial", -1);
  detectorMaterial      = BuildMaterial("detectorMaterial", -1);
  maskMaterial   = new G4Material* [inputFileReader->GetMaskMaterial().size()];
  G4int size = inputFileReader->GetMaskMaterial().size();
  for (G4int i = 0; i < size; i++)
  {
    maskMaterial[i] = BuildMaterial("maskMaterial", i);
  }
}

G4VPhysicalVolume* TEIDetectorConstruction::DefineVolumes()
{
  // General parameters
  G4bool checkOverlaps = true;
  G4bool boolOp = false; // No idea what this is
  
  // Dimensions
    
  // World
  G4ThreeVector worldSize = inputFileReader->GetWorldSize();
  G4ThreeVector worldOrigin = G4ThreeVector(0*cm, 0*cm, 0*cm);
  G4int worldCopy = 0;
  
  // Detector
  G4double detectorInnerRad = 0.*cm;
  G4double detectorOuterRad = inputFileReader->GetDetectorDiameter()/2;
  G4double detectorZ = inputFileReader->GetDetectorHeight();
  G4double detectorStartTheta = 0.*deg;
  G4double detectorStopTheta = 360.*deg;
  G4ThreeVector detectorPosWRTWorld = inputFileReader->GetDetectorPosition();
  
  // Mask
  G4double maskInnerRadius  = inputFileReader->GetMaskRadius() - 10*cm;
  G4double maskOuterRadius  = inputFileReader->GetMaskRadius() + 10*cm;
  G4double maskZ            = inputFileReader->GetMaskHeight() + 2;
  G4double maskStartTheta   = 0.*deg;
  G4double maskStopTheta    = 360.*deg;
  G4ThreeVector maskPosWRTWorld = G4ThreeVector(0.*cm, 0.*cm, 0.*cm);
  
  // Mask Elements
  
  G4int numberOfMaskElements = inputFileReader->GetMaskMaterial().size();
  
  G4int maskCopy = 0; 
  
  // Creation of the world. Must be placed unrotated at (0, 0, 0)
  
  G4Box* solidWorld = new G4Box("World",                              // Name. Type G4String
                                worldSize.getX()/2,                   // Half length in X 
                                worldSize.getY()/2,                   // Half length in Y
                                worldSize.getZ()/2);                  // Half length in Z
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,       // Solid tie in
                                                    worldMaterial,    // Material
                                                    "World");         // Name
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                 // Rotation. Type G4RotationMatrix
                                                   worldOrigin,       // Origin. Type G4ThreeVector
                                                   logicWorld,        // Logical tie in
                                                   "World",           // Name
                                                   0,                 // Mother volume
                                                   boolOp,            // Boolean operations
                                                   worldCopy,         // Copy number
                                                   checkOverlaps);    // Overlap checking
  
  // Creation of the detector
  G4Tubs* solidDetector = new G4Tubs("Detector", 
                                detectorInnerRad, 
                                detectorOuterRad, 
                                detectorZ/2, 
                                detectorStartTheta, 
                                detectorStopTheta);
  logicDetector = new G4LogicalVolume(solidDetector, 
                                      detectorMaterial, 
                                      "Detector");
  logicDetector->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,inputFileReader->GetDetectorTrackingEnergyCut(),0));
  new G4PVPlacement(0, 
                    detectorPosWRTWorld, 
                    logicDetector, 
                    "Detector", 
                    logicWorld, 
                    boolOp,
                    0, 
                    checkOverlaps);
  
  // Partial creation of the mask. The physical placement will be done after all of the mask elements are a part of the mask
  G4Tubs* solidMask = new G4Tubs("Mask",
                                  maskInnerRadius,
                                  maskOuterRadius,
                                  maskZ/2,
                                  maskStartTheta,
                                  maskStopTheta);
  G4LogicalVolume* logicMask = new G4LogicalVolume(solidMask,
                                                   worldMaterial,
                                                   "Mask");
                                                   
  // Creation of the mask elements. I know these arrays are made with new and ought to be deleted BUT I think all of the geometry is owned by the runManager so maybe if I delete something here, the runManager may find some crap later when it tries access the address    
  G4Box**             solidMaskElement;
  G4LogicalVolume**   logicMaskElement;
  G4RotationMatrix**  maskElementRotation;
  G4ThreeVector**     maskElementPosWRTWorld;

  solidMaskElement        = new G4Box* [numberOfMaskElements];
  logicMaskElement        = new G4LogicalVolume* [numberOfMaskElements];
  maskElementRotation     = new G4RotationMatrix* [numberOfMaskElements];
  maskElementPosWRTWorld  = new G4ThreeVector* [numberOfMaskElements];
  
  G4VisAttributes* tungstenVis = new G4VisAttributes(G4Colour::Yellow());
  tungstenVis->SetForceSolid(true);
  G4VisAttributes* leadVis = new G4VisAttributes(G4Colour::Yellow());
  leadVis->SetForceSolid(true);
  G4VisAttributes* hdpeVis     = new G4VisAttributes(G4Colour::Blue());
  hdpeVis->SetForceSolid(true);
  
  G4String maskElementName = "Mask";
  G4String maskElementID;
  for (G4int i = 0; i < numberOfMaskElements; i++)
  {                  
    // Naming of the mask elements
    maskElementID = maskElementName + to_string(i);  
        
    solidMaskElement[i] = new G4Box(maskElementID, 
                                    inputFileReader->GetMaskThickness(i)/2,
                                    inputFileReader->GetMaskWidth(i)/2,
                                    inputFileReader->GetMaskHeight()/2);
                                                                    
    logicMaskElement[i] = new G4LogicalVolume(solidMaskElement[i], 
                                              maskMaterial[i],
                                              maskElementID);
                                               
    logicMaskElement[i]->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,inputFileReader->GetMaskTrackingEnergyCut(i),0));
    maskElementRotation[i] = new G4RotationMatrix();
    maskElementPosWRTWorld[i] = new G4ThreeVector();
    
    maskElementRotation[i]->rotateZ(-(inputFileReader->GetMaskCenterAngle(i)));
    // The position is detemined by the MaskCenterAngle.
    maskElementPosWRTWorld[i]->setX(inputFileReader->GetMaskRadius()*cos(inputFileReader->GetMaskCenterAngle(i)));
    maskElementPosWRTWorld[i]->setY(inputFileReader->GetMaskRadius()*sin(inputFileReader->GetMaskCenterAngle(i)));
    maskElementPosWRTWorld[i]->setZ(inputFileReader->GetMaskCenterHeight());
    
   
    new G4PVPlacement(maskElementRotation[i], 
                      *maskElementPosWRTWorld[i],
                      logicMaskElement[i], 
                      maskElementID, 
                      logicMask,
                      boolOp, 
                      maskCopy, 
                      checkOverlaps);
                    
    if (maskMaterial[i]->GetName() == "tungsten")
    {
      logicMaskElement[i]->SetVisAttributes(tungstenVis);
    }
    else if (maskMaterial[i]->GetName() == "hdpe")
    {
      logicMaskElement[i]->SetVisAttributes(hdpeVis);
    }
    else if (maskMaterial[i]->GetName() == "lead")
    {
      logicMaskElement[i]->SetVisAttributes(leadVis);
    }
  }
  
  // Placement of mask in world
  G4RotationMatrix* maskRotation = new G4RotationMatrix();
  maskRotation->rotateZ(inputFileReader->GetMaskRotationAngle());
  
  new G4PVPlacement(maskRotation, 
                    maskPosWRTWorld, 
                    logicMask, 
                    "Mask", 
                    logicWorld, 
                    boolOp,
                    0, 
                    checkOverlaps);         
  // Visulaization attributes

  G4VisAttributes* boxVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
  
  // logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
  logicMask->SetVisAttributes(G4VisAttributes::GetInvisible()); // That way we don't see the mask, just the elements
  logicWorld->SetVisAttributes(boxVisAtt);
  // logicMask->SetVisAttributes(boxVisAtt);
  if (detectorMaterial->GetName() == "stilbene")
  {
    G4VisAttributes* stilbeneVis = new G4VisAttributes(G4Colour::Magenta());
    logicDetector->SetVisAttributes(stilbeneVis);  
  }
  else if (detectorMaterial->GetName() == "CLYC")
  {
    G4VisAttributes* CLYCVis = new G4VisAttributes(G4Colour::Blue());
    logicDetector->SetVisAttributes(CLYCVis);
  }
  

  // delete[] solidMaskElement;
  // delete[] logicMaskElement;
  // delete[] maskElementRotation;
  // delete[] maskElementPosWRTWorld;

  return(physWorld);
}

// You must use the SDandField option even if there is no field
void TEIDetectorConstruction::ConstructSDandField()
{
  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  G4String SDName;
  
  G4VSensitiveDetector* detector = new TEIDetectorSD(SDName = "/detector");  
  SDMan->AddNewDetector(detector);
  logicDetector->SetSensitiveDetector(detector);
  
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

// This could be made faster, but it's relatively insignificant so I'm not going to
G4Material* TEIDetectorConstruction::BuildMaterial(G4String materialName, G4int i)
{
  G4String message;
  if (materialName == "worldMaterial")
  {
    materialName = inputFileReader->GetWorldMaterial();
  }
  else if (materialName == "detectorMaterial")
  {
    materialName = inputFileReader->GetDetectorMaterial();
  }
  else if (materialName == "maskMaterial")
  {
    materialName = inputFileReader->GetMaskMaterial(i);
  }
  else
  {
    message = "'" + materialName + "' is not an accepted material name type.";
    G4Exception("TEIDetectorConstruction::BuildMaterial()", "Invalid material name type", FatalException, message);
  }
  G4int z; // Atomic number
  G4int n; // Number of nucleons
  G4int a; // mass of mole
  G4double relativeAbundance;
  G4bool isotopes;
  
  // Elements
  // Retrieving elemental information from the nistManager. It's also possible 
  // individually control the isotopic composition
  G4NistManager* nistManager = G4NistManager::Instance();

  G4int nComp;
  G4double massFrac;
  G4double density;
  // There is no way to create a material, without knowing its density beforehand
  if (materialName == "air")
  {
    G4Element* C = nistManager->FindOrBuildElement(z = 6,  isotopes = true);
    G4Element* N = nistManager->FindOrBuildElement(z = 7,  isotopes = true);
    G4Element* O = nistManager->FindOrBuildElement(z = 8,  isotopes = true);
    G4Element* Ar = nistManager->FindOrBuildElement(z = 18,  isotopes = true);
    nComp = 4;
    density = 0.001225*g/cm3;
    G4Material* air = new G4Material("air", density, nComp);
    air->AddElement(C,  massFrac = 0.01*perCent);
    air->AddElement(N,  massFrac = 75.53*perCent);
    air->AddElement(O,  massFrac = 23.18*perCent);
    air->AddElement(Ar, massFrac = 1.28*perCent);
    return(air);
  }
  // A vacuum is just a very low dense gas
  else if (materialName == "vacuum")
  {
    G4Element* H = nistManager->FindOrBuildElement(z = 1,  isotopes = true);
    nComp = 1;
    density = 0.00000000001*mg/m3;
    G4Material* vacuum = new G4Material("vacuum", density, nComp);
    vacuum->AddElement(H, massFrac = 100*perCent);
    return(vacuum);
  }
  else if (materialName == "stilbene")
  {
    G4Element* H = nistManager->FindOrBuildElement(z = 1,  isotopes = true);
    G4Element* C = nistManager->FindOrBuildElement(z = 6,  isotopes = true);
    nComp = 2;
    density = 0.9707*g/cm3;
    G4Material* stilbene = new G4Material("stilbene", density, nComp);
    stilbene->AddElement(H, massFrac = 6.71*perCent);
    stilbene->AddElement(C, massFrac = 93.29*perCent);
    return(stilbene);
  }
  else if (materialName == "tungsten")
  { 
    G4Element* W = nistManager->FindOrBuildElement(z = 74,  isotopes = true);
    nComp = 1;
    density = 19.25*g/cm3;
    G4Material* tungsten = new G4Material("tungsten", density, nComp);
    tungsten->AddElement(W, massFrac = 100*perCent);
    return(tungsten);
  }
  else if (materialName == "hdpe")
  {
    G4Element* H = nistManager->FindOrBuildElement(z = 1,  isotopes = true);
    G4Element* C = nistManager->FindOrBuildElement(z = 6,  isotopes = true);
    nComp = 2;
    density = 0.93*g/cm3;
    G4Material* hdpe = new G4Material("hdpe", density, nComp);
    hdpe->AddElement(H, massFrac = 14.3716*perCent);
    hdpe->AddElement(C, massFrac = 85.6284*perCent);
    return(hdpe);
  }
  else if (materialName == "lead")
  {
    G4Element* Pb = nistManager->FindOrBuildElement(z = 82, isotopes = true);
    nComp = 1;
    density = 11.34*g/cm3;
    G4Material* lead = new G4Material("lead", density, nComp);
    lead->AddElement(Pb, massFrac = 100*perCent);
    return(lead);
  }
  else if (materialName == "CLYC")
  {
    // http://rmdinc.com/wp-content/uploads/2016/06/CLYC-Properties-5-10-16.pdf

    G4Isotope* Li6 = new G4Isotope("Li6", z = 3, n = 6, a = 0.);
    G4Isotope* Li7 = new G4Isotope("Li7", z = 3, n = 7, a = 0.);
    nComp = 2;
    G4Element* Li = new G4Element("Enriched Lithium", "Li", nComp);
    Li->AddIsotope(Li6, relativeAbundance = 95*perCent);
    Li->AddIsotope(Li7, relativeAbundance = 5*perCent);
    G4Element* Cl = nistManager->FindOrBuildElement(z = 17,  isotopes = true);
    G4Element* Y  = nistManager->FindOrBuildElement(z = 39,  isotopes = true);
    G4Element* Cs = nistManager->FindOrBuildElement(z = 55,  isotopes = true);
    G4Element* Ce = nistManager->FindOrBuildElement(z = 58,  isotopes = true);
    nComp = 5;
    density = 3.31*g/cm3;
    G4Material* CLYC = new G4Material("CLYC", density, nComp);
    CLYC->AddElement(Li, massFrac = 1.20*perCent);
    CLYC->AddElement(Cl, massFrac = 36.67*perCent);
    CLYC->AddElement(Y,  massFrac = 15.33*perCent);
    CLYC->AddElement(Cs, massFrac = 45.82*perCent);
    CLYC->AddElement(Ce, massFrac = 1*perCent);
    
    return(CLYC);
  } 
  else if (materialName == "CZT")
  {
    nComp = 3;
    density = 5.78*g/cm3;
    G4Element* Cd = nistManager->FindOrBuildElement(z = 48, isotopes = true);
    G4Element* Zn = nistManager->FindOrBuildElement(z = 30, isotopes = true);
    G4Element* Te = nistManager->FindOrBuildElement(z = 52, isotopes = true);
    G4Material* CZT = new G4Material("CZT", density, nComp);
    CZT->AddElement(Cd, massFrac = 42.99*perCent);
    CZT->AddElement(Zn, massFrac = 2.78*perCent);
    CZT->AddElement(Te, massFrac = 54.23*perCent);
    
    return(CZT);
  }  
  else
  {
    message = "'" + materialName + "' is not an accepted material name. Not a valid material.";
    G4Exception("TEIDetectorConstruction::BuildMaterial()", "Invalid material name", FatalException, message);
  }
}

  
  
