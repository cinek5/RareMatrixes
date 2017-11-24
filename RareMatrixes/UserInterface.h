#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "RareMatrixes.h"
using namespace std;
class UserInterface {

public:
	void  v_handleSingleInput();
	
private:
	vector<string> s_sliceCommand(string str);
	bool checkArguments(int numberOfArguments, vector<string>& slicedCommands);
	bool checkCommand(vector<string>& slicedCommands);
	bool is_number(string& s);
	bool checkAddmatArguments(vector<string>& slicedCommands);
	bool checkRenameArguments(vector<string>& slicedCommands);
	bool checkDefineArguments(vector<string>& slicedCommands);
	int* makeCoordsArray(int index,vector<string>& slicedCommands);
	int* makeNewCoordsArray(int num_of_dims, vector<string>& slicedCommands);
	RareMatrixes rareMatrixes;





};

