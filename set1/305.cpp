#include <iostream>
#include <vector>
using namespace std;

int answers[14];
int findMinimal(int k);

int main()
{
   for (int k=1; k<14; k++)
      answers[k-1] = findMinimal(k);
   int input = 0;
   while (cin>>input)
   {
      if (!input)
	 return 0;
      cout << answers[input-1] << endl;
   }
   return 0;
}

//Gets the smallest m for a particular number of people
int findMinimal(int k)
{
   int size = k*2;
   int m = k;

   while(1)
   {
      int iter = 0;
      for (int i=0; i<k; i++)
      {
	 iter = (iter + (m-1)) % (size);
	 if (iter < k) {
	    m++;
	    size = k*2;
	    break;
	 }
	 size--;
	 if (i == (k-1))
	    return m;
      }
   }
}
