#include <cmath>
#include <iostream>
#include "big_int.h"
#include<cstdlib>
using namespace std;
int main()
{
    //freopen("in.in", "r", stdin);
    //freopen("2^10000000.txt", "w", stdout);
    //big_int ans=pow_int(2,10000000);
    big_int a, b;
    a.in();
    b.in();
    (a / b).out();
    //fclose(stdin);
    //ans.out();
    //fclose(stdout);
    return 0;
}