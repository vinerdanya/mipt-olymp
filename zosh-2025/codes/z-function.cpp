#include<iostream>
#include<string>
#include<vector>


int main() {
    std::string s;
    std::cin >> s;
    std::vector<int> z(s.size());
    int L = 0, R = 0;
	z[0] = s.size();
    for (int i = 1; i < s.size(); ++i) {
        if (i <= R) {
            z[i] = std::min(z[i - L], R - i + 1);
        }
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
    for (auto i : z) {
        std::cout << i << ' ';
    }

    return 0;
}