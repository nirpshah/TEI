// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// InputFileReader

#ifndef TEIInputFileReader_h 
#define TEIInputFileReader_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ThreeVector.hh"
#include "TEISpectrumInfo.hh"
#include "globals.hh"
#include <iostream>
#include <fstream>
#include <ios>
#include <iomanip>
#include <deque>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TEIInputFileReader
{
  public:
    TEIInputFileReader();
    TEIInputFileReader(G4String inInputFileName);
    ~TEIInputFileReader();
    
    static TEIInputFileReader* Instance();
    
    void ReadInputFile();
    void ReadInputFile(G4String inputFileName);
    
    void            SetInputFileName(G4String inInputFileName) {inputFileName = inInputFileName;}
    
    G4String              GetMacroFileName()                  const {return macroFileName;}
    G4String              GetOutputFileName()                 const {return outputFileName;}
    G4String              GetHeaderFileName()                 const {return headerFileName;}
    G4bool                GetProgressBar()                    const {return progressBar;}
    G4bool                GetCollectTimes()                   const {return collectTimes;}
          
    G4int                 GetNumberOfThreads()                const {return numberOfThreads;}
    G4int                 GetNumberOfParticles()              const {return numberOfParticles;}
    G4int                 GetNumberOfEvents()                 const {return numberOfEvents;}
          
    G4String              GetDetectorMaterial()               const {return detectorMaterial;}
    G4double              GetDetectorHeight()                 const {return detectorHeight;}
    G4double              GetDetectorDiameter()               const {return detectorDiameter;}
    G4ThreeVector         GetDetectorPosition()               const {return detectorPosition;}
    G4double              GetDetectorTrackingEnergyCut()      const {return detectorTrackingEnergyCut;}
          
    deque<G4String>       GetSourceName()                     const {return sourceName;}
    G4String              GetSourceName(G4int i)              const {return sourceName[i];}
    deque<G4String>       GetSourceShape()                    const {return sourceShape;}
    G4String              GetSourceShape(G4int i)             const {return sourceShape[i];}
    deque<G4double>       GetSourceProbability()              const {return sourceProbability;}
    G4double              GetSourceProbability(G4int i)       const {return sourceProbability[i];}
    deque<G4ThreeVector>  GetSourcePosition()                 const {return sourcePosition;}
    G4ThreeVector         GetSourcePosition(G4int i)          const {return sourcePosition[i];}
    deque<G4double>       GetSourceRadius1()                  const {return sourceRadius1;}
    G4double              GetSourceRadius1(G4int i)           const {return sourceRadius1[i];}
    deque<G4double>       GetSourceRadius2()                  const {return sourceRadius2;}
    G4double              GetSourceRadius2(G4int i)           const {return sourceRadius2[i];}
    deque<G4double>       GetSourceConeAperture()             const {return sourceConeAperture;}
    G4double              GetSourceConeAperture(G4int i)      const {return sourceConeAperture[i];}
    deque<G4ThreeVector>  GetSourceDirection()                const {return sourceDirection;}
    G4ThreeVector         GetSourceDirection(G4int i)         const {return sourceDirection[i];}
    deque<G4int>          GetSourceParticle()                 const {return sourceParticle;}
    G4int                 GetSourceParticle(G4int i)          const {return sourceParticle[i];}
    deque<G4double>       GetSourceEnergy()                   const {return sourceEnergy;}
    G4double              GetSourceEnergy(G4int i)            const {return sourceEnergy[i];}
    deque<G4double>       GetSourceEnergyProbability()        const {return sourceEnergyProbability;}
    G4double              GetSourceEnergyProbability(G4int i) const {return sourceEnergyProbability[i];}
    deque<SpectrumInfo>   GetWattSpectrum()                   const {return wattSpectrum;}
    SpectrumInfo          GetWattSpectrum(G4int i)            const {return wattSpectrum[i];}
    deque<SpectrumInfo>   GetGaussianSpectrum()               const {return gaussianSpectrum;}
    SpectrumInfo          GetGaussianSpectrum(G4int i)        const {return gaussianSpectrum[i];}
    deque<SpectrumInfo>   GetMaxwellianSpectrum()             const {return maxwellianSpectrum;}
    SpectrumInfo          GetMaxwellianSpectrum(G4int i)      const {return maxwellianSpectrum[i];}
     
    deque<G4String>       GetMaskMaterial()                   const {return maskMaterial;}
    G4String              GetMaskMaterial(G4int i)            const {return maskMaterial[i];}
    deque<G4double>       GetMaskThickness()                  const {return maskThickness;}
    G4double              GetMaskThickness(G4int i)           const {return maskThickness[i];}
    deque<G4double>       GetMaskWidth()                      const {return maskWidth;}
    G4double              GetMaskWidth(G4int i)               const {return maskWidth[i];}
    deque<G4double>       GetMaskCenterAngle()                const {return maskCenterAngle;}
    G4double              GetMaskCenterAngle(G4int i)         const {return maskCenterAngle[i];}
    deque<G4double>       GetMaskTrackingEnergyCut()     const {return maskTrackingEnergyCut;}
    G4double              GetMaskTrackingEnergyCut(G4int i) const {return maskTrackingEnergyCut[i];}
    G4double              GetMaskHeight()                     const {return maskHeight;}
    G4double              GetMaskRadius()                     const {return maskRadius;}
    G4double              GetMaskCenterHeight()               const {return maskCenterHeight;}
    G4double              GetMaskRotationAngle()              const {return maskRotationAngle;}
            
    G4String              GetWorldMaterial()                  const {return worldMaterial;}
    G4ThreeVector         GetWorldSize()                      const {return worldSize;}
          
    G4String              GetPhysicsList()                    const {return physicsList;}
    deque<G4String>       GetParticle()                       const {return particle;}
    G4String              GetParticle(G4int i)                const {return particle[i];}
    deque<G4String>       GetGammaProcess()                   const {return gammaProcess;}
    G4String              GetGammaProcess(G4int i)            const {return gammaProcess[i];}
    deque<G4String>       GetElectronProcess()                const {return electronProcess;}
    G4String              GetElectronProcess(G4int i)         const {return electronProcess[i];}
    deque<G4String>       GetPositronProcess()                const {return positronProcess;}
    G4String              GetPositronProcess(G4int i)         const {return positronProcess[i];}
    deque<G4String>       GetProtonProcess()                  const {return protonProcess;}
    G4String              GetProtonProcess(G4int i)           const {return protonProcess[i];}
    deque<G4String>       GetNeutronProcess()                 const {return neutronProcess;}
    G4String              GetNeutronProcess(G4int i)          const {return neutronProcess[i];}
    deque<G4String>       GetGenericIonProcess()              const {return genericIonProcess;}
    G4String              GetGenericIonProcess(G4int i)       const {return genericIonProcess[i];}
    G4double              GetDefaultProductionRangeCut()      const {return defaultProductionRangeCut;}
    G4double              GetGammaProductionRangeCut()        const {return gammaProductionRangeCut;}
    G4double              GetNeutronProductionRangeCut()      const {return neutronProductionRangeCut;}        
  
  private:
    static TEIInputFileReader* instance;
    
    G4String              macroFileName;
    G4String              outputFileName;
    G4String              headerFileName;
    G4bool                progressBar;
    G4bool                collectTimes;
          
    G4String              inputFileName;
    G4String              inputStart;
    G4String              inputEnd;
        
    G4int                 numberOfThreads;
    G4int                 numberOfParticles;
    G4int                 numberOfEvents;
    
    G4String              detectorMaterial;
    G4double              detectorHeight;
    G4double              detectorDiameter;
    G4ThreeVector         detectorPosition;
    G4double              detectorTrackingEnergyCut;
    
    deque<G4String>       sourceName;
    deque<G4String>       sourceShape;
    deque<G4double>       sourceProbability;
    deque<G4ThreeVector>  sourcePosition;
    deque<G4double>       sourceRadius1;
    deque<G4double>       sourceRadius2;
    deque<G4double>       sourceConeAperture;
    deque<G4ThreeVector>  sourceDirection;
    deque<G4int>          sourceParticle;
    deque<G4double>       sourceEnergy;
    deque<G4double>       sourceEnergyProbability;
    deque<SpectrumInfo>   wattSpectrum;
    deque<SpectrumInfo>   gaussianSpectrum;
    deque<SpectrumInfo>   maxwellianSpectrum;
    
    deque<G4String>       maskMaterial;
    deque<G4double>       maskThickness;
    deque<G4double>       maskWidth;
    deque<G4double>       maskCenterAngle;
    deque<G4double>       maskTrackingEnergyCut;
    G4double              maskHeight;
    G4double              maskRadius;
    G4double              maskCenterHeight;
    G4double              maskRotationAngle;
    
    G4String              worldMaterial;
    G4ThreeVector         worldSize;
    
    G4String              physicsList;
    deque<G4String>       particle;
    deque<G4String>       gammaProcess;
    deque<G4String>       electronProcess;
    deque<G4String>       positronProcess;
    deque<G4String>       protonProcess;
    deque<G4String>       neutronProcess;
    deque<G4String>       genericIonProcess;
    G4double              defaultProductionRangeCut;  
    G4double              gammaProductionRangeCut;
    G4double              neutronProductionRangeCut;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
