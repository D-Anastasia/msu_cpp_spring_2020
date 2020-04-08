#ifndef hw_05
#define hw_05

#include <iostream>

class BigInt {
	char *data;
	bool sign;
	size_t size;
	BigInt add(const BigInt& a,const BigInt& b);
	BigInt sub(const BigInt& a,const BigInt& b);
public:
	BigInt();
	BigInt(const BigInt &a);
	BigInt(int a);
	BigInt(char *data1,bool sign1,size_t size1);
	BigInt operator-();
	BigInt& operator=(const BigInt &a);
	bool operator<(const BigInt &a);
	bool operator<=(const BigInt &a);
	bool operator>(const BigInt &a);
	bool operator>=(const BigInt &a);
	bool operator==(const BigInt &a);
	bool operator!=(const BigInt &a);
	BigInt operator+(const BigInt& a);
	BigInt operator-(const BigInt& a);
	BigInt operator+(int a);
	BigInt operator-(int a);
	friend std::ostream& operator<<(std::ostream& out, const BigInt& num);
	~BigInt();
};

#endif