#pragma once
#include<string>
#include "CSparseCell.h"
#include <iostream>
#include "Communicate.h"
#define DEFAULT_NAME "def_name"
#define DEFAULT_ALLOCATED_SPARSECELLS_ARRAY_SIZE 8
using namespace std;

class CSparseMatrix
{
public:
	CSparseMatrix();
	~CSparseMatrix();
	CSparseMatrix(string name, int num_of_dims, int *dims_range_array,int default_value);
	CSparseMatrix(CSparseMatrix & other);
	CSparseMatrix(int num_of_dims, int *dims_range_array,int default_value);
	void defineNewValue(int *coordinates, int value);
	void setDefaultValue(int newDefValue);
	int getValue(int *coordinates);
	int getNumOfDims();
	string getStringRepresentation();
	string getName();
	void setName(string name);
	bool checkCoordinatesBounds(int *coordinates);
	string getNameSizeStringRepresentation();


private:
	int default_value;
	int allocated_sparsecells_array_size;
	int num_of_dims;
	int *dims_range_array;
	int num_defined_cells;
	string name;
	CSparseCell **defined_cells;
	int findSparseCellIndex(int *coordinates);
	int findSparseCellIndex(CSparseCell & cell);
	int binarySearchHelper(CSparseCell & cell, int l, int r);
	void reallocateCellsArray(int newSize);
	void insertNewCell(CSparseCell* cell);
	void deleteCell(int index);
	void printCommunicate(Communicate communicate);
	void init(int num_of_dims, int *dims_range_array, int default_value);

	

};

