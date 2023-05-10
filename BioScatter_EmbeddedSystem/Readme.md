# Installing Code Composer Studio
## Download
Open the following link to download the CCS installation package for the latest Windows version. [CCSTUDIO — Code Composer Studio™ integrated development environment (IDE)](https://dr-download.ti.com/software-development/ide-configuration-compiler-or-debugger/MD-J1VdearkvK/12.3.0/CCS12.3.0.00005_win64.zip). You can also open the following link to select and download the CCS installation package for Windows 12.1.0 or later.

```
https://www.ti.com/tool/CCSTUDIO#downloads
```

## Installation

Open the downloaded package and follow the installation instructions to install CCS on your computer.

# Project, Build and Flash
1. Download the [BioScatter](https://github.com/wlJiao/BioScatter/archive/refs/heads/main.zip) Repository.
2. Open the CCS IDE and set the workspace path to `BioScatter/BioScatter_EmbeddedSystem/`.
3. Connect the tag with the laptop through an MSP430 USB debug interface. Please refer to Figure 1 in the appendix section of our paper for how to make the connection.
4. In the CCS IDE, open `BioScatter/main.c`, the file is located in the Project Explorer subwindow on the left, click the Build button (the hammer icon) at the bottom of the toolbar, then click the Flash button (the bottom arrow icon) or the Debug button, and the program will start running.

> Please note that if you do not have a connected tag and laptop, you can only build, not flash or debug.

# Files Declaration

This section describes only the functions of related folders in the current directory. For descriptions of the program files, please see the `BioScatter/BioScatter_EmbeddedSystem/BioScatter/Readme.md`.

- `BioScatter`: the project folder, where all program files are located.
- Others: some configuration files about the CCS IDE workspace.
