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
#include <memory>
#include <utility>
#include <limits>
#include <new>

#include <cstddef>
#include <cstdint>

using namespace std::string_literals;
using namespace std::string_view_literals;

constexpr auto STREAMSIZE_MAX = std::numeric_limits<std::streamsize>::max();

auto get_inputs(const std::size_t n_inputs) {
    std::vector<std::string> inputs{};
    inputs.reserve(n_inputs);
    
    for (std::size_t i = 0 ; i < n_inputs; ++i) {
        std::string input{};
        std::getline(std::cin, input);
        inputs.emplace_back(std::move(input));
    }

    return inputs;
}

// Number of segments required to display a given decimal digit
constexpr std::array _seven_segment_display_lookup = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

auto count_segments(const std::string& digits) -> std::size_t {
    std::size_t count = 0;
    for (const auto& digit : digits) {
        auto number = digit - '0';
        count += _seven_segment_display_lookup[number];
    }
    return count;
}

// https://resources.beecrowd.com/repository/UOJ_1168.html
auto main() -> int {
    std::size_t N{}; std::cin >> N;
    std::cin.ignore(STREAMSIZE_MAX, '\n');

    for (const auto& input : get_inputs(N)) {
        auto count = count_segments(input);
        std::cout << count << " leds\n";
    }
}
