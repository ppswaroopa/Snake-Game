# Find SDL2_ttf library and include paths
# This module sets the following variables:
#   SDL2TTF_FOUND        - True if SDL2_ttf is found
#   SDL2TTF_INCLUDE_DIRS - Include directories for SDL2_ttf
#   SDL2TTF_LIBRARIES    - List of SDL2_ttf libraries

find_path(SDL2MIXER_INCLUDE_DIRS SDL_mixer.h)
find_library(SDL2MIXER_LIBRARIES NAMES SDL2_mixer)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2MIXER REQUIRED_VARS SDL2MIXER_INCLUDE_DIRS SDL2MIXER_LIBRARIES)
