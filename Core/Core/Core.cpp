#include"Core.h"
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std;
int LONG(WORD *wod, int len,char *result[], int H, int T, char _h, char _t ,int mark) {
	//int W, C, H, T, R;//when -w -c -h -t -r occur in argvs,being 1; else  keeping 0
	int max_words = 0, max_chs = 0, n_chs = 0;//number of words,chars,(words when most chars)
	int tmp_words = 0, tmp_chs = 0;//number of words ,chars in current words-chain
	int *wordchain, *charchain;  //record longest words-chain of most words and most chars
	int *tmpwords; //record current words-chain
	int left[26][26];
	int *index[26][26];
	int *parent[26][26];
	int top[26][26];
	int *lens[26][26];
	int i, j, k, l, m, n, p, q, r, s, start = 0;
	char a, b;
	wordchain = nullptr;
	charchain = nullptr;


	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			left[i][j] = 0;
			top[i][j] = 0;
			index[i][j] = new int[len];
			lens[i][j] = new int[len];
			parent[i][j] = new int[len];
			index[i][j][0] = 0;
			lens[i][j][0] = 0;
			parent[i][j][0] = 0;
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
						tmpwords[tmp_words - 1] = (int)index[k][l][top[k][l]];
						if (T == 1 && _t - 'a' == l) {
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
						if (tmp_words > max_words &&T==0) {
							if ((T == 1 && _t-'a'==l) || (T == 0)) {
								if (wordchain != nullptr)free(wordchain);
								wordchain = (int *)malloc(sizeof(int)*tmp_words);
								for (p = 0; p < tmp_words; p++) {
									wordchain[p] = tmpwords[p];
								}
								max_words = tmp_words;
							}
						}
						if (tmp_chs > max_chs&&T==0) {
							if ((T == 1 && _t-'a'==l) || (T == 0)) {
								if (charchain != nullptr)free(charchain);
								charchain = (int *)malloc(sizeof(int)*tmp_words);
								for (p = 0; p < tmp_words; p++) {
									charchain[p] = tmpwords[p];
								}
								max_chs = tmp_chs;
								n_chs = tmp_words;
							}
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
	if (mark == 1) {
		//result = new char*[max_words];
		for (i = 0; i < max_words; i++) {
			result[i] = new char[strlen(wod[wordchain[i]]->word) + 1];
			strcpy_s(result[i], strlen(wod[wordchain[i]]->word) + 1, wod[wordchain[i]]->word);
			//std::cout << wod[wordchain[i]]->word << ' ';
		}
	}
	else{
		//result = new char*[n_chs];
		for (i = 0; i < n_chs; i++) {
			result[i] = new char[strlen(wod[charchain[i]]->word) + 1];
			strcpy_s(result[i], strlen(wod[charchain[i]]->word) + 1, wod[charchain[i]]->word);
			//std::cout << wod[charchain[i]]->word << ' ';
		}
	}
	if (mark == 1) {
		return max_words;
	}
	else if (mark == 0) {
		return n_chs;
	}
	else {
		return -1;
	}
	
}


int nocircle(WORD words[], int len) {
	char charac[30], c, d;
	WORD *cirlist, *cirlist1;

	int top = -1, hcnt[30], tcnt[30], i, j, flag = 0, m, n, cirtop = -1, cirtop1 = -1;
	cirlist = new WORD[len];
	cirlist1 = new WORD[len];
	//for (i = 0; i < 10000; i++) {
	//	cirlist[i] = new Word();
	//	cirlist1[i] = new Word();
	//}
	for (i = 0; i < len; i++) {
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

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	WORD *wod = new WORD[len];
	int i;
	int H=0, T=0;
	for (i = 0; i < len; i++) {
		wod[i] = new Word();
		wod[i]->h = words[i][0];
		wod[i]->t = words[i][strlen(words[i]) - 1];
		wod[i]->word = new char[strlen(words[i]) + 1];
		strcpy_s(wod[i]->word, strlen(words[i]) + 1, words[i]);

	}
	if (enable_loop == false) {
		i=nocircle(wod, len);
		if (i == 0) {
			//std::cout << "circle are not allowed";
			return -1;
		}
		else {
			if (head >= 'a'&&head <= 'z') {
				H = 1;
			}
			if (tail >= 'a'&&tail <= 'z') {
				T = 1;
			}
			i=LONG(wod, len, result, H, T, head, tail,1);
			return i;
		}
	}
	else {
		if (head >= 'a'&&head <= 'z') {
			H = 1;
		}
		if (tail >= 'a'&&tail <= 'z') {
			T = 1;
		}
		i = LONG(wod, len, result, H, T, head,tail,1);
		return i;
	}
	return -1;
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
	WORD *wod = new WORD[len];
	int i;
	int H = 0, T = 0;
	for (i = 0; i < len; i++) {
		wod[i] = new Word();
		wod[i]->h = words[i][0];
		wod[i]->t = words[i][strlen(words[i]) - 1];
		wod[i]->word = new char[strlen(words[i]) + 1];
		strcpy_s(wod[i]->word, strlen(words[i]) + 1, words[i]);
	}
	if (enable_loop == false) {
		i = nocircle(wod, len);
		if (i == 0) {
			//std::cout << "circle are not allowed";
			return -1;
		}
		else {
			if (head >= 'a'&&head <= 'z') {
				H = 1;
			}
			if (tail >= 'a'&&tail <= 'z') {
				T = 1;
			}
			i = LONG(wod, len, result, H, T, head,tail, 0);
			return i;
		}
	}
	else {
		if (head >= 'a'&&head <= 'z') {
			H = 1;
		}
		if (tail >= 'a'&&tail <= 'z') {
			T = 1;
		}
		i = LONG(wod, len, result, H, T,head,tail, 0);
		return i;
	}
	return -1;
}
bool Core::has_circle(char *words[],int len) {
	WORD *wod = new WORD[len];
	int i;
	for (i = 0; i < len; i++) {
		wod[i] = new Word();
		wod[i]->h = words[i][0];
		wod[i]->t = words[i][strlen(words[i]) - 1];
		wod[i]->word = new char[strlen(words[i]) + 1];
		strcpy_s(wod[i]->word, strlen(words[i]) + 1, words[i]);
	}
	i = nocircle(wod, len);
	if (i == 0) {
		return true;
	}
	else if(i==1){
		return false;
	}
	else {
		return false;
	}
}

int Core::readfile(char *path, char *words[]) {
	ifstream infile;
	char cc=' ',*tpwd;
	int top = -1,j=0,TOP=-1,flag=0;
	tpwd = new char[100];
	infile.open(path);
	if (!infile) {
		cout << "file not exist";
		return -1;
	}
	infile >> noskipws;
	try {
		while (!infile.eof()) {
			cc = infile.get();
			if (cc >= 'a'&&cc <= 'z'&&top<99) {
				tpwd[++top] = cc;
			}
			else if (cc >= 'A'&&cc <= 'Z'&&top<99) {
				cc += 32;
				tpwd[++top] = cc;
			}
			else {
				tpwd[++top] = '\0';
				if (strlen(tpwd) > 1) {
					for (j = 0; j <= TOP; j++) {
						if (strcmp(words[j], tpwd) == 0) {
							flag = 1;
							break;
						}
					}
					if (flag == 0) {
						words[++TOP] = new char[top + 1];
						strcpy_s(words[TOP], strlen(tpwd) + 1, tpwd);
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
		return TOP + 1;
	}
	catch (...) {
		cout << "error when read";
		return -1;
	}
}