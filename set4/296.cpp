#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

int fourInts[10000][4];

void output(bool guess[])
{
   int num=0;
   int last=0;
   for(int i=0; i<10000; i++)
   {
      if(guess[i])
      {
	 num++;
	 last = i;	 
      }
   }
   
   if(num==0)
   {
      puts("impossible");
   }
   else
      if(num==1)
      {
	 printf("%04d\n",last);
      }
      else
      {
	 
	 puts("indeterminate");
      }
}

int main()
{
   for(int i=0; i<10000; i++)
   {
      int temp = i;
      for(int j=0; j<4; j++)
      {
	 fourInts[i][j] = temp%10;
	 temp/=10;
      }
   }
   int M;
   cin >> M;
 
   for(int r=0; r<M; r++)
   {
      bool guess[10000];
      for(int i=0; i<10000; i++)
	  guess[i] = true;

      int n;
      cin >> n;
      for(int i=0; i<n; i++)
      {
	 int num;
	 int A,B;
	 char format;
	 cin >> num >> A >> format >>B;
	 
	 int numDigit[4];
	 for(int j=0; j<4; j++)
	 {
	    numDigit[j] = num%10;
	    num/=10;
	 }
	 
	 for(int j=0; j<10000; j++)
	 {
	    int statNum[10] = {0};
	    int statTable[10] = {0};
	    int calA = 0, calB = 0;
	    
	    for(int d=0; d<4; d++)
	    {
	       if(numDigit[d]==fourInts[j][d])
		  calA++;
	       statNum[numDigit[d]]++;
	       statTable[fourInts[j][d]]++;
	    }
	    
	    for(int s=0; s<10; s++)
	    {
	       calB+=min(statNum[s],statTable[s]);
	    }
	    calB-=calA;
	    
	    guess[j] = guess[j]&&(calA==A&&calB==B);
	    
	 }
	 
      }
      output(guess);
   }
}
