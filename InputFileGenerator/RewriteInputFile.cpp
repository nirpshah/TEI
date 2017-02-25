// Niral Shah
// 8/11/16
// RewriteInputFile
// Takes in four inputs. First is the name of the input file, second si the name of the output file, third is the string to search for and fourth is the partial string that needs to replace it

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

#include "Constants.h"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool RewriteInputFile(string inputFileName, string outputFileName, string searchTerm, string replaceTerm)
{  
  ifstream inputFile;
  inputFile.open(inputFileName.c_str());
  
  ofstream outputFile;
  string outputFileName2 = outputFileName + ".txt";
  outputFile.open(outputFileName2.c_str());
  
  if (inputFile.fail())
  {
    cout << "In RewriteInputFile. inputFile.open() failed" << endl << flush;
    return(false);
  }
  
  if (outputFile.fail())
  {
    cout << "In RewriteInputfile. outputFile.open() failed" << endl << flush;
    return(false);
  }
  
  bool searchTermFound = false;
  bool outputFileNameFound = false;
  bool headerFileNameFound = false;
  string tempLine;
  stringstream tempStream;
  string tempString;
  
  while ((!(inputFile.eof())) && (!(inputFile.fail())))
  {
    tempStream.clear();
    tempStream.str("");
    getline(inputFile, tempLine, '\n');
    tempStream << tempLine;
    tempStream >> tempString;
    //cout << tempString << endl << flush;

    if (tempString == searchTerm)
    {
      searchTermFound = true;
      outputFile << left << setw(NUMBEROFSPACES) << searchTerm << replaceTerm << endl;
    }
    else if (tempString == "outputFileName")
    {
      outputFileNameFound = true;
      tempString = outputFileName + ".data";
      outputFile << left << setw(NUMBEROFSPACES) << "outputFileName" << tempString << endl;
    }
    else if (tempString == "headerFileName")
    {
      headerFileNameFound = true;
      tempString = outputFileName + ".head";
      outputFile << left << setw(NUMBEROFSPACES) << "headerFileName" << tempString << endl;
    }
    else
    {
      outputFile << tempLine << endl;
    }
    tempString.clear();
  }
  
  if (!searchTermFound)
  {
    cout << "In RewriteInputFile. searchTerm was not found." << endl << flush;
    return(false);
  }
  
  if (!outputFileNameFound)
  {
    cout << "In RewriteInputFile. outputFileName was not found." << endl << flush;
    return(false);
  }
  
  if (!headerFileNameFound)
  {
    cout << "In RewriteInputFile. headerFileName was not found." << endl << flush;
    return(false);
  }
  
  inputFile.close();
  outputFile.close();
 
  return(true);
}
  
  
  
  
  
  
  
