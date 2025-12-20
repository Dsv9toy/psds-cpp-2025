#include <stdexcept>
#include <iostream>
#include <vector>
#include <cstdint>

/*
Необходимо реализовать перегрузку побитовых операторов для перечисления `CheckFlags`:

- `operator|` - возвращает результат побитового ИЛИ двух перечислений
- `operator&` - возвращает `true`, если все активные флаги одного операнда
  присутствуют у другого операнда, иначе возвращает `false`. В случае когда у одного
  из операндов нет активных флагов возвращает `false`
- `operator^` - возвращает результат исключающего ИЛИ двух перечислений.
- `operator~` - инвертирует установленные флаги (для `NONE` результат будет `ALL`)
- `operator<<` - выводит через запятую в произвольный поток вывода имена включенных 
  флагов проверки
// Думаю сделать мини функцию для маскирования 


*/

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

// Вспомогательная функция для маскирования
uint8_t maskFlags(CheckFlags flags) {
    return static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::ALL);
}

//operator| - побитовое ИЛИ
CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    uint8_t result = maskFlags(lhs) | maskFlags(rhs);
    return static_cast<CheckFlags>(result);
}

//  operator& - проверка что один набор содержит другой
bool operator&(CheckFlags lhs, CheckFlags rhs) {
    uint8_t lhsMasked = maskFlags(lhs);
    uint8_t rhsMasked = maskFlags(rhs);
    
    // Если любой из операндов NONE -> false (по условию)
    if (lhsMasked == 0 || rhsMasked == 0) {
        return false;
    }
    
    return ((lhsMasked & rhsMasked) == lhsMasked) || 
           ((lhsMasked & rhsMasked) == rhsMasked);
}

//operator^ - исключающее ИЛИ
CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    uint8_t result = maskFlags(lhs) ^ maskFlags(rhs);
    return static_cast<CheckFlags>(result);
}

//operator~ - инвертирование
CheckFlags operator~(CheckFlags flags) {
    uint8_t masked = maskFlags(flags);
    uint8_t inverted = ~masked;
    uint8_t result = inverted & static_cast<uint8_t>(CheckFlags::ALL);
    
    return static_cast<CheckFlags>(result);
}

// operator<< - вывод в поток
std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    uint8_t masked = maskFlags(flags);
    
    if (masked == 0) {
        os << "NONE";
        return os;
    }
    
    if (masked == static_cast<uint8_t>(CheckFlags::ALL)) {
        os << "TIME, DATE, USER, CERT, KEYS, DEST";
        return os;
    }
    
    bool isFirst = true;
    
    // Проверяем каждый флаг
    if (masked & static_cast<uint8_t>(CheckFlags::TIME)) {
        os << "TIME";
        isFirst = false;
    }
    
    if (masked & static_cast<uint8_t>(CheckFlags::DATE)) {
        if (!isFirst) {
            os << ", ";
        }
        os << "DATE";
        isFirst = false;
    }
    
    if (masked & static_cast<uint8_t>(CheckFlags::USER)) {
        if (!isFirst) {
            os << ", ";
        }
        os << "USER";
        isFirst = false;
    }
    
    if (masked & static_cast<uint8_t>(CheckFlags::CERT)) {
        if (!isFirst) {
            os << ", ";
        }
        os << "CERT";
        isFirst = false;
    }
    
    if (masked & static_cast<uint8_t>(CheckFlags::KEYS)) {
        if (!isFirst) {
            os << ", ";
        }
        os << "KEYS";
        isFirst = false;
    }
    
    if (masked & static_cast<uint8_t>(CheckFlags::DEST)) {
        if (!isFirst) {
            os << ", ";
        }
        os << "DEST";
    }
    
    return os;
}
