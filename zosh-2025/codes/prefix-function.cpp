#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefix_function(std::string s) {
    int n = (int) s.size();
    std::vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0)
            cur = p[cur - 1];
        if (s[i] == s[cur])
            p[i] = cur + 1;
    }
    return p;
}

int main() {
    std::string s;
    std::cin >> s;
    std::vector<int> mas = prefix_function(s);
    
    for (int i = 0; i < mas.size(); ++i){
        std::cout << mas[i] << " ";
    }

    return 0;
}