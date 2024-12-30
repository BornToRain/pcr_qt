cmake_minimum_required(VERSION 3.14)
# set(CMAKE_C_COMPILER clang)
# set(CMAKE_CXX_COMPILER clang++)
project(pcr_qt VERSION 0.1 LANGUAGES CXX)

# ---- qt自动生成脚本 ----
set(CMAKE_AUTOMOC ON)

# ---- C++编译器相关 ----
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# clang
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wno-deprecated-declarations -Wno-ignored-optimization-argument -Wthread-safety)
  # gcc
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wno-deprecated-declarations -Wno-ignored-optimization-argument -ffloat-store)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ---- 格式化相关 ----
include(cmake/lint-target.cmake)

# ---- 拼写相关 ----
include(cmake/spell-target.cmake)

# ---- 项目信息 ----
include(cmake/info.cmake)

# ---- 运行函数 ----
set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/6.7.3/gcc_arm64) # qt安装路径
find_package(Qt6 REQUIRED COMPONENTS
  Core
  Gui
  Widgets
)
find_package(PCL REQUIRED COMPONENTS
  io
  filters
  visualization
)
find_package(VTK REQUIRED)

aux_source_directory(components COMPONENTS)
qt_add_executable(${PROJECT_NAME}
  MANUAL_FINALIZATION
  main.cpp
  main_window.h
  main_window.cpp
  ${COMPONENTS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt6::Core
  Qt6::Gui
  Qt6::Widgets
  ${PCL_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  ${BUNDLE_ID_OPTION}
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(${PROJECT_NAME})
