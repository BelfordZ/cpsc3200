#include <iostream>
#include <cmath>
using namespace std;

int main()
{
   long long x, y;
   while(cin>>x>>y)
      (x < y) ? (cout << y-x << endl) : (cout << x-y << endl);
   return 0;
}
