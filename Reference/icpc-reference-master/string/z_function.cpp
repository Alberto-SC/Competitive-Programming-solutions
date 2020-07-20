// returns size of common prefix starting in i
vector<int> z_function (const string &s) {
    int n = size(s), L = 0, R = 0;
    vector<int> z(n, 0);
    
    for(int i = 1; i < n; i++) {
        if (i <= R) z[i] = min(z[i - L], R - i + 1);
        while(z[i] + i < n && s[z[i] + i] == s[z[i]]) z[i]++;
        if(R < i + z[i] - 1) L = i, R = i + z[i] - 1;
    }
    
    return z; // z[i] = s.size() => match start
}

// Only contiguous error, else FFT!
bool matchError (string &p, string&t, int e = 1) {
  auto n = p.size(), m = t.size();
  auto s = p; s += "#"; s += t;
  auto z = z_function(s);
  
  reverse(begin(p), end(p));
  reverse(begin(t), end(t));
  auto g = p; g += "#"; g += t;
  auto iz = z_function(g);
  
  for (int i = n+1; i < z.size() - n; i++) 
    if (iz[z.size() - i + 1] + z[i] + e >= n)
      return true;
  
  return false;
}
