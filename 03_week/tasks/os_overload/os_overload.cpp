#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>

struct Coord2D {
    int x = 0;
    int y = 0;
};

struct Circle {
    Coord2D coord;
    unsigned radius = 1;  // по умолчанию 1
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

//оператор вывода для Coord2D
std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << "(" << coord.x << ", " << coord.y << ")";
    return os;
}

// Оператор вывода для Circle
std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "circle[";
    
    if (circle.radius != 0) {
        os << circle.coord << ", r = " << circle.radius;
    }
    
    os << "]";
    return os;
}

// Оператор вывода для CircleRegion
std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {

    if (region.second) {
        os << "+";
    } else {
        os << "-";
    }
    os << region.first;
    return os;
}

    //  Оператор вывода для CircleRegionList
std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    os << "{";
    
    if (!list.empty()) {
        os << "\n";
        
        for (size_t i = 0; i < list.size(); ++i) {
            os << "\t" << list[i]; 
    // Запятая после всех элементов, кроме последнего
            if (i != list.size() - 1) os << ",";
            os << "\n";
        }
    }
    
    os << "}";
    return os;
}
