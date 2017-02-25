// Niral Shah 
// 662 keV gamma source with stilbene and a single tungsten panel.
// SpectrumInfo

#ifndef TEISpectrumInfo_h
#define TEISpectrumInfo_h 1

#include "G4ThreeVector.hh"

struct SpectrumInfo
{
  G4double data[4];
};
// data[0] tell us what type of spectrum. Refer to TEIConstants
// data[1] is the first coefficient
// data[2] is the second.
// data[3] is the third. 
#endif

// https://arxiv.org/pdf/1410.1769.pdf - Watt parameters for the los alamos model
// http://web.ornl.gov/~webworks/cppr/y2001/rpt/109646_.pdf - MCNP-DSP Users Manual
// http://web.mit.edu/22.54/ProblemSets/ps1.pdf - Problem set 1: Beginning to use MCNP
// https://mit-crpg.github.io/openmc/methods/physics.html#maxwell
// http://www.nucleonica.net/wiki/images/8/89/mcnpvoli.pdf - page H-3

// For PROMPTGAMMAFISSION
// Name	              Equation	                          Range	      Area	  Fraction      CDF
// Generic            N(E) = a*exp(-b*E)
// First Exponential	N(E) = 38.13*(E-0.085)*exp(1.648*E)	0.085-0.3	  1.28833	0.1536592668  0.1536592668
// Second Exponential	N(E) = 26.8*exp(-2.30*E)	          0.3-1	      4.67622	0.5577332953  0.7113925621
// Third Exponential	N(E) = 8.0*exp(-1.10*E)	            1-8	        2.41978	0.2886074379  1

// To calculate the equations in primaryGeneratorAction, use this methodology. For First Exponential:
// In wolfram alpha, type integrate from (lowerRangeBound) to y a/area*fraction*exp(-b*E). Click on the resulting equation which is somehting like c1-c2*exp(-b*y). Now add it by the CDF of the exponential before it. So thats c1-c2*exp(-b*y)+CDF(i-1). For the SecondExponential it should be 0.697068-1.38976*e^(-2.3*y)+0.1536592668. Then type, solve for y x=0.697068-1.38976*e^(-2.3*y)+0.1536592668. x in this case is the random variable that is betwee 0.1536 to 0.711. y is the energy of the gamma. In this case, the solution is tempEnergy = 0.434783*log(-76564700/(55092024*tempDouble-46868287)).
