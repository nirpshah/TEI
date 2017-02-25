// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// Constants

#ifndef TEIConstants_h
#define TEIConstants_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const int UNKNOWN = 0;  
const int GAMMA = 1;
const int ELECTRON = 2;
const int POSITRON = 3;
const int PROTON = 4;
const int NEUTRON = 5;
const int GENERIC_ION = 6;
const int C12 = 7;
const int C13 = 8;

const int WATT = -1;
const int GAUSSIAN = -2;
const int MAXWELLIAN = -3;
const int PROMPT_FISSION_GAMMA = -4;

// If you change the PFG exponential functions, you have to change the distributions in PrimaryGeneratorAction
const double PROMPT_FISSION_GAMMA_FIRST_EXPONENTIAL = 0.1536592668;
const double PROMPT_FISSION_GAMMA_SECOND_EXPONENTIAL = 0.7113925621;
const double PROMPT_FISSION_GAMMA_THIRD_EXPONENTIAL = 1;

const int CIRCLE = 10;
const int SQUARE = 11;

// const int RADIOACTIVEDECAY = -10;

//const int GPHOTOELECTRICEFFECT = 10;
//const int GCOMPTONSCATTERING = 11;
//const int GPAIRPRODUCTION = 12;

//const int EMULTIPLESCATTERING = 20;
//const int EIONISATION = 21;
//const int EBREMSSTRAHLUNG = 22;
//const int ECOULOMBSCATTERING = 23;

//const int PMULTIPLESCATTERING = 30;
//const int PIONISATION = 31;
//const int PBREMSSTRAHLUNG = 32;
//const int PANNIHILATION = 33;
//const int PCOULOMBSCATTERING = 34;

//const int HMULTIPLESCATTERING = 40;
//const int HIONISATION = 41;
//const int HELASTICSCATTERING = 42;
//const int HINELASTICSCATTERING = 43;

//const int NELASTICSCATTERING = 50;
//const int NINELASTICSCATTERING = 51;
//const int NCAPTURE = 52;
//const int NFISSION = 53;

//const int GIMULTIPLESCATTERING = 60;
//const int GIIONISATION = 61;
//const int GIELASTICSCATTERING = 62;
//const int GIINELASTICSCATTERING = 63;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
