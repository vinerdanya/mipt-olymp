#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll k = 131;

struct StringHash {
    ll n;
    string s;
    vector<ull> h, p;
    StringHash (string s) : s(s), n((ll) s.size()) {
        h = vector<ull>(n + 1, 0);
        p = vector<ull>(n + 1, 1);
        for(ll i = 1; i <= n; ++i){
            h[i] = h[i - 1] * k + ull(s[i - 1] - 'a' + 1);
            p[i] = p[i - 1] * k;
        }
    }
    ull get_hash(ll l, ll r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
};

int main() {
    string line; cin >> line;
    StringHash hesh(line);
    unordered_set <ull> s;

    for (int i = 1; i <= line.size(); i++) {
        for (int j = i; j <= line.size(); j++) {
            s.insert(hesh.get_hash(i, j));
        }
    }
    cout << s.size();

    return 0;
}