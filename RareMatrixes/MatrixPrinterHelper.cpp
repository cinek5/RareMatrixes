#include "stdafx.h"
#include "MatrixPrinterHelper.h"


void MatrixPrinterHelper::reset()
{
	for (int i = 0; i < num_of_dims; i++) {
		coords[i] = 0;
	}
}

void MatrixPrinterHelper::tick()
{
	tick(num_of_dims - 1);
}

bool MatrixPrinterHelper::isDone()
{
	for (int i = 0; i < num_of_dims; i++) {
		if (coords[i] != dims_range_array[i] - 1) return false;
	}
	return true;
}

MatrixPrinterHelper::MatrixPrinterHelper(int num_of_dims, int * dims_range_array)
{
	this->dims_range_array = new int[num_of_dims];
	this->num_of_dims = num_of_dims;
	for (int i = 0; i < num_of_dims; i++) {
		this->dims_range_array[i] = dims_range_array[i];
	}
	this->coords = new int[num_of_dims];
	reset();
	
}

MatrixPrinterHelper::~MatrixPrinterHelper()
{
	delete coords;
	delete dims_range_array;
}

int * MatrixPrinterHelper::getCoords()
{
	return coords;
}

void MatrixPrinterHelper::tick(int index)
{
	if (index >= 0 && index < num_of_dims) {
		if (coords[index] + 1 <= dims_range_array[index] - 1) {
		    coords[index]++;
		}
		else {
			coords[index] = 0;
			tick(index - 1);

		}
	}

}
