#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

void  v_handleSingleInput();
vector<string> s_sliceCommand(string str);
bool b_checkArguments(int numberOfArguments, vector<string>& slicedCommands);
bool b_checkCommand(vector<string>& slicedCommands);
bool is_number(string& s);
