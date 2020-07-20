int lcm(int a, int b){
    int g = gcd(a, b);
    return g ? (a / g * b) : 0;
}