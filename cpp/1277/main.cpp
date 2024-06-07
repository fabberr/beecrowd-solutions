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

constexpr auto STREAMSIZE_MAX = std::numeric_limits<std::streamsize>::max();

using namespace std::string_literals;
using namespace std::string_view_literals;

enum class record_type : char { ATTENDANCE = 'P', ABSTINENCE = 'A' };

typedef struct {
    std::vector<std::string> student_names   = {};
    std::vector<std::string> attendance_data = {};
    std::size_t n_inputs = 0;
} inputs_t;

typedef struct {
    std::string_view name = {};
    int attendances = 0;
    int abstinences = 0;
    int sample_size = 0;

    auto parse_attendance_data(std::span<const char> attendance_data) -> void {
        for (const auto& record : attendance_data) {
            switch (record) {
                case static_cast<int>(record_type::ATTENDANCE):
                    this->attendances++;
                    this->sample_size++;
                    break;
                case static_cast<int>(record_type::ABSTINENCE):
                    this->abstinences++;
                    this->sample_size++;
                    break;
                default: // medical leave - do not increase sample size
                    break;
            }
        }
    }
} student_t;

auto read_next_inputs(const std::size_t n) -> std::vector<std::string> {
    auto inputs = std::vector<std::string>{};
    inputs.reserve(n);

    for (std::size_t i = 0 ; i < n; ++i) {
        std::string input{};
        std::cin >> input;
        inputs.emplace_back(std::move(input));
    }

    return inputs;
}

auto parse_inputs(const inputs_t& inputs) -> std::vector<student_t> {

    auto students = std::vector<student_t>(inputs.n_inputs);
    
    for (std::size_t i = 0; i < inputs.n_inputs; ++i) {
        auto& current_student = students[i];
        current_student.name = inputs.student_names[i];

        current_student.parse_attendance_data(inputs.attendance_data[i]);
    }

    return students;
}

auto get_students_with_attendance_below_threshold(std::span<const student_t> students) -> std::vector<student_t> {

    constexpr const double ATTENDANCE_THRESHOLD = 75.0;

    const auto is_student_below_threshold = [](const student_t& s) -> bool {
        const auto attendance_pct = (s.attendances * 100.0) / s.sample_size;
        return (attendance_pct < ATTENDANCE_THRESHOLD);
    };
    
    auto result = std::vector<student_t>{};
    std::copy_if(
        students.begin(), students.end(),
        std::back_inserter(result),
        is_student_below_threshold
    );
    return result;
}

auto get_output(std::span<const student_t> students) -> std::string {
    constexpr const char SEPARATOR_CHAR = ' ';

    if (students.empty()) {
        return "";
    }

    std::ostringstream oss{};
    bool isFirst = true;

    for (const auto& student : students) {
        if (isFirst) {
            isFirst = false;
        } else {
            oss << SEPARATOR_CHAR;
        }
        oss << student.name;
    }
    return oss.str();
}

// https://resources.beecrowd.com/repository/UOJ_1277.html
auto main() -> int {
    // Number of test cases
    std::size_t T{}; std::cin >> T;

    for ( ; T > 0; --T) {
        // Number of students in this test case
        std::size_t N{}; std::cin >> N;
        std::cin.ignore(STREAMSIZE_MAX, '\n');

        const auto inputs = inputs_t {
            .student_names   = read_next_inputs(N),
            .attendance_data = read_next_inputs(N),
            .n_inputs        = N,
        };

        const auto students = parse_inputs(inputs);
        std::cout << get_output(get_students_with_attendance_below_threshold(students)) << '\n';
    }
}
