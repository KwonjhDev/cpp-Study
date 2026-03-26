#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;
const int root = 15311432;
const int root_inv = 469870224;
const int root_pow = 8388608;

int modPow(int a, int b) {
    int ans = 1;
    while (b != 0) {
        if (b % 2 == 1) ans = (long long)ans * a % MOD;
        a = (long long)a * a % MOD;
        b /= 2;
    }
    return ans;
}

void ntt(vector<int> &A, int n, bool invert) {
    
    int log_n = 0;
    while ((1 << log_n) < n) log_n++;
    
    vector<int> rev(n);
    for (int i=0; i<n; i++) {
        rev[i] = 0;
        for (int j=0; j<log_n; j++) {
            if (i & (1 << j)) {
                rev[i] |= 1 << (log_n - 1 - j);
            }
        }
    }
    for (int i=0; i<n; i++) {
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    }
    
    for (int length = 2; length <= n; length*=2) {
        int step;
        if (invert) step = modPow(root_inv, root_pow/length);
        else step = modPow(root, root_pow/length);
        
        for (int i=0; i<n; i+=length) {
            int w = 1;
            
            for (int j=0; j<length/2; j++) {
                int u = A[i + j];
                int v = (long long)A[i + j + length/2] * w % MOD;
                
                A[i + j] = (u + v) % MOD;
                A[i + j + length/2] = (u - v + MOD) % MOD;
                
                w = (long long)w * step % MOD;
            }
        }
    }
    
    if (invert) {
        int inv_n = modPow(n, MOD - 2);
        for (int i=0; i<n; i++) {
            A[i] = (long long) A[i] * inv_n % MOD;
        }
    }
}

string mul(string a, string b) {
    string ans;
    vector<int> A, B;
    
    for (int i = a.length() - 1; i>=0; i--) {
        A.push_back(a[i] - '0');
    }
    for (int i = b.length() - 1; i>=0; i--) {
        B.push_back(b[i] - '0');
    }
    
    int n = 1;
    while (n<A.size() + B.size()) {
        n *= 2;
    }
    
    A.resize(n);
    B.resize(n);
    
    ntt(A, n, false);
    ntt(B, n, false);
    
    for (int i=0; i<n; i++) {
        A[i] = (long long)A[i] * B[i] % MOD;
    }
    
    ntt(A, n, true);
    
    vector<long long> res(n);
    for (int i=0; i<n; i++) {
        res[i] = A[i];
    }
    
    for (int i=0; i<(int)res.size(); i++) {
        if (res[i] >= 10) {
            if (i + 1 == (int)res.size()) res.push_back(0);
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    
    for (int i = (int)res.size()-1; i>=0; i--) {
        ans += to_string(res[i]);
    }
    
    return ans;
}

int main () {
    string a, b;
    cin >> a >> b;
    
    cout << mul(a, b);
    return 0;
}
