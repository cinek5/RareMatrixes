#pragma once
#include "CSparseMatrix.h"
#include <iostream>
#include <vector>
#include <string>
#include "stdafx.h"
using namespace std;
class RareMatrixes {
public:
	RareMatrixes();
	~RareMatrixes();
	void addMat(int num_of_dims,int* dims_range_array,int default_value,string name);
	void addMat(int num_of_dims,int* dims_range_array,int default_value);
	void deleteMat(int index);
	void deleteAll();
	void setName(int index,string name);
	void cloneMat(int index);
	void defVal(int index, int* coordinates, int value);
	void list();
	void print(int index);
	int getNumOfDims(int index);
	
	
private:
	vector<CSparseMatrix*> matrices;
	bool checkIndex(int index);
	bool checkCoordinates(int index, int* coordinates);
	void destroyMatrixes();


};
