typedef struct { int v[2][2]; } matriz;
matriz I, FIB;

matriz MM(matriz x, matriz y){ // MATRIZ MULTIPLICATION
    matriz k;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            k.v[i][j] = (x.v[i][0] * y.v[0][j] + x.v[i][1] * y.v[1][j]);
    return k; 
}

matriz fastPot(matriz x, int exp){ // FASTPOT MATRIZ EDITION
    if(exp <= 0) return I;
    if(exp%2)   return MM(x, fastPot(MM(x, x), (exp-1)/2));
    return fastPot(MM(x, x), exp/2);
}

void startFastPot(int N) {      // resposta esta em FIB.v[1][0]
    I.v[0][1] = I.v[1][0] = 0; I.v[0][0] = I.v[1][1] = 1; // matriz identidade
    FIB.v[0][0] = FIB.v[0][1] = FIB.v[1][0] = 1; FIB.v[1][1] = 0;
    FIB = fastPot(INI, N); // N eh o n-ezimo numero de fibonacci
}