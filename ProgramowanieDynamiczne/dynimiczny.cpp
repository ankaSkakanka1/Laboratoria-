#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long W;
    int n;      
    std::cin >> W >> n;

    std::vector<long long> dp(W + 1, 0);

    for (int i = 0; i < n; ++i) {
        long long s, v;
        std::cin >> s >> v;

        for (long long current_w = W; current_w >= s; --current_w) {
            dp[current_w] = std::max(dp[current_w], dp[current_w - s] + v);
        }
    }

    std::cout << dp[W] << std::endl;

    return 0;
}