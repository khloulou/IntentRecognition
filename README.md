# Intent Recognition Project

## Descripion

The user inputs an utterance and the corresponding intent will be displayed.

## Software Architecture 

*	src/
       * IntentRecogintion.cpp:  Class IntentRecognition that easily can be extended by adding the necessary methods or variables and create new classes if for example we want  to create different intent types.
       * main()
       * Data : intent.json : contains the utterance and its intents, so it can easily be extended by adding new intents
*	Tests/
       * test.cpp : using catch2, it tests the 3 uses cases and also another that have different semantic inputs you can add as many tests as you want.

*	Include/
       * nlohmann for using the library json
       * catch.hpp for using catch2 for Unit testing
       * RapidFuzz library imported from github and added as subdirectory in cmakeFile

## Algorithm

-	Levenstein Distance algorithm: The Levenshtein distance is a string metric for measuring difference between two sequences. Informally, the Levenshtein distance between two words is the minimum number of single-character edits (i.e. insertions, deletions or substitutions) required to change one word into the other.
-	RapidFuzzy library can also be using to measure the difference between strings.

## Performance :

*	I have created a function " performanceMesure(string mesure)" in the intentRecognition class that measure the confidence of the intent recognition; it stocks into a file "performance.txt" the measurement ( 0 to 1), 
1 refers to an exact intent recognition, 0 refers to the lowest intent recognition.
*	The performance can be improved by adding an additional layer based on the Fuzzy algorithm and can be combined with the Levenstein Distance to improve the score of intent matching.
*	When strings have the same distance or ratio we can use another semantic algorithm to have more precise results.

## Tests 

* The 3 uses cases : What is the weather like today?, What is the weather like in Paris today?, Tell me an interesting fact are executed correctly.
* In the test.cpp file, you can find all the uses cases that I have tested, you can add your own tests and execute it with /build/tests/test.exe.

## Usage 

Create build folder: mkdir build


Compile and generate MakeFile :

*	On Windows:
cd build && cmake .. -G "Unix Makefiles" 
make
*	On Linux 
cd build && cmake .. &&  make

* App Execution
Run intentRecognition.exe for executing the app 

* Tests Execution
Run build/tests/test.exe for executing unit tests

