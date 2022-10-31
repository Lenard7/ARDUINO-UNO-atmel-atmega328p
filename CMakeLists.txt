cmake_minimum_required(VERSION 3.14)

project("Embedded_practice" VERSION 0.1 LANGUAGES CXX C ASM)

## AVR Chip Configuration
# 16Mhz, this should match the crystal on your board,
set(F_CPU 16000000UL)

# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega328p)

# Default Baudrate for UART, read avr include/util/setbaud.h for usage
set(BAUD 115200)

# Port for the board
set(PORT /dev/ttyACM0)

# TODO [lpavic]: see if this is needed
# The programmer to use, read avrdude manual for list
set(PROG_TYPE avrispmkII)

# TODO [lpavic]: see if this is needed
# AVR Fuses, must be in concordance with your hardware and F_CPU
# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p
set(E_FUSE 0xfd)
set(H_FUSE 0xda)
set(L_FUSE 0xfd)
set(LOCK_BIT 0xff)

# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

# Pass defines to compiler
# these are options to avr compiler, F_CPU is for frequency of CPU, and BAUD for baud rate
add_definitions(
    -DF_CPU=${F_CPU}
    -DBAUD=${BAUD}
)
# mmcu MUST be passed to both the compiler and linker, this handles the linker
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

# mmcu MUST be passed to both the compiler and linker, this handles the compiler
add_compile_options(
    -mmcu=${MCU} # MCU
#     -std=gnu99 # C99 standard
    -std=c++14
    -Os # optimize
    -Wall # enable warnings
    -Wno-main
    -Wundef
    -pedantic
    -Wstrict-prototypes
    -Werror
    -Wfatal-errors
    -Wl,--relax,--gc-sections
    -g
    -gdwarf-2
    -funsigned-char # a few optimizations
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    -fno-split-wide-types
    -fno-tree-scev-cprop
)

# TODO [lpavic]: see if this is needed
# file(GLOB SRC_FILES 
#     "${PROJECT_SOURCE_DIR}/*.cpp"
# ) # Load all files in src folder
# file(GLOB SRC_FILES "~/Desktop/Engineering_projects/Ele_projekti/ARDUINO-UNO-atmel-atmega328p/src/*.cpp")

# TODO [lpavic]: see if this is needed or should this only be handled with add_subdirectory and inside those subdirectories should be other CMakeLists
# Create one target
add_executable(${PROJECT_NAME} 
    # ${SRC_FILES}
    # ${PROJECT_SOURCE_DIR}/firmware/main.cpp
    ${CMAKE_SOURCE_DIR}/src/firmware/main.cpp
)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PROJECT_NAME} 
    PROPERTIES OUTPUT_NAME 
        ${PROJECT_NAME}.elf
)

# TODO [lpavic]: see if this is needed or needs to be modified
# Strip binary for upload
add_custom_target(strip ALL avr-strip ${PROJECT_NAME}.elf DEPENDS ${PROJECT_NAME})

# TODO [lpavic]: see if this is needed or needs to be modified
# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex DEPENDS strip)

# TODO [lpavic]: see if this is needed or needs to be modified
# Transform binary into hex file, this is the eeprom part (empty if you don't
# use eeprom static variables)
add_custom_target(eeprom avr-objcopy -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.eep DEPENDS strip)

# TODO [lpavic]: see if this is needed or needs to be modified
# Upload the firmware with avrdude
add_custom_target(upload avrdude  -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PROJECT_NAME}.hex DEPENDS hex)

# TODO [lpavic]: see if this is needed or needs to be modified
# Upload the eeprom with avrdude
add_custom_target(upload_eeprom avrdude -c ${PROG_TYPE} -p ${MCU}  -U eeprom:w:${PROJECT_NAME}.eep DEPENDS eeprom)

# TODO [lpavic]: see if this is needed or needs to be modified
# Burn fuses
add_custom_target(fuses avrdude -c ${PROG_TYPE} -p ${MCU}  -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m )

# TODO [lpavic]: see if this is needed or needs to be modified - clean.sh script is sufficient for now
# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}.hex;${PROJECT_NAME}.eeprom;${PROJECT_NAME}.lst")

# TODO [lpavic]: for test purpose only, compare this with privious targets and see what to do
add_custom_target(upload_test avrdude -F -V -c arduino -p ${MCU} -P ${PORT} -b ${BAUD} -U flash:w:${PROJECT_NAME}.hex)

add_subdirectory(src)