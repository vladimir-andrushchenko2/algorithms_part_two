#include <iostream>

size_t NPossibleSearchTrees(int n) {
    if (n < 2) {
        return 1;
    }

    size_t output{};

    for (int i = 1; i <= n; ++i) {
        output += NPossibleSearchTrees(i - 1) * NPossibleSearchTrees(n - i);
    }

    return output;
}

int main(int argc, const char * argv[]) {
    int n;
    std::cin >> n;

    std::cout << NPossibleSearchTrees(n) << '\n';
    return 0;
}
