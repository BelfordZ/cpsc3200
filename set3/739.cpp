#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

#define n 1000000
int parent[n];

int getRoot(int i)
{
   //recurse until the value of the array position equals its index
   if (parent[i] == i)
      return i;
    return parent[i] = getRoot(parent[i]);
}

int main()
{
   int testCases;
   scanf("%d", &testCases);
   bool isBlankLine = false;
   
   while (testCases--)
   {
      for (int i = 0; i<n; i++)
	 parent[i] = i;
      
      int numOfComps;
      scanf ("%d", &numOfComps);
      getchar();
      
      char c;
      int compi, compj;
      int connectedCount = 0;
      int unconnectedCount = 0;
      
      while ((c = getchar()) && isalpha (c))
      {	 
	 scanf ("%d %d", &compi, &compj);
	 getchar();
	 
	 int p = getRoot(compi);
	 int q = getRoot(compj);
	 
	 if (c == 'c')
	 {
	    parent[p] = q;
	 }
	 else
	 {
	    if (p == q)
	       connectedCount++;
	    else
	       unconnectedCount++;
	 }
      }
      
      if (isBlankLine)
	 printf("\n");
      
      isBlankLine = true;
      printf ("%d,%d\n", connectedCount, unconnectedCount);
   }
   return 0;
}
