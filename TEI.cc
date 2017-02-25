// Niral Shah
// This is the TEI system. In case you don't know, TEI is time encoded imaging where a mask is rotated around a detector. If there is a radiation source in the area, the count rate seen by the detector will change in time as mask elements go in front of it.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIDetectorConstruction.hh"     // You will define your geometry here
#include "TEIActionInitialization.hh"     // This will include all of the potential actions
#include "TEIDataCollector.hh"            // This will collect all of the data and print it to the outputFile
#include "TEIInputFileReader.hh"          // The input file reader. You MUST have an input file.
#include "TEIInitializePhysicsList.hh"    // This creates the physics list
#include "TEITimingCollector.hh"

#ifdef G4MULTITHREADED                    
#include "G4MTRunManager.hh"              // The multithreaded manager
#else
#include "G4RunManager.hh"                // The normal manager. You may only have one at a time
#endif

#include "G4UImanager.hh"                 // UI Managers             
#include "G4VisExecutive.hh"              
#include "G4UIExecutive.hh"               
#include "Randomize.hh"                   // To choose the random number engine

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <mutex>                          // For multithreading

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// You MUST provide a input file. There is no default option. If for some reason you have lost the input file, refer to the inputFileReader.
int main(int argc, char** argv)
{
  // For error handling
  G4String message;
  
  // Report the start time
  time_t startT = time(nullptr);        // Time is measured in seconds since 1970 or some shit like that
  char* formattedTime = ctime(&startT); // This formats the time to something more useful. Note that there is an endline charater already attached to it.  
  G4cout << G4endl << "Start Time: " << string(formattedTime) << G4endl;
  
  // Data Collector. When constructed, it already sets the outputFileName according to system time.
  TEIDataCollector* dataCollector = new TEIDataCollector();
  
  if (argc == 1)
  {
    message = "No input file provided. You must provide an input file, no exceptions. Check the repository for a simulation that will work without an input file." ;
    G4Exception("main", "No Input File", FatalException, message);
  }
  else if (argc > 2)
  {
    message = "Only one input allowed which is the inputFileName. Inputs: ";
    for (G4int i = 0; i < argc; i++)
    {
      message = message + argv[i] + " ";
    }
    G4Exception("main", "Too many Inputs", FatalException, message);
  }

  G4String inputFileName = string(argv[1]);
  TEIInputFileReader* inputFileReader =  TEIInputFileReader::Instance();     
  inputFileReader->ReadInputFile(inputFileName);
  TEITimingCollector* timingCollector = new TEITimingCollector();
  
  if (!(inputFileReader->GetCollectTimes()))
  {
    timingCollector = NULL;
  }

  G4UIExecutive* ui = 0;
  // "ui" for the macroFileName means the use wants the interactive method.
  if (inputFileReader->GetMacroFileName() == "ui")
  { 
    ui = new G4UIExecutive(argc, argv);
  }
    
  // Choose the random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);        
  
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(inputFileReader->GetNumberOfThreads());
#else
  G4RunManager* runManager = new G4RunManager();
#endif

  // Detector Construction
  runManager->SetUserInitialization(new TEIDetectorConstruction);

  // Physics List
  InitializePhysicsList(runManager);
  
  // User Action Initialization
  // If an output file was specified, great! use it, if not, use system time to 
  // create a unique output file.
  // If the input for the outputFileName is not "auto" then change the outputFileName
  if (!((inputFileReader->GetOutputFileName()) == " "))
  {
    dataCollector->SetOutputFileName(inputFileReader->GetOutputFileName());
  }
  
  runManager->SetUserInitialization(new TEIActionInitialization(dataCollector));

  G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
  
  // Get the pointer to the user interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  // Either run from the macro file or run from the UI. If the ui is still null, then we use a macro file.
  if (!ui) // Using a macro file
  {
    if (inputFileReader->GetCollectTimes())
    {
      timingCollector->MarkTime("Before runs");
    }
    G4String command = "/control/execute ";
    G4String fileName = inputFileReader->GetMacroFileName();
    UImanager->ApplyCommand(command+fileName);
    runManager->BeamOn(inputFileReader->GetNumberOfEvents());
    delete ui;      // I'm not 100% certain this is supposed to be here since there isn't a delete in the B1 example
    if (inputFileReader->GetCollectTimes())
    {
    timingCollector->MarkTime("After runs");
    }
  }
  else    // Using an interactive session
  {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  time_t endT = time(nullptr);
  formattedTime = ctime(&endT);
  G4cout << G4endl << "End Time: " << string(formattedTime) << G4endl;
  dataCollector->SetEndTime();
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Right before printing the output file");
  }
  dataCollector->PrintHeader();
  
  // Print all data to outputFile
  dataCollector->PrintData();
  if (inputFileReader->GetCollectTimes())
  {
    timingCollector->MarkTime("Right after printing the output file");
    timingCollector->PrintTime("times.txt");
  }
  
  // Job termination. Free the store: user actions, physics_list, detector_description are owned and deleted by the run manager, so they should not be deleted in the main() program!

  delete visManager;
  delete runManager;
  delete dataCollector;
  delete timingCollector;
  
  // Report the end time
  
}

