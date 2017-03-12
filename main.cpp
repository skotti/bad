#include <iostream>
#include "array.h"
#include <exception>
#include <stdexcept>
#include <fstream>
using namespace std;

class Test {
public:
	int x;
	int y;

	Test(){
		cout <<"Default contructor "<<endl;
		x = 1;
		y = 1;
	}

	Test(int a, int b) {
		x = a;
		y = b;
	}

	Test(const Test& other) {
		cout<<"Copy constructor is called"<<endl;
		x = other.x;
		y = other.y;
	}

	const Test& operator= (const Test& other) {
		cout<<"Operator = is called"<<endl;
		x = other.x;
		y = other.y;
		return *this;
	}
	Test(Test&& other) : x(move(other.x)), y(move(other.y)){}

	friend ostream& operator<< (ostream& stream, const Test& matrix) {
		stream <<matrix.y<< matrix.x << '\n';
    	return stream;
	}
};

#define CHECK(cond, message, out) if (!cond) {\
							out<<"LINE : "<<__LINE__<<endl;\
							out<<"TEST CONDITION FAILED WITH RESULT"<<endl;\
							out<<message<<endl;\
							return -1;\
							}

#define TEST_VALIDITY(cond, expr, out) if (!cond){\
								out<<expr<<endl;}

int test1(ofstream& out) {
		int* a = new int(5);
		for (int i = 0; i < 5; i++)
			a[i] = i;
		Array<int> ar(a, 5);
		CHECK((ar[1] == 1), "Invalid work of pointer constructor", out)
		Array<int> ar1 = ar;
		CHECK((ar1[1] == 1), "Invalid work of copy constructor", out)
		ar1+=ar;
		CHECK((ar1[1] == 2), "Invalid work of +=", out)
		return 1;
}

int test2(ofstream& out) {
		int* a = new int(5);
		for (int i = 0; i < 5; i++)
			a[i] = i;
		Array<int> ar(a, 5);
		CHECK((ar[1] == 1), "Invalid work of pointer constructor", out)
		Array<int> ar1 = ar;
		CHECK((ar1[1] == 1), "Invalid work of copy constructor", out)
		Array<int> ar2 = ar;
		CHECK((ar2[1] == 1), "Invalid work of copy constructor", out)
		Array<int> a3 = ar1 + ar + ar2;
		CHECK((a3[4] == 12), "Invalid work of +", out)
		return 1;
}

int test3(ofstream& out) {
		int* a = new int(5);
		for (int i = 0; i < 5; i++)
			a[i] = i;
		Array<int> ar(a, 5);
		CHECK((ar[1] == 1), "Invalid work of pointer constructor", out)
		ar.emplace(3, 87);
		CHECK((ar[3] == 87), "Invalid work of emplace", out)
		ar.pop_back();
		CHECK((ar.size() == 5), "Invalid work of pop", out)
		return 1;
}

int test9(ofstream& out) {
		int* a = new int(5);
		for (int i = 0; i < 5; i++)
			a[i] = i;
		Array<int> ar(a, 5);
		ar.insert(&ar[2], 8);
		CHECK((ar[2] == 8), "Invalid work of insert", out)
		return 1;
}

/*int test4(ofstream& out) {
		int* a = new int(5);
		for (int i = 0; i < 5; i++)
			a[i] = i;
		Array<int> ar(a, 5);
		CHECK((ar[1] == 1), "Invalid work of pointer constructor", out)
		Array<int>::Iterator<int> i = ar.begin();
		i++;
		CHECK((*i == 1), "Invalid work of iterator", out)
		Array<int>::Iterator<int> i1 = ar.end();
		i1--;
		CHECK((*i1 == 4), "Invalid work of iterator", out)
		i1--;
		CHECK((*i1 == 3), "Invalid work of iterator", out)
		return 1;
}
*/
int test5(ofstream& out) {
		Array<Test>* a = new Array<Test>(5);
		Test* t = new Test(1,2);
		a->push_back(*t);
		CHECK((a[0].data()[0].x == 1), "Invalid work of push for complex class", out)
		return 1;
}

int test7(ofstream& out) {
		Test* t = new Test[2];
		t[0].x = 3; t[0].y = 3;
		t[1].x = 5; t[1].y = 5;
		Array<Test> a(t, 2);
		return 1;
}

int test8(ofstream& out) {
		Test* t = new Test[2];
		Array<Test> a(2);
		return 1;
}

/*int test6(ofstream& out) {
		int* a = new int(5);
		for (int i = 0; i < 5; i++)
			a[i] = i;
		Array<int> ar(a, 5);
		Array<int>::Iterator<int> i = ar.begin();
		i++;
		i++;
		ar.insert(i, 8);
		CHECK((ar[2] == 8), "Invalid work of insert and iterator", out)
		return 1;
}*/

void test_run() {
		try {
			ofstream out("file");
			int result;
			//result = test1(out);
			//TEST_VALIDITY((result == 1), "TEST 1 HAS FAILED", out)
			//result = test2(out);
			//TEST_VALIDITY((result == 1), "TEST 2 HAS FAILED", out)
			//result = test3(out);
			//TEST_VALIDITY((result == 1), "TEST 3 HAS FAILED", out)
			//result = test4(out);
			//TEST_VALIDITY((result == 1), "TEST 4 HAS FAILED", out)
			//result = test5(out);
			//TEST_VALIDITY((result == 1), "TEST 5 HAS FAILED", out)
			//result = test6(out);
			//TEST_VALIDITY((result == 1), "TEST 6 HAS FAILED", out)
			//result = test7(out);
			//result = test8(out);
			result = test9(out);
			TEST_VALIDITY((result == 1), "TEST 9 HAS FAILED", out)
		} catch(exception& e) {
				cout<<"Exception occured"<<endl;
		}
}

int main() {
	test_run();
	return 1;
}
