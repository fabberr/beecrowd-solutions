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

using frequency_map_t = std::map<char, std::size_t>;

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

auto normalize_tolower(std::span<char> span) -> std::span<char> {
    std::transform(span.begin(), span.end(), span.begin(), ::tolower);
    return span;
}

auto compute_letter_frequencies(std::span<char> input) -> frequency_map_t {

    auto is_letter = [](const char ch) -> bool { return ('a' <= ch and ch <= 'z'); };

    frequency_map_t frequencies{};
    for (const auto ch : input) {
        if (is_letter(ch)) { frequencies[ch]++; }
    }

    return frequencies;
}

auto get_highest_frequencies(const frequency_map_t& frequencies) -> std::vector<frequency_map_t::value_type> {

    // Find the highest count
    auto [_, highest_count] = *std::max_element(
        frequencies.begin(), frequencies.end(),
        [](const auto& a, const auto& b) -> bool { return (a.second < b.second); }
    );

    // Find all the elements that have the highest count (will always be at least one)
    std::vector<frequency_map_t::value_type> highest_frequency_letters{};
    std::copy_if(
        frequencies.begin(), frequencies.end(),
        std::back_inserter(highest_frequency_letters),
        [&highest_count](const auto& element) -> bool { return (element.second == highest_count); }
    );
    return highest_frequency_letters;
}

auto format_results(std::span<frequency_map_t::value_type const> highest_frequency_letters) -> void {
    for (const auto [ch, _] : highest_frequency_letters) {
        std::cout << ch;
    }
    std::cout << '\n';
}

// https://resources.beecrowd.com/repository/UOJ_1255.html
auto main() -> int {
    std::size_t N{}; std::cin >> N;
    std::cin.ignore(STREAMSIZE_MAX, '\n');

    for (auto& input : get_inputs(N)) {
        auto&& frequencies = compute_letter_frequencies(normalize_tolower(input));
        const auto highest_frequencies = get_highest_frequencies(frequencies);
        format_results(highest_frequencies);
    }
}
