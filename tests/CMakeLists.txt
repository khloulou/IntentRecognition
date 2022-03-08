

file(COPY ../src/intent.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test 
test.cpp
../src/intentRecognition.cpp
../src/intentRecognition.h
)







