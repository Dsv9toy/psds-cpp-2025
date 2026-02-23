#include <string>
#include <utility> 
/*
Необходимо реализовать классы `SharedPtr` и `WeakPtr`, которые представляют собой
аналоги `std::shared_ptr` и `std::weak_ptr`. То есть `SharedPtr` реализует 
семантику разделяемого владения, а `WeakPtr` представляет наблюдателя. В качестве 
объекта владения выступает строка `std::string`.
Идея реализовать какую-то структуру, которая бы содержала кол-во shared и weak
*/

struct ControlBlock {
    std::string* objPtr;      // указатель на управляемый объект
    size_t sharedCount;    // количество SharedPtr
    size_t weakCount;      // количество WeakPtr
    
    ControlBlock(std::string* ptr) 
        : objPtr(ptr), sharedCount(1), weakCount(1) {} 
    
    ~ControlBlock() {
        delete objPtr;  
    }
};

class SharedPtr {
private:
    std::string* rawPtr_;     
    ControlBlock* block_;   // указатель на управляющий блок
    
    //конструктор для создания из сырого указателя с контролем
    SharedPtr(std::string* ptr, ControlBlock* block) 
        : rawPtr_(ptr), block_(block) {
        if (block_) {
            block_->sharedCount++;
        }
    }
    
public:
    SharedPtr() : rawPtr_(nullptr), block_(nullptr) {}
    
    //Конструктор от сырого указателя
    explicit SharedPtr(std::string* someptr) 
        : rawPtr_(someptr), block_(someptr ? new ControlBlock(someptr) : nullptr) {}
    
    //Конструктор копирования
    SharedPtr(const SharedPtr& other) 
        : rawPtr_(other.rawPtr_), block_(other.block_) {
        if (block_) {
            block_->sharedCount++;
        }
    }
    
    // Конструктор перемещения
    SharedPtr(SharedPtr&& other) noexcept 
        : rawPtr_(other.rawPtr_), block_(other.block_) {
        other.rawPtr_ = nullptr;
        other.block_ = nullptr;
    }

    ~SharedPtr() {
        release();
    }
    
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();  // освобождаем текущее владение
            
            rawPtr_ = other.rawPtr_;
            block_ = other.block_;
            if (block_) {
                block_->sharedCount++;
            }
        }
        return *this;
    }
    
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            
            rawPtr_ = other.rawPtr_;
            block_ = other.block_;
            
            other.rawPtr_ = nullptr;
            other.block_ = nullptr;
        }
        return *this;
    }
    
    std::string& operator*() const {
        return *rawPtr_;
    }
    
    std::string* operator->() const {
        return rawPtr_;
    }
    
    std::string* Get() const {
        return rawPtr_;
    }
    
    void Reset(std::string* new_ptr = nullptr) {
        release();
        
        rawPtr_ = new_ptr;
        block_ = new_ptr ? new ControlBlock(new_ptr) : nullptr;
    }
    
    void Swap(SharedPtr& other) noexcept {
        std::swap(rawPtr_, other.rawPtr_);
        std::swap(block_, other.block_);
    }
    
    // Количество владельцев
    size_t UseCount() const {
        return block_ ? block_->sharedCount : 0;
    }
    
    // Оператор приведения к bool
    explicit operator bool() const {
        return rawPtr_ != nullptr;
    }
    
private:
    // Освобождение владения
    void release() {
        if (block_) {
            block_->sharedCount--;
            if (block_->sharedCount == 0) {
                block_->objPtr = nullptr;  // объект удалится в деструкторе блока
                // Не удаляем блок, если есть weak_ptr
                if (block_->weakCount == 0) {
                    delete block_;
                }
            }
        }
        rawPtr_ = nullptr;
        block_ = nullptr;
    }
    
    // Дружба жвачка с WeakPtr для доступа к управляющему блоку
    friend class WeakPtr;
};

class WeakPtr {
private:
    std::string* rawPtr_;      
    ControlBlock* block_;   
    
public:
    WeakPtr() : rawPtr_(nullptr), block_(nullptr) {}
    WeakPtr(const SharedPtr& sp) 
        : rawPtr_(sp.rawPtr_), block_(sp.block_) {
        if (block_) {
            block_->weakCount++;
        }
    }
    WeakPtr(const WeakPtr& other) 
        : rawPtr_(other.rawPtr_), block_(other.block_) {
        if (block_) {
            block_->weakCount++;
        }
    }
    WeakPtr(WeakPtr&& other) noexcept 
        : rawPtr_(other.rawPtr_), block_(other.block_) {
        other.rawPtr_ = nullptr;
        other.block_ = nullptr;
    }
    ~WeakPtr() {
        release();
    }
    
    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            
            rawPtr_ = other.rawPtr_;
            block_ = other.block_;
            if (block_) {
                block_->weakCount++;
            }
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            
            rawPtr_ = other.rawPtr_;
            block_ = other.block_;
            
            other.rawPtr_ = nullptr;
            other.block_ = nullptr;
        }
        return *this;
    }

    WeakPtr& operator=(const SharedPtr& sp) {
        release();
        
        rawPtr_ = sp.rawPtr_;
        block_ = sp.block_;
        if (block_) {
            block_->weakCount++;
        }
        return *this;
    }

    void Reset() {
        release();
    }

    void Swap(WeakPtr& other) noexcept {
        std::swap(rawPtr_, other.rawPtr_);
        std::swap(block_, other.block_);
    }
    
    // Количество владельцев (SharedPtr)
    size_t UseCount() const {
        return block_ ? block_->sharedCount : 0;
    }
    
    // Проверка, жив ли объект
    bool Expired() const {
        return !block_ || block_->sharedCount == 0;
    }
    
    // Создание SharedPtr, если объект ещё жив
    SharedPtr Lock() const {
        if (Expired()) {
            return SharedPtr();
        }
        return SharedPtr(rawPtr_, block_);  // используем приватный конструктор
    }
    
private:
    // Освобождение наблюдения
    void release() {
        if (block_) {
            block_->weakCount--;
            if (block_->sharedCount == 0 && block_->weakCount == 0) {
                delete block_;
            }
        }
        rawPtr_ = nullptr;
        block_ = nullptr;
    }
};
////////////////////////////////Доп.Функции////////////////////////
// Функция MakeShared
SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

// Функция Swap для SharedPtr
void Swap(SharedPtr& lhs, SharedPtr& rhs) noexcept {
    lhs.Swap(rhs);
}

// Функция Swap для WeakPtr
void Swap(WeakPtr& lhs, WeakPtr& rhs) noexcept {
    lhs.Swap(rhs);
}