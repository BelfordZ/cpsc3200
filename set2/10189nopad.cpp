#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int makeIndex(int row, int col);
void buildMapNumbers();
void printResults(int itr);

int rowMax, colMax;
vector<string> gameMap;

int main()
{
   int iter = 1;
   while(cin>>rowMax>>colMax)
   {
      gameMap.clear();
      if (rowMax == 0 && colMax == 0)
  	 return 0;
      else if (iter != 1)
	 cout << endl;
      char tmp;
      int mapSize = ((rowMax) * (colMax));
    
      for (int i=0; i<mapSize; i++)
      {
	 cin>>tmp;
	 string tmpStr(1,tmp);
	 gameMap.push_back(tmpStr);
      }

      buildMapNumbers();
      printResults(iter);
      iter++;
   }
   return 0;
}
void buildMapNumbers()
{
   for (int row=0; row < rowMax; row++)
   {
      for(int col=0; col < colMax; col++)
      {
	 //if im a bomb... increment everyone around me (xept bombs)
	 if (gameMap[makeIndex(row,col)] == "*")
	 {
	    for (int i=-1; i<2; i++)
	    {
	       for (int j=-1; j<2; j++)
	       {
		  if (row+i>-1 && col+j>-1 && row+i<rowMax && col+j<colMax)
		  {
		     int tmp = makeIndex((row+i), (col+j));
		     //cout << "@ (" <<row << ", "<<col<<")"<< endl;
		     //cout << ">>>>> (" << row+i << ", " << col+i << ")" << endl;
		     if (gameMap[tmp] != "*")
			gameMap[tmp] += ".";
		  }
	       }
	    }
	 }
      }	     
   }
   for (int row=0; row < rowMax; row++)
   {
      for(int col=0; col < colMax; col++)
      {
	 if (gameMap[makeIndex(row, col)] != "*")
	    gameMap[makeIndex(row, col)] = static_cast<ostringstream*>( &(ostringstream() << (gameMap[makeIndex(row, col)].size()-1)))->str();
      }
   }
}
void printResults(int itr)
{
   cout << "Field #" << itr << ":" << endl;
   for (int row=0; row<rowMax; row++)
   {
      for (int col=0; col<colMax; col++)
      {
	 cout << gameMap[makeIndex(row,col)];
	 if (col == colMax-1)
	    cout <<endl;
      }
   }
}
int makeIndex(int row, int col)
{
   return (((row)*(colMax))+col);
}
