// Niral Shah 
// TEI
// PhysicsList

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIPhysicsList.hh"
#include "TEIInputFileReader.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4EmParameters.hh"
#include "G4LossTableManager.hh"
#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4UserSpecialCuts.hh"

// Transportation for all particles
#include "G4Transportation.hh"

// Gamma Processes
#include "G4GammaConversion.hh"
#include "G4ComptonScattering.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4PhotoNuclearProcess.hh"
#include "G4CascadeInterface.hh"

// Electron Processes
#include "G4eMultipleScattering.hh"
// #include "G4WentzelVIModel.hh"
// #include "G4UrbanMscModel.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"

// Positron Processes
// #include "G4MultipleScattering.hh"
// #include "G4eIonisation.hh"
// #include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

// Proton Processes
// #include "G4MultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4HadronElasticProcess.hh"
#include "G4HadronElasticDataSet.hh"
#include "G4LEHadronProtonElastic.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"

// Neutron Processes
// #include "G4HadronElasticProcess.hh"
#include "G4HadronElasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
// #include "G4NeutronCaptureAtRest.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPThermalScatteringData.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4NeutronHPFission.hh"
#include "G4NeutronHPFissionData.hh"

// Generic Ion Processes
// #include "MultipleScattering.hh"
#include "G4ionIonisation.hh"
// #include "G4HadronElasticProcess"
#include "G4NuclNuclDiffuseElastic.hh"
#include "G4ComponentGGNuclNuclXsc.hh"
#include "G4CrossSectionElastic.hh"
#include "G4IonInelasticProcess.hh"
#include "G4TripathiCrossSection.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4EmModelActivator.hh"
// #include "G4RadioactiveDecay.hh"
// #include "G4NuclideTable.hh"
// #include "G4IonConstructor.hh"

// Particles
// #include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4GenericIon.hh"

#include <deque>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIPhysicsList::TEIPhysicsList(G4int inVerboseLevel)
  : G4VUserPhysicsList()
{
  SetVerboseLevel(inVerboseLevel);
  gammaCreated      = false;
  electronCreated   = false;
  positronCreated   = false;
  protonCreated     = false;
  neutronCreated    = false;
  genericIonCreated = false;
  
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIPhysicsList::~TEIPhysicsList()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIPhysicsList::ConstructParticle()
{
  G4int size;
  G4String tempString;
  size = inputFileReader->GetParticle().size();
  for (int i = 0; i < size; i++)
  {
    tempString = inputFileReader->GetParticle(i);
 
    // Bosons
    if (tempString == "gamma")
    {
      G4Gamma::Gamma();
      gammaCreated = true;
    }
    // Leptons
    else if (tempString == "electron")
    {
      G4Electron::Electron();
      electronCreated = true;
    }
    else if (tempString == "positron")
    {
      G4Positron::Positron();
      positronCreated = true;
    }
    // Baryons
    else if (tempString == "proton")
    {
      G4Proton::Proton();
      protonCreated = true;
    }
    else if (tempString == "neutron")
    {
      G4Neutron::Neutron();
      neutronCreated = true;
    }
    // Ions
    else if (tempString == "genericIon")
    {
      G4GenericIon::GenericIon();
      // G4IonConstructor iConstructor;
      // iConstructor.ConstructParticle();
      
      genericIonCreated = true;
    }
    else
    {
      G4String message = "G4 attempted to make particle '" + tempString + "' but it isn't allowed.";
      G4Exception("TEIPhysicsList::ConstructParticle()", "Invalid Particle", JustWarning, message);
    }
  }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIPhysicsList::ConstructProcess()
{ 
  G4String message;
  G4int i;
  G4int size;
  G4String tempString;
  AddTransportation();
  theParticleIterator->reset();
  while ((*theParticleIterator)())
  {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* processManager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    // G4ProcessVector* processVector = processManager->GetProcessList();
    // G4cout << particleName << ": " << processVector->entries() << G4endl << std::flush;
    
    if ((particleName == "gamma") && (gammaCreated))
    {
      size = inputFileReader->GetGammaProcess().size();
      for (i = 0; i < size; i++)
      {
        tempString = inputFileReader->GetGammaProcess(i);
        
        if (tempString == "photoElectricEffect")
        { 
          processManager->AddDiscreteProcess(new G4PhotoElectricEffect()); 
        }
        else if (tempString == "comptonScattering")
        {
          processManager->AddDiscreteProcess(new G4ComptonScattering());
        }
        else if (tempString == "pairProduction")
        {
          processManager->AddDiscreteProcess(new G4GammaConversion());
        }
        else if (tempString == "inelasticScattering")
        {
          G4PhotoNuclearProcess* photoNuclearProcess = new G4PhotoNuclearProcess();
          
          G4CascadeInterface* bertiniModel = new G4CascadeInterface();
          photoNuclearProcess->RegisterMe(bertiniModel);
          
          processManager->AddDiscreteProcess(photoNuclearProcess);
        }
        else
        {
          message = "For particle '" + particleName + "', process '" + tempString + "' does not have a description.";
          G4Exception("TEIPhysicsList::ConstructProcess()", "Invalid Process", JustWarning, message);
        }
      }
    }
    else if ((particleName == "e-") && (electronCreated))
    {
      size = inputFileReader->GetElectronProcess().size();
      for (i = 0; i < size; i++)
      {
        tempString = inputFileReader->GetElectronProcess(i);
        
        if (tempString == "multipleScattering")
        { 
          processManager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
        }
        else if (tempString == "ionisation")
        {
          processManager->AddProcess(new G4eIonisation(),        -1, 2, 2);
        }
        else if (tempString == "bremsstrahlung")
        {
          processManager->AddProcess(new G4eBremsstrahlung(),    -1, 3, 3);
        }
        else
        {
          message = "For particle '" + particleName + "', process '" + tempString + "' does not have a description.";
          G4Exception("TEIPhysicsList::ConstructProcess()", "Invalid Process", JustWarning, message);
        }
      }
    }
    else if ((particleName == "e+") && (positronCreated))
    {
      size = inputFileReader->GetPositronProcess().size();
      for (i = 0; i < size; i++)
      {
        tempString = inputFileReader->GetPositronProcess(i);
        
        if (tempString == "multipleScattering")
        { 
          processManager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
        }
        else if (tempString == "ionisation")
        {
          processManager->AddProcess(new G4eIonisation(),         -1, 2, 2);
        }
        else if (tempString == "bremsstrahlung")
        {
          processManager->AddProcess(new G4eBremsstrahlung(),     -1, 3, 3);
        }
        else if (tempString == "annihilation")
        {
          processManager->AddProcess(new G4eplusAnnihilation(),    1,-1, 4);
        }
        else
        {
          message = "For particle '" + particleName + "', process '" + tempString + "' does not have a description.";
          G4Exception("TEIPhysicsList::ConstructProcess()", "Invalid Process", JustWarning, message);
        }
      }
    }
    else if ((particleName == "proton") && (protonCreated))
    {
      size = inputFileReader->GetProtonProcess().size();
      for (i = 0; i < size; i++)
      {
        tempString = inputFileReader->GetProtonProcess(i);
        
        if (tempString == "multipleScattering")
        { 
          processManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
        }
        else if (tempString == "ionisation")
        {
          processManager->AddProcess(new G4hIonisation(),        -1, 2, 2);
        }
        else if (tempString == "elasticScattering")
        {
          G4HadronElasticProcess* protonElasticProcess = new G4HadronElasticProcess();
          
          G4HadronElasticDataSet* protonElasticDataSet = new G4HadronElasticDataSet();
          protonElasticProcess->AddDataSet(protonElasticDataSet);
          
          G4LEHadronProtonElastic* protonElasticModel = new G4LEHadronProtonElastic();
          protonElasticProcess->RegisterMe(protonElasticModel);
          
          processManager->AddDiscreteProcess(protonElasticProcess);;
        }
        else if (tempString == "inelasticScattering")
        {
          //http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch05s02.html
          G4ProtonInelasticProcess* protonInelasticProcess = new G4ProtonInelasticProcess();
          
          G4ExcitationHandler* excitationHandler = new G4ExcitationHandler();
          G4PreCompoundModel* preCompoundModel = new G4PreCompoundModel(excitationHandler);
          
          protonInelasticProcess->RegisterMe(preCompoundModel);
          
          processManager->AddDiscreteProcess(protonInelasticProcess);
        }
        else
        {
          message = "For particle '" + particleName + "', process '" + tempString + "' does not have a description.";
          G4Exception("TEIPhysicsList::ConstructProcess()", "Invalid Process", JustWarning, message);
        }
      }
    }
    else if ((particleName == "neutron") && (neutronCreated))
    {
      size = inputFileReader->GetNeutronProcess().size();
      for (i = 0; i < size; i++)
      {
        tempString = inputFileReader->GetNeutronProcess(i);
        
        if (tempString == "elasticScattering")
        { 
          G4HadronElasticProcess* neutronElasticProcess = new G4HadronElasticProcess();
          
          G4NeutronHPElasticData* HPElasticData = new G4NeutronHPElasticData();
          neutronElasticProcess->AddDataSet(HPElasticData);
          
          G4NeutronHPElastic* neutronElasticModel = new G4NeutronHPElastic;
          neutronElasticProcess->RegisterMe(neutronElasticModel);
          
          processManager->AddDiscreteProcess(neutronElasticProcess);
        }
        else if (tempString == "inelasticScattering")
        {
          G4NeutronInelasticProcess* neutronInelasticProcess = new G4NeutronInelasticProcess();
          
          G4NeutronHPInelasticData* neutronHPInelasticData = new G4NeutronHPInelasticData();
          neutronInelasticProcess->AddDataSet(neutronHPInelasticData);
          
          G4NeutronHPInelastic* neutronHPInelastic = new G4NeutronHPInelastic();
          neutronInelasticProcess->RegisterMe(neutronHPInelastic);
          
          processManager->AddDiscreteProcess(neutronInelasticProcess);
        }
        else if (tempString == "capture")
        {
          G4HadronCaptureProcess* neutronCaptureProcess = new G4HadronCaptureProcess();
          
          G4NeutronHPCaptureData* neutronHPCaptureData = new G4NeutronHPCaptureData();
          neutronCaptureProcess->AddDataSet(neutronHPCaptureData);
          
          G4NeutronHPCapture* neutronHPCapture = new G4NeutronHPCapture();
          neutronCaptureProcess->RegisterMe(neutronHPCapture);
          
          processManager->AddDiscreteProcess(neutronCaptureProcess);
        }
        else if (tempString == "fission")
        {
          G4HadronFissionProcess* neutronFissionProcess = new G4HadronFissionProcess();
          
          G4NeutronHPFissionData* neutronHPFissionData = new G4NeutronHPFissionData();
          neutronFissionProcess->AddDataSet(neutronHPFissionData);
          
          G4NeutronHPFission* neutronHPFission = new G4NeutronHPFission();
          neutronFissionProcess->RegisterMe(neutronHPFission);
          
	        processManager->AddDiscreteProcess(neutronFissionProcess);
        }
        else
        {
          message = "For particle '" + particleName + "', process '" + tempString + "' does not have a description.";
          G4Exception("TEIPhysicsList::ConstructProcess()", "Invalid Process", JustWarning, message);
        }
      }    
      // G4NeutronCaptureAtRest* natrestProc = new G4NeutronCaptureAtRest();
	    // processManager->AddRestProcess(natrestProc);
	    processManager->AddProcess(new G4UserSpecialCuts(),-1,-1,1);
    }
    else if ((particleName == "GenericIon") && (genericIonCreated))
    {
      size = inputFileReader->GetGenericIonProcess().size();
      for (i = 0; i < size; i++)
      {
        tempString = inputFileReader->GetGenericIonProcess(i);
        
        if (tempString == "multipleScattering")
        { 
          processManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
        }
        else if (tempString == "ionisation")
        {
          processManager->AddProcess(new G4ionIonisation(),-1, 2, 2);
        }
        /*else if (tempString == "elasticScattering")
        {
          G4HadronElasticProcess* hadElastProc = new G4HadronElasticProcess("ionElastic");
          G4NuclNuclDiffuseElastic* ionElastic = new G4NuclNuclDiffuseElastic;
          ionElastic->SetMinEnergy(0.0);
          hadElastProc->RegisterMe(ionElastic);
          
          G4ComponentGGNuclNuclXsc* ionElasticXS = new G4ComponentGGNuclNuclXsc;
          G4VCrossSectionDataSet* ionElasticXSDataSet = new G4CrossSectionElastic(ionElasticXS);
          ionElasticXSDataSet->SetMinKinEnergy(0.0);
          hadElastProc->AddDataSet(ionElasticXSDataSet);
	        // hadElastProc->RegisterMe(elasticModel);
	        processManager->AddDiscreteProcess(hadElastProc);
        }
        else if (tempString == "inelasticScattering")
        {
          G4TripathiCrossSection* tripathiData = new G4TripathiCrossSection();
          G4IonInelasticProcess* ionProc = new G4IonInelasticProcess();
	        ionProc->AddDataSet(tripathiData);
	        processManager->AddDiscreteProcess(ionProc);
        }*/
        /*else if (tempString == "radioactiveDecay")
        {
          G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
          radioactiveDecay->SetARM(false);
          G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper(); 
          ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
          // processManager->AddProcess(radioactiveDecay);
          G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*picosecond);
          G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*eV);
        }*/
        else
        {
          message = "For particle '" + particleName + "', process '" + tempString + "' does not have a description.";
          G4Exception("TEIPhysicsList::ConstructProcess()", "Invalid Process", JustWarning, message);
        }
      }
    }
    else
    {
      if (verboseLevel > 0)
      {
        message = "G4 attempted to make processes for particle '" + tempString + "' but it isn't allowed.";
        G4Exception("TEIPhysicsList::ConstructProcess()", "Invalid Particle Process", JustWarning, message);
      }
    }
  }
  
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);

  G4EmModelActivator mact;
  mact.ConstructProcess();
}
      
void TEIPhysicsList::SetCuts()
{
  SetDefaultCutValue(inputFileReader->GetDefaultProductionRangeCut());
  if (gammaCreated)
  { 
    SetCutValue(inputFileReader->GetGammaProductionRangeCut(), "gamma");
  }
  if (neutronCreated)
  {
    SetCutValue(inputFileReader->GetNeutronProductionRangeCut(), "neutron");
  }
}

