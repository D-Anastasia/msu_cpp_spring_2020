#include <cstdio>
#include <iostream>
#include <cstring>
#include "parser.hpp"
using namespace std;
int len_numbers = 0, len_str = 0;

void f11(int n){
	cout << "number " << n <<  endl;
}
void f22(const char* str){
	cout << "str " << str << endl;
}
void f33(){
	cout << "Start parsing" << endl;
}
void f44(){
	cout << "End" << endl;
}
void f1(int n){
	len_numbers += 1;
}
void f2(const char* str){
	len_str += 1;
}

int main(void){
	register_on_number_callback(f11);
	register_on_str_callback(f22);
	register_begin(f33);
	register_end(f44);
	parse("abc 123 123a a123\t56\n omg u8\n ");

	register_on_number_callback(f1);
	register_on_str_callback(f2);
	register_begin(f33);
	register_end(f44);
	parse("abc 123 123a a123\t56\n omg u8\n ");

	if(len_numbers != 2){
		cout << "err" << endl;
	}
	if(len_str != 5){
		cout << "err" << endl;
	}
}