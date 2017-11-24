#include "stdafx.h"
#include <iostream>
#include <map>
#include "UserInterface.h"



using namespace std;

void UserInterface::v_handleSingleInput()
{
	string inputLine;
	getline(cin, inputLine);
	if (!inputLine.empty())
	{
		map<string, int >  commandsMap;
		commandsMap["ADDMAT"] = 0;
		commandsMap["DEF"] = 1;
		commandsMap["CLONE"] = 2;
		commandsMap["PRINT"] = 3;
		commandsMap["RENAME"] = 4;
		commandsMap["DEL"] = 5;
		commandsMap["DELALL"] = 6;
		commandsMap["LIST"] = 7;
		for (string::size_type i = 0; i < inputLine.length(); i++)
		{
			inputLine[i] = toupper(inputLine[i]);
		}
		vector<string> slicedCommands = s_sliceCommand(inputLine);
		string command = slicedCommands[0];

		if (checkCommand(slicedCommands)) {
			switch (commandsMap[command]) {
			case 0: // ADDMAT 
			{
				int num_of_dims = stoi(slicedCommands[1]);
				int default_value = stoi(slicedCommands[num_of_dims + 2]);
				int *dims_range_array = makeNewCoordsArray(num_of_dims, slicedCommands);
				if (slicedCommands.size() == num_of_dims + 4) {
					rareMatrixes.addMat(num_of_dims, dims_range_array, default_value, slicedCommands[num_of_dims + 3]);
				}
				else {
					rareMatrixes.addMat(num_of_dims, dims_range_array, default_value);
				}

				delete dims_range_array;
			}
			break;
			case 1: //DEF
			{
				int index = stoi(slicedCommands[1]);
				int * coordinates = makeCoordsArray(index, slicedCommands);
				int value = stoi(slicedCommands[slicedCommands.size() - 1]);
				rareMatrixes.defVal(index, coordinates, value);
				delete coordinates;
			}
			break;
			case 2: // CLONE
			{
				rareMatrixes.cloneMat(stoi(slicedCommands[1]));
			}
			break;
			case 3: // PRINT
				rareMatrixes.print(stoi(slicedCommands[1]));

				break;
			case 4: // RENAME
			{
				rareMatrixes.setName(stoi(slicedCommands[1]), slicedCommands[2]);
			}
			break;
			case 5: // DEL
			{
				rareMatrixes.deleteMat(stoi(slicedCommands[1]));
			}
			break;
			case 6: //DELALL
			{
				rareMatrixes.deleteAll();
			}
			break;
			case 7: //list
				rareMatrixes.list();
				break;



			}
		}
		else {
			cout << "WRONG COMMAND, TRY AGAIN" << endl;
		}
	}
	else {
		cout << "empty line" << endl;
	}

}

vector<string> UserInterface::s_sliceCommand(string str)
{
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

bool UserInterface::checkArguments(int numberOfArguments, vector<string>& slicedCommands)
{
	if (slicedCommands.size() != numberOfArguments) return false;
	for (unsigned i = 1; i < slicedCommands.size(); i++) {
		if (!is_number(slicedCommands[i])) return false;
	}
	return true;
}

bool UserInterface::checkCommand(vector<string>& slicedCommands)
{
	map<string, int>::iterator it;
	map<string, int>  numOfArgsMap;
	numOfArgsMap["ADDMAT"] = -1;
	numOfArgsMap["LIST"] = 1;
	numOfArgsMap["DEF"] = -3;
	numOfArgsMap["RENAME"] = -2;
	numOfArgsMap["PRINT"] = 2;
	numOfArgsMap["DEL"] = 2;
	numOfArgsMap["DELALL"] = 1;
	numOfArgsMap["CLONE"] = 2;
	string command = slicedCommands[0];
	it = numOfArgsMap.find(command);
   

	if (it != numOfArgsMap.end()) {
		int numberOfArgs = numOfArgsMap[command];
		switch (numberOfArgs) {
		case -1:
		
			return checkAddmatArguments(slicedCommands);
			break;
		case -2:
			return checkRenameArguments(slicedCommands);
			break;
		case -3:
			return checkDefineArguments(slicedCommands);
			break;
		default:
			return checkArguments(numOfArgsMap[command], slicedCommands);
			break;
	    
		}
		




	
	}

	return false;
}

bool UserInterface::is_number(string & s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool UserInterface::checkAddmatArguments(vector<string>& slicedCommands)
{
	
	int num_of_args = slicedCommands.size();
	
	if (num_of_args < 2) return false; else if (num_of_args < stoi(slicedCommands[1]) + 3)  return false; 
	if (!is_number(slicedCommands[1])) return false;
	int num_of_dims = stoi(slicedCommands[1]);
	
	if (slicedCommands.size() != num_of_dims + 3 && slicedCommands.size() != num_of_dims + 4) return false;
	for (int i = 2; i < num_of_dims + 2;i++) {
		
		if (!is_number(slicedCommands[i])) return false;
	}
	
	return true;
}

bool UserInterface::checkRenameArguments(vector<string>& slicedCommands)
{
	if (slicedCommands.size() < 3) return false;
	if (!is_number(slicedCommands[1])) return false;
	if (is_number(slicedCommands[2])) return false;
	return true;
}

bool UserInterface::checkDefineArguments(vector<string>& slicedCommands)
{
	int num_of_args = slicedCommands.size();
	if (num_of_args < 2) return false; else if (num_of_args < stoi(slicedCommands[1])+2) return false;
	if (!is_number(slicedCommands[1])) return false;
	int num_of_dims = rareMatrixes.getNumOfDims(stoi(slicedCommands[1]));
	if (slicedCommands.size() != num_of_dims + 3) return false;
	for (int i = 2; i < num_of_dims + 3; i++) {
		if (!is_number(slicedCommands[i])) return false;
	}
	return true;
}

int * UserInterface::makeCoordsArray(int index, vector<string>& slicedCommands)
{
	int num_of_dims = rareMatrixes.getNumOfDims(index);
	
	return makeNewCoordsArray(num_of_dims,slicedCommands);
}

int * UserInterface::makeNewCoordsArray(int num_of_dims, vector<string>& slicedCommands)
{
	int* coordinates = new int[num_of_dims];
	for (int i = 2; i < num_of_dims + 2; i++) {
		coordinates[i - 2] = stoi(slicedCommands[i]);
	}
	return coordinates;
}

