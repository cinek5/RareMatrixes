#include "stdafx.h"
#include "CSparseMatrix.h"
#include "helperfunctions.h"

CSparseMatrix::CSparseMatrix()
{
	this->name = DEFAULT_NAME;

	printCommunicate(CREATE);
}


CSparseMatrix::~CSparseMatrix()
{    
	delete this->dims_range_array;
	
	for (int i = 0; i < num_defined_cells; i++) {
		delete  defined_cells[i];
	}
	
	delete[] defined_cells;
	printCommunicate(DESTROY);
	
}
CSparseMatrix::CSparseMatrix( CSparseMatrix &other)
{
	this->name = other.name+"_copy";
	this->default_value = other.default_value;
	this->allocated_sparsecells_array_size = other.allocated_sparsecells_array_size;
	this->num_of_dims = other.num_of_dims;
	this->dims_range_array = new int[num_of_dims];
	copyIntArray(other.dims_range_array, dims_range_array, num_of_dims);
	this->num_defined_cells = other.num_defined_cells;
	this->defined_cells = new CSparseCell*[allocated_sparsecells_array_size];
	for (int i = 0; i < num_defined_cells; i++) {
		CSparseCell* cell = new CSparseCell(*other.defined_cells[i]);
		defined_cells[i] = cell;
	}

	

}

CSparseMatrix::CSparseMatrix(string name, int num_of_dims, int * dims_range_array,int default_value)
{
	init(num_of_dims, dims_range_array, default_value);
	this->name = name;
	printCommunicate(CREATE);
}

CSparseMatrix::CSparseMatrix(int num_of_dims, int * dims_range_array, int default_value)
{
	init(num_of_dims, dims_range_array, default_value);
	printCommunicate(CREATE);

}

void CSparseMatrix::defineNewValue(int * coordinates, int value)
{   
	int index = findSparseCellIndex(coordinates);

	
	if (value != default_value) { // value is other than default value
		if (index != -1) { // value under specified coordinates already exists, needs to be swaped
			defined_cells[index]->value = value;
		}
		else { // new CSparseCell object needs  to be created
			
			if (num_defined_cells + 1 > allocated_sparsecells_array_size) { // realocate the array if it's too small
				reallocateCellsArray(allocated_sparsecells_array_size * 2);
			} 
		
			CSparseCell* newCell = new CSparseCell(num_of_dims, coordinates, value);
			insertNewCell(newCell);
		}
	} else { // now we have to check if deletion is needed
		if (index != -1) {
			deleteCell(index);
			
			if (allocated_sparsecells_array_size >= num_defined_cells * 2)
				reallocateCellsArray(allocated_sparsecells_array_size * 3 / 4);
				
		}
	}

}
void CSparseMatrix::insertNewCell(CSparseCell * cell)
{
	int i = num_defined_cells;
	while (i > 0 && (defined_cells[i-1]->isMoreThan(cell) )  )  {
		defined_cells[i] = defined_cells[i - 1];
		i--;
	}
	defined_cells[i] = cell;
	num_defined_cells++;
}

void CSparseMatrix::deleteCell(int index)
{
	int i = index; 
	delete defined_cells[index];
	while (i < num_defined_cells - 1) {
		defined_cells[i] = defined_cells[i + 1];
		i++;
	}
	num_defined_cells--;
	
}

void CSparseMatrix::printCommunicate(Communicate communicate)
{
	
	if (communicate == CREATE) {
		cout << "create: " << name << endl;
	}
	else if (communicate == DESTROY) {
		cout << "destroy: " << name << endl;
	}
	
}

void CSparseMatrix::init(int num_of_dims, int * dims_range_array, int default_value)
{
	this->name = DEFAULT_NAME;
	this->num_of_dims = num_of_dims;
	this->dims_range_array = new int[num_of_dims];
	for (int i = 0; i <num_of_dims; i++) {
		this->dims_range_array[i] = dims_range_array[i];
	}
	this->default_value = default_value;
	defined_cells = new CSparseCell*[DEFAULT_ALLOCATED_SPARSECELLS_ARRAY_SIZE];
	allocated_sparsecells_array_size = DEFAULT_ALLOCATED_SPARSECELLS_ARRAY_SIZE;
}

bool CSparseMatrix::checkCoordinatesBounds(int * coordinates)
{
	for (int i = 0; i < num_of_dims; i++) {
		if (dims_range_array[i] <= coordinates[i]) return false;
	}
	return true;
}

string CSparseMatrix::getNameSizeStringRepresentation()
{

	string matrix_representation;
	matrix_representation = this->name;
	matrix_representation += " size: [ ";
	for (int i = 0; i < num_of_dims; i++) {
		matrix_representation += to_string(dims_range_array[i]);
		matrix_representation += " ";
	}

	matrix_representation += " ]";

	return matrix_representation;
}


void CSparseMatrix::setDefaultValue(int newDefValue)
{   
	
	this->default_value = newDefValue;
	for (int i = 0; i < num_defined_cells; i++) {
		if (defined_cells[i]->value == default_value) deleteCell(i);
	}
}

int CSparseMatrix::getValue(int * coordinates)
{   
	int index = findSparseCellIndex(coordinates);
    
	if (index != -1) return defined_cells[index]->value;
	else return default_value;
}

int CSparseMatrix::getNumOfDims()
{
	return num_of_dims;
}

string CSparseMatrix::getStringRepresentation()
{
	
	string matrix_representation;
	matrix_representation = "size: [ ";
	for (int i = 0; i < num_of_dims; i++) {
		matrix_representation += to_string(dims_range_array[i]);
		matrix_representation += " ";
	}

	matrix_representation += " ] values: ";
	
	for (int i = 0; i < num_defined_cells; i++) {
		matrix_representation += "[ ";
		CSparseCell * cell = defined_cells[i];
		for (int j = 0; j < num_of_dims; j++) {
			
			matrix_representation += to_string(cell->coordinates[j]);
		    matrix_representation += " ";
		}
		matrix_representation += "]: ";
	    matrix_representation += to_string(cell->getValue());
		matrix_representation += "; ";
	}


	

	/*
	int current_csparsecell_index = 0;
    
	for (int i = 0; i < num_of_dims; i++) {
		for (int j = 0; j < dims_range_array[i]; j++) {

		}
	}

	return string();
	*/
	return matrix_representation;
}

string CSparseMatrix::getName()
{
	return this->name;

}

void CSparseMatrix::setName(string name)
{
	this->name = name;
}

int CSparseMatrix::findSparseCellIndex(int * coordinates)
{
	
	CSparseCell tempCell(num_of_dims, coordinates);
	
	return binarySearchHelper(tempCell, 0, num_defined_cells-1);
}
int CSparseMatrix::findSparseCellIndex(CSparseCell & cell)
{
	return binarySearchHelper(cell, 0, num_defined_cells-1);
}
int CSparseMatrix::binarySearchHelper(CSparseCell & cell, int left, int right)
{
	if (left<=right && num_defined_cells>0)
	{
		int mid = left + ( (right - left) / 2) ;
		
		if (cell.hasEqualCoordinates(defined_cells[mid]->coordinates))  return mid;

	
		if (defined_cells[mid]->isMoreThan(&cell)) return binarySearchHelper(cell,left, mid-1 );

		
		return binarySearchHelper(cell, mid+1, right);
	}
	return -1;
}

void CSparseMatrix::reallocateCellsArray(int newSize)
{
	
	CSparseCell** new_cells_array = new (CSparseCell*[newSize]);
	
	allocated_sparsecells_array_size = newSize;
	for (int i = 0; i < num_defined_cells; i++) {
		new_cells_array[i] = defined_cells[i];
	}
    
	delete [] defined_cells; //kasuje nieuzywane wskazniki
	defined_cells = new_cells_array;
}


