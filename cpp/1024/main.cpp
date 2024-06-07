// C++ stdlib
#include <vector>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <string_view>
#include <span>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <limits>
#include <memory>
#include <new>

// C stdlib
#include <cstddef>
#include <cstdint>

using namespace std::string_literals;
using namespace std::string_view_literals;

constexpr auto STREAMSIZE_MAX = std::numeric_limits<std::streamsize>::max();

auto get_inputs(const std::size_t n) -> std::vector<std::string> {
    std::vector<std::string> inputs{};
    inputs.reserve(n);

    for (std::size_t i = 0 ; i < n; ++i) {
        std::string input{};
        std::getline(std::cin, input);
        inputs.emplace_back(std::move(input));
    }

    return inputs;
}

namespace cypher {

auto first_pass(std::span<char> mutable_str) -> std::span<char> {

    auto is_lowercase = [](const char ch) -> bool { return ('a' <= ch and ch <= 'z'); };
    auto is_uppercase = [](const char ch) -> bool { return ('A' <= ch and ch <= 'Z'); };

    // Shift letters 3 places to the right
    for (auto& ch : mutable_str) {
        if (is_lowercase(ch) or is_uppercase(ch)) {
            ch += 3;
        }
    }
    return mutable_str;
}

auto second_pass(std::span<char> mutable_str) -> std::span<char> {
    
    // Reverse the input (in-place)
    const auto len = mutable_str.size();
    for (std::size_t i = 0; i < len / 2; ++i) {
        std::exchange(
            mutable_str[len - i - 1], std::exchange(mutable_str[i], mutable_str[len - i - 1])
        );
    }
    return mutable_str;
}

auto third_pass(std::span<char> mutable_str) -> std::span<char> {

    // Shift all characters after the first half one place to the left
    const auto len = mutable_str.size();
    for (std::size_t i = len / 2; i < len; ++i) {
        mutable_str[i]--;
    }
    return mutable_str;
}

auto encrypt(const std::string& message) -> std::string {
    
    std::string copy{message};

    third_pass(second_pass(first_pass(copy)));

    return copy;
}

} // namespace cypher

// https://resources.beecrowd.com/repository/UOJ_1024.html
auto main() -> int {
    std::size_t N{}; std::cin >> N;
    std::cin.ignore(STREAMSIZE_MAX, '\n');

    for (auto& input : get_inputs(N)) {
        auto encrypted_message = cypher::encrypt(input);
        std::cout << encrypted_message << '\n';
    }
}
