// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// Source

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEISource.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEISource::TEISource(G4String inName)
{
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
  // The source name is recognizable, then build what we know about it and get the rest from inputFileReader
  name = inName;
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* gamma = particleTable->FindParticle(particleName="gamma");
  G4ParticleDefinition* neutron = particleTable->FindParticle(particleName="neutron");
  // G4ParticleDefinition* geantino = particleTable->FindParticle(particleName="geantino");
  
  spectrumInfo.data[0] = 0;
  spectrumInfo.data[1] = 0;
  spectrumInfo.data[2] = 0;
  spectrumInfo.data[3] = 0;
  // Z = 0;
  // A = 0;
  // ionCharge = 0;
  // excitationEnergy = 0;
  
  if (name == "custom")
  {
    // Do nothing
  }
  else if (name == "cs-137")
  {
    particle = gamma;
    energyRandom = false;
    lineEnergy.push_back(661.7*keV);
    lineProbability.push_back(1);
  } 
  else if (name == "co-60")
  {
    particle = gamma;
    energyRandom = true;
    lineEnergy.push_back(1173.228*keV);
    lineEnergy.push_back(1332.492*keV);
    lineProbability.push_back(0.9985);
    lineProbability.push_back(0.999826);
  }
  else if (name == "ba-133")
  {
    particle = gamma;
    energyRandom = true;
    lineEnergy.push_back(53.1622*keV);
    lineEnergy.push_back(79.6142*keV);
    lineEnergy.push_back(80.9979*keV);
    lineEnergy.push_back(160.6121*keV);
    lineEnergy.push_back(223.2368*keV);
    lineEnergy.push_back(276.3989*keV);
    lineEnergy.push_back(302.8508*keV);
    lineEnergy.push_back(356.0129*keV);
    lineEnergy.push_back(383.8485*keV);
    lineProbability.push_back(0.0214);
    lineProbability.push_back(0.0263);
    lineProbability.push_back(0.3331);
    lineProbability.push_back(0.00638);
    lineProbability.push_back(0.00450);
    lineProbability.push_back(0.0713);
    lineProbability.push_back(0.1831);
    lineProbability.push_back(0.6205);
    lineProbability.push_back(0.0894);
  }
  else if (name == "cd-109")
  {
    particle = gamma;
    energyRandom = false;
    lineEnergy.push_back(88.0336*keV);
    lineProbability.push_back(1);
  }
  else if (name == "co-57")
  {
    particle = gamma;
    energyRandom = true;
    lineEnergy.push_back(14.41295*keV);
    lineEnergy.push_back(122.06065*keV);
    lineEnergy.push_back(136.47356*keV);
    lineEnergy.push_back(692.01*keV);
    lineProbability.push_back(0.0915);
    lineProbability.push_back(0.8551);
    lineProbability.push_back(0.1071);
    lineProbability.push_back(0.00159);
  }
  else if (name == "mn-54")
  {
    particle = gamma;
    energyRandom = false;
    lineEnergy.push_back(834.848*keV);
    lineProbability.push_back(1);
  }
  else if (name == "na-22")
  {
    particle = gamma;
    energyRandom = true;
    lineEnergy.push_back(511*keV);
    lineEnergy.push_back(1274.537*keV);
    lineProbability.push_back(1.807);
    lineProbability.push_back(0.9994);
  }
  else if (name == "dd")
  {
    particle = neutron;
    energyRandom = false;
    lineEnergy.push_back(2500*keV);
    lineProbability.push_back(1);
  }
  else if (name == "dt")
  {
    particle = neutron;
    energyRandom = false;
    lineEnergy.push_back(14100*keV);
    lineProbability.push_back(1);
  }
  else if (name == "cf-252-n")
  {
    particle = neutron;
    energyRandom = true;
    lineEnergy.push_back(WATT);
    lineProbability.push_back(1);
    spectrumInfo.data[0] = WATT;
    spectrumInfo.data[1] = 1.209; // 1.025
    spectrumInfo.data[2] = 0.836; // 2.926
    // spectrumInfo.data[3] = 2*exp(-1*spectrumInfo.data[1]*spectrumInfo.data[2]/4)/(sqrt((pi*spectrumInfo.data[1]*spectrumInfo.data[1]*spectrumInfo.data[1]*spectrumInfo.data[2])));   
  }
  else if (name == "u-238-n")
  {
    particle = neutron;
    energyRandom = true;
    lineEnergy.push_back(WATT);
    lineProbability.push_back(1);
    spectrumInfo.data[0] = WATT;
    spectrumInfo.data[1] = 0.78;
    spectrumInfo.data[2] = 5.194;
  }
  else if (name == "pu-240-n")
  {
    particle = neutron;
    energyRandom = true;
    lineEnergy.push_back(WATT);
    lineProbability.push_back(1);
    spectrumInfo.data[0] = WATT;
    spectrumInfo.data[1] = 0.799;
    spectrumInfo.data[2] = 4.903;
  }
  else if (name == "pu-242-n")
  {
    particle = neutron;
    energyRandom = true;
    lineEnergy.push_back(WATT);
    lineProbability.push_back(1);
    spectrumInfo.data[0] = WATT;
    spectrumInfo.data[1] = 0.834;
    spectrumInfo.data[2] = 4.432;
  }
  else if (name == "cm-242-n")
  {
    particle = neutron;
    energyRandom = true;
    lineEnergy.push_back(WATT);
    lineProbability.push_back(1);
    spectrumInfo.data[0] = WATT;
    spectrumInfo.data[1] = 0.891;
    spectrumInfo.data[2] = 4.046;
  }
  else if (name == "cm-244-n")
  {
    particle = neutron;
    energyRandom = true;
    lineEnergy.push_back(WATT);
    lineProbability.push_back(1);
    spectrumInfo.data[0] = WATT;
    spectrumInfo.data[1] = 0.906;
    spectrumInfo.data[2] = 3.848;
  }
  else if (name == "am-li")
  {
    // Tagziria and Looman, Ideal amli source
    particle = neutron;
    energyRandom = true;
    G4int temp = 0;
    for (G4int i = 0; i < 50; i ++)
    {
      temp = i*0.04 + 0.02;
      lineEnergy.push_back(temp);
    }
    lineProbability.push_back(0.00808);
    lineProbability.push_back(0.02423);
    lineProbability.push_back(0.04388);
    lineProbability.push_back(0.06233);
    lineProbability.push_back(0.06);
    lineProbability.push_back(0.0527);
    lineProbability.push_back(0.0527);
    lineProbability.push_back(0.0488);
    lineProbability.push_back(0.04439);
    lineProbability.push_back(0.043);
    lineProbability.push_back(0.03915);
    lineProbability.push_back(0.03861);
    lineProbability.push_back(0.03749);
    lineProbability.push_back(0.03137);
    lineProbability.push_back(0.02987);
    lineProbability.push_back(0.02961);
    lineProbability.push_back(0.02951);
    lineProbability.push_back(0.02826);
    lineProbability.push_back(0.02639);
    lineProbability.push_back(0.02495);
    lineProbability.push_back(0.02363);
    lineProbability.push_back(0.02381);
    lineProbability.push_back(0.02264);
    lineProbability.push_back(0.02149);
    lineProbability.push_back(0.01991);
    lineProbability.push_back(0.01951);
    lineProbability.push_back(0.01664);
    lineProbability.push_back(0.01645);
    lineProbability.push_back(0.01507);
    lineProbability.push_back(0.01314);
    lineProbability.push_back(0.01109);
    lineProbability.push_back(0.01043);
    lineProbability.push_back(0.00957);
    lineProbability.push_back(0.00673);
    lineProbability.push_back(0.00618);
    lineProbability.push_back(0.00394);
    lineProbability.push_back(0.00289);
    lineProbability.push_back(0.00159);
    lineProbability.push_back(0.00172);
    lineProbability.push_back(0.00142);
    lineProbability.push_back(0.00123);
    lineProbability.push_back(0.0016);
    lineProbability.push_back(0.00117);
    lineProbability.push_back(0.00161);
    lineProbability.push_back(0.0016);
    lineProbability.push_back(0.00154);
    lineProbability.push_back(0.00119);
    lineProbability.push_back(0.00085);
    lineProbability.push_back(0.00138);
    lineProbability.push_back(0.00123);
  }
  else if ((name == "cf-252-g") || (name == "u-238-g") || (name == "pu-240-g") || (name == "pu-242-g") || (name == "cm-242-g") || ("cm-244-g"))
  {
    particle = gamma;
    energyRandom = true;
    lineEnergy.push_back(PROMPT_FISSION_GAMMA);
    lineProbability.push_back(1);
  }
  else
  {
    name = "Unknown";
    G4cout << "Need Exception" << G4endl << std::flush;
  }
  lineProbability = Normalize(lineProbability);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEISource::~TEISource()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

deque<G4double> TEISource::Normalize(deque<G4double> inDeque)
{
  G4double sum = 0;
  size = inDeque.size();
  for (G4int i = 0; i < size; i++)
  {
    sum = sum + inDeque[i];
  }
  for (G4int i = 0; i < size; i++)
  {
    inDeque[i] = inDeque[i]/sum;
  }
  return(inDeque);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEISource::GenerateRotationMatrix()
{
  // Idk, what do you want me to tell ya. Details for these vectors can be found at http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/. Which rotation you do first matters a lot, so do it correctly. For this its z and then y, I think. I actually don't know anymore...
  
  G4double cosBeta;
  G4double sinBeta;
  G4double cosGamma;
  G4double sinGamma;
  // G4double rotationMatrixX[3][3];
  G4double rotationMatrixY[3][3];
  G4double rotationMatrixZ[3][3]; 
  
  rotationMatrix = new G4double*[3];
  for (G4int i = 0; i < 3; i++)
  {
    rotationMatrix[i] = new G4double[3];
  }
  
  for (G4int i = 0; i < 3; i++)
  {
    for (G4int j = 0; j < 3; j++)
    {
      rotationMatrix[i][j] = 0;
    }
  }

  // cosAlpha = 1;
  // sinAlpha = 0;

  cosBeta = direction.getZ();
  sinBeta = (sqrt(1-direction.getZ()*direction.getZ()));

  // If z = 1, then we will be dividing by zero. Which we can't. 
  if ((direction.getZ() == 1) || (direction.getZ() == -1))
  {   
    cosGamma = 1;
    sinGamma = 0;
  }
  else
  {   
    cosGamma = direction.getX()/(sqrt(1 - direction.getZ()*direction.getZ()));
    sinGamma = direction.getY()/(sqrt(1 - direction.getZ()*direction.getZ()));
  }

  // 

  /*
  rotationMatrixX[0][0] = 1;
  rotationMatrixX[0][1] = 0;
  rotationMatrixX[0][2] = 0;
  rotationMatrixX[1][0] = 0;
  rotationMatrixX[1][1] = cosAlpha;
  rotationMatrixX[1][2] = -1*sinAlpha;
  rotationMatrixX[2][0] = 
  rotationMatrixX[2][1] = sinAlpha;
  rotationMatrixX[2][2] = cosAlpha;
  */
  // By definition
  rotationMatrixY[0][0] = cosBeta;
  rotationMatrixY[0][1] = 0;
  rotationMatrixY[0][2] = sinBeta;
  rotationMatrixY[1][0] = 0;
  rotationMatrixY[1][1] = 1;
  rotationMatrixY[1][2] = 0;
  rotationMatrixY[2][0] = -1*sinBeta;
  rotationMatrixY[2][1] = 0;
  rotationMatrixY[2][2] = cosBeta;
 
  rotationMatrixZ[0][0] = cosGamma;
  rotationMatrixZ[0][1] = -1*sinGamma;
  rotationMatrixZ[0][2] = 0;
  rotationMatrixZ[1][0] = sinGamma;
  rotationMatrixZ[1][1] = cosGamma;
  rotationMatrixZ[1][2] = 0;
  rotationMatrixZ[2][0] = 0;
  rotationMatrixZ[2][1] = 0;
  rotationMatrixZ[2][2] = 1;
  
  // Multiply
  int k = 0;
  for (int resultRow = 0; resultRow < 3; resultRow++)
  {
    for (int resultCol = 0; resultCol < 3; resultCol++)
    {
      k = 0;
      for (k = 0; k < 3; k++)
      {
        rotationMatrix[resultRow][resultCol] = rotationMatrix[resultRow][resultCol] + rotationMatrixZ[resultRow][k]*rotationMatrixY[k][resultCol];
      }
    }
  }
 
  /*
  for (int i = 0; i < 3; i++)
  {
    for (int j =0; j < 3; j++)
    {
      G4cout << rotationMatrix[i][j] << " " << std::flush;
    }
    G4cout << G4endl << std::flush;
  }
  */
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEISource::ReadParameters(G4int i)
{
  inputFileReader = TEIInputFileReader::Instance();
  
  tempString = inputFileReader->GetSourceShape(i);
  if (tempString == "circle")
  {
    SetShape(CIRCLE);
  }
  else if (tempString == "square")
  {
    SetShape(SQUARE);
  }
  else
  {
    message = "Invalid Shape: " + tempString;
    G4Exception("TEISource::ReadParameters", "Invalid Shape", JustWarning, message);
  }
  SetProbability(inputFileReader->GetSourceProbability(i));
  SetPosition(inputFileReader->GetSourcePosition(i));
  SetRadius1(inputFileReader->GetSourceRadius1(i));
  SetRadius2(inputFileReader->GetSourceRadius2(i));
  SetConeAperture(inputFileReader->GetSourceConeAperture(i));
  if (coneAperture == 0)
  {
    directionRandom = false;
  }
  else
  {
    directionRandom = true;
  }
  
  SetDirection(inputFileReader->GetSourceDirection(i));
  if (direction.mag() != 0)
  {
    direction = direction/direction.mag();
  }
  
  if (direction.mag2() == 0)
  {
    direction = inputFileReader->GetDetectorPosition() - position;
    direction = direction/direction.mag();
  }
  GenerateRotationMatrix();
  
  if (name == "custom")
  {
    SetParticle(inputFileReader->GetSourceParticle(i));
    SetLineEnergy(inputFileReader->GetSourceEnergy(i));
    
    if (lineEnergy[0] == WATT)
    {
      SetSpectrumInfo(inputFileReader->GetWattSpectrum(i));
      // Gotta calculate the amplitude.
      spectrumInfo.data[3] = 2*exp(-1*spectrumInfo.data[1]*spectrumInfo.data[2]/4)/(sqrt((pi*spectrumInfo.data[1]*spectrumInfo.data[1]*spectrumInfo.data[1]*spectrumInfo.data[2])));    
    }
    else if (lineEnergy[0] == GAUSSIAN)
    {
      SetSpectrumInfo(inputFileReader->GetGaussianSpectrum(i));
      spectrumInfo.data[3] = 0;    
    }
    else if (lineEnergy[0] == MAXWELLIAN)
    {
      SetSpectrumInfo(inputFileReader->GetMaxwellianSpectrum(i));
      // incomplete  
    }
    else
    {
      SpectrumInfo tempSpectrumInfo;
      tempSpectrumInfo.data[0] = 0;
      tempSpectrumInfo.data[1] = 0;
      tempSpectrumInfo.data[2] = 0;
      tempSpectrumInfo.data[3] = 0;
      SetSpectrumInfo(tempSpectrumInfo);
    }

    SetLineProbability(inputFileReader->GetSourceEnergyProbability(i));

    SetEnergyRandom(false);
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEISource::SetParticle(G4int inParticle)
{
  if (inParticle == GAMMA)
  {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    particle = particleTable->FindParticle(particleName="gamma");
  }
  else if (inParticle == NEUTRON)
  {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    particle = particleTable->FindParticle(particleName="neutron");
  }
  else
  {
    message = "I literally can't make this particle. Get your life together.";
    G4Exception("TEISource::SetParticle", "Particle Unknown", FatalException, message);
  }
}



/*
if (sourceLineEnergy[lineIndex] == WATT)
        {
          // Brute force rejection method for watt spectrum. 
          tempEnergy = G4UniformRand()*15;
          tempHeight = G4UniformRand()*sourceSpectrumInfo[lineIndex]->data[3];
          while (tempHeight > (sourceSpectrumInfo[lineIndex]->data[3]*exp(-tempEnergy/sourceSpectrumInfo[lineIndex]->data[1])*sinh(sqrt(sourceSpectrumInfo[lineIndex]->data[2]*tempEnergy))))
          {
            tempEnergy = G4UniformRand()*15;
            tempHeight = G4UniformRand()*sourceSpectrumInfo[lineIndex]->data[3];
          }
          tempEnergy = tempEnergy*MeV;
          particleGun->SetParticleEnergy(tempEnergy);
        }
*/
