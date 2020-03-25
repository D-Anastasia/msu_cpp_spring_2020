#ifndef P_03
#define P_03

class Matrix{
	size_t rows;
	size_t cols;
	int**M;
public:
	struct proxy {
		int *row;
		size_t c;
		proxy(int* s,size_t col);
		int& operator[](size_t j);
	};
	Matrix(size_t r,size_t c);
	size_t getRows();
	size_t getColumns();
	Matrix& operator*=(int k);
	proxy operator[](size_t i);
	bool operator==(const Matrix& b);
	bool operator!=(const Matrix& b);
	~Matrix();
};

#endif