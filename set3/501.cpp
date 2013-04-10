#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int main()
{
   int t;
   scanf( "%d", &t );
   while(t--)
   {
      int n, m, x;
      scanf("%d %d", &n, &m);
      
      queue<int> add, get;
      for (int i = 0; i<n; i++)
      {
	 scanf("%d", &x);
	 add.push(x);
      }
      for (int i = 0; i<m; i++)
      {
	 scanf("%d", &x);
	 get.push(x);
      }
      
      int k = 0;
      priority_queue<int, vector<int>, greater<int> > minQueue;
      priority_queue<int, vector<int>, less<int> > maxQueue;
      
      while (!add.empty())
      {	 
	 if (!minQueue.empty() && add.front() > maxQueue.top())
	 {
	    minQueue.push(add.front());
	 }
	 else
	 {
	    maxQueue.push(add.front());
	 }
	 add.pop();
	 
	 while (!get.empty() && (maxQueue.size() + minQueue.size() == get.front()))
	 {
	    while (maxQueue.size() != k)
	    {
	       if (maxQueue.size() < k)
	       {
		  maxQueue.push(minQueue.top());
		  minQueue.pop();
	       }
	       else if (maxQueue.size() > k)
	       {
		  minQueue.push(maxQueue.top());
		  maxQueue.pop();
	       }
	    }
	    
	    printf("%d\n", minQueue.top());
	    ++k;
	    get.pop();
	 }
      }
   }
   return 0;
}
