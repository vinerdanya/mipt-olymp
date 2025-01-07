#include <iostream>
#include <vector>
#include <string>

int64_t mod = 1e9 + 7;
std::vector<int64_t> p;
std::vector<int64_t> base;

int64_t hash(const std::vector<int64_t>& p, const std::vector<int64_t>& base, size_t i, size_t j) {
    int64_t h = p[j] - p[i - 1] * base[j - i + 1] % mod;
    h = (mod + h) % mod;
    return h;
}

void preprocess(const std::string& s, std::vector<int64_t>& p, std::vector<int64_t>& base) {
    base.resize(s.size());
    p.resize(s.size());
    base[0] = 1;

    for (size_t i = 1; i < base.size(); ++i) {
        base[i] = base[i - 1] * 257 % mod;
    }

    for (size_t i = 1; i < p.size(); ++i) {
        p[i] = (p[i - 1] * base[1] + s[i]) % mod;
    }
}

int main() {
    std::string a, b;
    std::cin >> a >> b;

    a = '#' + a;
    b = '#' + b;

    preprocess(a, p, base);
    std::vector<int64_t> pa = p, base_a = base;
    preprocess(b, p, base);
    std::vector<int64_t> pb = p, base_b = base;

    bool found = false;
    size_t n = a.size() - 1;
    size_t m = b.size() - 1; 

    for (size_t i = 1; i + n - 1 <= m; ++i) {
        if (hash(pb, base_b, i, i + n - 1) == hash(pa, base_a, 1, n)) {
            found = true;
            break;
        }
    }

    if (found) {
        std::cout << "Yes" << "\n";
    } else {
        std::cout << "No" << "\n";
    }

    return 0;
}
