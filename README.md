# BioScatter
BioScatter is a low-power sweat sensing system, which consists of a BioScatter tag and a USRP reader with a laptop. This repository includes four parts: 1) the BioScatter tag's hardware design files (circuit schematic, PCB file, and the program for MSP430 MCU); 2) the BioScatter reader's data collection program (reader.grc) and the data analysis program; 3) a voltage monitoring experiment video; 4) figures that illustrate the flow of experiments, electrode fabrication, the workflow of programs and the experiment setup.

The most important file is "BioScatter_Designfiles" and "BioScatter_EmbeddedSystem" program.

## BioScatter tag

- The folder "BioScatter_Designfiles" is the most important part, which includes the detailed circuit schematic diagram and the PCB file. These files are designed with Altium Designer. The hardware of BioScatter tag is a four-layer printing circuit board, comprised of an MSP430 micro-controller unit, active components (crystal oscillator, operational amplifiers, comparators, diodes, MOSFET, level shifter, switch, several IC chips), shunt voltage reference, and passive components (resistors, inductors, and capacitors), printed dipole antenna.

- The folder "BioScatter_EmbeddedSystem" is the program for MSP430 MCU that performs the logic control task (sensing and voltage monitoring/calibration). These files are designed with Code Composer Studio and the programming language is C.

## Reader

- The file Reader.grc can be opened with GNU radio software. GNU radio should be version 3.7.11 or newer, running on the Ubuntu OS 16.04 or newer. Reader.grc connects the USRP as the transceiver and controls the USRP to transmit a carrier signal at 910MHz and to receive the tag's backscatter signal.

- The hardware of the reader consists of a USRP N210 SDR, a UBX40 daughterboard, two antennae of 850-950 MHz, and a laptop with Ubuntu OS.

- The folder "ReaderDataAnalysis" is the MATLAB program that takes the collected data from "Reader.grc" as input and outputs the estimated sweat concentration level.

We provide a video of BioScatter hardware prototype and experiment process, which is available at: YouTube https://youtu.be/SeuaicnlDGQ.

## Minimal System
The folder <Minimal System> contains two data files, two MATLAB function files (funcCutProfile.m, main.m), and one main function (Main1.m). These files can be opened with MATLAB. The steps to run are simple:
"Open Main1.m,; click the Run button; the program will display the IV profiles of urea acid and ascorbic acid with different concentrations, as well as the sensing accuracy result hotmap."
  
## Reader Program
The folder <Reader Program> includes two files.
  "Reader.grc" can be opened with GNU radio 3.7.11 or newer version.
  "figure-data_collection_grc.pdf" is an explanation file about "Reader.grc".
  
## ReaderDataAnalysis
  The folder <ReaderDataAnalysis> consists of the overall signal processing flow in Matlab.
  "main.m" is the main function;
  "funcReadIQDataInParProcessing.m" is a function for loading the raw sample data from "Reader.grc" program. The raw data is a large binary file, usually with a size of 700M~1G. Thus, to accelerate the loading speed, we use the parallel operation in Matlab.
  "funcNormDivSeg.m" is a function for pre-processing the loaded IQ data, which first produces a complex matrix (IQ matrix). This function is responsible for normalizing the amplitude of the signal and remove the offset of the whole signal due to dynamic interference.
  "funcDemodulate.m" is a function for demodulating the pulse interval modulated signal that is the sweat sensor's analog output (IV profile). Then this function outputs the demodulated I-V profile.
  "funcCutProfile" is a function for trimming the I-V profile to realize a general-formatted IV profile matrix. The output I-V profile is used for sweat concentration estimation.
  "funcLevelIdentification.m" is a function for identifying the current sweat concentration.
