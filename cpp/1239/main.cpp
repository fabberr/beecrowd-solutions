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
#include <ranges>
#include <limits>
#include <memory>
#include <new>
#include <type_traits>

// C stdlib
#include <cstddef>
#include <cstdint>

using namespace std::string_literals;
using namespace std::string_view_literals;

/** `std::to_underlying` is a C++23 feature, which beecrowd does not currently support 🫠 yet. */
constexpr inline auto
_to_underlying(auto enum_value) -> auto {
#ifdef __cpp_lib_to_underlying
    return std::to_underlying(enum_value);
#else
    return static_cast<std::underlying_type_t<decltype(enum_value)>>(enum_value);
#endif
}

enum class MarkdownToken : char { Emphasis = '_', Boldface = '*' };

enum class HtmlElementState : std::size_t { Opening, Closing };

constexpr inline auto
operator!(const HtmlElementState& state) -> HtmlElementState {
    using enum HtmlElementState;
    return (state == Opening) ? Closing : Opening;
}

auto enclose_html_element(std::string_view element, const HtmlElementState state) -> std::string {
    static std::array _map = {
        std::make_pair("<"sv , ">"sv), // HtmlElementState::Opening
        std::make_pair("</"sv, ">"sv), // HtmlElementState::Closing
    };

    const auto& [start, end] = _map[_to_underlying(state)];
    return std::string(start).append(element).append(end);
};

auto map_token(const MarkdownToken token) -> std::string_view {
    static std::map<MarkdownToken, std::string_view> _map = {
        { MarkdownToken::Boldface, "b"sv },
        { MarkdownToken::Emphasis, "i"sv },
    };

    return _map[token];
}

auto make_markdown_parser(MarkdownToken token) -> auto {

    using enum HtmlElementState;

    return [token = _to_underlying(token), element = map_token(token), state = Opening, result = ""s]
    (const char& input) mutable -> std::string_view {

        if (input != token) {
            return std::string_view(&input, 1);
        }

        result = enclose_html_element(element, state);
        state = !state;
        return result;
    };
}

// https://resources.beecrowd.com/repository/UOJ_1239.html
auto main() -> int {
    auto parseBoldface = make_markdown_parser(MarkdownToken::Boldface);
    auto parseEmpasis = make_markdown_parser(MarkdownToken::Emphasis);

    for (std::string text{}; std::getline(std::cin, text); ) {
        auto result = std::string();
        result.reserve(text.length() * 1.25);

        for (const auto& ch : text) {
            result.append(parseBoldface(ch));
        }

        auto copy = std::string(result);
        result.clear();
        for (const auto& ch : copy) {
            result.append(parseEmpasis(ch));
        }

        std::cout << result << '\n';
    }
}
