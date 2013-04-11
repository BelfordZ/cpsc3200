/*
 * Solution to Blackjack
 *
 */

#include <fstream>
#include <iomanip>

using namespace std;

int value[256];
char *cards = "23456789TJQKA";

void init(void)
{
  int c;

  for (c = '2'; c <= '9'; c++) {
    value[c] = c-'0';
  }
  value['K'] = value['Q'] = value['J'] = value['T'] = 10;
  value['A'] = 11;   /* assume to be 11 to start with */
}

int hand_value(char a, char b)
{
  int val = value[a] + value[b];
  return (val > 21) ? val - 10 : val;    /* deal with 2 A's */
}

int main(void)
{
  int n;
  char faceup, my1, my2;
  int freq[256], i, j, myvalue, first = 1;
  double prob;
  ifstream in("blackjack.in");
  ofstream out("blackjack.out");

  init();
  while (in >> n && n > 0) {
    if (!first) {
      out << endl;
    }
    first = 0;
    for (i = 0; i < 13; i++) {
      freq[cards[i]] = 4*n;
    }

    in >> faceup >> my1 >> my2;
    freq[faceup]--;  freq[my1]--;  freq[my2]--;
    prob = 0.0;
    myvalue = hand_value(my1, my2);

    for (i = 0; i < 13; i++) {
      if (hand_value(faceup, cards[i]) < myvalue) {
        prob += freq[cards[i]];
      }
    }
    prob = prob * 100.0 / (52*n-3);
    out << fixed << setprecision(3) << prob << "%" << endl;
  }
  return 0;
}
