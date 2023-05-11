# BioScatter Artifact Overview
BioScatter is a low-power sweat sensing system, which consists of a BioScatter tag and a USRP reader with a laptop. This repository includes four parts: 1) the BioScatter tag's hardware design files (circuit schematic, PCB file, and the program for MSP430 MCU); 2) the BioScatter reader's data collection program (reader.grc) and the data analysis program; 3) a voltage monitoring experiment video; 4) figures that illustrate the flow of experiments, electrode fabrication, the workflow of programs and the experiment setup.

The most important file is `BioScatter_Designfiles` and `BioScatter_EmbeddedSystem`.

## BioScatter tag
- The folder `BioScatter_Designfiles` is the most important part, which includes the detailed circuit schematic diagram and the PCB file. These files are designed with Altium Designer. The hardware of BioScatter tag is a four-layer printing circuit board, comprised of an MSP430 micro-controller unit, active components (crystal oscillator, operational amplifiers, comparators, diodes, MOSFET, level shifter, switch, several IC chips), shunt voltage reference, and passive components (resistors, inductors, and capacitors), printed dipole antenna.
- The folder `BioScatter_EmbeddedSystem` is the program for MSP430 MCU that performs the logic control task (sensing and voltage monitoring/calibration). These files are designed with Code Composer Studio and the programming language is C.

## Reader
- The file Reader.grc can be opened with GNU radio software. GNU radio should be version 3.7.11 or newer, running on the Ubuntu OS 16.04 or newer. Reader.grc connects the USRP as the transceiver and controls the USRP to transmit a carrier signal at 910MHz and to receive the tag's backscatter signal.
- The hardware of the reader consists of a USRP N210 SDR, a UBX40 daughterboard, two antennae of 850-950 MHz, and a laptop with Ubuntu OS.
- The folder `ReaderDataAnalysis` is the MATLAB program that takes the collected data from "Reader.grc" as input and outputs the estimated sweat concentration level.

## Demos
- We provide a video of BioScatter hardware prototype and experiment process, which is available at: YouTube `https://youtu.be/SeuaicnlDGQ`.
- `voltage_monitoring_experiment.mp4` is a demo for introducing the voltage monitoring module.
- `Minimal System` is a demo that shows the IV profiles of different concentrations and the sensing accuracy.

## Folders Overview
- `BioScatter_DesignFiles` is the BioScatter tag's hardware design files, including the circuit diagram, the PCB file.
- `BioScatter_EmbeddedSystem` is the BioScatter tag's control logic program for MSP430 MCU.
- `Reader Program` is a GNU radio program for reader, which connects USRP, transmit the carrier to the tag and receive the backscatter signal from tag.   
- `ReaderDataAnalysis` consists of the overall signal processing flow in Matlab. The required Matlab version is MATLAB R2021b or newer.

