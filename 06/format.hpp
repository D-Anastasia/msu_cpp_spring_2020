#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <string>



template<class T>
void process(std::vector <std::string> &v, T &&cur) {
	std::stringstream s;
    s << cur;
    v.push_back(s.str());
}

template<class T, class... Args>
void process(std::vector <std::string> &v, T &&cur, Args &&... args) {
	std::stringstream s;
	s << cur;
	v.push_back(s.str());
	process(v, args...);
}

template<class... Args>
std::string format(std::string str, Args &&... args) {
	std::vector <std::string> v;
	std::string res;
	res = "";
	std::string num;
	num = "";
	process(v, args...);
	int cond = 0;
	for(int i = 0; i < str.size(); i++){
		switch(cond){
			case 0:
				if(str[i] == '{'){
					cond = 1;
				} else if(str[i] == '}'){
					throw std::runtime_error("");
				}else{
					res += str[i];
				} 
				break;
			case 1:
				if(isdigit(str[i])){
					num += str[i];
				} else if(str[i] == '}'){
					cond = 0;
					if(num.size() > 0){
						int a = atoi(num.c_str());
						if(a < v.size()){
							res += v[a];
						} else{
							throw std::runtime_error("");
						}
					} else{
						throw std::runtime_error("");
					}
					num = "";
				} else{
					throw std::runtime_error("");
				}
				break;
		}
	}
	return res;
}