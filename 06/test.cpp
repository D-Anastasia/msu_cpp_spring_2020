#include <iostream>
#include"format.hpp"
#include <cassert>
#include <sstream>
int main(){
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");
	auto text1 = format("{10} something {1} something {0}", 2, "one", 1, 1, 1, 1, 1, 1, 1, 1, 2);
	assert(text1 == "2 something one something 2");
}