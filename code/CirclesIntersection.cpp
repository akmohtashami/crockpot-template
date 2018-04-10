#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double dist(double x1, double y1, double x2, double y2) { return hypot(x2-x1,y2-y1); }

double circle_area(double r) { return r*r*M_PI; }

double f(double l, double r, double R){
    double cosa = (l*l + r*r - R*R)/(2.0*r*l);
    double a = acos(cosa);
    return r*r*(a - sin(2*a)/2);
}

double intersection_area(double x1, double y1, double r1, double x2, double y2, double r2)
{
  double l = dist(x1, y1, x2, y2);
  if(l >= r1 + r2) return 0;
  else if(r2 >= l + r1) return circle_area(r1);
  else if(r1 >= l + r2) return circle_area(r2);
  return f(l, r1, r2) + f(l, r2, r1);
}
