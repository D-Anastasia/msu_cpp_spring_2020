#ifndef P_02
#define P_02

using OnNumber = void(*)(const char* number);
using OnStr = void(*)(const char* str);
using OnBegin = void(*)();
using OnEnd = void(*)();
extern OnNumber Number;
extern OnStr Str;
extern OnBegin Begin;
extern OnEnd End;
void parse(const char*);
void register_on_number_callback(OnNumber callback);
void register_on_str_callback(OnStr callback);
void register_begin(OnBegin callback);
void register_end(OnEnd callback);


#endif