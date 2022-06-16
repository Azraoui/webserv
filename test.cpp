#include <iostream>
#include <set>
#include <map>
#include <array>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
	// set<pair<string, size_t> > test;

	// test.insert(make_pair(string("127.3.4.44"),44));
	// test.insert(make_pair(string("127.3.4.44"),54));
	// test.insert(make_pair(string("157.3.4.44"),44));

	// for (auto i = test.begin(); i != test.end(); ++i)
	// {
	// 	std::cout << i->first << " " << i->second << std::endl;
	// }
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	vector<int> v2;
	v2.assign(v1.begin() + 1, v1.end());
	for (int i = 0; i < v2.size(); i++)
		std::cout << v2[i] << std::endl;
}