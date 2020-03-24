#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>

#include"matrix.hpp"

int main(void){
	Matrix a(2,3);
	for(int i = 0;i<2;i++){
		for (int j = 0;j<3;j++){
			a[i][j] = 1;
		}
	}
	Matrix a1(2,3);
	for(int i = 0;i<2;i++){
		for (int j = 0;j<3;j++){
			a1[i][j] = 1;
		}
	}
	bool b = (a1==a);
	assert(b==1);
	assert(a[0][1]==1);
	a[0][1] = 2;
	a *= 3;
	assert(a[0][1]==6);
	assert(a[0][2]==3);
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);

	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);


	
}