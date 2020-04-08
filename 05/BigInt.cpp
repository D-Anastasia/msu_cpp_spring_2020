#include <iostream>
#include <cstring>

#include "BigInt.hpp"

BigInt::BigInt(){
	sign = 0;
	size = 1;
	data = new char[1];
	data[0] = '0';
}
BigInt::BigInt(const BigInt &a){
	sign = a.sign;
	size = a.size;
	data = new char[size];
	std::copy(a.data, a.data + size, data);
}
BigInt::BigInt(char *data1,bool sign1,size_t size1){
	sign = sign1;
	size = size1;
	data = data1;
}
BigInt::BigInt(int a){
	sign = 0;
	if(a<0){
		sign = 1;
	}
	size = 0;
	int b = a;
	if(b<0){
		b = -b;
	}
	int c = b;
	while(b>0){
		b = b/10;
		size+=1;
	}
	if (size>0) data = new char[size];
	for(int i = 0;i<size;i++){
		data[i] = char(c%10+'0');
		c = c/10;
	}
	if(size == 0){
		char* tmp = new char[1];
		data = tmp;
		data[0] = '0';
		size = 1;
	}

}
BigInt BigInt::operator-(){
	BigInt res = *this;
	res.sign = !sign;
	return res;
}
bool BigInt::operator<(const BigInt &a){
	if(a.sign != sign){
		return sign<a.sign;
	} else if(a.size!=size){
		if(sign == 0){
			return size<a.size;
		} else{
			return size>a.size;
		}
	} else{
		int eq = 1;
		for(int i = size-1;i>=0;i--){
			if(data[i]<a.data[i]){
				return 1;
			} else if(data[i]>a.data[i]){
				return 0;
			}
		}
		return 0;
	}
}
bool BigInt::operator>(const BigInt &a){
	if(a.sign != sign){
		return sign>a.sign;
	} else if(a.size!=size){
		if(sign == 0){
			return size>a.size;
		} else{
			return size<a.size;
		}
	} else{
		int eq = 1;
		for(int i = size-1;i>=0;i--){
			if(data[i]>a.data[i]){
				return 1;
			} else if(data[i]<a.data[i]){
				return 0;
			}
		}
		return 0;
	}
}
bool BigInt::operator<=(const BigInt &a){
	return !(*this>a);
}
bool BigInt::operator>=(const BigInt &a){
	return !(*this<a);
}
BigInt& BigInt::operator=(const BigInt &a){
	if (this == &a) {
		return *this;
	}
	size = a.size;
	sign = a.sign;
	char* tmp = new char[size];
	delete[] data;
	data = tmp;
	std::copy(a.data, a.data + size, data);
	return *this;
}
bool BigInt::operator==(const BigInt &a){
	return (*this>a == 0) && (*this<a == 0);
}
bool BigInt::operator!=(const BigInt &a){
	return !(*this==a);
}
BigInt BigInt::add(const BigInt& a,const BigInt& b){
	int max_size = std::max(a.size, b.size) + 1;
	int min_size = std::min(a.size, b.size);
	char* tmp = new char[max_size];
	int p = 0;
	int k;
	for(int i = 0;i<min_size;i++){
		k = a.data[i]-'0'+ b.data[i]-'0' + p;
		p = 0;
		if(k>=10){
			p = 1;
		}
		tmp[i] = char(k%10+'0');
	}
	for(int i = min_size;i<max_size-1;i++){
		if(a.size>b.size){
			k = a.data[i]-'0' + p;
		} else{
			k = b.data[i]-'0' + p;
		}
		p = 0;
		if(k>=10){
			p = 1;
		}
		tmp[i] = char(k%10+'0');
	}
	if(p==1){
		tmp[max_size-1] = '1';
	} else{
		tmp[max_size-1] = '0';
	}
	if(tmp[max_size-1] == '0' && max_size!=1){
		char* tmp1 = new char[max_size-1];
		std::copy(tmp, tmp + max_size -1, tmp1);
		delete[] tmp;
		tmp = tmp1;
		max_size -=1;
	}
	BigInt res = BigInt(tmp,a.sign,max_size);
	return res;
}
BigInt BigInt::sub(const BigInt& a,const BigInt& b){
	int max_size = std::max(a.size, b.size);
	int min_size = std::min(a.size, b.size);
	char* tmp = new char[max_size];
	bool new_sign = a.sign;
	int max = 1;
	if(a.sign == 1){
		if(BigInt(a)>BigInt(b)){
			max = 0;
		}
	} else{
		if(BigInt(a)<BigInt(b)){
			max = 0;
		}
	}
	int p = 0;
	int k;
	for(int i = 0;i<min_size;i++){
		if(max){
			k = (a.data[i]-'0')- (b.data[i]-'0') - p+0;
		} else{
			k = (b.data[i]-'0')- (a.data[i]-'0') - p+0;
		}
		p = 0;
		if(k < 0){
			p = 1;
			k =k+10;
		}
		tmp[i] = char(k%10+'0');
	}
	for(int i = min_size;i<max_size;i++){
		if(max){
			k = a.data[i]-'0' - p;
		} else{
			k = b.data[i]-'0' - p;
		}
		p = 0;
		if(k<0){
			p = 1;
			k+=10;
		}
		tmp[i] = char(k%10+'0');
	}
	int u = max_size-1;
	for(int i = u;i>0;i--){
		if(tmp[i] == '0' && max_size!=1){
			char* tmp1 = new char[max_size-1];
			std::copy(tmp, tmp + max_size -1, tmp1);
			delete[] tmp;
			tmp = tmp1;
			max_size -=1;
		} else{
			break;
		}
	}
	if(!max){
		if(a.sign){
			new_sign = 0;
		} else{
			new_sign = 1;
		}
	}
	BigInt res = BigInt(tmp,new_sign,max_size);
	return res;
}
BigInt BigInt::operator+(const BigInt &a){
	if (sign == a.sign) {
		return add(*this, a);
	} else {
		if (sign) {
			return sub(*this, a);
		} else {
			return sub(a, *this);
		}
	}
	return *this;
}

BigInt BigInt::operator-(const BigInt& a) {
	if (sign == a.sign) {
		return sub(*this,a);
	} else {
		return add(*this, a);
	}
}
std::ostream& operator<<(std::ostream& out, const BigInt& num) {
	if (num.sign == 1){
		out << '-';
	}
	for (int i = num.size - 1; i >= 0; i--){
		out << num.data[i];
	}
	return out;
}     
BigInt BigInt::operator+(int a){
	return *this + BigInt(a);
}
BigInt BigInt::operator-(int a){
	return *this - BigInt(a);
}
BigInt::~BigInt() {
	delete[] data;
}