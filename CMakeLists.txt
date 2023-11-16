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
  src/j2me/Layer.cpp
  src/j2me/Graphics.cpp
  src/j2me/Displayable.cpp
  src/j2me/Image.cpp
  src/j2me/TiledLayer.cpp
  src/j2me/Display.cpp
  src/j2me/Sprite.cpp
  src/j2me/Canvas.cpp
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
  src/BackgroundCanvas.cpp
  src/Ball.cpp
  src/Board.cpp
  src/BonusBrick.cpp
  src/BonusLayer.cpp
  src/Brick.cpp
  src/BricksLayer.cpp
  src/Level.cpp
  src/LivesLayer.cpp
  src/Main.cpp
  src/MenuCanvas.cpp
  src/PointLayer.cpp
  src/ResourceManager.cpp
  src/Settings.cpp
  src/ShadowText.cpp
  src/TextLayer.cpp
  src/TextCanvas.cpp
  src/TitleCanvas.cpp
)

if(UNIX AND NOT APPLE)
  target_sources(arkanerd PRIVATE
    src/os_util_linux.cpp
  )
elseif(WIN32)
  target_sources(arkanerd PRIVATE
    src/os_util_win32.cpp
  )
else()
  message(SEND_ERROR "Platform currently unsupported")
endif()

target_include_directories(arkanerd PRIVATE
  src/
)

target_link_libraries(arkanerd PRIVATE
  j2me
  sfml-graphics
  sfml-window
  project_options
  project_warnings
)

add_custom_command(
  TARGET arkanerd POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_directory
  ${PROJECT_SOURCE_DIR}/res
  $<TARGET_FILE_DIR:arkanerd>/res
  VERBATIM
)

if(WIN32)
  add_custom_command(TARGET arkanerd POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:arkanerd> $<TARGET_FILE_DIR:arkanerd> COMMAND_EXPAND_LISTS)
endif()
