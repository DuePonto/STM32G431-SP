cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
 
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
 
# Add you project name
project(STM32G431-SP C CXX ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
 
# Add carnel name
set(MCPU cortex-m4)
 
# Uncomment for hardware floating point
add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
 
# Uncomment for software floating point
# add_compile_options(-mfloat-abi=soft)
  
add_compile_options(-mcpu=${MCPU} -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
  
# Uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
 
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()
 
# Add Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/Core/Inc
        ${CMAKE_SOURCE_DIR}/App/Inc
        ${CMAKE_SOURCE_DIR}/Drivers/STM32G4xx_HAL_Driver/Inc
        ${CMAKE_SOURCE_DIR}/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32G4xx/Include
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include

        # FreeRTOS
        ${CMAKE_SOURCE_DIR}/Libs/FreeRTOS/include
        ${CMAKE_SOURCE_DIR}/Libs/FreeRTOS/portable/GCC/ARM_CM4F

        # Devices
        ${CMAKE_SOURCE_DIR}/Libs/MG996r_HAL
        ${CMAKE_SOURCE_DIR}/Libs/MPU9255_HAL
        )
 
# Add C defines
add_definitions(-DUSE_HAL_DRIVER -DSTM32G431xx)
 
# Add you source file
file(GLOB_RECURSE SOURCES
        "Core/Src/*.c"
        "App/Src/*.cpp"
        "Drivers/STM32G4xx_HAL_Driver/Src/*.c"
        "startup_stm32g431xx.s"

        # FreeRTOS
        "Libs/FreeRTOS/*.c"
        "Libs/FreeRTOS/portable/GCC/ARM_CM4F/port.c"

        # Devices
        "Libs/MG996r_HAL/*.cpp"
        "Libs/MPU9255_HAL/*.c"
        )
 
# Add lincer file
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32G431CBUx_FLASH.ld)
 
# this options for C++
add_link_options(-specs=nosys.specs -lstdc++)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=${MCPU} -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})
 
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
 
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")