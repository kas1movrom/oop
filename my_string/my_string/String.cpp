//
// Created by romka on 11.11.2023.
//

#include "String.h"

namespace MyFpmiString {

    bool String::Check(const String &str, size_t idx) const {
        for (int i = static_cast<int>(str.size_) - 1; i >= 0; --i) {
            if (str.array_[i] != array_[idx - (str.size_ - 1) + i]) {
                return false;
            }
        }
        return true;
    }

    bool String::RCheck(const String &str, size_t idx) const {
        for (size_t i = 0; i < str.size_; ++i) {
            if (str[i] != array_[idx + i]) {
                return false;
            }
        }
        return true;
    }

    void String::SetNull(const String &str) {
        for (size_t i = 0; i < str.size_; ++i) {
            tab[str.array_[i]] = 0;
        }
    }

    void String::Reallocation() {
        if (capacity_ == 0) {
            ++capacity_;
        }
        Reallocation(capacity_ * factor);
    }

    void String::Reallocation(size_t new_cap) {
        capacity_ = new_cap;
        auto tmp = new char[capacity_];
        memcpy(tmp, array_, size_);

        delete[] array_;
        array_ = tmp;
    }


    String::String() noexcept: size_(0), capacity_(0), array_(nullptr) {}

    String::String(size_t size, char ch): size_(size), capacity_(size),
            array_(new char[size]) {
        memset(array_, ch, size);
    }

    String::String(const std::initializer_list<char> &list): size_(list.size()),
            capacity_(size_), array_(new char[size_]) {
        std::copy(list.begin(), list.end(), array_);
    }

    String::String(const String &str): String(str.array_) {}

    String::String(char ch): String(1, ch) {}

    String::String(String &&str) noexcept: size_(str.size_), capacity_(str.capacity_),
            array_(str.array_) {
        str.size_ = 0;
        str.capacity_ = 0;
        str.array_ = nullptr;
    }

    String::String(const String &str, size_t start, size_t len) {
        if (start >= str.size_) {
            throw std::out_of_range("StringOutOfRange!");
        }
        size_ = std::min(len, str.size_ - start);
        capacity_ = size_;
        array_ = new char[size_];

        memcpy(array_, str.array_ + start, size_);
    }

    String::String(const char* str): size_(strlen(str)), capacity_(size_),
            array_(new char[size_]) {
        memcpy(array_, str, size_);
    }


    String::~String() {
        delete[] array_;
    }


    char* String::Data() noexcept {
        return array_;
    }

    const char* String::Data() const noexcept {
        return array_;
    }

    const char *String::CStr() const noexcept {
        return array_;
    }

    size_t String::Size() const noexcept {
        return size_;
    }

    size_t String::Length() const noexcept {
        return size_;
    }

    bool String::Empty() const noexcept {
        return size_ == 0;
    }

    size_t String::Capacity() const noexcept {
        return capacity_;
    }

    char& String::Front() {
        return array_[0];
    }

    char String::Front() const {
        return array_[0];
    }

    char& String::Back() {
        return array_[size_ - 1];
    }

    char String::Back() const {
        return array_[size_ - 1];
    }

    char& String::At(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        return array_[index];
    }

    char String::At(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        return array_[index];
    }


    void String::Swap(String &other) noexcept {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);
    }


    size_t String::Copy(char *str, size_t len, size_t pos) const {
        if (pos > size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        size_t result = std::min(len, size_ - pos);
        memcpy(str, array_ + pos, result);
        return result;
    }


    void String::Clear() noexcept {
        size_ = 0;
    }

    void String::Resize(size_t new_size, char ch) {
        if (size_ >= new_size) {
            size_ = new_size;
            return;
        }
        if (new_size > capacity_) {
            Reallocation(new_size);
        }
        memset(array_ + size_, ch, new_size - size_);
        size_ = new_size;
    }

    void String::Reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            Reallocation(new_cap);
        }
    }

    void String::ShrinkToFit() {
        if (size_ != 0) {
            Reallocation(size_);
            return;
        }
        capacity_ = 0;
        delete[] array_;
        array_ = nullptr;
    }

    void String::push_back(char ch) {
        if (size_ >= capacity_) {
            Reallocation();
        }
        array_[size_++] = ch;
    }

    char String::pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("StringOutOfRange");
        }
        return array_[--size_];
    }


    String &String::Erase(size_t num, size_t pos) {
        if (pos > size_) {
            throw std::out_of_range("StringOutOfRange!");
        }
        auto tmp = new char[capacity_];
        size_t len = std::min(num, size_ - pos);

        memcpy(tmp, array_, pos);
        memcpy(tmp + pos, array_ + pos + len, (size_ - pos) - len);

        size_ -= len;
        delete[] array_;
        array_ = tmp;
        return *this;
    }


    String &String::Assign(const String &other) {
        return (*this = other);
    }

    String &String::Assign(const String &other, size_t num, size_t pos) {
        String tmp = String(other, pos, num);
        Swap(tmp);
        return *this;
    }

    String &String::Assign(char ch, size_t num) {
        String tmp = String(num, ch);
        Swap(tmp);
        return *this;
    }

    String &String::Assign(const std::initializer_list<char> &list) {
        String tmp = String(list);
        Swap(tmp);
        return *this;
    }


    String &String::Append(const String &other, size_t num, size_t pos) {
        if (pos > other.size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        size_t len = std::min(num, size_ - pos);
        if (capacity_ < len + size_) {
            Reallocation(len + size_);
        }
        memcpy(array_ + size_, other.array_ + pos, len);
        size_ += len;
        return *this;
    }

    String &String::Append(char ch, size_t num) {
        if (capacity_ < size_ + num) {
            Reallocation(size_ + num);
        }
        memset(array_ + size_, ch, num);
        size_ += num;
        return *this;
    }

    String &String::Append(const String &other) {
        return this->Append(other, other.size_);
    }

    String &String::Append(const std::initializer_list<char> &list) {
        size_t len = list.size();
        if (capacity_ < size_ + len) {
            Reallocation(size_ + len);
        }
        std::copy(list.begin(), list.end(), array_ + size_);
        size_ += len;
        return *this;
    }


    String String::SubStr(size_t pos, size_t num) const {
        String str = String(*this, pos, num);
        return str;
    }


    String &String::Insert(size_t idx, const String &str, size_t pos, size_t count) {
        if (idx > size_ || pos > str.size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        size_t len = std::min(count, str.size_ - pos);
        auto tmp = new char[(capacity_ = size_ + len)];

        memcpy(tmp, array_, idx);
        memcpy(tmp + idx, str.array_ + pos, len);
        memcpy(tmp + idx + len, array_ + idx, size_ - idx);

        delete[] array_;
        array_ = tmp;
        size_ = capacity_;
        return *this;
    }

    String &String::Insert(size_t idx, const String &other) {
        return this->Insert(idx, other, 0, other.size_);
    }

    String &String::Insert(size_t idx, size_t n, char ch) {
        if (idx > size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        auto tmp = new char[(capacity_ = size_ + n)];

        memcpy(tmp, array_, idx);
        memset(tmp + idx, ch, n);
        memcpy(tmp + idx + n, array_ + idx, size_ - idx);

        delete[] array_;
        array_ = tmp;
        size_ = capacity_;
        return *this;
    }

    String &String::Insert(size_t idx, const std::initializer_list<char> &list) {
        if (idx > size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        size_t len = list.size();
        auto tmp = new char[(capacity_ = size_ + len)];

        memcpy(tmp, array_, idx);
        std::copy(list.begin(), list.end(), tmp + idx);
        memcpy(tmp + idx + len, array_ + idx, size_ - idx);

        delete[] array_;
        array_ = tmp;
        size_ = capacity_;
        return *this;
    }


    String &String::Replace(size_t start, size_t num, const String &other, size_t pos, size_t len) {
        return this->Erase(num, start).Insert(start, other, pos, len);
    }

    String &String::Replace(size_t start, size_t num, const String &other) {
        return this->Replace(start, num, other, 0, other.size_);
    }

    String &String::Replace(size_t start, size_t num, char ch, size_t len) {
        return this->Erase(num, start).Insert(start, len, ch);
    }

    String &String::Replace(size_t start, size_t num, const std::initializer_list<char> &list) {
        return this->Erase(num, start).Insert(start, list);
    }


    size_t String::Find(char ch, size_t pos) const {
        if (pos > size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        for (size_t i = pos; i < size_; ++i) {
            if (array_[i] == ch) {
                return i;
            }
        }
        return -1;
    }

    size_t String::Find(const String &str, size_t pos) const {
        if (pos > size_ || str.size_ > size_ - pos) {
            throw std::out_of_range("StringOutOfRange");
        }
        for (int i = static_cast<int>(str.size_) - 2; i >= 0; --i) {
            auto idx = static_cast<unsigned char>(str.array_[i]);
            if (tab[idx] == 0) {
                tab[idx] = static_cast<int>(str.size_) - i - 1;
            }
        }
        if (tab[str.array_[str.size_ - 1]] == 0) {
            tab[str.array_[str.size_ - 1]] = static_cast<int>(str.size_);
        }
        for (size_t i = pos + str.size_ - 1; i < size_; ++i) {
            if (Check(str, i)) {
                SetNull(str);
                return i - (size_ - 1);
            }
            i += (tab[array_[i] == 0] ? str.size_ : tab[array_[i]]);
        }
        SetNull(str);
        return -1;
    }

    size_t String::Find(size_t pos, const String &str, size_t start, size_t n) const {
        return Find(String(str, start, n), pos);
    }

    size_t String::RFind(char ch, size_t pos) const {
        if (pos > size_) {
            throw std::out_of_range("StringOutOfRange");
        }
        for (size_t i = size_ - 1; i >= pos; --i) {
            if (array_[i] == ch) {
                return i;
            }
        }
        return -1;
    }

    size_t String::RFind(const String &str, size_t pos) const {
        if (pos > size_ || str.size_ > size_ - pos) {
            throw std::out_of_range("StringOutOfRange");
        }
        for (size_t i = 1; i < str.size_; ++i) {
            auto idx = static_cast<unsigned char>(str.array_[i]);
            if (tab[idx] == 0) {
                tab[idx] = static_cast<int>(i);
            }
        }
        if (tab[str.array_[0]] == 0) {
            tab[str.array_[0]] = static_cast<int>(str.size_);
        }
        for (int i = static_cast<int>(size_ - str.size_); i >= pos; --i) {
            if (RCheck(str, i)) {
                SetNull(str);
                return i;
            }
            i -= (tab[array_[i] == 0] ? static_cast<int>(str.size_) : tab[array_[i]]);
        }
        SetNull(str);
        return -1;
    }

    size_t String::RFind(size_t pos, const String &str, size_t start, size_t n) const {
        return RFind(String(str, start, n), pos);
    }


    String& String::operator=(const String &other) {
        if (this == &other) {
            return *this;
        }
        String tmp = *this;
        Swap(tmp);
        return *this;
    }

    String& String::operator=(String &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        String tmp = std::move(other);
        Swap(tmp);
        return *this;
    }

    char& String::operator[](size_t index) {
        return array_[index];
    }

    char String::operator[](size_t index) const {
        return array_[index];
    }

    std::ostream& operator<<(std::ostream& out, const String& str) {
        out << str.Data();
        return out;
    }

    std::istream& operator>>(std::istream& in, String& str) {
        std::vector<char> vec;
        char ch;
        do {
            ch = static_cast<char>(getchar());
            vec.push_back(ch);
        } while (ch != ' ' && ch != '\n' && ch != '\t');

        auto tmp = new char[(str.capacity_ = vec.size())];
        memcpy(tmp, vec.data(), vec.size());

        delete[] str.array_;
        str.array_ = tmp;
        str.size_ = str.capacity_;
        return in;
    }


    String &String::operator+=(const String &other) {
        return this->Append(other);
    }

    String &String::operator+=(const std::initializer_list<char> &list) {
        return this->Append(list);
    }

    String &String::operator+=(char ch) {
        return this->Append(ch, 1);
    }


    int String::Compare(const String &other) const noexcept {
        return this->Compare(0, size_, other);
    }

    int String::Compare(size_t pos, size_t len, const String &other) const {
        return this->Compare(pos, len, other, 0, other.Size());
    }

    int String::Compare(size_t pos, size_t len, const String &other, size_t sub_pos, size_t sub_len) const {
        if (pos > size_ || sub_pos > other.size_) {
            throw std::out_of_range("StringOutOfRange!");
        }
        size_t call_size = std::min(len, size_ - pos), other_size = std::min(sub_len, other.size_ - sub_pos);
        for (size_t i = 0; i < std::min(call_size, other_size); ++i) {
            if (array_[pos + i] != other.array_[sub_pos + i]) {
                return array_[pos + i] - other.array_[sub_pos + i];
            }
        }
        if (call_size != other_size) {
            return static_cast<int>(call_size) - static_cast<int>(other_size);
        }
        return 0;
    }



    bool operator==(const String& str1, const String& str2) {
        if (str1.Size() != str2.Size()) {
            return false;
        }
        for (size_t i = 0; i < str1.Size(); ++i) {
            if (str1[i] != str2[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const String& str1, const String& str2) {
        return !(str1 == str2);
    }

    bool operator<(const String& str1, const String& str2) {
        return str1.Compare(str2) < 0;
    }

    bool operator<=(const String& str1, const String& str2) {
        return !(str1 > str2);
    }

    bool operator>(const String& str1, const String& str2) {
        return str2 < str1;
    }

    bool operator>=(const String& str1, const String& str2) {
        return !(str1 < str2);
    }
} // MyFpmiString