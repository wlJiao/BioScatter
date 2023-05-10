################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ProgramFiles/Ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx -O0 --opt_for_speed=0 --use_hw_mpy=F5 --include_path="C:/ProgramFiles/Ti/ccs1210/ccs/ccs_base/msp430/include" --include_path="D:/LYL/Desktop/BioScatter/BioScatter" --include_path="D:/LYL/Desktop/BioScatter/BioScatter/Sensor/Include" --include_path="D:/LYL/Desktop/BioScatter/BioScatter/Communication/Include" --include_path="D:/LYL/Desktop/BioScatter/BioScatter/Voltage/Include" --include_path="D:/LYL/Desktop/BioScatter/BioScatter/System/Include" --include_path="C:/ProgramFiles/Ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --include_path="D:/LYL/Desktop/BioScatter/BioScatter/System" --advice:power="all" --advice:hw_config=all --define=__MSP430FR2355__ --define=_FRWP_ENABLE --define=_INFO_FRWP_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


