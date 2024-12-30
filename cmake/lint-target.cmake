set(
  FORMAT_PATTERNS
  components/*.cpp
  components/*.h
  main.cpp
  main_window.cpp
  main_window.h
  CACHE STRING
  "; separated patterns relative to the project source dir to format"
)

set(FORMAT_COMMAND clang-format CACHE STRING "Formatter to use")

add_custom_target(
  format-fix
  COMMAND "${CMAKE_COMMAND}"
  -D "FORMAT_COMMAND=${FORMAT_COMMAND}"
  -D "PATTERNS=${FORMAT_PATTERNS}"
  -D FIX=YES
  -P "${PROJECT_SOURCE_DIR}/cmake/lint.cmake"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  COMMENT "Fixing the code"
  VERBATIM
)
