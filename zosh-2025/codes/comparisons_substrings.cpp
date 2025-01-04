#include <iostream>
#include <vector>

int64_t mod = 1e9 + 7;
std::string s;
std::vector<int64_t> p;
std::vector<int64_t> base;

int64_t hash(size_t i, size_t j){
    int64_t h = p[j] - p[i - 1] * base[j - i + 1] % mod;
    h = (mod + h) % mod;
    return h;
}


int main() {
    std::cin >> s;

    s = '#' + s;
    base.resize(s.size());
    p.resize(s.size());
    base[0] = 1;

    for (size_t i = 1; i < base.size(); ++i) {
        base[i] = base[i - 1] * 257 % mod;
    }

    for (size_t i = 1; i < p.size(); ++i) {
        p[i] = (p[i - 1] * base[1] + s[i]) % mod;
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i){
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        if (hash(a, b) == hash(c, d)){
            std::cout << "Yes" << "\n";
        } else {
            std::cout << "No" << "\n";
        }
    }

    return 0;
}