#include "helperfunctions.h"
#include "stdafx.h"


void copyIntArray(int * toCopy, int * newArray, int range)
{
	for (int i = 0; i < range; i++) {
		newArray[i] = toCopy[i];
	}
}





