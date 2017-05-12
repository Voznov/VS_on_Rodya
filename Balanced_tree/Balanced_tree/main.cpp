#include <iostream>
#include "balanced_tree.h"
#include <vector>
#include <array>

using namespace std;

void b_out(balanced_tree& b)
{
	for (balanced_tree::iterator it = b.begin(); it != b.end(); ++it)
		cout << *it << ' ';
	cout << endl;
}


int main()
{
	balanced_tree b;
	for (int i = 0; i < 20; ++i)
		b.insert(i);
	b_out(b);
	
	for (int i = 0; i < 10; ++i)
		b.remove(2 * i);
	b_out(b);

	balanced_tree c;
	vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.push_back(2 * i);
	c += v;
	b_out(c);

	balanced_tree a;
	a = b + v;
	b_out(a);

	array<int, 5> x;
	for (int i = 0; i < 5; ++i)
		x[i] = (i + 1) * 100;
	a += x;
	b_out(a);
	
	system("pause");
	return 0;
}