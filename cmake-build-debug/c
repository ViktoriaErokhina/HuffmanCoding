#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

unsigned char gen(unsigned char l, unsigned char r) {
	return (unsigned char)(rand() % (r - l + 1) + l);
}

int main()
{
	srand(time(NULL));
	freopen("a.txt", "wb", stdout);

	int n = 100500;
	unsigned char l = 50, r = 60;
	for (int i = 0; i < n; i++) {
		unsigned char a = gen(l, r);
		cout << a;
	}

	return 0;
}