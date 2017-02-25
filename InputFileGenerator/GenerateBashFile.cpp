// Niral Shah
// 8/11/16
// Generates a bash file for running the rotations.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "GenerateBashFile.h"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool GenerateBashFile(string bashFileName, string fileName)
{
  string message = "./TEI";
  ofstream bashFile;
  
  bashFile.open(bashFileName.c_str(), std::ios::app);
  
  if (bashFile.fail())
  {
    cout << "In GenerateBashFile. bashFile failed to open." << endl << flush;
    return(false);
  }
  
  message = message + " " + fileName + ".txt";
  bashFile << message << endl;
  bashFile.close();
  
  return(true);
}
  
