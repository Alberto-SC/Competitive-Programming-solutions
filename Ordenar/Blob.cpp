#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int dx[] = {1, -1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};
bool visitado[30][30];

int dfs(char mapa[30][30], int x, int y, int row, int col) {
	mapa[x][y] = true;
	int tam = 1;
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (mapa[nx][ny] == '1' && !visitado[nx][ny] && nx >= 0 && ny < row && ny >= 0 && ny < col) {
			tam += dfs(mapa, nx, ny, row, col); 
		}
	}
	return tam;
}

int main() {
	
	int TC, row, col;
	char mapa[30][30];
	string line;

	cin >> TC;
	while (getchar() != '\n');
	while (getchar() != '\n');
	while (TC--) {
		row = 0;
		while (1) {
			getline(cin, line);
			//cout << line.size() << "\n";
			if (line.size() == 0) break;
			col = line.size();
			for (int i = 0; i < line.size(); i++) {
				mapa[row][i] = line[i];
			}
			row++;
		}
		memset(visitado, false, sizeof(visitado));
		int ans = (int)-1e9;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int tam;
				if (!visitado[i][j] && mapa[i][j] =='1') {
					tam = dfs(mapa, i, j, row, col);
				}
				ans = max(ans, tam);
			}
		}
		cout << ans << "\n";
		if (TC) cout << "\n";
	}
	return 0;
}
