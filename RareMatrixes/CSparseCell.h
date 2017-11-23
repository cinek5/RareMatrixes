#pragma once
class CSparseCell
{
public:
	friend class CSparseMatrix;
	bool hasEqualCoordinates(int *coordinates);
	bool isMoreThan(CSparseCell* other);
	int getValue();
	CSparseCell();
	CSparseCell(int num_of_dims, int *coordinates);
	CSparseCell(int num_of_dims, int *coordinates,int value);
	CSparseCell(CSparseCell &other);
	~CSparseCell();
	
private: 
	int num_of_dims;
	int *coordinates;
	int value;
	void init(int num_of_dims, int *coordinates);
	

};

