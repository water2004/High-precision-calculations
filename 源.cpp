#include "big_int.h"
#include<iostream>
using namespace std;
int main()
{
	big_int num1;
	num1.in();
	int a, b;
	cin >> a;
	(pow_int(num1,a)).out();
	return 0;
}