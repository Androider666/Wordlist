#include"pch.h"
#include <iostream>
#include<stdio.h>
#include<fstream>
#include<filesystem>
#include<string.h>
//////////////////
////////////////////
using namespace std;
typedef struct struct1 {
	char h;
	char t;
	char *word;
}Word, *WORD;     //structure to record words' information
void initial(int argc, char **argv);
void Error(int n); //handle errors,print messages according to n
int nocircle(WORD words[],int len);   //return 1 when no circle, return 0 when exist circle(s)
int in_array(char *arr, int len, char cc);//return index of cc in arr,else return -1
void LONG(WORD *wod, int len, int H, int T, char _h, char _t);//searching words-chain made up with most words or chars
int W=0, C=0, H=0, T=0, R=0;//when -w -c -h -t -r occur in argvs,being 1; else  keeping 0
int max_words = 0, max_chs = 0, n_chs = 0;//number of words,chars,(words when most chars)
int tmp_words = 0, tmp_chs = 0;//number of words ,chars in current words-chain
int *wordchain, *charchain;  //record longest words-chain of most words and most chars
int *tmpwords; //record current words-chain
int nocircle_int = 1; //store returned value of function nocircle
char _h='\0', _t='\0'; //store character after -h and -t
char *path;  //store path of input file
ifstream infile;
FILE *file;
errno_t err;
int TOP = -1;  //head of words stack
WORD words[10000]; //words stack
int *index[26][26];
int *parent[26][26];
int *lens[26][26];

int main(int argc,char **argv)
{
	
	int i, j;

	initial( argc, argv);

	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			index[i][j] = new int[10000];
			lens[i][j] = new int[10000];
			parent[i][j] = new int[10000];
			index[i][j][0] = 0;
			lens[i][j][0] = 0;
			parent[i][j][0] = 0;
		}
	}

	if (R == 0) {
		nocircle_int = nocircle(words,TOP+1);
		if (nocircle_int == 0) {
			Error(6);
		}
		else {
			LONG(words, TOP + 1, H, T, _h, _t);
			if (W == 1) {
				cout << "max_words:" << max_words << " ";
				for (i = 0; i < max_words; i++) {
					cout << words[wordchain[i]]->word << '-';
				}
				try {
					err = fopen_s(&file, "./solution.txt", "w");
					if (err != 0)Error(7);
					for (i = 0; i < max_words; i++) {
						fprintf(file, words[wordchain[i]]->word);
						if (i != (max_words - 1))fprintf(file, "\n");
					}
				}
				catch (...) {
					Error(7);
				}
			}
			else if (C == 1) {
				cout << "n_maxchars:" << n_chs << ' ';
				for (i = 0; i < n_chs; i++) {
					cout << words[charchain[i]]->word << '-';
				}
				try {
					err = fopen_s(&file, "./solution.txt", "w");
					if (err != 0)Error(7);
					else {
						for (i = 0; i < n_chs; i++) {
								fprintf(file, words[charchain[i]]->word);
								if (i != (max_words - 1))fprintf(file, "\n");
						}
					}
				}
				catch (...) {
					Error(7);
				}
			}
		}
	}
	else if (R == 1) {
		LONG(words, TOP + 1, H, T, _h, _t);
		if (W == 1) {
			cout << "max_words:" << max_words << " ";
			for (i = 0; i < max_words; i++) {
				cout << words[wordchain[i]]->word << '-';
			}
			try {
				err = fopen_s(&file, "./solution.txt", "w+");
				if (err != 0)Error(7);
				else {
					for (i = 0; i < max_words; i++) {
						fprintf_s(file, words[wordchain[i]]->word);
						if (i != (max_words - 1))fprintf_s(file, "\n");
					}
				}
				fclose(file);
			}
			catch (...) {
				Error(7);
			}
		}
		else if (C == 1) {
			cout << "n_maxchars:" << n_chs << ' ';
			for (i = 0; i < n_chs; i++) {
				cout << words[charchain[i]]->word << '-';
			}
			try {
				err = fopen_s(&file, "./solution.txt", "w+");
				if (err != 0)Error(7);
				else {
					for (i = 0; i < n_chs; i++) {
						fprintf_s(file, words[charchain[i]]->word);
						if (i != (max_words - 1))fprintf_s(file, "\n");
					}
				}
				fclose(file);
			}
			catch (...) {
				Error(7);
			}
		}
	}

	return 0;
}
void initial(int argc, char **argv) {
	int i, j, top = -1, flag = 0;
	char cc = ' ', *tpwd,*path;
	path = new char[100];
	tpwd = new char[100];
	for (i = 0; i < 10000; i++) {
		words[i] = (WORD)malloc(sizeof(Word));
	}
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-r") == 0) {
			R = 1;
		}
		else if (strcmp(argv[i], "-w") == 0) {
			W = 1;
		}
		else if (strcmp(argv[i], "-c") == 0) {
			C = 1;
		}
		else if (strcmp(argv[i], "-h") == 0) {
			if (i < (argc - 1)) {
				if (strlen(argv[i + 1]) == 1 && (argv[i + 1][0]>='a') && (argv[i + 1][0]<='z')) {
					H = 1;
					_h = argv[i + 1][0];
					i++;
				}
				else {
					Error(1);
				}
			}
			else Error(1);
		}
		else if (strcmp(argv[i], "-t") == 0) {
			if (i < (argc - 1)) {
				if (strlen(argv[i + 1]) == 1 && (argv[i + 1][0]>='a') && (argv[i + 1][0] <='z')) {
					T = 1;
					_t = argv[i + 1][0];
					i++;
				}
				else Error(2);
			}
			else {
				Error(2);
			}
		}
		else {
			if (i != (argc - 1)) {
				Error(3);
			}
			else {
				strcpy_s(path, strlen(argv[argc - 1])+1, argv[argc - 1]);
			}
		}

	}
	try {
		infile.open(path);
		if (!infile) {
			Error(4);
		}
		infile >> noskipws;
		while (!infile.eof()) {
			cc = infile.get();
			if (cc >= 'a'&&cc <= 'z') {
				tpwd[++top] = cc;
			}
			else if (cc >= 'A'&&cc <= 'Z') {
				cc += 32;
				tpwd[++top] = cc;
			}
			else {
				tpwd[++top] = '\0';
				if (strlen(tpwd) > 1) {
					for (j = 0; j <= TOP; j++) {
						if (strcmp(words[j]->word, tpwd) == 0) {
							flag = 1;
							break;
						}
					}
					if (flag == 0) {
						if (R == 0 && TOP >= 9999)Error(8);
						if (R == 1 && TOP >= 99)Error(9);
						//words[++TOP] = (Word *)malloc(sizeof(Word));
						//words[++TOP] = new Word();
						TOP++;
						if (TOP < 10000) {
							words[TOP]->h = tpwd[0];
							words[TOP]->t = tpwd[strlen(tpwd) - 1];
							words[TOP]->word = new char[top + 1];
							strcpy_s(words[TOP]->word, strlen(tpwd) + 1, tpwd);
						}
					}
					else if (flag == 1) {
						flag = 0;
					}
					tpwd[0] = '\0';
					top = -1;
				}
				else {
					top = -1;
					tpwd[0] = '\0';
				}
			}
		}
		infile.close();
	}
	catch (...) {
		Error(5);
	}

}

int nocircle(WORD words[],int len) {
	char charac[30], c, d;
	WORD *cirlist,*cirlist1;

	int top = -1, hcnt[30], tcnt[30], i, j, flag = 0, m, n, cirtop = -1,cirtop1=-1;
	cirlist = new WORD[len];
	cirlist1 = new WORD[len];
	//for (i = 0; i < 10000; i++) {
	//	cirlist[i] = new Word();
	//	cirlist1[i] = new Word();
	//}
	for (i = 0; i <len; i++) {
		for (j = i + 1; j < len; j++) {
			if (words[i]->h - words[i]->t == 0 && words[j]->h - words[j]->t == 0 && words[i]->h - words[j]->h == 0) {
				return 0;
			}
		}
	}
	for (i = 0; i < len; i++) {
		if (words[i]->h - words[i]->t != 0) {
			cirlist[++cirtop] = words[i];
		}
	}

	for (i = 0; i < 30; i++) {
		hcnt[i] = 0;
		tcnt[i] = 0;
	}
	for (i = 0; i <= cirtop; i++) {
		c = cirlist[i]->h;
		for (j = 0; j <= top; j++) {
			if (charac[j] - c == 0) {
				hcnt[j]++;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			charac[++top] = c;
			hcnt[top]++;
		}
		flag = 0;

		c = cirlist[i]->t;
		for (j = 0; j <= top; j++) {
			if (charac[j] - c == 0) {
				tcnt[j]++;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			charac[++top] = c;
			tcnt[top]++;
		}
		flag = 0;

	}
	charac[top + 1] = '\0';
	flag = 1;
	while (flag == 1) {
		for (i = 0; i <= top; i++) {
			if (hcnt[i] == 0 || tcnt[i] == 0) {
				for (j = i; j <= top; j++) {
					charac[j] = charac[j + 1];
					hcnt[j] = hcnt[j + 1];
					tcnt[j] = tcnt[j + 1];
				}
				top--;
				i--;
			}
		}

		for (i = 0; i <= cirtop; i++) {
			c = cirlist[i]->h;
			d = cirlist[i]->t;
			m = in_array(charac, top + 1, c);
			n = in_array(charac, top + 1, d);
			if (m == -1 && n == -1) {
				;
			}
			else if (m != -1 && n != -1) {
				cirlist1[++cirtop1] = cirlist[i];
			}
			else {
				if (m > -1)hcnt[m]--;
				else if (n > -1)tcnt[n]--;
			}
		}
		for (cirtop = 0; cirtop <= cirtop1; cirtop++) {
			cirlist[cirtop] = cirlist1[cirtop];
		}
		cirtop--;
		cirtop1 = -1;
		flag = 0;
		for (i = 0; i <= top; i++) {
			if (hcnt[i] == 0 || tcnt[i] == 0) {
				flag = 1;
				break;
			}
		}
	}
	if (cirtop > -1) {
		return 0;
	}
	return 1;
}

int in_array(char *arr, int len, char cc) {
	int i, flag = 0;
	for (i = 0; i < len; i++) {
		if (cc - arr[i] == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 1)return i;
	return -1;
}

void LONG(WORD *wod, int len, int H, int T, char _h, char _t) {
	int left[26][26];
	//int *index[26][26];
	//int *parent[26][26];
	int top[26][26];
	//int *lens[26][26];
	int i, j, k, l, m, n, p, q, r, s,  start = 0;
	char a, b;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			left[i][j] = 0;
			top[i][j] = 0;
		}
	}
	for (i = 0; i < len; i++) {
		a = wod[i]->h;
		b = wod[i]->t;
		left[a - 'a'][b - 'a']++;
		m = left[a - 'a'][b - 'a'];
		index[a - 'a'][b - 'a'][m] = i;
		index[a - 'a'][b - 'a'][0]++;
		lens[a - 'a'][b - 'a'][m] = strlen(wod[i]->word);
		lens[a - 'a'][b - 'a'][0]++;
	}
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (left[i][j] > 0) {
				for (k = 1; k <= left[i][j]; k++) {
					for (l = k + 1; l <= left[i][j]; l++) {
						if (lens[i][j][k] < lens[i][j][l]) {
							m = index[i][j][k];
							index[i][j][k] = index[i][j][l];
							index[i][j][l] = m;
							m = lens[i][j][k];
							lens[i][j][k] = lens[i][j][l];
							lens[i][j][l] = m;
						}
					}
				}
			}
		}
	}
	tmpwords = new int[len];
	for (i = 25; i >= 0; i--) {
		for (j = 25; j >= 0; j--) {
			if (H == 1) {
				if (_h - 'a' != i)break;
			}
			if (left[i][j] > 0) {
				tmp_words = 0;
				tmp_chs = 0;
				k = i; l = j;
				m = i; n = j;
				start = 1;
				for (p = 0; p < 26; p++) {
					for (q = 0; q < 26; q++) {
						parent[p][q][0] = 0;
					}
				}
				while (parent[k][l][0] > 0 || start == 1) {
					top[k][l]++;
					tmp_words++;
					tmp_chs += lens[k][l][top[k][l]];
					left[k][l]--;
					if (tmp_words <= len) {
						tmpwords[tmp_words - 1] = index[k][l][top[k][l]];
						if (T == 1 && _t-'a'==l) {
							if (tmp_words > max_words) {
								if (wordchain != nullptr)free(wordchain);
								wordchain = (int *)malloc(sizeof(int)*tmp_words);
								for (p = 0; p < tmp_words; p++) {
									wordchain[p] = tmpwords[p];
								}
								max_words = tmp_words;
							}
							if (tmp_chs > max_chs) {
								if (charchain != nullptr)free(charchain);
								charchain = (int *)malloc(sizeof(int)*tmp_words);
								for (p = 0; p < tmp_words; p++) {
									charchain[p] = tmpwords[p];
								}
								max_chs = tmp_chs;
								n_chs = tmp_words;
							}
						}
					}
					if (start == 1)start = 0;
					for (p = 25; p >= 0; p--) {
						if (left[l][p] > 0)break;
					}
					if (p < 0) {
						if (tmp_words > max_words && T == 0) {
							if (wordchain != nullptr)free(wordchain);
							wordchain = (int *)malloc(sizeof(int)*tmp_words);
							for (p = 0; p < tmp_words; p++) {
								wordchain[p] = tmpwords[p];
							}
							max_words = tmp_words;
						}
						if (tmp_chs > max_chs &&  T == 0) {
							if (charchain != nullptr)free(charchain);
							charchain = (int *)malloc(sizeof(int)*tmp_words);
							for (p = 0; p < tmp_words; p++) {
								charchain[p] = tmpwords[p];
							}
							max_chs = tmp_chs;
							n_chs = tmp_words;
						}


						while (parent[k][l][0] > 0) {
							for (r = l - 1; r >= 0; r--) {
								if (left[k][r] > 0)break;
							}
							if (r >= 0) {
								left[k][l]++;
								top[k][l]--;
								parent[k][l][0]--;
								tmp_words--;
								tmp_chs -= lens[k][l][top[k][l] + 1];
								parent[k][r][0]++;
								parent[k][r][parent[k][r][0]] = parent[k][l][parent[k][l][0] + 1];
								l = r;
								break;
							}
							else {
								if (parent[k][l][0] > 0) {
									r = parent[k][l][parent[k][l][0]] / 26;
									s = parent[k][l][parent[k][l][0]] - 26 * r;
									left[k][l]++;
									top[k][l]--;
									parent[k][l][0]--;
									tmp_words--;
									tmp_chs -= lens[k][l][top[k][l] + 1];
									k = r;
									l = s;
									if (parent[k][l][0] > 0) {
										m = parent[k][l][parent[k][l][0]] / 26;
										n = parent[k][l][parent[k][l][0]] - 26 * m;
									}
								}

							}
						}
					}
					else {
						m = k;
						n = l;
						k = l;
						l = p;
						parent[k][l][0]++;
						parent[k][l][parent[k][l][0]] = 26 * m + n;
						
					}

				}
				left[k][l]++;
				parent[k][l][0] = 0;
				top[k][l]--;
				tmp_words--;
				tmp_chs -= lens[k][l][top[k][l] + 1];
			}
		}
	}
}


void Error(int n) {
	cout << "Error: ";
	switch (n) {
	case 1: cout << "wrong format after -h!";                   break;
	case 2: cout << "wrong format after -t!";                   break;
	case 3: cout << "wrong format in argvs!";                   break;
	case 4: cout << "file doesn't exsits!";                     break;
	case 5: cout << "error when read file!";                    break;
	case 6: cout << "There exists circle(s),check words again!"; break;
	case 7: cout << "error when write data!";                   break;
	case 8: cout << "number of words larger than 10000!";       break;
	case 9: cout << "number of words larger than 100!";         break;
	default:break;
	}
	exit(0);
}


