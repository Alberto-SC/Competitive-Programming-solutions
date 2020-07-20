// a*x + b*y = c
tuple<ii, ii, int> diophantine (int a, int b, int c) {
    ll d, x1, y1;
    tie(d, x1, y1) = gcd_extended(a, b);

    if (c % d) { // No solution
        throw;
    }

    c /= d;
    
    int x0 = c * x1;
    int f = -b / d; // X is defined by -b

    // X = x0 + f*t
    ii X = make_pair(x0, f); 

    int y0 = c * y1;
    int g = a / d; // Y is defined by a

    // Y = x0 + g*t; -> (y0, g)
    ii Y = make_pair(y0, g);

    return make_tuple(X, Y, c);
}