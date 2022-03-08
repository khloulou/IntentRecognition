#include<string>
using namespace std;

// Class intent that can be extended 

class intentRecognition
{
	
public:

	double confidence;
	intentRecognition();
	~intentRecognition();
	//calculate the utterance having the max length
	int utteranceMaxLength(string jsonfilePath);
	// This function will calculate the difference between two strings (user input and the command);
	int levensteinDistance(const char input[], const char scompare[]);
	/* It will compare the user input with the command existingand the one having the shortest distance, it intent
	 will be displayed.*/
	string getIntent(string user_cmd);
	// Put the confidence score into performance.txt file
	void performanceMesure(string score);
};

