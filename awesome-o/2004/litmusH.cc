#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(void)
{
  ifstream in("litmus.in");
  ofstream out("litmus.out");

  double a, b, c;
  double Ka, C, x;
  int m, n;

  while (in >> Ka >> C >> m >> n) {
    if (Ka == 0 && C == 0 && m == 0 && n == 0)
      break;

    a = m*n;
    b = Ka;
    c = -Ka*C;
    
    x = (-b + sqrt(b*b-4*a*c))/(2*a);
    out << setprecision(3) << fixed << -log10(m*x) << endl;
  }
  
  return 0;
}
