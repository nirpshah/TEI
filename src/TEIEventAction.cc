// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// TEIEventAction

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TEIEventAction.hh"
#include "TEIDetectorHit.hh"
#include "TEIDataCollector.hh"
#include "TEIEventDataMember.hh"
#include "TEIInputFileReader.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4Threading.hh"

#include <iomanip>
using namespace std;

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIEventAction::TEIEventAction(TEIDataCollector* inDataCollector) : G4UserEventAction(), detectorHCID(-1)
{ 
  dataCollector = inDataCollector;
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
  updateEventNumber = 0;
  numberOfBars = 0;
  numberOfEvents = inputFileReader->GetNumberOfEvents();
  createBar = true;
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  colSize = size.ws_col;
  offset = 0;
  progressBar = inputFileReader->GetProgressBar();
  if (inputFileReader->GetMacroFileName() == "ui")
  {
    progressBar = false;
  }
  else if (G4Threading::IsWorkerThread())
  {
    if (G4Threading::G4GetThreadId() != 0)
    {
      progressBar = false;
    }
    else
    {
      offset = 8;
    }
  }
  else
  {
    offset = 0;
  }
  
  seconds[0] = 0;
  seconds[1] = 0;
  minutes[0] = 0;
  minutes[1] = 0;
  hours[0] = 0;
  hours[1] = 0;
  startTime = time(nullptr);
  message = new char [(colSize + 1 - offset)];
  barSize = size.ws_col - 19 - offset;
  CreateBar();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIEventAction::TEIEventAction() : G4UserEventAction()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TEIEventAction::~TEIEventAction()
{ ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIEventAction::BeginOfEventAction(const G4Event* event)
{ 
  // Alright. So basically, it gives the detector its ID which can only happen after everything is made so its here.
  // Then we go into the updating/making of the progress bar. First is whether or not this thread or simulation should be making a progress bar. If yes, check if its time to update. If it is, add a bar to the message and update time.
  // G4cout << "In TEIEventAction::BeginOfEventAction" << endl;
  if (detectorHCID == -1)
  {
    G4SDManager* SDMan = G4SDManager::GetSDMpointer();
    detectorHCID = SDMan->GetCollectionID("detector/detectorColl");
  }
  
  if (progressBar)
  { 
    G4int eventID = event->GetEventID();
    if (eventID >= updateEventNumber)
    {
      // Adding a bar to the progress bar is just changing the character at the index value
      message[numberOfBars] = '|';
      
      currentTime = time(nullptr);
      timeElapsed = currentTime - startTime;
      endTime = static_cast<G4double>(timeElapsed)/static_cast<G4double>(eventID)*static_cast<G4double>(numberOfEvents);
      // We use a bunch of mods and dividing and changing units to get the time to work out. Read thorugh the code and it shoud work.
      seconds[1] = timeElapsed % 10;
      timeElapsed = timeElapsed - seconds[1];
      seconds[0] = (timeElapsed % 60)/10;
      timeElapsed = timeElapsed - seconds[0]*10;
      
      timeElapsed = timeElapsed/60;
      minutes[1] = timeElapsed % 10;
      timeElapsed = timeElapsed - minutes[1];
      minutes[0] = (timeElapsed % 60)/10;
      timeElapsed = timeElapsed - minutes[0]*10;
      
      timeElapsed = timeElapsed/60;
      hours[1] = timeElapsed % 10;
      timeElapsed = timeElapsed - hours[1];
      hours[0] = timeElapsed/10;
      timeElapsed = timeElapsed - hours[1]*10;
      
      message[barSize+2] = digits[hours[0]];
      message[barSize+3] = digits[hours[1]];
      message[barSize+5] = digits[minutes[0]];
      message[barSize+6] = digits[minutes[1]];
      message[barSize+8] = digits[seconds[0]];
      message[barSize+9] = digits[seconds[1]];
      
      seconds[1] = endTime % 10;
      endTime = endTime - seconds[1];
      seconds[0] = (endTime % 60)/10;
      endTime = endTime - seconds[0]*10;
      
      endTime = endTime/60;
      minutes[1] = endTime % 10;
      endTime = endTime - minutes[1];
      minutes[0] = (endTime % 60)/10;
      endTime = endTime - minutes[0]*10;
        
      endTime = endTime/60;
      hours[1] = endTime % 10;
      endTime = endTime - hours[1];
      hours[0] = endTime/10;
      endTime = endTime - hours[1]*10;
     
      message[barSize+11] = digits[hours[0]];
      message[barSize+12] = digits[hours[1]];
      message[barSize+14] = digits[minutes[0]];
      message[barSize+15] = digits[minutes[1]];
      message[barSize+17] = digits[seconds[0]];
      message[barSize+18] = digits[seconds[1]];
      
      // Push the message out. And then return to the front of the line.
      G4cout << message << "\r" << flush;
      numberOfBars++;
      updateEventNumber = (numberOfBars)*(static_cast<G4double>(numberOfEvents)/static_cast<G4double>(barSize)); 
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TEIEventAction::EndOfEventAction(const G4Event* event)
{
  // G4cout << G4endl << G4endl << "***** In TEIEventAction::EndOfEventAction *****" << G4endl << G4endl << G4endl
  
  // Check if we have a hit
  
  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if (!hce)
  {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found." << G4endl;
    G4Exception("TEIEventAction::EndOfEventAction()",
                "TEICode001", JustWarning, msg);
    return;
  }
  // Get hits collection
  TEIDetectorHitsCollection* detectorHC = 
        static_cast<TEIDetectorHitsCollection*>(hce->GetHC(detectorHCID));
        
  if (!detectorHC)
  {
    G4ExceptionDescription msg;
    msg << "Some of hits collections of this event  not found." << G4endl;
    G4Exception("TEIEventAction::EndOfEventAction()",
                "TEICode001", JustWarning, msg);
    return;
  }
  
  // Data Collection
  // Check if to see if there is anything to collect. The eventDataMember does all of the data collecting
  if (detectorHC->entries())
  {
    TEIEventDataMember* eventDataMember = new TEIEventDataMember(event, detectorHCID);
    dataCollector->CollectData(eventDataMember);
    // G4cout << G4endl << "***** In TEIEventAction::EndOfEventAction *****" << G4endl << G4endl;
    // G4cout << G4endl << G4Threading::G4GetThreadId() << G4endl;
  }
}

void TEIEventAction::CreateBar()
{
  message[0] = '[';
  for (i = 1; i < (barSize); i++)
  {
    message[i] = ' ';
  }
  message[i++] = ']';
  message[i++] = ' ';
  message[i++] = '0';
  message[i++] = '0';
  message[i++] = ':';
  message[i++] = '0';
  message[i++] = '0';
  message[i++] = ':';
  message[i++] = '0';
  message[i++] = '0';
  message[i++] = '/';
  message[i++] = '0';
  message[i++] = '0';
  message[i++] = ':';
  message[i++] = '0';
  message[i++] = '0';
  message[i++] = ':';
  message[i++] = '0';
  message[i++] = '0';
  message[i++] = '\0';
}
 





















//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
