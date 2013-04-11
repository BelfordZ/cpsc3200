#define PROBLEM 8 /* The problem # here */ 
#define TEAM 0 /* Your team # here */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

ifstream in;
ofstream out; 
void solve_problem(); 

int main(void)
{
  char filename[64];
  sprintf(filename, "prob%d.dat", PROBLEM); 
  in.open(filename, ios::in); 
  if (!in) { 
    cout << "could not open input file " << filename << endl; 
    exit(1); 
  } 
  sprintf(filename, "prob%d.out", PROBLEM); 
  out.open(filename, ios::out); 
  if (!out) { 
    cout << "could not open output file " << filename << endl; 
    exit(1);
  } 
  out << "Program " << PROBLEM << " by team " << TEAM << endl; 
  solve_problem(); 
  out << "End of program " << PROBLEM << " by team " << TEAM << endl;
  return 0; 
}

string best_hand;
int best_score;
int best_result;

void best_play(string &hand, int index)
{
  if (index == 6) {
    int val, score;
    val = (hand[0]-'0' + hand[2]-'0') * 10 + (hand[1]-'0' + hand[3]-'0');
    score = abs(100-val);
    if (best_score == -1 || score < best_score) {
      best_score = score;
      best_hand = hand;
      best_result = val;
    }
  } else {
    best_play(hand, index+1);
    for (int i = index+1; i < 6; i++) {
      swap(hand[index], hand[i]);
      best_play(hand, index+1);
      swap(hand[index], hand[i]);
    }
  }
}

int play(string &hand)
{
  best_score = -1;
  best_play(hand, 0);
  out << best_hand.substr(0, 2) << "+" << best_hand.substr(2,2) << "="
      << best_result << endl;
  return best_score;
}

void solve_problem(void)
{
  string hand, deal;
  
  while (getline(in, hand)) {
    int score = play(hand);
    while (getline(in, deal) && deal.length() > 0) {
      hand = best_hand;
      hand.replace(0, 4, deal);
      score += play(hand);
    }
    out << "score: " << score << endl;
  }
}

