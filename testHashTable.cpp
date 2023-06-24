#include "Mayunorder_map.h"
#include<iostream>
using namespace std;
void testHash()
{
	Mayunorder_map<int, int> m;
	m.insert(make_pair(1, 3));
	m.insert(make_pair(5, 32));
	m.insert(make_pair(2, 32));
	m.insert(make_pair(8, 31));
	Mayunorder_map<int, int>::iterator it = m.begin();
	while(it != m.end())
	{
		cout << it->first << ' ' << it->second << endl;
		++it;
	}
}