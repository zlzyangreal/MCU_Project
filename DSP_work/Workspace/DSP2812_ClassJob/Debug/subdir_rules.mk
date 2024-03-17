################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/diansai/CCS12.3/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/diansai/DSP_work/Workspace/DSP2812_ClassJob" --include_path="D:/diansai/DSP_work/Workspace/DSP2812_ClassJob/inc" --include_path="D:/diansai/DSP_work/Workspace/DSP2812_ClassJob/src" --include_path="D:/diansai/CCS12.3/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


