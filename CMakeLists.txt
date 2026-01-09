cmake_minimum_required(VERSION 3.23)

project(
    snake_rogue
    VERSION 1.0
    DESCRIPTION "A traditional roguelike where the player plays as a snake"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sets both output directories to the same predictable location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "C:/Program Files/NASM") # This should be replaced
endif()

# Setting up the project source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/game/source/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/core/source/*.cpp")
add_executable(${PROJECT_NAME} ${MY_SOURCES})

file(GLOB_RECURSE HEADER_FILES "game/source/*.h" "core/source/*h")
foreach(header ${HEADER_FILES})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Set the RPATH on apple and linux
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
    )
elseif(UNIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()

if(WIN32)
  set(MATH_LIBRARY "" CACHE STRING "" FORCE)
endif()

# Specify that we want to build SDL_TTF's dependencies
set(SDLTTF_VENDORED ON) 

# Set a variable for our vendor directory
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/core/vendor") 

# Add the SDL libraries from our submodules
add_subdirectory(${VENDOR_DIR}/SDL) 
add_subdirectory(${VENDOR_DIR}/SDL_image) 
add_subdirectory(${VENDOR_DIR}/SDL_ttf)
add_subdirectory(${VENDOR_DIR}/eventpp)

target_link_libraries(${PROJECT_NAME}
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    eventpp::eventpp
)

# Copy data folder to build output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/game/data
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
    COMMENT "Copying data folder to build output directory"
)
