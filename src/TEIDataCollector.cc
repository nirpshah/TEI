// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// DataCollector
// DataCollector holds a deque that holds TEIEventDataMember objects that hold all the data from each event. 

#include "TEIDataCollector.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

#include <ctime>
#include <mutex>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

namespace 
{
  G4Mutex TEIDataCollectorMutex = G4MUTEX_INITIALIZER; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

// Default constructor uses the system time to create a unique file name
TEIDataCollector::TEIDataCollector()
{ 
  inputFileReader = TEIInputFileReader::Instance();
  timingCollector = TEITimingCollector::Instance();
  // G4cout << G4endl << G4endl <<  "***** In TEIDataCollector::TEIDataCollector *****" << G4endl << G4endl << G4endl;
  rawStartTime = time(nullptr);
  char* formattedTime = ctime(&rawStartTime);
  
  // At the end of formatted time, there is a newline character so I just pop that off.
  outputFileName = "Output: " + string(formattedTime);
  outputFileName.pop_back();
  outputFileName = outputFileName + ".txt";
  headerFileName = "Header: " + string(formattedTime);
  headerFileName.pop_back();
  headerFileName = headerFileName + ".txt";
  startTime = string(formattedTime);
  startTime.pop_back();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

TEIDataCollector::~TEIDataCollector()
{ ;} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void TEIDataCollector::SetOutputFileName(G4String inOutputFileName)
{
  outputFileName = inOutputFileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4String TEIDataCollector::GetOutputFileName()
{
  return(outputFileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void TEIDataCollector::SetHeaderFileName(G4String inHeaderFileName)
{
  headerFileName = inHeaderFileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4String TEIDataCollector::GetHeaderFileName()
{
  return(headerFileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void TEIDataCollector::CollectData(TEIEventDataMember* inEventDataMember)
{
  // In each event, if there was a hit, an eventDataMember is created and filled with relevant info. The pointer to the data is sent here and stored for future reference. Since all threads report here, this must be mutex locked.
  G4AutoLock l(&TEIDataCollectorMutex);
  l.lock();
  // G4cout << G4endl << G4endl << "***** In TEIDataCollector::CollectData *****" << G4endl << G4endl << G4endl;
  simData.push_back(inEventDataMember);
  l.unlock();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void TEIDataCollector::PrintData()
{
  // G4cout << G4endl << G4endl << "***** In TEIDataCollector::PrintData() *****" << G4endl << G4endl << G4endl;
  // Printing is handled at the specific dataMemberLevel.
  TEIEventDataMember* tempDataMember;
  G4int size = simData.size();;

  for(G4int i = 0; i < size; i++)
  {
    tempDataMember = simData.front();
    tempDataMember->PrintData(outputFileName);
    simData.pop_front();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void TEIDataCollector::PrintHeader()
{
  // G4cout << G4endl << G4endl << "***** In TEIDataCollector::PrintHeader() *****" << G4endl << G4endl << G4endl;
  ofstream headerFile;
  headerFile.open(headerFileName, std::ios_base::app);
  headerFile << "Start Time: " << startTime << G4endl << "End Time: " << endTime << G4endl;
  headerFile.close();
  
  G4int size = simData.size();
  if (!size)
  {
    headerFile.open(headerFileName, std::ios_base::app);
    headerFile << "No events were recorded. " << G4endl;
  }
  else
  {
    simData.front()->PrintHeader(headerFileName);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void TEIDataCollector::SetStartTime()
{
  time_t t = time(nullptr);
  char* formattedTime = ctime(&t);
  startTime = string(formattedTime);
  startTime.pop_back();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void TEIDataCollector::SetEndTime()
{
  time_t t = time(nullptr);
  char* formattedTime = ctime(&t);
  endTime = string(formattedTime);
  endTime.pop_back();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
