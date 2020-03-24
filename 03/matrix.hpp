#ifndef P_03
#define P_03

class Matrix{
	int rows;
	int cols;
	int**M;
public:
	struct proxy {
		int *row;
		int c;
		proxy(int* s,int col);
		int& operator[](int j);
	};
	Matrix(const int& r,const int &c);
	int getRows();
	int getColumns();
	Matrix& operator*=(int k);
	proxy operator[](int i);
	bool operator==(Matrix& b);
	~Matrix();
};

#endif