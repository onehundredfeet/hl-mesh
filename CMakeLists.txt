cmake_minimum_required(VERSION 3.10)
project( hl-houdini )

SET(library_name houdini.hdll)

if (NOT HE_VERSION) 
    set(HE_VERSION "19.0.531")
endif()

if (NOT HE_MAJOR_MINOR_VERSION) 
    set(HE_MAJOR_MINOR_VERSION "19.0")
endif()

set (HOUDINI_FRAMEWORK_PATH "/Applications/Houdini/Houdini${HE_VERSION}/Frameworks/Houdini.framework/Versions/${HE_MAJOR_MINOR_VERSION}")
set (HOUDINI_TOOLKIT "${HOUDINI_FRAMEWORK_PATH}/Resources/toolkit")



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

if (NOT HOUDINIENGINE_INC_DIR) 
set(HOUDINIENGINE_INC_DIR "${HOUDINI_TOOLKIT}/include")
endif()



add_library(${library_name} SHARED
#Input C++ files go here
#${HOUDINIENGINE_SRC_DIR}/INPUT FILES GO HERE.cpp
src/hl_string_helpers.cpp
src/houdini.cpp
src/hlhapiutil.cpp
)

set_target_properties(${library_name}
PROPERTIES
PREFIX ""
OUTPUT_NAME houdini
SUFFIX .hdll
)

cmake_policy(SET CMP0015 NEW)


target_include_directories(${library_name}
PRIVATE
${HOUDINIENGINE_INC_DIR}
${HL_INCLUDE_DIR}
)

link_directories(${library_name}
${HL_LIB_DIR}
)

find_library(LIBHL NAMES hl 
             HINTS ${HL_LIB_DIR} )



target_link_libraries(${library_name}
${LIBHL}
)
IF(APPLE)
list(APPEND CMAKE_PREFIX_PATH "${HOUDINI_TOOLKIT}/cmake")
find_package(Houdini REQUIRED   )
message("Houdini Found ${Houdini_FOUND}")
message("inc ${Houdini_INCLUDE_DIR}")
message("inc ${HOUDINI_INCLUDE_DIR}")
message("inc ${HOUDINIENGINE_INC_DIR}")
include_directories(${HOUDINI_INCLUDE_DIR})

# Link against the Houdini libraries, and add required include directories and compile definitions.
target_link_libraries( ${library_name} Houdini )
# Configure several common target properties, such as its output directory.
#houdini_configure_target( ${library_name} )

MARK_AS_ADVANCED(HOUDINI_LIBRARY)
ENDIF (APPLE)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


if (UNIX)
    # Some special flags are needed for GNU GCC compiler
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC  -O3  -fpermissive ")
    #not sure why the ${HL_LIB_DIR} is necessary given the above.
    
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -shared -Wl ")
#    get_property(library_location TARGET ${library_name} PROPERTY LOCATION)



    add_custom_command(TARGET ${library_name}

    # Run after all other rules within the target have been executed
    POST_BUILD
    COMMAND echo -e "\texecuting a POST_BUILD command ${library_name}"
    COMMAND install_name_tool -id ${library_name} ${library_name}
    COMMAND install_name_tool -change @rpath/Houdini.framework/Versions/${HE_MAJOR_MINOR_VERSION}/Houdini /Applications/Houdini/Houdini19.0.531/Frameworks/Houdini.framework/Versions/19.0/Houdini houdini.hdll
    COMMENT "This command will be executed after building bar"
    VERBATIM
)

endif (UNIX)

install(TARGETS ${library_name} DESTINATION ${HDLL_DESTINATION})
