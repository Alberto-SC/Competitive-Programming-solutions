
#include <bits/stc++.h>
using namespace std; 
const int maxn = 1e5;
char str[maxn + 5], s[maxn + 5];
int n, m, rk[maxn + 5], tp[maxn + 5], tax[maxn + 5], sa[maxn + 5], height[maxn + 5];
void Sort(){ 
	for(int i = 0; i <= m; i++) tax[i] = 0;
	for(int i = 1; i <= n; i++) tax[rk[tp[i]]] ++;  
	for(int i = 1; i <= m; i++) tax[i] += tax[i - 1];
	for(int i = n; i >= 1; i--) sa[tax[rk[tp[i]]]--] = tp[i];
}
 
bool cmp(int f[], int x, int y, int w){
	return f[x] == f[y] && f[x + w] == f[y + w];
}
 
void Suffix(){
	//sa
	for(int i = 1; i <= n; i++) rk[i] = s[i], tp[i] = i;
	m = 127;//字符集
	Sort();
	for(int w = 1, p = 1, i; p < n; w <<= 1, m = p){//倍增更新rk
		// 
		for(p = 0, i = n - w + 1; i <= n; i++){
			tp[++p] = i;//将长度越界的第二关键字设为0
		}
		for(int i = 1; i <= n; i++){
			if(sa[i] > w) tp[++p] = sa[i] - w;
		}
		Sort();//更新sa
		swap(rk, tp);//用tp储存上一轮rk
		rk[sa[1]] = p = 1;
		for(int i = 2; i <= n; i++) rk[sa[i]] = cmp(tp, sa[i], sa[i - 1], w) ? p : ++p;
	}
	//height
	int j, k = 0;
	for(int i = 1 ; i <= n; i++){
		if(k) k--;
		j = sa[rk[i] - 1];
		while(s[i + k] == s[j + k]) k++;
		height[rk[i]] = k;
	}
}
int main(){
    int n;
    return 0;
}