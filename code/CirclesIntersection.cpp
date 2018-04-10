#include <iomanip>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
typedef long double ld;

const int MAX_N = 2e5+10;
const int INF = 1e9;
const ld eps = 1e-8;

bool is_zero(ld x) {
  if(abs(x) <= eps)
    return true;
  return false;
}

struct point {
public:
  ld x, y;
  point() {
  }
  point(ld xx, ld yy) {
    x = xx;
    y = yy;
  }
};


struct circle {
public:
  ld r;
  point o;
  circle(ld rr, ld x, ld y) {
    r = rr;
    o.x = x;
    o.y = y;
  }
  ld S() {
    return M_PI*r*r;
  }
  ld distance(point p1, point p2) { return hypot(p2.x-p1.x,p2.y-p1.y); }
  /*
    0 = other is inside this, zero point
    1 = other is tangent inisde of this, one point 
    2 = other is intersect with this, two point
    3 = other is tangent outside of this, one point
    4 = other is outside of this, zero point
  */
  pair<int, vector<point> > intersect(circle other) {
    vector<point> v;
    ld sumr = other.r + r;
    ld rr = r - other.r;
    ld dis = distance(o, other.o);

    ld a = (r*r - other.r*other.r + dis*dis)/(2*dis);
    ld h = sqrt(r*r-a*a);
    point p2(o.x, o.y);
    p2.x = a*(other.o.x - o.x)/dis;
    p2.y = a*(other.o.y - o.y)/dis;

    if(is_zero(sumr-dis)) {
      v.push_back(p2);
      return make_pair(3, v);
    }
    if(is_zero(rr - dis)) {
      v.push_back(p2);
      return make_pair(1, v);
    }
    if(dis <= rr) 
      return make_pair(0, v);
    if(dis >= sumr)
      return make_pair(4, v);

		
    point p3(p2.x + h*(other.o.y - o.y)/dis, p2.y - h*(other.o.x - o.x)/dis);
    point p4(p2.x - h*(other.o.y - o.y)/dis, p2.y + h*(other.o.x - o.x)/dis);
    v.push_back(p3);
    v.push_back(p4);
    return make_pair(2, v);
  }

  ld f(ld l, ld r, ld R){
    ld cosa = (l*l + r*r - R*R)/(2.0*r*l);
    ld a = acos(cosa);
    return r*r*(a - sin(2*a)/2);
  }
  
  ld intersection_area(circle c2) {
    ld l = distance(o, c2.o);
    if(l >= r + c2.r) return 0;
    else if(c2.r >= l + r) return S();
    else if(r >= l + c2.r) return c2.S();
    return f(l, r, c2.r) + f(l, c2.r, r);
  }
};

int main() {
  ld x1, y1, r1, x2, y2, r2;
  cin>>x1>>y1>>r1>>x2>>y2>>r2;
  circle a(r1, x1, y1);
  circle b(r2, x2, y2);
  pair<int, vector<point> > ans = a.intersect(b);
  for(int i=0;i<ans.second.size();i++)
    cout<<ans.second[i].x<<" "<<ans.second[i].y<<endl;
} 
