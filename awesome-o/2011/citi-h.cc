#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;
using namespace std::rel_ops;

const int MAX_TRIPS = 100;

const int daysInMonth[2][13] = {
  { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

bool isLeap(int y)
{
  return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

struct Date
{
  int m, d, y;

  Date() 
    : m(1), d(1), y(1980) { }

  Date(int index)
    : m(1), d(1), y(1980)
  {
    while (index-- > 0) {
      inc();
    }
  }

  Date(int mm, int dd, int yy)
    : m(mm), d(dd), y(yy) { }

  bool operator<(const Date &date) const
  {
    if (y != date.y) return y < date.y;
    if (m != date.m) return m < date.m;
    return d < date.d;
  }

  bool operator==(const Date &date) const
  {
    return y == date.y && m == date.m && d == date.d;
  }
  
  void inc()
  {
    if (d++ == daysInMonth[isLeap(y)][m]) {
      d = 1;
      if (m++ == 12) {
	m = 1;
	y++;
      }
    }
  }

  void dec()
  {
    if (d-- == 1) {
      if (m-- == 1) {
	m = 12;
	y--;
      }
      d = daysInMonth[isLeap(y)][m];
    }
  }

  int index() const
  {
    Date start(1, 1, 1980);
    int ans = 0;
    while (start < *this) {
      start.inc();
      ans++;
    }
    return ans;
  }
};

istream &operator>>(istream &is, Date &date)
{
  char c;
  return is >> date.m >> c >> date.d >> c >> date.y;
}

ostream &operator<<(ostream &os, const Date &date)
{
  return os << date.m << '/' << date.d << '/' << date.y;
}

bool solve()
{
  Date reside, landing;
  if (!(cin >> reside >> landing)) {
    return false;
  }
  int start_i = reside.index(), land_i = landing.index();

  const int MAX_DAYS = 100*366; // 100 years is more than enough
  bool absent[MAX_DAYS];    
  fill(absent, absent+MAX_DAYS, false);

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    Date start, end;
    cin >> start >> end;
    int si = start.index(), ei = end.index();
    fill(absent+si, absent+ei+1, true);
  }

  int count[MAX_DAYS] = {0};    // cumulative sum of half days
  for (int i = start_i; i < MAX_DAYS; i++) {
    int tally = (i < land_i) ? 1 : 2;
    count[i] = (i > 0) ? count[i-1] : 0;
    if (!absent[i]) {
      count[i] += tally;
    }
  }
  
  for (int app = land_i+1; app < MAX_DAYS; app++) {
    int start = max(max(0, app - 1460), land_i - 730);
    
    int halfdays = count[app-1];
    if (start > 0) {
      halfdays -= count[start-1];
    }
    
    //    cout << "app = " << Date(app) << ": start = " << Date(start) << ", halfdays = " << halfdays << endl;
    if (halfdays / 2 >= 1095) {
      Date d(app);
      cout << d << endl;
      return true;
    }
  }

  assert(false);
}

int main()
{
  while (solve())
    ;
  return 0;
}
