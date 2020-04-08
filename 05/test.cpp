#include <iostream>
#include "BigInt.hpp"
#include <cassert>
#include <sstream>
int main()
{
	BigInt a = 1;
	BigInt b = a;
	BigInt c = a + b + 2;
	std::cout<<c<<std::endl;
	BigInt a5 = BigInt(100);
	BigInt b1 = BigInt(100);
	std::cout<<b1+a5<<std::endl;
	BigInt d = b1-a5;
	std::cout<<d<<std::endl;
	BigInt a1(1000000000);
	std::cout << a1 << std::endl;
	BigInt a2 = 2000000000;
	std::cout << a1 + a2 << std::endl;
	std::cout << a1 - a2 << std::endl;
	BigInt a3 = a2;
	std::cout << a3 - a2 << std::endl;
	std::cout << (a3 == a2) << std::endl;
	std::cout << (a1 < a2) << std::endl;
	std::cout << (a3 <= a2) << std::endl;
	a3 = a3 + 10;
	std::cout << -a3 << std::endl;
	return 0;
}