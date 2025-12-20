#include <stdexcept>
#include <tuple>

struct Date {
    unsigned year = 0;
    unsigned month = 0;
    unsigned day = 0;
};

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == 
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < 
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

int markWeight(char mark) {
    switch (mark) {
        case 'Z': return 1;
        case 'D': return 2;
        case 'C': return 3;
        case 'B': return 4;
        case 'A': return 5;
        default: return 0;
    }
}

bool operator==(const StudentInfo& lhs, const StudentInfo& rhs) {
    return std::tie(lhs.mark, lhs.score) == 
           std::tie(rhs.mark, rhs.score);
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    return std::make_tuple(markWeight(lhs.mark), 
                           lhs.score,
                           -static_cast<int>(lhs.course), 
                           lhs.birth_date.year,
                           lhs.birth_date.month,
                           lhs.birth_date.day) 
           < 
           std::make_tuple(markWeight(rhs.mark), 
                           rhs.score,
                           -static_cast<int>(rhs.course),
                           rhs.birth_date.year,
                           rhs.birth_date.month,
                           rhs.birth_date.day);
}

bool operator!=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs == rhs);
}

bool operator>(const StudentInfo& lhs, const StudentInfo& rhs) {
    return rhs < lhs;
}

bool operator<=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs < rhs);
}
