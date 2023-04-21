# BioScatter
BioScatter is a low-power sweat sensing system, which consists of a BioScatter tag and a USRP reader with a laptop. This repository includes three parts: 1) the BioScatter tag's hardware design files (circuit schematic, PCB file, and the program for MSP430 MCU); 2) the BioScatter reader's data collection program (reader.grc) and the data analysis program; 3) a voltage monitoring experiment video.

The most important file is the tag's circuit schematic file and the BioScatter_EmbeddedSystem program.

The hardware of BioScatter system has two parts listed as follows:

\textbf{BioScatter tag.} 

- The folder "BioScatter_Designfiles" is the most part, which includes the detailed circuit schematic diagram and the PCB file. These files are designed with Altium Designer. The hardware of BioScatter tag is a four-layer printing circuit board, comprised of a micro-controller unit (MCU, MSP430), active components (crystal oscillator, operational amplifiers, comparators, diodes, MOSFET, level shifter, switch, several IC chips), shunt voltage reference, and passive components (resistors, inductors, and capacitors), printed dipole antenna.

- The folder "BioScatter_EmbeddedSystem" is the program for MSP430 MCU that performs the logic control task (sensing and voltage monitoring/calibration). These files are designed with Code Composer Studio and the programming language is \texttt{C} language.

\textbf{Reader.} 

- The hardware of the reader consists of a USRP N210 SDR, a UBX40 daughterboard, two antennae of 900~MHz, and a laptop with Linux OS.

- The file Reader.grc is used with GNU radio software which requires version 3.7.11 or newer.
