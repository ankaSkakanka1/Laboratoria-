#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
struct Item {
    long long size;
    long long value;
    double ratio;
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long W;
    int n;      
    std::cin >> W >> n;

    std::vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> items[i].size >> items[i].value;
        items[i].ratio = static_cast<double>(items[i].value) / items[i].size;
    }

    std::sort(items.begin(), items.end(), compareItems);

    long long current_weight = 0;
    long long total_value = 0;

    for (int i = 0; i < n; ++i) {
        if (current_weight + items[i].size <= W) {
            current_weight += items[i].size;
            total_value += items[i].value;
        }
    }

    std::cout << total_value << std::endl;
}
