#include <cstdio>
#include <iostream>
#include <cstring>
#include "parser.hpp"
using namespace std;


OnNumber Number;
OnStr Str;
OnBegin Begin;
OnEnd End;

void parse(const char* text){
	if (Begin != NULL) Begin();
	int i = 0, start_cur_token = 0;
	int condition = 0;
	const int start_token = 0, number_token = 1, str_token = 2;
	string token = "";
	while(text[i] != '\0'){
		switch (condition){
			case start_token:
				start_cur_token = i;
				if(isdigit(text[i])){
					condition = number_token;
					token = text[i];
				} else if(!isspace(text[i])) {
					condition = str_token;
					token = text[i];
				}
				break;
			case number_token:
				if(isspace(text[i])){
					if(i - start_cur_token > 0){
						if(Number != NULL) Number(atoi(token.c_str()));
					}
					token = "";
					condition = start_token;
				} else if(!isdigit(text[i])){
					condition = str_token;
					token += text[i];
				} else{
					token += text[i];
				}
				break;
			case str_token:
				if(isspace(text[i])){
					if(i - start_cur_token > 0){
						if(Str != NULL) Str(token.c_str());		
					}
					token = "";
					condition = start_token;
				}
				token += text[i];
				break;
		}
		i++;
	}
	if (End != NULL) End();

}

void register_on_number_callback(OnNumber callback){
	Number = callback;
}
void register_on_str_callback(OnStr callback){
	Str = callback;
}
void register_begin(OnBegin callback){
	Begin = callback;
}
void register_end(OnEnd callback){
	End = callback;
}