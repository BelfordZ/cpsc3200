#include <iostream>
#include <string>
using namespace std;
int keys[11] = {-1,0,0,0,0,0,0,0,0,0,0};
int keyState[11] = {-1,0,0,0,0,0,0,0,0,0,0};
//I know... its ugly. BUT, it took me less time to write then it would have to do it in a smarter way :)

void doKey(int key){
  if (keyState[key] == 0){
    keyState[key] = 1;
    keys[key]++;
  }
}

void addToCount(char c)
{
  if (c == 'c') {
    keyState[1] = 0;

    doKey(2);
    doKey(3);
    doKey(4);
    
    keyState[5] = 0;
    keyState[6] = 0;

    doKey(7);
    doKey(8);
    doKey(9);
    doKey(10);
  }
  else if (c == 'd'){
    keyState[1] = 0;

    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;

    doKey(7);
    doKey(8);
    doKey(9);
    
    keyState[10] = 0;
  }
  else if (c == 'e'){
    keyState[1] = 0;
    
    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;

    doKey(7);
    doKey(8);

    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'f'){
    keyState[1] = 0;

    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;

    doKey(7);

    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'g'){
    keyState[1] = 0;

    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;
    keyState[7] = 0;
    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'a'){
    keyState[1] = 0;

    doKey(2);
    doKey(3);

    keyState[4] = 0;
    keyState[5] = 0;
    keyState[6] = 0;
    keyState[7] = 0;
    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'b'){
    keyState[1] = 0;

    doKey(2);
    keyState[3] = 0;
    keyState[4] = 0;
    keyState[5] = 0;
    keyState[6] = 0;
    keyState[7] = 0;
    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'C'){
    keyState[1] = 0;
    keyState[2] = 0;
    
    doKey(3);
    
    keyState[4] = 0;
    keyState[5] = 0;
    keyState[6] = 0;
    keyState[7] = 0;
    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'D'){
    doKey(1);
    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;

    doKey(7);
    doKey(8);
    doKey(9);

    keyState[10] = 0;
  }
  else if (c == 'E'){
    doKey(1);
    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;

    doKey(7);
    doKey(8);
   
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'F'){
    doKey(1);
    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;

    doKey(7);

    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'G'){
    doKey(1);
    doKey(2);
    doKey(3);
    doKey(4);

    keyState[5] = 0;
    keyState[6] = 0;
    keyState[7] = 0;
    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'A'){
    doKey(1);
    doKey(2);
    doKey(3);

    keyState[4] = 0;
    keyState[5] = 0;
    keyState[6] = 0;
    keyState[7] = 0;
    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
  else if (c == 'B'){
    doKey(1);
    doKey(2);
    
    keyState[3] = 0;
    keyState[4] = 0;
    keyState[5] = 0;
    keyState[6] = 0;
    keyState[7] = 0;
    keyState[8] = 0;
    keyState[9] = 0;
    keyState[10] = 0;
  }
}

int main()
{
  int t =0;
  cin >> t;
  string tmp;
  getline(cin, tmp);

  for (int i=0; i<t; i++) {
    for (int sigh=1; sigh<11; sigh++)
      keys[sigh] = 0;
    string line;
    getline(cin, line);

    for (int j=0; j<line.size(); j++)
      addToCount(line[j]);
    
    for (int k=1; k<11; k++)
      cout << keys[k] << " ";

    cout << endl;
  }
}
