#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> point;
typedef pair<point, point> line;

point operator - (const point &a, const point &b)
{
	return point(a.first - b.first, a.second - b.second);
}

bool cmp(line a, line b)
{
	bool aa = a.first < a.second;
	bool ab = b.first < b.second;
	long long x = (long long)(a.second.second - a.first.second) * (b.second.first - b.first.first);
	long long y = (long long)(b.second.second - b.first.second) * (a.second.first - a.first.first);
	if (aa == ab)
	{
		if (x == y)
		{
			if (aa)
				return a.first < b.first;
			else
				return b.first < a.first;
		}
		else
			return x < y;
	}
	else
		return aa;
}

long long cross(point a, point b)
{
	return ((long long)a.first * b.second - (long long)a.second * b.first);
}

bool covers(line a, line b, line c)
{
	long long frac1_top = cross(b.first - a.first, b.second - b.first);
	long long frac1_bot = cross(a.second - a.first, b.second - b.first);
	long long frac2_top = cross(c.first - a.first, c.second - c.first);
	long long frac2_bot = cross(a.second - a.first, c.second - c.first);
	return frac2_top * frac1_bot < frac1_top * frac2_bot;
}

bool parallel(line a, line b)
{
	return cross(a.second - a.first, b.second - b.first) == 0;
}

vector<line> half_plane(vector<line> v)
{
	sort(v.begin(), v.end(), cmp);
	vector<line> st;
	for (int i = 0; i < v.size(); i++)
	{
		while (st.size() > 1 && covers(st[st.size() - 2], st[st.size() - 1], v[i]))
			st.pop_back();
		if (st.size() > 0 && parallel(st.back(), v[i]) && (v[i].first < v[i].second || st.back().first >= st.back().second))
			st.pop_back();
		st.push_back(v[i]);
	}
	int f = 0;
	while ((int)st.size() - f > 2)
	{
		if (covers(st[st.size() - 2], st[st.size() - 1], st[f]))
			st.pop_back();
		else if (covers(st[st.size() - 1], st[f], st[f + 1]))
			f++;
		else
			break;
	}
	if ((int)st.size() - f == 2)
	{
		if (parallel(st.back(), st[f]) == 0)
		{
			if (st[f].first > st.back().first)
			{
				st.clear();
				return st;
			}
		}
	}
	vector<line> st2;
	for (int i = f; i < st.size(); i++)
		st2.push_back(st[i]);
	return st2;
}


int main()
{
	int n;
	cin >> n;
	vector<line> lines;
	for (int i = 0; i < n; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		lines.push_back(line(point(x1, y1), point(x2, y2)));
	}
	lines = half_plane(lines);
	cout << lines.size() << endl;
	for (int i = 0; i < lines.size(); i++)
		cout << lines[i].first.first << " " << lines[i].first.second << " " << lines[i].second.first << " " << lines[i].second.second << endl;
}
