#include <cstdio>
#include <iostream>
#include <cstring>
#include "matrix.hpp"

Matrix::proxy::proxy(int* s,int col){
	row = s;
	c=col;
}

int& Matrix::proxy::operator[](int j) {
	if(j>=c || j<0){
		throw std::out_of_range("");
	}
	return row[j];
}
Matrix::Matrix(const int& r,const int &c){
	rows = r;
	cols = c;
	M = new int*[rows];
	for (int i = 0;i<rows;i++){
		M[i] = new int[cols];
	}
}
int Matrix::getRows(){
	return rows;
}
int Matrix::getColumns(){
	return cols;
}
Matrix::proxy Matrix::operator[](int i) {
	if(i>=rows || i<0){
		throw std::out_of_range("");
	}
	return proxy(M[i],cols);
}
Matrix& Matrix::operator*=(int k) {
 	for(int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){
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
bool Matrix::operator==(Matrix& b) {
	if(this->rows!=b.rows){
		std::cout<<"a";
		return false;
	}
	if(this->cols!=b.cols){
		std::cout<<"b";
		return false;
	}
	for(int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){
			if(this->M[i][j]!=b.M[i][j]){
				std::cout<<"a";
				return false;
			}
		}
	}
	return true;
}