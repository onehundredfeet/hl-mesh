cmake_minimum_required(VERSION 3.10)
project( hl-gltf )

SET(library_name gltf.hdll)

if (NOT HE_VERSION) 
    set(HE_VERSION "19.0.531")
endif()

if (NOT HE_MAJOR_MINOR_VERSION) 
    set(HE_MAJOR_MINOR_VERSION "19.0")
endif()


if (NOT HL_INCLUDE_DIR) 
    set(HL_INCLUDE_DIR "/usr/local/include")
endif()

if (NOT HL_LIB_DIR) 
    set(HL_LIB_DIR "/usr/local/lib")
endif()

if (NOT COMMON_LIB_DIR) 
    set(COMMON_LIB_DIR "/usr/local/lib")
endif()

if (NOT HDLL_DESTINATION) 
    set(HDLL_DESTINATION "/usr/local/lib")
endif()

if (NOT GLTF_INC_DIR) 
set(GLTF_INC_DIR "ext/tinygltf")
endif()

if (NOT DRACO_INC_DIR) 
set(DRACO_INC_DIR "/usr/local/include")
endif()

if (NOT DRACO_LIB_DIR) 
set(DRACO_LIB_DIR "/usr/local/lib")
endif()

add_library(${library_name} SHARED
#Input C++ files go here
#${GLTF_SRC_DIR}/INPUT FILES GO HERE.cpp
src/hl_string_helpers.cpp
src/gltf.cpp
src/gltf_core.cpp
)

set_target_properties(${library_name}
PROPERTIES
PREFIX ""
OUTPUT_NAME gltf
SUFFIX .hdll
)

cmake_policy(SET CMP0015 NEW)


target_include_directories(${library_name}
PRIVATE
${GLTF_INC_DIR}
${HL_INCLUDE_DIR}
${DRACO_INC_DIR}
)

link_directories(${library_name}
${HL_LIB_DIR}
${DRACO_LIB_DIR}
)

find_library(LIBHL NAMES hl
             HINTS ${HL_LIB_DIR} )

find_library(LIBDRACO NAMES draco
             HINTS ${DRACO_LIB_DIR} )


target_link_libraries(${library_name}
${LIBHL}
${LIBDRACO}
)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


if (UNIX)
    # Some special flags are needed for GNU GCC compiler
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC  -O3  -fpermissive")
    #not sure why the ${HL_LIB_DIR} is necessary given the above.
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -shared  ")

    # find_library(LIBHL NAMES hl HINTS ${HL_LIB_DIR} )
else()
    #find_library(LIBHL NAMES libhl HINTS ${HL_LIB_DIR} )
endif (UNIX)


install(TARGETS ${library_name} DESTINATION ${HDLL_DESTINATION})
