#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int m = 1000000007;
template <typename T>
struct Matrix {
    vector < vector <T> > A;
    int r,c;
    Matrix(){
        this->r = 0;
        this->c = 0;
    }
    Matrix(int r,int c){
        this->r = r;
        this->c = c;
        A.assign(r , vector <T> (c));
    }

    Matrix(int r,int c,const T &val){
        this->r = r;
        this->c = c;
        A.assign(r , vector <T> (c , val));
    }
    Matrix(int n){
        this->r = this->c = n;
        A.assign(n , vector <T> (n));
        for(int i=0;i<n;i++)
            A[i][i] = (T)1;
    }
    Matrix operator * (const Matrix<T> &B){
        assert(c == B.r);
        int i,j,k;
        int x = r;
        int y = c;
        int z = B.c;
        Matrix <T> C(x,z,0);
        for(i=0 ; i<x ; i++)
            for(j=0 ; j<z ; j++)
                for(k=0 ; k<y ; k++)
                    C[i][j] = (C[i][j] + ( (lli)A[i][k] * (lli)B[k][j] ) %m)%m;
        return C;
    }
    Matrix operator ^ (long long n){
        assert(r == c);
        int i,j;
        Matrix <T> C(r);
        Matrix <T> X(r,c,0);
        for(i=0;i<r;i++)
            for(j=0;j<c;j++)
                X[i][j] = A[i][j];
        while(n){
            if(n&1)
                C *= X;
            X *= X;
            n /= 2;
        }
        return C;
    }
    vector<T>& operator [] (int i){
        assert(i < r);
        assert(i >= 0);
        return A[i];
    }

    const vector<T>& operator [] (int i) const{
        assert(i < r);
        assert(i >= 0);
        return A[i];
    }

    friend ostream& operator << (ostream &out,const Matrix<T> &M){
        for (int i = 0; i < M.r; ++i) 
            for (int j = 0; j < M.c; ++j) 
                out << M[i][j] << " \n"[j == M.c-1];
        return out;
    }


    void operator *= (const Matrix<T> &B){
        (*this) = (*this)*B;
    }

    void operator ^= (long long n){
        (*this)  =(*this)^n;
    }

};

int main(){
    lli n,b,k,x;
    cin>>n>>b>>k>>x;
    vector<int> nums(n);
    vector<int> bk(10);
    for(auto &c:nums)cin>>c,bk[c]++;
    Matrix<lli> M(x,x);
    Matrix<lli> F(x);
    for(int i = 0;i<x;i++){
        for(int j = 0;j<n;j++){
            M[i][(10*i+nums[j])%x]++;
        }
    }
    M^=b;
    // cout<<M<<endl;
    lli ans = 0;
    cout<<M[0][k]<<endl;
    // cout<<ans<<endl;
    return 0; 
}