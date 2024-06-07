#include <iostream>
#include <cassert>

bool isOdd(const int n) { return (n % 2) != 0; }

int main() {
    int N{};
    std::cin >> N;

    assert(1 <= N and N <= 1000);

    for (int i = 1; i<= N; ++i) {
        if (isOdd(i)) {
            std::cout << i << '\n';
        }
    }
}
