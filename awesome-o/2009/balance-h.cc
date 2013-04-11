#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

int main(void)
{
  int n_ins, n_terms, n_rebalance;

  cin >> n_ins >> n_terms >> n_rebalance;

  vector<double> ffee(n_ins), pfee(n_ins), principal(n_ins), ratio(n_ins);

  for (int i = 0; i < n_ins; i++) {
    cin >> ffee[i];
  }
  for (int i = 0; i < n_ins; i++) {
    cin >> pfee[i];
  }

  double total = 0.0;
  for (int i = 0; i < n_ins; i++) {
    cin >> principal[i];
    total += principal[i];
  }
  for (int i = 0; i < n_ins; i++) {
    ratio[i] = (total > 0 ? principal[i] / total : 0);
  }

  for (int i = 0; i < n_terms; i++) {
    if (i && i % n_rebalance == 0) {
      // rebalance
      total = 0.0;
      for (int j = 0; j < n_ins; j++) {
	total += principal[j];
      }
      for (int j = 0; j < n_ins; j++) {
	principal[j] = ratio[j] * total;
      }
    }

    for (int j = 0; j < n_ins; j++) {
      double returns;
      cin >> returns;
      if (principal[j] <= 0.0) continue;
      double change = -ffee[j] + (-pfee[j] + returns)*principal[j];
      if ((principal[j] += change) < 0) {
	principal[j] = 0.0;
      }
    }
  }
  
  for (int i = 0; i < n_ins; i++) {
    if (i) cout << ' ';
    assert(fabs(principal[i]*100 - floor(principal[i]*100) - 0.500) > 1e-3);
    cout << fixed << setprecision(2) << principal[i];
  }
  cout << endl;
    
  return 0;
}
