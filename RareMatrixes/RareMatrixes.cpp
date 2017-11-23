// RareMatrixes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RareMatrixes.h"

RareMatrixes::RareMatrixes()
{
}

RareMatrixes::~RareMatrixes()
{
	destroyMatrixes();
}

void RareMatrixes::deleteMat(int index)
{  
	if (checkIndex(index)) {
		delete matrices[index];
		matrices.erase(matrices.begin() + index);
	}
}

void RareMatrixes::deleteAll()
{
	destroyMatrixes();
	matrices.clear();
}

void RareMatrixes::setName(int index, string name)
{
	if (checkIndex) {
		matrices[index]->setName(name);
	}
}

void RareMatrixes::cloneMat(int index)
{   
	if (checkIndex(index)) {
		CSparseMatrix * cell = new  CSparseMatrix(*matrices[index]);
		   
		matrices.push_back(cell);
	}
}

void RareMatrixes::defVal(int index, int * coordinates, int value)
{
	if (checkIndex && checkCoordinates) {
		matrices[index]->defineNewValue(coordinates, value);
	}
}

bool RareMatrixes::checkIndex(int index)
{
	if (index < matrices.size() && index>=0) return true;
	cout << "ERROR: INDEX OUT OF BOUNDS" << endl;
	return false;
}

bool RareMatrixes::checkCoordinates(int index, int * coordinates)
{
	CSparseMatrix * matrix = matrices[index];

	return matrix->checkCoordinatesBounds(coordinates);
}

void RareMatrixes::destroyMatrixes()
{
	for (unsigned i = 0; i < matrices.size(); i++) {
		delete matrices[i];
	}
}
