#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

#ifdef _WIN32
#include <windows.h>

string GbkToUtf8(const char* src_str);
string Utf8ToGbk(const char* src_str);
#else
#include <iconv.h>

int GbkToUtf8(char* str_str, size_t src_len, char* dst_str, size_t dst_len);

int Utf8ToGbk(char* src_str, size_t src_len, char* dst_str, size_t dst_len);


#endif


