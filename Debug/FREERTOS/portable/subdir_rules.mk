################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FREERTOS/portable/%.obj: ../FREERTOS/portable/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1200/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1200/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include" --include_path="Z:/win/desktop/ece353/freertos/FreeRTOSv202112.00/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="Z:/win/desktop/ece353/freertos/FreeRTOSv202112.00/FreeRTOS/Source/include" --include_path="Z:/win/desktop/ece353/freertos/finalproject" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FREERTOS/portable/$(basename $(<F)).d_raw" --obj_directory="FREERTOS/portable" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FREERTOS/portable/%.obj: ../FREERTOS/portable/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1200/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1200/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include" --include_path="Z:/win/desktop/ece353/freertos/FreeRTOSv202112.00/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="Z:/win/desktop/ece353/freertos/FreeRTOSv202112.00/FreeRTOS/Source/include" --include_path="Z:/win/desktop/ece353/freertos/finalproject" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FREERTOS/portable/$(basename $(<F)).d_raw" --obj_directory="FREERTOS/portable" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


