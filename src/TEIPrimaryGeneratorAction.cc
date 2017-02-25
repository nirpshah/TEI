// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// PrimaryGeneratorAction
// Plain and simple, the fastest way to do work is to use arrays. So all the sources and all of their relevant information has a copy here as an arrray to enable fast extraction.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIPrimaryGeneratorAction.hh"
#include "TEIInputFileReader.hh"
#include "TEISpectrumInfo.hh"
#include "TEIConstants.hh"

// #include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"
#include "globals.hh"

#include <math.h>
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIPrimaryGeneratorAction::TEIPrimaryGeneratorAction() 
: G4VUserPrimaryGeneratorAction(), particleGun(0)
{
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
  
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Initializing primary generator action");
  }
  
  // Initialize
  particleGun = new G4ParticleGun(inputFileReader->GetNumberOfParticles());
  sourceDirectionRandom = NULL;
  sourceDirection = NULL;
  cosThetaLimit = NULL;
  rotationMatrix = NULL;
  sourceLineEnergy = NULL;
  sourceEnergyRandom = false;
  sourceLineProbability = NULL;
  sourceShape = NULL;
  sourcePosition = NULL;
  sourceRadius1 = NULL;
  sourceRadius2 = NULL;
  sourceParticle = NULL;
  sourceSpectrumInfo = NULL;
  // sourceZ = NULL;
  // sourceA = NULL;
  // sourceIonCharge = NULL;
  // sourceExcitationEnergy = NULL;
  
  // Initialize
  for (i = 0; i < 3; i++)
  {
    particleDirectionArray[i] = 0;
    particleDeviation[i] = 0;
    
    particlePositionArray[i] = 0;
    particlePositionDeviation[i] = 0;
  }
  
  cosTheta = 0;
  phi = 0;
  sinTheta = 0;
  i = 0;
  j = 0;
  size = 0;
  totalLineSize = 0;
  
  GenerateSource();
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Done initializing primary generator action");
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIPrimaryGeneratorAction::~TEIPrimaryGeneratorAction()
{
  delete particleGun;
  delete[] sourceDirectionRandom;
  delete[] sourceDirection;
  delete[] cosThetaLimit;
  delete[] rotationMatrix;
  delete[] sourceLineEnergy;
  delete[] sourceLineProbability;
  delete[] sourceShape;
  delete[] sourcePosition;
  delete[] sourceRadius1;
  delete[] sourceRadius2;
  delete[] sourceParticle;
  delete[] sourceSpectrumInfo;
  // delete[] sourceZ;
  // delete[] sourceA;
  // delete[] sourceIonCharge;
  // delete[] sourceExcitationEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("At start of generate primaries");
  }
  // Each potential combination of source particle, energy, position, etc is given a probability of happening. This already happened in the generate source function. Now we will generate a random number, and see which one of those will be picked. If the random number is less than a sourceProbability bound, then the particle associated with that line index will be created, if not, move up the chain until you find which particle.
  if (sourceEnergyRandom)
  {
    // Generate a random number and see where it falls on our CDF. According to that, give the source it's characteristics.
    tempDouble = G4UniformRand();
    lineIndex = 0; 
    foundEnergy = false;
    // If we haven't checked the entire array or found the correct particle type, go to the next sourceLineProbability in its array.
    while ((lineIndex < totalLineSize) && (!foundEnergy))
    {
      // Suppose the random number is 0.5 and there are two potential particles. A gamma with 1 MeV and a gamma with 2 MeV. The 1 MeV gamma, let say, has a probability of 0.33 while the other has a probability of 0.66. Recall that PDFs are changed to CDFs in generate source. Then, this loop will go: 0.5 <= 0.33?, false, lineIndex++, 0.5 <= (0.33 + 0.66)? true, so then the source is made up of characteristics at lineIndex. 
      if (tempDouble <= sourceLineProbability[lineIndex])
      {
        if (sourceLineEnergy[lineIndex] == WATT)
        {
          // https://mit-crpg.github.io/openmc/methods/physics.html#maxwell
          tempEnergy = 0;
          while ((tempEnergy <= 0) || (tempEnergy > 20))
          {
            tempEnergy = -sourceSpectrumInfo[lineIndex]->data[1]*(log(G4UniformRand())+log(G4UniformRand())*(cos(pi*G4UniformRand()/2))*(cos(pi*G4UniformRand()/2)));
            tempEnergy = tempEnergy + sourceSpectrumInfo[lineIndex]->data[1]*sourceSpectrumInfo[lineIndex]->data[1]*sourceSpectrumInfo[lineIndex]->data[2]*0.25 + (2*G4UniformRand()-1)*sourceSpectrumInfo[lineIndex]->data[1]*sqrt(sourceSpectrumInfo[lineIndex]->data[2]*tempEnergy);
          }
          tempEnergy = tempEnergy*MeV;
          particleGun->SetParticleEnergy(tempEnergy);
        }
        else if (sourceLineEnergy[lineIndex] == GAUSSIAN)
        {
          tempDouble = 0;
          while (tempDouble <= 0)
          {
            tempEnergy = (RandGauss::shoot(sourceSpectrumInfo[lineIndex]->data[1], sourceSpectrumInfo[lineIndex]->data[2]));
          } 
          tempEnergy = tempEnergy*MeV;
          particleGun->SetParticleEnergy(tempEnergy);
        }
        else if (sourceLineEnergy[lineIndex] == MAXWELLIAN)
        {
          //
        }
        /*else if (sourceLineEnergy[lineIndex] == RADIOACTIVEDECAY) // Failed
        {
          particleGun->SetParticleEnergy(0.*keV);
          sourceParticle[lineIndex] = G4IonTable::GetIonTable()->GetIon(sourceZ[lineIndex], sourceA[lineIndex]);
          particleGun->SetParticleCharge(sourceIonCharge[lineIndex]);
        }*/
        else if (sourceLineEnergy[lineIndex] == PROMPT_FISSION_GAMMA)
        {
          // I was forced to rejection sample because the function isn't very easy to invert, if at all
          // Also, if you change the PFG exponential functions, you have to change these distributions
          tempDouble = G4UniformRand();
          if (tempDouble < PROMPT_FISSION_GAMMA_FIRST_EXPONENTIAL)
          {
            tempEnergy = G4UniformRand()*(0.3-0.085)+0.085;
            tempHeight = G4UniformRand()*13.4407;
            while (tempHeight > (38.13*(tempEnergy-0.085)*exp(1.648*tempEnergy)))
            {
              tempEnergy = G4UniformRand()*(0.3-0.085)+0.085;
              tempHeight = G4UniformRand()*13.4407;
            }
            tempEnergy = tempEnergy*MeV;
            particleGun->SetParticleEnergy(tempEnergy);
          }
          else if (tempDouble < PROMPT_FISSION_GAMMA_SECOND_EXPONENTIAL)
          {
            tempEnergy = 0.434783*log(-76564700./(55092024.*tempDouble-46868287.));
            tempEnergy = tempEnergy*MeV;
            particleGun->SetParticleEnergy(tempEnergy);
          }
          else
          {
            tempEnergy = 10./11.*log(-78070400./(90003124.*tempDouble-90014965.));
            tempEnergy = tempEnergy*MeV;
            particleGun->SetParticleEnergy(tempEnergy);
          }
        }
        else
        {         
          particleGun->SetParticleEnergy(sourceLineEnergy[lineIndex]);
        }
        // Once you know the line index, stop looking for it
        foundEnergy = true;
      }
      else
      {
        lineIndex++;
      }
    } 
  }
  else
  { 
    lineIndex = 0;
    particleGun->SetParticleEnergy(sourceLineEnergy[lineIndex]);
  }
  
  // If the source direction is random, generate a random number, scale it to the approriate
  // range and add it to the lower bound of the range.
  if (sourceDirectionRandom)
  { 
    for (i = 0; i < 3; i++)
    {
      particleDirectionArray[i] = 0;
    }
    // Lets say we want a random number from 0.85 to 1. Then generate a random number from 0 to 1, scale it by multipling by 0.15, and then add it to 0.85.
    cosTheta = G4UniformRand()*(1 - cosThetaLimit[lineIndex]) + cosThetaLimit[lineIndex];
    phi = twopi*G4UniformRand();
    sinTheta = sqrt(1. - cosTheta*cosTheta);
    // Spherical to cartesian
    particleDeviation[0] = (sinTheta*cos(phi));
    particleDeviation[1] = (sinTheta*sin(phi));
    particleDeviation[2] = (cosTheta);
    // Rotate by the rotation array. We have to rotate things because the cosTheta, etc, sampling is done with respect to the z axis but we want the source to point in perhaps a different direction
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 3; j++)
      {
        particleDirectionArray[i] = particleDirectionArray[i] + rotationMatrix[lineIndex][i][j]*particleDeviation[j];       
      }
    }
    particleDirection.setX(particleDirectionArray[0]);
    particleDirection.setY(particleDirectionArray[1]);
    particleDirection.setZ(particleDirectionArray[2]);
    particleGun->SetParticleMomentumDirection(particleDirection);
  }
  else
  {
    particleGun->SetParticleMomentumDirection(sourceDirection[lineIndex]);
  }
  
  // This chooses where the particle is emitted from if the source radius isn't zero
  // You may be wondering, "Niral, how the hell does this work. You offset the particle position in the x and y when the source is actually in the y and z! This must shirley be wrong!". You are correct young padawan but understand that in this world, the source starts on the z axis and is then rotated to its place. So when the rotation occurs, all will be ok.
  if (sourceShape[lineIndex] == CIRCLE)
  {
    if (!(sourceRadius1[lineIndex] == 0))
    {
      for (i = 0; i < 3; i++)
      {
        particlePositionArray[i] = 0;
      }
      phi = twopi*G4UniformRand();
      tempDouble = G4UniformRand(); // The radial position
      particlePositionDeviation[0] = sqrt(tempDouble)*cos(phi)*sourceRadius1[lineIndex];
      particlePositionDeviation[1] = sqrt(tempDouble)*sin(phi)*sourceRadius1[lineIndex];
      particlePositionDeviation[2] = 0;
      for (i = 0; i < 3; i++)
      {
        for (j = 0; j < 3; j++)
        {
          particlePositionArray[i] = particlePositionArray[i] + rotationMatrix[lineIndex][i][j]*particlePositionDeviation[j];       
        }
      }
      particlePosition.setX(sourcePosition[lineIndex].getX() + particlePositionArray[0]);
      particlePosition.setY(sourcePosition[lineIndex].getY() + particlePositionArray[1]);
      particlePosition.setZ(sourcePosition[lineIndex].getZ() + particlePositionArray[2]);
      particleGun->SetParticlePosition(particlePosition);
    }
    else
    {
      particleGun->SetParticlePosition(sourcePosition[lineIndex]);
    }
  }
  else if (sourceShape[lineIndex] == SQUARE)
  {
    for (i = 0; i < 3; i++)
    {
      particlePositionArray[i] = 0;
    }
    particlePositionDeviation[0] = (G4UniformRand()-0.5)*sourceRadius1[lineIndex];
    particlePositionDeviation[1] = (G4UniformRand()-0.5)*sourceRadius2[lineIndex];
    particlePositionDeviation[2] = 0;
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 3; j++)
      {
        particlePositionArray[i] = particlePositionArray[i] + rotationMatrix[lineIndex][i][j]*particlePositionDeviation[j];       
      }
    }
    particlePosition.setX(sourcePosition[lineIndex].getX() + particlePositionArray[0]);
    particlePosition.setY(sourcePosition[lineIndex].getY() + particlePositionArray[1]);
    particlePosition.setZ(sourcePosition[lineIndex].getZ() + particlePositionArray[2]);
    particleGun->SetParticlePosition(particlePosition);
      
  }
  
  
  particleGun->SetParticleDefinition(sourceParticle[lineIndex]);
 
  particleGun->GeneratePrimaryVertex(anEvent);
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("At end of generate primaries");
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIPrimaryGeneratorAction::GenerateSource()
{ 
  // We want to make a fast way to access all of the source info. So we read the sources from inputFileReader, make all of them individually, and then combine everything into a set of arrays that describe our source. The ring leader of all of this is the source probability. The random number will be set equal to the cdf of source probability and whatever array index this happens at is the source for this event.
  // First we make all of the sources.
  
  size = inputFileReader->GetSourceName().size();
  totalLineSize = 0;
  deque<TEISource*> sources;
  
  for (i = 0; i < size; i++)
  {
    TEISource* tempSource = new TEISource(inputFileReader->GetSourceName(i));
    tempSource->ReadParameters(i);   
    sources.push_back(tempSource);
    totalLineSize = totalLineSize + tempSource->GetLineEnergy().size();
  }
  // Then we make their faster counterparts.
  sourceDirectionRandom = new G4bool                [totalLineSize];
  sourceDirection       = new G4ThreeVector         [totalLineSize];
  cosThetaLimit         = new G4double              [totalLineSize];
  rotationMatrix        = new G4double**            [totalLineSize];
  sourceLineEnergy      = new G4double              [totalLineSize];        
  sourceLineProbability = new G4double              [totalLineSize];
  sourceShape           = new G4double              [totalLineSize];
  sourcePosition        = new G4ThreeVector         [totalLineSize];
  sourceRadius1         = new G4double              [totalLineSize];
  sourceRadius2         = new G4double              [totalLineSize];       
  sourceParticle        = new G4ParticleDefinition* [totalLineSize];
  sourceSpectrumInfo    = new SpectrumInfo*         [totalLineSize];
  // sourceZ               = new G4int                 [totalLineSize];
  // sourceA               = new G4int                 [totalLineSize];
  // sourceIonCharge       = new G4double              [totalLineSize];
  // sourceExcitationEnergy = new G4double             [totalLineSize];
  
    
  size = inputFileReader->GetSourceName().size();
  int tempLineSize = 0;
  int k = 0;
  for (i = 0; i < size; i++)
  {
    tempLineSize = sources[i]->GetLineEnergy().size();
    for (j = 0; j < tempLineSize; j++)
    {
      sourceDirectionRandom[k] = sources[i]->GetDirectionRandom();
      sourceDirection[k] = sources[i]->GetDirection();
      cosThetaLimit[k] = cos(sources[i]->GetConeAperture()/2);
      rotationMatrix[k] = sources[i]->GetRotationMatrix();
      sourceLineEnergy[k] = sources[i]->GetLineEnergy(j);
      sourceLineProbability[k] = (sources[i]->GetLineProbability(j))*(sources[i]->GetProbability());
      sourceShape[k] = sources[i]->GetShape();
      sourcePosition[k] = sources[i]->GetPosition();
      sourceRadius1[k] = sources[i]->GetRadius1();
      sourceRadius2[k] = sources[i]->GetRadius2();
      sourceParticle[k] = sources[i]->GetParticle();
      sourceSpectrumInfo[k] = sources[i]->GetSpectrumInfo();
      // sourceZ[k] = sources[i]->GetZ();
      // sourceA[k] = sources[i]->GetA();
      // sourceIonCharge[k] = sources[i]->GetIonCharge();
      // sourceExcitationEnergy[k] = sources[i]->GetExcitationEnergy();
      k++;
    }
  }
  sourceEnergyRandom = true;
  if (totalLineSize == 1)
  {
    if (!sources[0]->GetEnergyRandom())
    {
      sourceEnergyRandom = false;
    }
  }

  // Gotta fully normalize.
  sourceLineProbability = Normalize(sourceLineProbability); 

  sourceLineProbability = PDFToCDF(sourceLineProbability);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

deque<G4double> TEIPrimaryGeneratorAction::PDFToCDF(deque<G4double> inPDF)
{
  deque<G4double> outCDF;
  size = inPDF.size();
  outCDF.assign(size, 0);
  for (i = 0; i < size; i++)
  {
    tempDouble = 0;
    for (j = 0; j <= i; j++)
    {
      tempDouble = tempDouble + inPDF[j];
    }
    outCDF[i] = tempDouble;
  }
  return(outCDF);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

deque<G4double> TEIPrimaryGeneratorAction::Normalize(deque<G4double> inDeque)
{
  G4double sum = 0;
  size = inDeque.size();
  for (i = 0; i < size; i++)
  {
    sum = sum + inDeque[i];
  }
  for (i = 0; i < size; i++)
  {
    inDeque[i] = inDeque[i]/sum;
  }
  return(inDeque);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double* TEIPrimaryGeneratorAction::Normalize(G4double* inArray)
{
  G4double sum = 0;
  for (i = 0; i < totalLineSize; i++)
  {
    sum = sum + inArray[i];
  }
  for (i = 0; i < totalLineSize; i++)
  {
    inArray[i] = inArray[i]/sum;
  }
  return(inArray);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double* TEIPrimaryGeneratorAction::PDFToCDF(G4double* inPDF)
{
  G4double* outCDF;
  outCDF = new G4double [totalLineSize];
  for (i = 0; i < totalLineSize; i++)
  {
    tempDouble = 0;
    for (j = 0; j <= i; j++)
    {
      tempDouble = tempDouble + inPDF[j];
    }
    outCDF[i] = tempDouble;
  }
  return(outCDF);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......









