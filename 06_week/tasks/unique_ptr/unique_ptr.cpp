#include <string>
#include <utility>  

/*
//Необходимо реализовать класс `UniquePtr`, который реализует семантику уникального
//владения строкой `std::string`. Класс соответствует умному указателю `std::unique_ptr`.
--Нельзя использовать умные указатели STL в реализации
*/

class UniquePtr {
private:
    std::string* objPtr_;  // сырой указатель на управляемый объект

public:
    UniquePtr() : objPtr_(nullptr) {}
    
//Конструктор от сырого указателя. explicit чтобы избежать неявных преобразований
    explicit UniquePtr(std::string* ptr) : objPtr_(ptr) {}
    
//Запрещаем копирование (уникальное владение!)
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
// Разрешаем перемещение
    UniquePtr(UniquePtr&& other) noexcept : objPtr_(other.objPtr_) {
        other.objPtr_ = nullptr;  
    }
    
//Оператор перемещающего присваивания
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete objPtr_;  
            objPtr_ = other.objPtr_;  // забираем указатель у other
            other.objPtr_ = nullptr;
        }
        return *this;
    }

    ~UniquePtr() {
        delete objPtr_;
    }

//разыменование
    std::string& operator*() const {
        return *objPtr_;
    }

// Оператор доступа к членам
    std::string* operator->() const {
        return objPtr_;
    }
    
// Получение сырого указателя
    std::string* Get() const {
        return objPtr_;
    }
    
//Освобождение владения (возвращает указатель и становится nullptr)
    std::string* Release() {
        std::string* temp = objPtr_;
        objPtr_ = nullptr;
        return temp;
    }
    
// Сброс с новым объектом (удаляет старый и принимает новый)
    void Reset(std::string* new_ptr = nullptr) {
        if (objPtr_ != new_ptr) {
            delete objPtr_;
            objPtr_ = new_ptr;
        }
    }
    
// Обмен с другим UniquePtr
    void Swap(UniquePtr& other) noexcept {
        std::swap(objPtr_, other.objPtr_);
    }

//привенедение к bool    
   explicit operator bool() const {
        return objPtr_ != nullptr;
    }
};

// Функция MakeUnique (с поддержкой копирования и перемещения). Принимает строку и возвращает умный указатель `UniquePtr`.
UniquePtr MakeUnique(const std::string& str) {
    return UniquePtr(new std::string(str));
}

UniquePtr MakeUnique(std::string&& str) {
    return UniquePtr(new std::string(std::move(str)));
}

// Функция для обмена умными указателями `UniquePtr`
void Swap(UniquePtr& lhs, UniquePtr& rhs) noexcept {
    lhs.Swap(rhs);
}