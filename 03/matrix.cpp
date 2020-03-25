#include <cstdio>
#include <iostream>
#include <cstring>
#include "matrix.hpp"

Matrix::proxy::proxy(int* s,size_t col){
	row = s;
	c=col;
}

int& Matrix::proxy::operator[](size_t j) {
	if(j>=c || j<0){
		throw std::out_of_range("");
	}
	return row[j];
}
Matrix::Matrix(size_t r, size_t c){
	rows = r;
	cols = c;
	M = new int*[rows];
	for (size_t i = 0;i<rows;i++){
		M[i] = new int[cols];
	}
}
size_t Matrix::getRows(){
	return rows;
}
size_t Matrix::getColumns(){
	return cols;
}
Matrix::proxy Matrix::operator[](size_t i) {
	if(i>=rows || i<0){
		throw std::out_of_range("");
	}
	return proxy(M[i],cols);
}
Matrix& Matrix::operator*=(int k) {
 	for(size_t i = 0;i<rows;i++){
		for (size_t j = 0;j<cols;j++){
			M[i][j] *= k;
		}
	}
	return *this;
}
Matrix::~Matrix(){
	if (M != NULL){
		for (int i = 0; i < rows; i++){
			if(M[i] != NULL) delete[] M[i];
		}
		delete[] M;
	}
}
bool Matrix::operator==(const Matrix& b) {
	if(rows!=b.rows){
		return false;
	}
	if(cols!=b.cols){
		return false;
	}
	for(int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){
			if(M[i][j]!=b.M[i][j]){
				return false;
			}
		}
	}
	return true;
}
bool Matrix::operator!=(const Matrix& b) {
	return !(*this==b);
}