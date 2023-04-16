#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;
#include"string.h"
int& fun(int& a, int* q)
{
	return q[a];
}
int main()
{

	gsy::Test01();

	return 0;
}