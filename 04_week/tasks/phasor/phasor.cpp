
#include <cmath>
#include <iostream>
#include <limits>
#include <iomanip> // Для форматирования вывода
/*
Необходимо реализовать класс, представляющий комплесн амплитуду
Комплексная амплитуда может быть реализована в различных формах: алгебраическая, показательная, тригонометрическая, временная
- Конструктор по умолчанию создает нулевой фазор.
- Конструктор, принимающий амплитуду и фазу в радианах.
Конструкторы с тегами `ExpTag`, `DegTag`, `AlgTag` в качестве третьего параметра:
- Конструктор с тегом `ExpTag` - делегирует работу основному конструктору
- Конструктор с тегом `DegTag` - из амплитуды и фазы в градусах
- Конструктор с тегом `AlgTag` - из алгебраической формы записи (_real_, _imag_)
//Нельзя `std::complex`
- Операторы `+` и `-` удобно реализовывать в декартовых координатах
- Операторы `*` и `/` удобно реализовывать в полярных координатах
Реализовать перегрузку оператора `<<` для вывода комплексной амплитуды в
поток в формате: 

`{mag}*e(j*{arg}) [{real} + j*{imag}]`, где

- `{mag}` - амплитуда
- `{arg}` - аргумент в градусах
- `{real}` - действительная часть
- `{imag}` - мнимая часть
Также предоставляются синонимы:
- Метод `Abs` - синоним метода `Magnitude`
- Метод `Angle` - синоним метода `Phase`
- Метод `A
//также необходима реализация и доступность арфим. операций  "+"  "-"  "*" ; "/" ; "унарный -""
//Нужна перегрузка += -=  *=  /=
Мыыы друзьяя, а для них, у друзей нет выходных
//Ключевое слово friend позволяет внешней функции или классу получать доступ к приватным private и защищенным protected членам класса. 
-Дается прямой доступ к приватным полям
-Не вызывает методы
-Не наследуется
-Нет двунаправленности(например если А дружит с Б, значит Б является другом А, но не наоборот).
Понадобилось для перегрузки вывода. Можно и по-другому, но мне просто понравилось это.
//Из тестов видно, что нужен setprecition(3) или что-то подобное
/////Осталась часть, которая дублируется на мой взгляд, но как это грамотно исправить пока не знаю(в конце кода где операторы)
1. Бинарные операторы (не члены класса) 
2. Операторы с вещественными числами
*/

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
public:
    Phasor() : real_(0.0), imag_(0.0) {}  // конструкторы
    Phasor(double magnitude, double phaseRad);
    Phasor(double magnitude, double phaseRad, ExpTag tag);
    Phasor(double magnitude, double phaseDeg, DegTag tag);
    Phasor(double real, double imag, AlgTag tag);
    
    void SetPolar(double magnitude, double phase_rad); 
    void SetCartesian(double real, double imag);
    
    double Magnitude() const; 
    double Phase() const;      
    double PhaseDeg() const;  
    double Real() const;
    double Imag() const;
    //Синонимы
    double Abs() const { return Magnitude(); }
    double Angle() const { return Phase(); }
    double AngleDeg() const { return PhaseDeg(); }

    Phasor operator+() const;  
    Phasor operator-() const;  
    
    Phasor& operator+=(const Phasor& other);
    Phasor& operator-=(const Phasor& other);
    Phasor& operator*=(const Phasor& other);
    Phasor& operator/=(const Phasor& other);
    
    Phasor& operator+=(double scalar);
    Phasor& operator-=(double scalar);
    Phasor& operator*=(double scalar);
    Phasor& operator/=(double scalar);

    Phasor Conj() const;  
    Phasor Inv() const;  

    friend bool operator==(const Phasor& lhs, const Phasor& rhs);
    friend bool operator!=(const Phasor& lhs, const Phasor& rhs);
    
    friend std::ostream& operator<<(std::ostream& os, const Phasor& p);
    
private:
    double real_;  
    double imag_; 
    
    static double NormalizeAngle(double angleRad);
    static double DegToRad(double deg);
    static double RadToDeg(double rad);
};

Phasor MakePhasorCartesian(double real, double imag);
Phasor MakePhasorPolar(double magnitude, double phaseRad);
Phasor MakePhasorPolarDeg(double magnitude, double phaseDeg);

// Реализации конструкторов
Phasor::Phasor(double magnitude, double phaseRad) {
    SetPolar(magnitude, phaseRad);
}

Phasor::Phasor(double magnitude, double phaseRad, ExpTag)
    : Phasor(magnitude, phaseRad) { //Делегирование 
}

Phasor::Phasor(double magnitude, double phaseDeg, DegTag) {
    SetPolar(magnitude, DegToRad(phaseDeg));
}

Phasor::Phasor(double real, double imag, AlgTag)
    : real_(real), imag_(imag) {
    // уже в декартовых координатах
}

// Реализации методов 
void Phasor::SetPolar(double magnitude, double phaseRad) {
    phaseRad = NormalizeAngle(phaseRad);
    real_ = magnitude * std::cos(phaseRad);
    imag_ = magnitude * std::sin(phaseRad);
}

void Phasor::SetCartesian(double real, double imag) {
    real_ = real;
    imag_ = imag;
}

double Phasor::Magnitude() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

double Phasor::Phase() const {
    if (real_ == 0.0 && imag_ == 0.0) return 0.0;  // для нулевого фазора фаза не определена, возвращаем 0
    return std::atan2(imag_, real_); // лучше чем std::atan(y/x) тк обрабатывает все квадранты и синтаксис приятнее
}

double Phasor::PhaseDeg() const {
    return RadToDeg(Phase());
}

double Phasor::Real() const {
    return real_;
}

double Phasor::Imag() const {
    return imag_;
}

Phasor Phasor::operator+() const {
    return *this;  // унарный "+"" ничего не меняет
}

Phasor Phasor::operator-() const {
    return Phasor(-real_, -imag_, AlgTag()); //создает новый объект, не меняя старый
}

Phasor& Phasor::operator+=(const Phasor& other) {
    real_ += other.real_;
    imag_ += other.imag_;
    return *this;
}

Phasor& Phasor::operator-=(const Phasor& other) {
    real_ -= other.real_;
    imag_ -= other.imag_;
    return *this;
}

Phasor& Phasor::operator*=(const Phasor& other) {
    // Умножение в полярных координатах
    double mag1 = Magnitude();
    double mag2 = other.Magnitude();
    double phase1 = Phase();
    double phase2 = other.Phase();
    
    double newMag = mag1 * mag2;
    double newPhase = phase1 + phase2;
    
    SetPolar(newMag, newPhase);
    return *this;
}

Phasor& Phasor::operator/=(const Phasor& other) {
    // Деление в полярных координатах
    double mag1 = Magnitude();
    double mag2 = other.Magnitude();
    
    if (mag2 == 0.0) throw std::runtime_error("division by zero detected"); //кидать всякое я уже умею. В тестах деление на ноль не проверяется, но пусть будет. не мешает же

    double phase1 = Phase();
    double phase2 = other.Phase();
    
    double newMag = mag1 / mag2;
    double newPhase = phase1 - phase2;
    
    SetPolar(newMag, newPhase);
    return *this;
}

Phasor& Phasor::operator+=(double scalar) {
    real_ += scalar;
    return *this;
}

Phasor& Phasor::operator-=(double scalar) {
    real_ -= scalar;
    return *this;
}

Phasor& Phasor::operator*=(double scalar) {
    real_ *= scalar;
    imag_ *= scalar;
    return *this;
}

Phasor& Phasor::operator/=(double scalar) {
    if (scalar == 0.0) throw std::runtime_error("division by zero detected");
    real_ /= scalar;
    imag_ /= scalar;
    return *this;
}

//Спец и доп. методы
//Сопряженное число. То есть если было x=a+ib, то вернется x'=a-ib
Phasor Phasor::Conj() const { 
    return Phasor(real_, -imag_, AlgTag());
}

Phasor Phasor::Inv() const {
    // 1/z = conj(z) / |z|^2
    double mag_sq = real_ * real_ + imag_ * imag_;

    return Phasor(real_ / mag_sq, -imag_ / mag_sq, AlgTag());
}

double Phasor::NormalizeAngle(double angleRad) {
    // Приводим угол к диапазону (-П, П]. Это надо потому что каждые 360 градусов ничего не меняют 370=10 
    const double two_pi = 2.0 * M_PI;
    // Убираем полные обороты
    angleRad = std::fmod(angleRad, two_pi); //Нашел fmod. Возвращает остаток от деления. Работает как сколько останется от x после вычитания максимально возможного количества целых y
    // Приводим к (-П, П]
    if (angleRad > M_PI) {
        angleRad -= two_pi;
    } else if (angleRad <= -M_PI) {
        angleRad += two_pi;
    }
    
    return angleRad;
}

double Phasor::DegToRad(double deg) {
    return deg * M_PI / 180.0;
}

double Phasor::RadToDeg(double rad) {
    return rad * 180.0 / M_PI;
}

// Дружественные операторы сравнения
bool operator==(const Phasor& lhs, const Phasor& rhs) {
    const double eps = 1e-10;  // точность сравнения
    return std::abs(lhs.real_ - rhs.real_) < eps &&
           std::abs(lhs.imag_ - rhs.imag_) < eps;
}

bool operator!=(const Phasor& lhs, const Phasor& rhs) {
    return !(lhs == rhs);
}

// Дружественный оператор вывода
std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    double mag = p.Magnitude();
    double arg_deg = p.PhaseDeg();
    double real = p.Real();
    double imag = p.Imag();
    
    // Устанавливаем фиксированный формат и точность 3 знака после запятой(тесты требуют)
    os << std::fixed << std::setprecision(3);
    os << mag << "*e(j*" << arg_deg << ") [" 
       << real << " + j*" << imag << "]";
    
    // Восстанавливаем состояние потока после наших издевательств над ним
    os.unsetf(std::ios_base::floatfield);
    os.precision(6);  // стандартная точность
    
    return os;
}
// Бинарные операторы (не члены класса) 
Phasor operator+(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result += rhs;
    return result;
}

Phasor operator-(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result -= rhs;
    return result;
}

Phasor operator*(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result *= rhs;
    return result;
}

Phasor operator/(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result /= rhs;
    return result;
}

// Операторы с вещественными числами
Phasor operator+(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result += scalar;
    return result;
}

Phasor operator+(double scalar, const Phasor& phasor) {
    return phasor + scalar;  // коммутативность
}

Phasor operator-(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result -= scalar;
    return result;
}

Phasor operator-(double scalar, const Phasor& phasor) {
    return Phasor(scalar, 0, AlgTag()) - phasor;
}

Phasor operator*(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result *= scalar;
    return result;
}

Phasor operator*(double scalar, const Phasor& phasor) {
    return phasor * scalar;  // коммутативность
}

Phasor operator/(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result /= scalar;
    return result;
}

Phasor operator/(double scalar, const Phasor& phasor) {
    return Phasor(scalar, 0, AlgTag()) / phasor;
}

// Функции создания
Phasor MakePhasorCartesian(double real, double imag) {
    return Phasor(real, imag, AlgTag());
}

Phasor MakePhasorPolar(double magnitude, double phaseRad) {
    return Phasor(magnitude, phaseRad);
}

Phasor MakePhasorPolarDeg(double magnitude, double phaseDeg) {
    return Phasor(magnitude, phaseDeg, DegTag());
}