#pragma once
#include "CSparseMatrix.h"
using namespace std;

int main()
{

	int * a = new int[3];
	a[0] = 3;
	a[1] = 2;
	a[2] = 1;
	CSparseMatrix*  matryca = new CSparseMatrix(3, a, 0);


	int *coords = new int[3];
	coords[0] = 2;
	coords[1] = 1;
	coords[2] = 0;
	matryca->defineNewValue(coords, 4);
	cout << matryca->getStringRepresentation() << endl;

	int *coords2 = new int[3];
	coords2[0] = 1;
	coords2[1] = 1;
	coords2[2] = 0;
	matryca->defineNewValue(coords2, 3);
	int *coords3 = new int[3];
	coords3[0] = 1;
	coords3[1] = 0;
	coords3[2] = 0;
	matryca->defineNewValue(coords3, 6);
	coords3[0] = 0;
	matryca->defineNewValue(coords3, 47);

	matryca->defineNewValue(coords2, 4);

	cout << matryca->getStringRepresentation() << endl;
	delete a;
	delete coords;
	delete coords3;
	delete coords2;
	delete matryca;
	return 0;
}

