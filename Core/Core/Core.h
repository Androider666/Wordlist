#pragma once
#include <iostream>
using namespace std;
#pragma once
typedef struct struct1 {
	char h;
	char t;
	char *word;
}Word, *WORD;
int LONG(WORD *wod, int len, char *result[], int H, int T, char _h, char _t, int mark);
int nocircle(WORD words[], int len);
int in_array(char *arr, int len, char cc);
class _declspec(dllexport) Core {
public:
	int static gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int static gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	bool static has_circle(char *words[], int len);
	int static readfile(char *path, char *words[]);
};