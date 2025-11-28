#include <iomanip>
// Поскольку литералы - это константы
// Создание пользовательского литерала начинается с обозначения constexpr - Значение будет констатной и будет вычислено на этапе компиляции
// (по крайней мере компилятор будет пытаться это сделать:)
// explicit - запрет на неявный вызов. Если ожидается какой-то литерал, но он не найден - выдаст ошибку, мол я не нашел, не знаю чё делать
// Далее идет тип данных, который будет возвращать наш литерал
// Далее идет operator"" и после него название литерала  _name 
// Далее в скобках пишется принимаемое значение с определенным типом данных 

// необходимо создать 11 пользовательских литератов
// _ft_to_m
//_ft_to_cm
//_ft_to_in
//_in_to_m
//_in_to_cm
//_in_to_ft
//_m_to_ft
//_m_to_in
//_m_to_cm
//_cm_to_m
//_cm_to_ft
//_cm_to_in
// Прописать их логику подобным образом. необходимо правильно определить точность. Размер принимаемых значений.
// Причем все преобразования возвращают тип `double`.
/*
Параметры типов должны быть только такие:
const char
unsigned long long int          // для целочисленного, но и то оно только unsigned типа
long double                     // просто double не проканает
char
wchar_t
char16_t
char32_t
const char'*', std::size_t
const wchar_t'*', std::size_t
const char16_t'*', std::size_t
const char32_t'*', std::size_t
*/

//1 фут = 0.3048 метра
//1 дюйм = 2.54 см = 0.0254м 
// Только к 22 годам понял, что футы - это типо ноги. 30см то примерно стопа:)
//-----------------------------Футы В куда угодно------------------------
constexpr long double operator""_ft_to_m(long double val) {
    
    return static_cast<double>(val * 0.3048);
}

constexpr long double operator""_ft_to_cm(long double val) {
    return static_cast<double>(val * 30.48);
}

constexpr long double operator""_ft_to_in(long double val) {
    return static_cast<double>(val / 0.083333333);
}

//-----------------------------Дюймы В куда угодно------------------------

constexpr long double operator""_in_to_m(long double val) {
    return static_cast<double>(val * 0.0254);
}

constexpr long double operator""_in_to_cm(long double val) {
    return static_cast<double>(val * 2.54);
}

constexpr long double operator""_in_to_ft(long double val) {
    return static_cast<double>(val / 12);
}

//-----------------------------Метры В куда угодно------------------------

constexpr long double operator""_m_to_ft(long double val) {
    return static_cast<double>(val / 0.3048);
}

constexpr long double operator""_m_to_in(long double val) {
    return static_cast<double>(val / 0.0254);
}

constexpr long double operator""_m_to_cm(long double val) {
    return static_cast<double>(val * 100);
}

//----------------------Сантиметры В куда угодно---------------------------

constexpr long double operator""_cm_to_m(long double val) {
    return static_cast<double>(val / 100);
}

constexpr long double operator""_cm_to_ft(long double val) {
    return static_cast<double>(val / 30.48);
}

constexpr long double operator""_cm_to_in(long double val) {
    return static_cast<double>(val / 2.54);
}
