#include <cstdio>
#include <set>
#include <iostream>

using namespace std;

int main()
{
   multiset<long> buys;
   multiset<long>::iterator minIter, maxIter;

   long T = 0, n = 0, cost = 0;
   while(scanf("%ld", &T) && T)
   {
      buys.clear();
      cost = 0;
      while(T--)
      {
	 scanf("%ld",&n);
	 while(n--)
	 {
	    long tmp;
	    scanf("%ld",&tmp);
	    buys.insert(tmp);
	 }
	 minIter = buys.begin();

	 maxIter = buys.end();
	 --maxIter;

	 cost += (*(maxIter) - *(minIter));

	 buys.erase(minIter);
	 buys.erase(maxIter);
      }
      
      printf("%ld\n",cost);
   }
   return 0;
}
