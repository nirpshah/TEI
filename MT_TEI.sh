# Bash file to run Geant4 simulations.
# Here's the plan. Make the TEI file. Make a new directory. Copy the program, the
# input file, and the template macro file to the new directory. 
# Generate all of the other macros
# Run the specified instances of Geant4

#!/bin/bash 

# Make TEI
make -j16
# Unique Directory
time="`date +%s`";
# newDir="Output_$time";
# User input directory
newDir="Sample"
#
mkdir $newDir
#
# Copy the essential files
cp TEI $newDir
cp run.mac $newDir
cp MacroGenerator $newDir
# cp inputFile /$newDir
#
cd $newDir
#
threads=16
g++ MacroGenerator.cc -o MacroGenerator
./MacroGenerator run.mac $threads 
#
i=1
macFile="run.mac"
outFileExt=".go"
let iMax=threads+1;
while [ $i -lt $iMax ];
do
  macFileMT=$macFile$i
  outFileMT=$newDir$i$outFileExt
 # 
  ./TEI $macFileMT $outFileMT &
  let i=i+1
done
exit 0
#

