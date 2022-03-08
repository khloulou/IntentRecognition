
#include <fstream>
#include<iostream>
#include "intentRecognition.h"
#include <string>


using namespace std;


int main()
{
	
	cout << " ********** Intent Recognizer App ******** " << std::endl;
	

	string user_cmd;
	while(user_cmd !="exit")
	{
		
		
		cout << " Please type your command :" << std::endl;
		getline(cin, user_cmd);

		if (user_cmd.empty() || user_cmd.find_first_not_of(' ') == std::string::npos)
		{
			cout << " You haven't entered anything, Please type you command  :" << std::endl;
			getline(cin, user_cmd);
		}
		intentRecognition intent;
		cout<<intent.getIntent(user_cmd);



		cout << " \n Would you like to exit ?(exit/No)" << endl;
		getline(cin, user_cmd);
		system("CLS");



	} 

	


	return 0;
}