#include <iostream>
#include "array_inner.h"
#include <exception>
#include <stdexcept>
#include <fstream>
using namespace std;

#define CHECK(cond, message, out) if (!cond) {\
							out<<"LINE : "<<__LINE__<<endl;\
							out<<"TEST CONDITION FAILED WITH RESULT"<<endl;\
							out<<message<<endl;\
							return -1;\
							}

#define TEST_VALIDITY(cond, expr, out) if (!cond){\
								out<<expr<<endl;}

int test1(ofstream& out) {
		FixedArray<int, 3> ar {{1,2,3}};
		CHECK((ar[1] == 2), "Invalid work of aggregate constructor", out);
		FixedArray<int, 3> ar1 = ar;
		CHECK((ar1[1] == 2), "Invalid work of aggregate constructor", out);
		return 1;
}

int test2(ofstream& out) {
		FixedArray<int, 3> ar {{1,2,3}};
		CHECK((ar[1] == 2), "Invalid work of aggregate constructor", out);
		FixedArray<int, 3> ar1 {{1,2,3}};
		CHECK((ar[1] == 2), "Invalid work of aggregate constructor", out);
		ar1+=ar;
		CHECK((ar1[2] == 6), "Invalid work of operator +", out);
		return 1;
}

int test3(ofstream& out) {
		FixedArray<int, 3> ar {{1,2,3}};
		CHECK((ar[1] == 2), "Invalid work of aggregate constructor", out);
		FixedArray<int, 3> ar1 {{1,2,3}};
		CHECK((ar[1] == 2), "Invalid work of aggregate constructor", out);
		FixedArray<int, 3> ar2 = ar1 + ar;
		CHECK((ar2[2] == 6), "Invalid work of operator +", out);
		return 1;
}

int main() {
		try {
			ofstream out("file");
			int result;
			result = test1(out);
			TEST_VALIDITY((result == 1), "TEST 1 HAS FAILED", out)
			result = test2(out);
			TEST_VALIDITY((result == 1), "TEST 2 HAS FAILED", out)
			result = test3(out);
			TEST_VALIDITY((result == 1), "TEST 3 HAS FAILED", out)
			/*result = test4(out);
			TEST_VALIDITY((result == 1), "TEST 4 HAS FAILED", out)
			result = test5(out);
			TEST_VALIDITY((result == 1), "TEST 4 HAS FAILED", out)*/
		} catch(exception& e) {
				cout<<"Exception occured"<<endl;
		}
}
