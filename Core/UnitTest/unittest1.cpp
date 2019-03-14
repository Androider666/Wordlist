#include "stdafx.h"
#include "CppUnitTest.h"
#include"../Core/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	char *longchar(char *arr[], int len) {
		int i, j, cnt = 0;
		char *tmp = nullptr;
		for (i = 0; i < len; i++) {
			cnt += strlen(arr[i]);
		}
		tmp = new char[cnt + 1];
		cnt = -1;
		for (i = 0; i < len; i++) {
			for (j = 0; j < strlen(arr[i]); j++) {
				tmp[++cnt] = arr[i][j];
			}
		}
		tmp[++cnt] = '\0';
		return tmp;
	}

	TEST_CLASS(UnitTest1)
	{
	public:
		int len1 = 10, len2 = 11;
		char *list1[10] = {"app","pdfcde","hefarry","yakorm","morning","ed","dail","left","pd","dot" };
		char *list2[11] = { "app","pdfcde","pd","die","early","ear","yet","tail","rabbittall","tab","leaf" };
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			int ans_len = 5;
			char *ans[5] = { "app","pdfcde","ed","dail","left" };
			char *result[5];
			int len = 0;
			len = Core::gen_chain_word(list1, len1, result, '\0', '\0', false);
			Assert::AreEqual(len, ans_len);
			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1,len1));

		}
		TEST_METHOD(TestMethod2) {
			int ans_len = 5;

			char *ans[5] = { "app","pdfcde","ed","dail","left" };

			char *result[5];

			int len = 0;

			len = Core::gen_chain_word(list1, len1, result, '\0', '\0', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod3) {
			int ans_len = 3;

			char *ans[3] = { "ed","dail","left" };

			char *result[3];

			int len = 0;

			len = Core::gen_chain_word(list1, len1, result, 'e', '\0', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod4) {
			int ans_len = 3;

			char *ans[3] = { "app","pdfcde","ed" };

			char *result[3];

			int len = 0;

			len = Core::gen_chain_word(list1, len1, result, '\0', 'd', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod5) {
			int ans_len = 2;

			char *ans[2] = { "pdfcde","ed" };

			char *result[2];

			int len = 0;

			len = Core::gen_chain_word(list1, len1, result, 'p', 'd', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod6) {
			int ans_len = 3;

			char *ans[3] = { "hefarry","yakorm","morning" };

			char *result[3];

			int len = 0;

			len = Core::gen_chain_char(list1, len1, result, '\0', '\0', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod7) {
			int ans_len = 4;

			char *ans[4] = { "pdfcde","ed","dail","left" };

			char *result[4];

			int len = 0;

			len = Core::gen_chain_char(list1, len1, result, 'p', '\0', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod8) {
			int ans_len = 4;

			char *ans[4] = { "app","pdfcde","ed","dail" };

			char *result[4];

			int len = 0;

			len = Core::gen_chain_char(list1, len1, result, '\0', 'l', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod9) {
			int ans_len = 3;

			char *ans[3] = { "pdfcde","ed","dail" };

			char *result[3];

			int len = 0;

			len = Core::gen_chain_char(list1, len1, result, 'p', 'l', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list1, len1));
		}
		TEST_METHOD(TestMethod10) {

			int ans_len = 5;

			char *ans[5] = { "app","pdfcde","ed","dail","left" };

			char *result[5];

			int len = 0;

			len = Core::gen_chain_word(list1, len1, result, '\0', '\0', true);

			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
		}
		TEST_METHOD(TestMethod11) {
			int ans_len = 4;

			char *ans[4] = { "pdfcde","ed","dail","left" };

			char *result[4];

			int len = 0;

			len = Core::gen_chain_char(list1, len1, result, 'p', '\0', true);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
		}
		TEST_METHOD(TestMethod12) {
			int ans_len = 7;

			char *ans[7] = { "app","pd","die","early","yet","tail","leaf" };

			char *result[7];

			int len = 0;

			len = Core::gen_chain_word(list2, len2, result, '\0', '\0', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list2, len2));
		}
		TEST_METHOD(TestMethod13) {

			int ans_len = 6;

			char *ans[6] = { "app","pd","die","early","yet","tab" };

			char *result[6];

			int len = 0;

			len = Core::gen_chain_word(list2, len2, result, '\0', 'b', true);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
		}
		TEST_METHOD(TestMethod14) {
			int ans_len = 4;

			char *ans[4] = { "app","pd","die","ear" };

			char *result[4];

			int len = 0;

			len = Core::gen_chain_word(list2, len2, result, 'a', 'r', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list2, len2));
		}
		TEST_METHOD(TestMethod15) {

			int ans_len = 5;

			char *ans[5] = { "app","pdfcde","ear","rabbittall","leaf" };

			char *result[5];

			int len = 0;

			len = Core::gen_chain_char(list2, len2, result, '\0', '\0', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list2, len2));
		}
		TEST_METHOD(TestMethod16) {
			int ans_len = 4;

			char *ans[4] = { "app","pdfcde","early","yet" };

			char *result[4];

			int len = 0;

			len = Core::gen_chain_char(list2, len2, result, '\0', 't', false);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list2, len2));
		}
		TEST_METHOD(TestMethod17) {
			int ans_len = 3;

			char *ans[3] = { "die","ear","rabbittall" };

			char *result[3];

			int len = 0;

			len = Core::gen_chain_char(list2, len2, result, 'd', 'l', true);
			Assert::AreEqual(len, ans_len);

			Assert::AreEqual(strcmp(longchar(result, len), longchar(ans, ans_len)), 0);
			Assert::IsFalse(Core::has_circle(list2, len2));


		}


	};
}