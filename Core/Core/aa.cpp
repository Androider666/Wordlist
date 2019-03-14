#include"Core.h"
int main() {
	int i = 0;
	int word_num = 7;
	int answer_num = 3;
	int res = 0;
	char *testlist1[5];
	char *result3[5];
	for (i = 0; i < 5; i++) {
		testlist1[i] = new char[20];
		result3[i] = new char[20];
	}
	strcpy_s(testlist1[0], 5, "afds");
	strcpy_s(testlist1[1], 5, "dsds");
	strcpy_s(testlist1[2], 5, "sfld");
	strcpy_s(testlist1[3], 5, "dlsk");
	strcpy_s(testlist1[4], 5, "mlds");

	
	res = Core::gen_chain_word(testlist1, 5, result3, '0','0', true);
	cout << res;
}