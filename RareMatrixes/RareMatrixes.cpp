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

void RareMatrixes::addMat(int num_of_dims, int * dims_range_array, int default_value, string name)
{
	if (checkRange(dims_range_array, num_of_dims)) {
		CSparseMatrix* newMatrix = new CSparseMatrix(name, num_of_dims, dims_range_array, default_value);
		matrices.push_back(newMatrix);
	}
}

void RareMatrixes::addMat(int num_of_dims, int * dims_range_array, int default_value)
{
	if (checkRange(dims_range_array, num_of_dims)) {
		CSparseMatrix* newMatrix = new CSparseMatrix(num_of_dims, dims_range_array, default_value);
		matrices.push_back(newMatrix);
		
	}
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
	if (checkIndex(index)) {
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
	if (checkIndex(index) && checkCoordinates(index,coordinates)) {
		matrices[index]->defineNewValue(coordinates, value);
	}
}

void RareMatrixes::list()
{   
    
	int num_of_matrices = matrices.size();
	if (num_of_matrices == 0) cout << "0 matrices."<<endl;
	else {
		cout << num_of_matrices << " matrices: " << endl; 
		for (int i = 0; i < num_of_matrices;i++) {
			cout << "[" << i << "] - " << matrices[i]->getNameSizeStringRepresentation() << endl;

		}
	}
}

void RareMatrixes::print(int index)
{
	if (checkIndex(index)) cout << matrices[index]->getStringRepresentation() << endl;
}

int RareMatrixes::getNumOfDims(int index)
{
	if (checkIndex(index)) return matrices[index]->getNumOfDims();
	else return -1;
	 
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
	bool areCoordsOk= matrix->checkCoordinatesBounds(coordinates);
	if (!areCoordsOk) cout << "ERROR: WRONG COORDINATES" << endl;
	return areCoordsOk;
}

bool RareMatrixes::checkRange(int * dims_array_range, int num_of_dims)
{   
	for (int i = 0; i < num_of_dims; i++) {
		if (dims_array_range[i] <= 0) {
			cout << "ERROR: WRONG DIMS RANGES" << endl;
			return false;
		}
	}
	return true;
}

void RareMatrixes::destroyMatrixes()
{
	for (unsigned i = 0; i < matrices.size(); i++) {
		delete matrices[i];
	}
}
