#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int hash[15][(1<<14)+7];
int n;
int mask, ans;
 
void recurse(int col, int left, int right, int depth)
{
   if(col == mask)
   {
      ans++;
      return;
   }
   
   int pos = mask &~ (col | left | right);
   
   while(pos)
    {
       int x = pos & -pos;
       pos = pos - x;
       
       if(!hash[depth][x])
	  recurse(col + x, (left + x) << 1, (right + x) >> 1, depth+1);
    }
}

int main()
{
   int kcase = 0;
   char c;
   while(cin>>n)
   {
      kcase++;
      if(n == 0)
	 break;

      memset(hash, 0, sizeof(hash));
      ans = 0;
      mask = (1 << n) - 1;

      for(int i = 0; i < n; ++i)
      {
	 for(int j = 0; j < n; ++j)
	 {
                cin>>c;
                if(c == '*')
		   hash[i][1<<j] = 1;
            }
        }
        recurse(0,0,0,0);
	cout << "Case " << kcase << ": " << ans << endl;
    }
    return n;
}
