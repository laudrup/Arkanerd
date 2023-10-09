cmake_minimum_required(VERSION 3.15)

project(arkanerd CXX)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/StaticAnalyzers.cmake)
include(cmake/Sanitizers.cmake)
include(FetchContent)

add_library(project_options INTERFACE)
add_library(project_warnings INTERFACE)

add_compile_options("-D_GLIBCXX_DEBUG")

target_compile_features(project_options INTERFACE
  cxx_std_17
)

if(WIN32)
  target_compile_definitions(project_options INTERFACE
    _CRT_SECURE_NO_WARNINGS
  )
endif()

option(ARKANERD_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)
set_project_warnings(project_warnings ${ARKANERD_WARNINGS_AS_ERRORS})
enable_sanitizers(project_options)

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

add_library(j2me STATIC
  src/j2me/MIDlet.cpp
  src/j2me/PlayerListener.cpp
  src/j2me/Command.cpp
  src/j2me/Manager.cpp
  src/j2me/List.cpp
  src/j2me/Layer.cpp
  src/j2me/Player.cpp
  src/j2me/StringItem.cpp
  src/j2me/Graphics.cpp
  src/j2me/RecordStore.cpp
  src/j2me/Displayable.cpp
  src/j2me/Item.cpp
  src/j2me/CommandListener.cpp
  src/j2me/Image.cpp
  src/j2me/TiledLayer.cpp
  src/j2me/GameCanvas.cpp
  src/j2me/Form.cpp
  src/j2me/Display.cpp
  src/j2me/Sprite.cpp
  src/j2me/Font.cpp
  src/j2me/Canvas.cpp
  src/j2me/ImageItem.cpp
  src/j2me/LayerManager.cpp
)

target_link_libraries(j2me PRIVATE
  project_options
  project_warnings
)

target_link_libraries(j2me PUBLIC
  sfml-graphics
)

add_executable(arkanerd
  src/ArkanerdCanvas.cpp
  src/ArkanerdThread.cpp
  src/Ball.cpp
  src/Board.cpp
  src/BonusBrick.cpp
  src/Bonus.cpp
  src/Brick.cpp
  src/BricksLayer.cpp
  src/Level.cpp
  src/LivesLayer.cpp
  src/Main.cpp
  src/PointLayer.cpp
  src/ScaleImage.cpp
  src/Settings.cpp
  src/TextLayer.cpp
  src/TitleCanvas.cpp
)

target_include_directories(arkanerd PRIVATE
  src/
)

target_link_libraries(arkanerd PRIVATE
  j2me
  project_options
  project_warnings
)
