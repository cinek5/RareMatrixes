#pragma once
#include <cstdlib>
#include <vector>
using namespace std;

class MatrixPrinterHelper
{
public:
	void reset();
	void tick();
	bool isDone();
	MatrixPrinterHelper(int num_of_dims, int* dims_range_array);
	~MatrixPrinterHelper();
	int* getCoords();
private: 

	int num_of_dims;
	int* dims_range_array;
	int* coords;
	void tick(int index);
};

