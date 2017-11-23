#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include "interface.h"



using namespace std;
void  v_handleSingleInput() {

	string inputLine;
	getline(cin, inputLine);
	map<string, int>  commandsMap;
	commandsMap["MVEC"] = 0;
	commandsMap["DEF"] = 1;
	commandsMap["GET"] = 2;
	commandsMap["LEN"] = 3;
	commandsMap["PRINT"] = 4;
	commandsMap["DEL"] = 5;
	for (string::size_type i = 0; i < inputLine.length(); i++)
	{
		inputLine[i] = toupper(inputLine[i]);
	}
	vector<string> slicedCommands = s_sliceCommand(inputLine);
	string command = slicedCommands[0];
	if (b_checkCommand(slicedCommands)) {
		switch (commandsMap[command]) {
		case 0:
			
			break;
		case 1:
			//def
		
			break;
		case 2:
			//get
			
			break;
		case 3:
			//len 
			
			break;
		case 4:
			//print
		
			break;
		case 5:
			
			break;



		}
	}
	else {
		cout << "WRONG COMMAND, TRY AGAIN" << endl;
	}




}
bool b_checkCommand(vector<string>& slicedCommands) {
	map<string, int>::iterator it;
	map<string, int>  numOfArgsMap;
	numOfArgsMap["MVEC"] = 3;
	numOfArgsMap["DEF"] = 3;
	numOfArgsMap["GET"] = 2;
	numOfArgsMap["LEN"] = 2;
	numOfArgsMap["PRINT"] = 1;
	numOfArgsMap["DEL"] = 1;
	string command = slicedCommands[0];
	it = numOfArgsMap.find(command);
	if (it != numOfArgsMap.end()) {
		return b_checkArguments(numOfArgsMap[command], slicedCommands);
	}



	return false;
}
bool b_checkArguments(int numberOfArguments, vector<string>& slicedCommands) {
	if (slicedCommands.size() != numberOfArguments) return false;
	for (unsigned i = 1; i < slicedCommands.size(); i++) {
		if (!is_number(slicedCommands[i])) return false;
	}
	return true;
}
bool is_number(std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

vector<string> s_sliceCommand(string str) {
	vector<string> result;
	size_t pos = 0;
	string delimiter;
	delimiter = " ";
	while ((pos = str.find(delimiter)) != std::string::npos) {
		string token;
		token = str.substr(0, pos);
		str.erase(0, pos + delimiter.length());
		if (token.length()>0) result.push_back(token);
	}
	if (str != " " && str != "") result.push_back(str);
	return result;
}
