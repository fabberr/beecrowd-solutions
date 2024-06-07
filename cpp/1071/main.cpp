#include <iostream>
#include <vector>

using list_t = std::vector<int>;

bool isOdd(const int n) { return (n % 2) != 0; }

list_t oddNumbersInRange(const int first, const int last) {
}

int sum(const list_t& nums) {
}

int main() {
    int x{}, y{};
    std::cin >> x >> y;
    
    std::cout << sum(oddNumbersInRange(x, y)) << '\n';
}