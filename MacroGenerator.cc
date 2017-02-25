// Niral Shah
// Generates macro files based on an input macro file and number of desired macro files

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <sstream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace patch
{
  template < typename T > std::string to_string ( const T& n )
  {
    ostringstream stm;
    stm << n;
    return stm.str();
  }
}
   
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

int main(int argc, char** argv)
{

  int workers;
  string templateFileName = "temp";
  ifstream templateFile;
  string outputFileName;
  ofstream outputFile;
  string tempLine;
  string seedLine = "/random/setSeeds";
  
  if (argc == 1)
  {
    cout << "Need template macro file. Cannot continue." << endl;
    exit(1);
  }
  else if (argc == 2)
  {
    templateFileName = string(argv[1]);
    workers = 16;
  }
  else if (argc == 3)
  {
    templateFileName = string(argv[1]);
    workers = atoi(argv[2]);
  }
  else
  {
    cout << "Too many arguments. Cannot continue." << endl;
    exit(1);
  }
  
  int place = 0;
  for (int i = 1; i <= workers; i++)
  {
    templateFile.open(templateFileName.c_str());
    if (templateFile.fail())
    {
      cout << "Unable to open template file. Perhaps the extension wasn't included." << endl;
      exit(1);
    }
    outputFileName = templateFileName + patch::to_string(i);
    outputFile.open(outputFileName.c_str());
    
    place = templateFile.tellg();
    int j = 0;
    while ((!templateFile.eof()) || (!templateFile.fail()))
    {
      // cout << j << endl;
      if (templateFile.fail())
      {
        cout << "Failed while writing to output." << endl;
        exit(1);
      }
      
      templateFile.seekg(place);
      getline(templateFile, tempLine, ' ');
     
      if (tempLine == seedLine)
      {
        tempLine = tempLine + " " + patch::to_string(i) + " " + patch::to_string(i);
        outputFile << tempLine << "\n";
        getline(templateFile, tempLine);
      }
      else
      {
        templateFile.seekg(place);
        getline(templateFile, tempLine);
        outputFile << tempLine << "\n";
      }
      place = templateFile.tellg();
      templateFile >> tempLine;
      j++;
    }
    templateFile.close();
    outputFile.close();
  }
      
    
  
  
  
  
}
    
