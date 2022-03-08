
#include "intentRecognition.h"

#include <fstream>
#include<iostream>
#include <list>

// To use Fuzzy Library
//#include "3rdparty/RapidFuzz/rapidfuzz/fuzz.hpp"

using namespace std;



//import nlohmann library to parse json
#include<nlohmann/json.hpp> 

#define  filePath "intent.json"

using json=nlohmann::json;

// Calculate the min of 2 variables
#define MIN(x,y) ((x) < (y) ? (x) : (y)) 

intentRecognition::intentRecognition()
{
}


intentRecognition::~intentRecognition()
{
}


int intentRecognition::levensteinDistance(const char input[], const char scompare[])
{
	int i, j, l1, l2, t, track;
	int dist[100][100];

	//stores the lenght of strings s1 and s2
	l1 = strlen(input);
	l2 = strlen(scompare);
	for (i = 0; i <= l1; i++) {
		dist[0][i] = i;
	}
	for (j = 0; j <= l2; j++) {
		dist[j][0] = j;
	}
	for (j = 1; j <= l1; j++) {
		for (i = 1; i <= l2; i++) {
			if (input[i - 1] == scompare[j - 1]) {
				track = 0;
			}
			else {
				track = 1;
			}
			t = MIN((dist[i - 1][j] + 1), (dist[i][j - 1] + 1));
			dist[i][j] = MIN(t, (dist[i - 1][j - 1] + track));
		}
	}

	return dist[l2][l1];
}

int intentRecognition::utteranceMaxLength(string jsonfilePath)
{
	std::ifstream file(jsonfilePath);
	json json_file = json::parse(file, nullptr, false);
	int max = 1;
	for (auto i : json_file.items())
	{
		if (i.key().length() > max)
		{
			max = i.key().length();
		}
	}
	return max;
}


void intentRecognition::performanceMesure(string score) {

	fstream file;

	file.open("performance.txt", std::ios_base::app);

	
	if (!file)
	{
		cout << "Error in creating 'performance.txt' file!!!" << endl;
		
	}
	
	file << score << "\n";
	

	
	file.close();
}

string intentRecognition::getIntent(string user_cmd)
{

	string intentResult = "";
	
	
	std::ifstream file(filePath);
	// The maximum distance that Levenstein can have is 3*maxLength of the strings
	int levenMaxDistance = 3 * utteranceMaxLength(filePath);
	std::tuple<std::string, int> intent;
	std::tuple<std::string, int> max_intent("", levenMaxDistance);
	// this is in case we want to use Fuzzy
	//std::tuple<std::string, int> min_intent("", 0);
	//list<tuple<string, int>> intent_maxScore;
	list<tuple<string, int>> intent_minScore;
	
	if (file.is_open())
	{
		
		// Parse the json file that contains the utterance and the intent, it can be extandable with different sentences 
		json json_file = json::parse(file, nullptr, false);



		if (json_file.is_discarded())
		{
			std::cerr << "parse error" << std::endl;
		}
	
	
	
		// Parse json items
		for (auto i : json_file.items())
		{

			double score = levensteinDistance(user_cmd.c_str(), i.key().c_str());

			//ratio is used to calculate the difference between strings with fuzzy library
			//double ratio = rapidfuzz::fuzz::token_set_ratio(user_cmd, i.key());
			
			//var confidence is used to measure the performance of the matching algorithm
			confidence = 1 - score / levenMaxDistance;
			
		
			
			string mesure = " The confidence between " + user_cmd + " and " + i.key() + " is " + to_string(confidence);
			performanceMesure(mesure);
			
			intent = std::make_tuple(i.value(), score);

			//To use fuzzy library
			/*if (ratio>get<1>(min_intent))
				{
				max_intent = make_tuple(i.value(), ratio);
				intent_minScore.clear();
				intent_minIntent.push_back(min_intent);


			   }else if (ratio == get<1>(min_intent))
			   {
				min_intent = make_tuple(i.value(), ratio);
				intent_minScore.push_back(min_intent);

		       }*/
			// put in the list only the intent having the minium score (highly match with the utterance)
			if (score< get<1>(max_intent))
			{
				max_intent = make_tuple(i.value(), score);
				intent_minScore.clear();
				intent_minScore.push_back(max_intent);
			

			}

			//if the user inputs and the utterance having the same score we will choose the first one
			// To Do use semantic algorithm
			else if (score == get<1>(max_intent))
			{
				max_intent = make_tuple(i.value(), score);
				intent_minScore.push_back(max_intent);
				
			}

		}
	}

	else {
		std::cout << " file error open " << std::endl;
	}

	




	for (auto currentTuple : intent_minScore)
	{
		intentResult = " Intent : " + get<0>(currentTuple);
		
	}

	return intentResult;
}
