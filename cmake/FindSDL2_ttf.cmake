# Find SDL2_ttf library and include paths
# This module sets the following variables:
#   SDL2TTF_FOUND        - True if SDL2_ttf is found
#   SDL2TTF_INCLUDE_DIRS - Include directories for SDL2_ttf
#   SDL2TTF_LIBRARIES    - List of SDL2_ttf libraries

find_path(SDL2TTF_INCLUDE_DIRS SDL_ttf.h)
find_library(SDL2TTF_LIBRARIES NAMES SDL2_ttf)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2TTF REQUIRED_VARS SDL2TTF_INCLUDE_DIRS SDL2TTF_LIBRARIES)
