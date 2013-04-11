#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

using namespace std;

int main(void)
{
  double odo, fuel;
  
  while (cin >> odo >> fuel) {
    if (odo == -1.0 && fuel == -1.0) break;
    
    double prev_odo = odo;
    double prev_fuel = fuel;
    double total_odo = 0.0, total_fuel = 0.0;
  
    while (cin >> odo >> fuel) {
      if (odo == 0.0 && fuel == 0.0) break;
      if (fuel < prev_fuel) {
	total_odo += odo - prev_odo;
	total_fuel += prev_fuel - fuel;
      }

      prev_odo = odo;
      prev_fuel = fuel;
    }

    double temp = total_odo * prev_fuel / total_fuel;
    assert(fabs(temp - floor(temp) - 0.5) > 0.001);

    cout << fixed << setprecision(0)
	 << total_odo * prev_fuel / total_fuel << endl;
  }

  return 0;
}
