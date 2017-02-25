// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// InputFileReader

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIInputFileReader.hh"
#include "TEIConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include <sstream>
#include <string>
#include <deque>
#include <stdio.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIInputFileReader* TEIInputFileReader::instance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIInputFileReader::TEIInputFileReader()
{
  inputStart = "Input Start:";
  inputEnd = "End";
  instance = this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIInputFileReader::TEIInputFileReader(G4String inInputFileName)
{
  inputFileName = inInputFileName;
  inputStart = "Input Start:";
  inputEnd = "End";
  ReadInputFile();
  instance = this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIInputFileReader::~TEIInputFileReader()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIInputFileReader* TEIInputFileReader::Instance()
{
  if (instance == 0)
  {
    static TEIInputFileReader inputFileReader;
    instance = &inputFileReader;
  }
  return instance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIInputFileReader::ReadInputFile(G4String inInputFileName)
{
  inputFileName = inInputFileName;
  ReadInputFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIInputFileReader::ReadInputFile()
{
  G4String message;
  
  ifstream inputFile;
  inputFile.open(inputFileName.c_str());
  
  if (inputFile.fail())
  {
    message = "Input file failed to open. This can happen for many reasons such as an incorrect file name or insufficient access permissions.";
    G4Exception("TEIInputFileName::ReadInputFile()", "Input File Fail", FatalException, message);
  }
  
  G4bool inputsFound = false;
  
  G4String tempString;
  // G4int tempInt;
  G4double tempDouble;
  G4ThreeVector tempThreeVector;
  stringstream tempStream;
  // G4int i;
  // G4int size;
  SpectrumInfo tempSpectrumInfo;
  
  // The "Input Start:" line is required in the inputFile just to speed up reading. If you don't find it before the reader fails or is at the end, then exception out.
  while ((inputsFound == false) && (!(inputFile.eof())) && (!(inputFile.fail())))
  {
    getline(inputFile, tempString);
    if (strcmp(tempString, inputStart) == 0) // If they compare correctly, it will output a 0.
    {
      inputsFound = true;
    }
  }
  
  if (inputsFound == false)
  {
    message = "You need the 'Input Start:' line in the code. Place is before you start inputing all of the data.";
    G4Exception("TEIInputFileReader::ReadInputFile()", "'Input Start:' not found", FatalException, message);
  }
  
  // Given that we haven't failed and haven't found the "End" line, read.
  while ((inputsFound == true) && (!inputFile.fail()))
  {
    inputFile >> tempString;
    if (false) // Always false to make copypasta easier
    { ;}
    else if ((strcmp(tempString, "macroFileName")) == 0)
    {
      inputFile >> macroFileName;
    }
    else if ((strcmp(tempString, "outputFileName")) == 0)
    {
      inputFile >> outputFileName;
    }
    else if ((strcmp(tempString, "headerFileName")) == 0)
    {
      inputFile >> headerFileName;
    }
    else if ((strcmp(tempString, "progressBar")) == 0)
    {
      inputFile >> tempString;
      if ((strcmp(tempString, "false")) == 0)
      {
        progressBar = false;
      }
      else
      {
        progressBar = true;
      }
    }
    else if ((strcmp(tempString, "collectTimes")) == 0)
    {
      inputFile >> tempString;
      if ((strcmp(tempString, "true")) == 0)
      {
        collectTimes = true;
      }
      else
      {
        collectTimes = false;
      }
    }
    //
    //
    else if ((strcmp(tempString, "numberOfThreads")) == 0)
    {
      inputFile >> numberOfThreads;
    }
    else if ((strcmp(tempString, "numberOfParticles")) == 0)
    {
      inputFile >> numberOfParticles;
    }
    else if ((strcmp(tempString, "numberOfEvents")) == 0)
    {
      inputFile >> numberOfEvents;
    }
    //
    //
    else if ((strcmp(tempString, "detectorMaterial")) == 0)
    {
      inputFile >> detectorMaterial;
    }
    else if ((strcmp(tempString, "detectorHeight")) == 0)
    {
      inputFile >> detectorHeight;
      // Numbers need units so you gotta multiply it by its unit. G4 changes the unit to it's own personal default.
      detectorHeight = detectorHeight*cm; 
    }
    else if ((strcmp(tempString, "detectorDiameter")) == 0)
    {
      inputFile >> detectorDiameter;
      detectorDiameter = detectorDiameter*cm;
    }
    else if ((strcmp(tempString, "detectorPosition")) == 0)
    {
      inputFile >> tempDouble;
      tempDouble = tempDouble*cm;
      detectorPosition.setX(tempDouble);
      
      inputFile >> tempDouble;
      tempDouble = tempDouble*cm;
      detectorPosition.setY(tempDouble);
      
      inputFile >> tempDouble;
      tempDouble = tempDouble*cm;
      detectorPosition.setZ(tempDouble);    
    }
    else if ((strcmp(tempString, "detectorTrackingEnergyCut")) == 0)
    {
      inputFile >> tempDouble;
      detectorTrackingEnergyCut = tempDouble*keV;
    }
    //
    //
    else if ((strcmp(tempString, "sourceName")) == 0)
    {
      // To read a list of potential whatevers, read the entire line, push it back into another stream, and read it piece by piece. This is certainly slowish but I can get an entire tine and never worry about skipping data.
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempString)
      {
        sourceName.push_back(tempString);
      }   
      // Once the while loop is done, the stream will fail, so we just reset it.
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceShape")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      while (tempStream >> tempString)
      {
        sourceShape.push_back(tempString);
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceProbability")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempDouble)
      {
        sourceProbability.push_back(tempDouble);
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourcePosition")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*cm;
        tempThreeVector.setX(tempDouble);
        
        tempStream >> tempDouble;
        tempDouble = tempDouble*cm;
        tempThreeVector.setY(tempDouble);
      
        tempStream >> tempDouble;
        tempDouble = tempDouble*cm;
        tempThreeVector.setZ(tempDouble);  
      
        sourcePosition.push_back(tempThreeVector);
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceRadius1")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*cm;  
        sourceRadius1.push_back(tempDouble);
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceRadius2")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*cm;  
        sourceRadius2.push_back(tempDouble);
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceConeAperture")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*deg;
        sourceConeAperture.push_back(tempDouble);
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceDirection")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*cm;
        tempThreeVector.setX(tempDouble);
        
        tempStream >> tempDouble;
        tempDouble = tempDouble*cm;
        tempThreeVector.setY(tempDouble);
      
        tempStream >> tempDouble;
        tempDouble = tempDouble*cm;
        tempThreeVector.setZ(tempDouble);  
        
        sourceDirection.push_back(tempThreeVector);
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceParticle")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempString)
      {
        if (tempString == "gamma")
        {
          sourceParticle.push_back(GAMMA);
        }
        else if (tempString == "neutron")
        {
          sourceParticle.push_back(NEUTRON);
        }
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceEnergy")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        if (tempDouble == WATT)
        {
          sourceEnergy.push_back(WATT);
        }
        else if (tempDouble == GAUSSIAN)
        {
          sourceEnergy.push_back(GAUSSIAN);
        }
        else if (tempDouble == MAXWELLIAN)
        {
          sourceEnergy.push_back(MAXWELLIAN);
        }
        else if (tempDouble > 0)
        {
          tempDouble = tempDouble*keV;
          sourceEnergy.push_back(tempDouble);
        }
        else
        {
          message = "The sourceEnergy you provided is not usable. You're lucky I even provide this error because this code doesn't error check well. ";
          G4Exception("TEIInputFileReader::ReadInputFile()", "Invalid sourceEnergy", FatalException, message);
        }
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "sourceEnergyProbability")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        sourceEnergyProbability.push_back(tempDouble);
        
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "wattSpectrum")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempDouble)
      {
        tempSpectrumInfo.data[0] = WATT;
        tempSpectrumInfo.data[1] = tempDouble;
        tempStream >> tempDouble;
        tempSpectrumInfo.data[2] = tempDouble;
        tempSpectrumInfo.data[3] = 0;
        wattSpectrum.push_back(tempSpectrumInfo);
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "gaussianSpectrum")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempDouble)
      {
        tempSpectrumInfo.data[0] = GAUSSIAN;
        tempSpectrumInfo.data[1] = tempDouble;
        tempStream >> tempDouble;
        tempSpectrumInfo.data[2] = tempDouble;
        tempSpectrumInfo.data[3] = 0;
        gaussianSpectrum.push_back(tempSpectrumInfo);
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "maxwellianSpectrum")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempDouble)
      {
        tempSpectrumInfo.data[0] = MAXWELLIAN;
        tempSpectrumInfo.data[1] = tempDouble;
        tempStream >> tempDouble;
        tempSpectrumInfo.data[2] = tempDouble;
        tempSpectrumInfo.data[3] = 0;
        maxwellianSpectrum.push_back(tempSpectrumInfo);
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    //
    //
    else if ((strcmp(tempString, "maskMaterial")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;

      while (tempStream >> tempString)
      {
        maskMaterial.push_back(tempString);
      }   
      if (tempStream.fail())
      {
        tempStream.clear();
      }
    }
    else if ((strcmp(tempString, "maskThickness")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*cm;
        maskThickness.push_back(tempDouble);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "maskWidth")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*cm;
        maskWidth.push_back(tempDouble);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "maskCenterAngle")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*deg;
        maskCenterAngle.push_back(tempDouble);
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "maskTrackingEnergyCut")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempDouble)
      {
        tempDouble = tempDouble*keV;
        maskTrackingEnergyCut.push_back(tempDouble);
      }
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "maskHeight")) == 0)
    {
      inputFile >> maskHeight;
      maskHeight = maskHeight*cm;
    }
    else if ((strcmp(tempString, "maskRadius")) == 0)
    {
      inputFile >> maskRadius;
      maskRadius = maskRadius*cm;
    }
    else if ((strcmp(tempString, "maskCenterHeight")) == 0)
    {
      inputFile >> maskCenterHeight;
      maskCenterHeight = maskCenterHeight*cm;
    }
    else if ((strcmp(tempString, "maskRotationAngle")) == 0)
    {
      inputFile >> maskRotationAngle;
      maskRotationAngle = maskRotationAngle*deg;
    }
    //
    //
    else if ((strcmp(tempString, "worldMaterial")) == 0)
    {
      inputFile >> worldMaterial;
    }
    else if ((strcmp(tempString, "worldSize")) == 0)
    {
      inputFile >> tempDouble;
      tempDouble = tempDouble*cm;
      worldSize.setX(tempDouble);
      
      inputFile >> tempDouble;
      tempDouble = tempDouble*cm;
      worldSize.setY(tempDouble);
      
      inputFile >> tempDouble;
      tempDouble = tempDouble*cm;
      worldSize.setZ(tempDouble);
    }
    //
    //
    else if ((strcmp(tempString, "physicsList")) == 0)
    {
      inputFile >> physicsList;
    }
    else if ((strcmp(tempString, "particle")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempString)
      {
        particle.push_back(tempString);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "gammaProcess")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempString)
      {
        gammaProcess.push_back(tempString);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "electronProcess")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempString)
      {
        electronProcess.push_back(tempString);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "positronProcess")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempString)
      {
        positronProcess.push_back(tempString);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "protonProcess")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempString)
      {
        protonProcess.push_back(tempString);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "neutronProcess")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempString)
      {
        neutronProcess.push_back(tempString);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "genericIonProcess")) == 0)
    {
      getline(inputFile, tempString, '\n');
      tempStream << tempString;
      
      while (tempStream >> tempString)
      {
        genericIonProcess.push_back(tempString);
      } 
      if (tempStream.fail())
      {
        tempStream.clear();
      } 
    }
    else if ((strcmp(tempString, "defaultProductionRangeCut")) == 0)
    {
      inputFile >> defaultProductionRangeCut;
      defaultProductionRangeCut = defaultProductionRangeCut*cm;
    }
    else if ((strcmp(tempString, "gammaProductionRangeCut")) == 0)
    {
      inputFile >> gammaProductionRangeCut;
      gammaProductionRangeCut = gammaProductionRangeCut*cm;
    }
    else if ((strcmp(tempString, "neutronProductionRangeCut")) == 0)
    {
      inputFile >> neutronProductionRangeCut;
      neutronProductionRangeCut = neutronProductionRangeCut*cm;
    }
    else if ((strcmp(tempString, inputEnd)) == 0)
    {
      inputsFound = false;
    }
    else
    {
      message = "New input: '" + tempString + "'. You need to register this input in the reader.";
      G4Exception("TEIInputFileReader::ReadInputFile()", "New Input", FatalException, message); 
    }
  }
  
  if (inputFile.fail())
  {
    message = "inputFileReader failed. Only God knows why. The last thing I read in: '" + tempString + "'.";
    G4Exception("TEIInputFileReader::ReadInputFile()", "inputFileReader failure", FatalException, message);
  }
  return;
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 
  
// Example of a input file:
/*
Input file for TEI. Description is below input details.

Input Start:
Input Start:

macroFileName             run.mac
outputFileName            auto
headerFileName            auto

numberOfThreads           15
numberOfParticles         1

detectorMaterial          stilbene
detectorHeight            7.62 
detectorDiameter          7.62
detectorPosition          0 0 0

sourceName                custom    custom
sourceProbability         1         0
sourcePosition            0 0 200   200 100 200
sourceConeAperture        15        40     
sourceDirection           0 0 0     0 0 0
sourceParticle            gamma     neutron
sourceEnergy              200       2500
sourceEnergyProbability   1         1
wattSpectrum              0 0       0 0
gaussianSpectrum          0 0       0 0 
maxwellianSpectrum        0 0       0 0

maskMaterial              tungsten  hdpe   tungsten   tungsten    tungsten    hdpe    tungsten  tungsten  tungsten  hdpe    
maskThickness             2         4      2          2           2           2       2         2         2         2
maskWidth                 9         6      6          6           12          14      7         11        13        10          
maskCenterAngle           0         35     55         65          100         135     170       205       270       325       
maskHeight                60        
maskRadius                40 
maskCenterHeight          0
maskRotationAngle         -60

worldMaterial             air
worldSize                 600 600 600

physicsList               custom
particle                  gamma electron positron proton neutron genericIon
gammaProcess              photoElectricEffect comptonScattering pairProduction
electronProcess           multipleScattering ionisation bremsstrahlung coulombScattering
positronProcess           multipleScattering ionisation bremsstrahlung annihilation coulombScattering
protonProcess             multipleScattering ionisation elasticScattering inelasticScattering
neutronProcess            elasticScattering inelasticScattering capture fission
genericIonProcess         multipleScattering ionisation elasticScattering inelasticScattering

End
End
*/  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
