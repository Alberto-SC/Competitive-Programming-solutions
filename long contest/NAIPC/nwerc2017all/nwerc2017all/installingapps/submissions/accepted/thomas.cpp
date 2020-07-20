// DP, process apps in descending order of the EXTRA space they need for installation

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nmax = 500, cmax = 10000;

struct app
{	int d, s, id;
	app() {}
	app (int d0, int s0, int id0)
	{	d = d0;
		s = s0;
		id = id0;
	}
};

app App[nmax];
int Size[nmax+1], Last[nmax+1], Prev[nmax+1][nmax+1], Order[nmax+1];

bool operator < (app A, app B)
{	return A.d-A.s > B.d-B.s;
}

int main()
{	int n, c, i, d, s, k, m;
	scanf("%d %d", &n, &c);
	for (i = 0; i < n; i++)
	{	scanf("%d %d", &d, &s);
		App[i] = app(d, s, i+1);
	}
	sort(App, App+n);
	m = 0;
	Size[0] = 0;
	for (i = 0; i < n; i++)
	{	for (k = m; k >= 0; k--)
			if (Size[k] + App[i].d <= c && Size[k] + App[i].s <= c && (k == m || Size[k+1] > Size[k] + App[i].s))
			{	Size[k+1] = Size[k] + App[i].s;
				Last[k+1] = i;
				Prev[k+1][i] = Last[k];
				if (k == m)
					m++;
			}
	}
	i = Last[m];
	for (k = m; k > 0; k--)
	{	Order[k-1] = i;
		i = Prev[k][i];
	}
	printf("%d\n", m);
	for (k = 0; k < m; k++)
		printf("%d%c", App[Order[k]].id, k<m-1?' ':'\n');
	return 0;
}