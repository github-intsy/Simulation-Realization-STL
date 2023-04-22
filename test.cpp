#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;
#include"list.h"
#include"string.h"
#include"vector.h"
int main()
{
	gsy_study_vector::test02();
	gsy_study_list::Test();
	gsy::Test02();
	/*vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	vector<int>::iterator i = v1.begin();
	v1.insert(v1.begin(), 100);
	for (auto e : v1)
		cout << e << ' ';*/
	return 0;
}