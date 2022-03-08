# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAG "-std=c++17")
# Name of the project
project(IntentRecognition)

include_directories(include)



file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/intent.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#Use the json library
include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
  GIT_TAG v3.10.5)

  FetchContent_MakeAvailable(json)




add_subdirectory(tests)

add_subdirectory(include/3rdparty/RapidFuzz)

# Add all the source files needed to build the executable
add_executable(
  IntentRecognition
   src/main.cpp
   src/intentRecognition.cpp
   src/intentRecognition.h
)

target_link_libraries(IntentRecognition 
PRIVATE nlohmann_json::nlohmann_json
rapidfuzz::rapidfuzz
)

