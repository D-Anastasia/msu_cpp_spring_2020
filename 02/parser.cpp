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
	char* tmp = new char[1];
	if (tmp == NULL){
		throw bad_alloc();
	}
	while(text[i] != '\0'){
		switch (condition){
			case 0:
				start_cur_token = i;
				if(text[i] >= '0' && text[i] <= '9'){
					condition = 1;
				} else if(text[i] != '\n' && text[i] != '\t' && text[i] != ' ') {
					condition = 2;
				}
				break;
			case 1:
				if(text[i] == '\n' || text[i] == '\t' || text[i] == ' '){
					if(i - start_cur_token > 0){
						delete[] tmp;
						tmp = new char[i - start_cur_token + 1];
						if (tmp == NULL){
							throw bad_alloc();
						}
						strncpy(tmp, text + start_cur_token, i - start_cur_token);
						tmp[i - start_cur_token] = '\0';
						if(Number != NULL) Number(tmp);
					}
					condition = 0;
				} else if(text[i] <= '0' || text[i] >= '9'){
					condition = 2;
				}
				break;
			case 2:
				if(text[i] == '\n' || text[i] == '\t' || text[i] == ' '){
					if(i - start_cur_token > 0){
						delete[] tmp;
						tmp = new char[i - start_cur_token + 1];
						if (tmp == NULL){
							throw bad_alloc();
						}
						strncpy(tmp, text + start_cur_token, i - start_cur_token);
						tmp[i - start_cur_token] = '\0';
						if(Str != NULL) Str(tmp);
					}
					condition = 0;
				}
				break;
		}
		i++;
	}
	delete[] tmp;
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