CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

# project name
PROJECT(ASCII_Hangman)

# specify sources and headers
SET(HDRS
   # module headers go here (*.h)
   game.h
   hangman.h
   menu.h
   sprites.h
   )
SET(SRCS
   # module implementations go here (*.cpp)
   main.cpp
   game.cpp
   hangman.cpp
   menu.cpp
   sprites.cpp
   )

# specify source directories
INCLUDE_DIRECTORIES(.)

# C++ standard
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -Wall -Werror")
IF (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.2)
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla")
ENDIF (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.2)

# default C++ compiler definitions
IF (NOT CMAKE_BUILD_TYPE)
   IF (UNIX)
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O")
   ENDIF (UNIX)
ENDIF (NOT CMAKE_BUILD_TYPE)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# extend cmake module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# find NCurses
FIND_PACKAGE(Curses REQUIRED)
INCLUDE_DIRECTORIES(${CURSES_INCLUDE_DIRS})

# build and link executable
ADD_EXECUTABLE(main ${HDRS} ${SRCS}) # compile main executable
TARGET_LINK_LIBRARIES(main
   ${GFXLIB_NAME} # link with ascii gfx lib
   )
TARGET_LINK_LIBRARIES(main
   ${CURSES_LIBRARIES} # link with NCurses
   )
IF (SDL_FOUND AND SDL_MIXER_FOUND)
   TARGET_LINK_LIBRARIES(main
      ${SDL_LIBRARY} # link with SDL
      ${SDL_MIXER_LIBRARY} # link with SDL mixer
      )
ENDIF (SDL_FOUND AND SDL_MIXER_FOUND)
IF ((SDL2_FOUND AND SDL2_MIXER_FOUND) AND NOT (SDL_FOUND OR SDL_MIXER_FOUND))
   TARGET_LINK_LIBRARIES(main
      ${SDL2_LIBRARY} # link with SDL2
      ${SDL2_MIXER_LIBRARY} # link with SDL2 mixer
      )
ENDIF ((SDL2_FOUND AND SDL2_MIXER_FOUND) AND NOT (SDL_FOUND OR SDL_MIXER_FOUND))
