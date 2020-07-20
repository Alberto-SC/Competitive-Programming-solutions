#include <cstdio>
#include <map>
#include <string>
using namespace std;

const int nmax = 20;

string Dutch[nmax];
map<string,string> Transl;
map<string,int> NrCorr, All;
map<string,bool> Corr;

int main()
{	int n, m, i, j;
	long long corr, all;
	bool correct;
	char w1[21], w2[21], judgment[21];
	string word, tr;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{	scanf("%s", w1);
		word = w1;
		Dutch[i] = word;
		NrCorr[word] = All[word] = 0;
		Corr[word] = true;
	}
	scanf("%d", &m);
	for (j = 0; j < m; j++)
	{	scanf("%s %s %s", w1, w2, judgment);
		word = w1;
		tr = w2;
		Transl[word] = tr;
		All[word]++;
		if (judgment[0] == 'c')
			NrCorr[word]++;
		else
			Corr[word] = false;
	}
	correct = true;
	corr = all = 1;
	for (i = 0; i < n; i++)
	{	if (!Corr[Dutch[i]])
			correct = false;
		corr *= NrCorr[Dutch[i]];
		all *= All[Dutch[i]];
	}
	if (all == 1)
	{	for (i = 0; i < n; i++)
			printf("%s%c", Transl[Dutch[i]].c_str(), i<n-1?' ':'\n');
		printf("%scorrect\n", correct?"":"in");
	}
	else
		printf("%lld correct\n%lld incorrect\n", corr, all-corr);
	return 0;
}