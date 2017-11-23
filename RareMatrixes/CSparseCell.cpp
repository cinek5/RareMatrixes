#include "stdafx.h"
#include "CSparseCell.h"
#include <iostream>

bool CSparseCell::hasEqualCoordinates(int * coordinates)
{   
	for (int i = 0; i < num_of_dims; i++) {
		if (this->coordinates[i] != coordinates[i]) return false;
	}
	return true;
}


bool CSparseCell::isMoreThan(CSparseCell * other)
{
	bool isMore = false;
	for (int i = 0; i < num_of_dims && !isMore; i++) {
		if (coordinates[i] > (other->coordinates[i])) {
			isMore = true;
		 }
   }

	return isMore;
}

int CSparseCell::getValue()
{
	return value;
}

CSparseCell::CSparseCell()
{
}

CSparseCell::CSparseCell(int num_of_dims, int * coordinates)
{
	
	init(num_of_dims, coordinates);

}

CSparseCell::CSparseCell(int num_of_dims, int * coordinates, int value)
{
	init(num_of_dims, coordinates);
	this->value = value;
}

CSparseCell::CSparseCell(CSparseCell & other)
{
	init(other.num_of_dims, other.coordinates);
	this->value = other.value;
}


CSparseCell::~CSparseCell()
{
	delete this->coordinates;
	
}

void CSparseCell::init(int num_of_dims, int * coordinates)
{
	this->num_of_dims = num_of_dims;
	this->coordinates = new int[num_of_dims];
	for (int i = 0; i<num_of_dims; i++)
		this->coordinates[i] = coordinates[i];
}
