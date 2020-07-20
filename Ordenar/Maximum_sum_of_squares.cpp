
#include <bits/stdc++.h>
using namespace std;

#define N 5
 
void printMaxSumSub(int mat[][N], int k)
{
    if (k > N) return;
    int stripSum[N][N];
    for (int j=0; j<N; j++)
    {

        int sum = 0;
        for (int i=0; i<k; i++)
            sum += mat[i][j];
        stripSum[0][j] = sum;
        for (int i=1; i<N-k+1; i++)
        {
            sum += (mat[i+k-1][j] - mat[i-1][j]);
            stripSum[i][j] = sum;
        }
    }

    int max_sum = INT_MIN, *pos = NULL;

    for (int i=0; i<N-k+1; i++)
    {

        int sum = 0;
        for (int j = 0; j<k; j++)
            sum += stripSum[i][j];
        if (sum > max_sum)
        {
            max_sum = sum;
            pos = &(mat[i][0]);
        }

        for (int j=1; j<N-k+1; j++)
        {
            sum += (stripSum[i][j+k-1] - stripSum[i][j-1]);
            if (sum > max_sum)
            {
                max_sum = sum;
                pos = &(mat[i][j]);
            }
        }
    }
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
            cout << *(pos + i*N + j) << " ";
        cout << endl;
    }
}
 
int main()
{
    int mat[N][N] = {{1, 1, 1, 1, 1},
                     {2, 2, 2, 2, 2},
                     {3, 8, 6, 7, 3},
                     {4, 4, 4, 4, 4},
                     {5, 5, 5, 5, 5},
            };
    int k = 3;
    cout << "Maximum sum 3 x 3 matrix is\n";
    printMaxSumSub(mat, k);
 
    return 0;
}