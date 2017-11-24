#pragma once
#include "CSparseMatrix.h"
#include "stdafx.h"
#include "UserInterface.h"
using namespace std;

int main()
{
	UserInterface userInterface;
	while (true) {
		userInterface.v_handleSingleInput();
	}
	
}

