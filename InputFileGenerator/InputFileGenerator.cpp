// Niral Shah
// 8/11/16
// Generates input files based on desired changes. It needs a seed input file.
// g++ InputFileGenerator.cpp RewriteInputFile.cpp GenerateBashFile.cpp -o InputFileGenerator

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define _USE_MATH_DEFINES

#include "RewriteInputFile.h"
#include "GenerateBashFile.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <ios>
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
  string inputFileName = "TEIInputFile.txt";
  string outputFileNameSeed = "URA_35_PW_30_MT_1_Tung_g_662";
  string bashFileName = "URA_35_PW_30_MT_1_Tung_g_662";
  
  bool rotateMask = true;
  double rotationRange[2] = {1, 360}; // Keep it in degrees
  double rotationResolution = 1;      // Keep it in degrees
  
  string outputFileName;
  string searchTerm;
  string replaceTerm;
  
  if (rotateMask)
  {
    string searchTerm = "maskRotationAngle";
    int numberOfRotations = (rotationRange[1] - rotationRange[0])/rotationResolution + 1;
    for (int i = 0; i < numberOfRotations; i++)
    {
      outputFileName = outputFileNameSeed + "_" + patch::to_string(((i*rotationResolution)+rotationRange[0]));
      replaceTerm = patch::to_string(((i*rotationResolution)+rotationRange[0]));
      RewriteInputFile(inputFileName, outputFileName, searchTerm, replaceTerm);
      GenerateBashFile(bashFileName, outputFileName);
    }
  }
  else
  {
    string searchTerm = "sourcePosition";
    for (int i = -10; i <= 10; i++)
    {
      outputFileName = outputFileNameSeed + patch::to_string(i*0.125*1000);
      replaceTerm = "299 " + patch::to_string(i*0.125) + " 0";
      RewriteInputFile(inputFileName, outputFileName, searchTerm, replaceTerm);
    }
  }
  return(0);
}
