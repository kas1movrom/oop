//
// Created by romka on 11.11.2023.
//

#ifndef FPMI_STRING_H
#define FPMI_STRING_H

#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>

namespace MyFpmiString {

    class String {

    private:

        size_t size_;
        size_t capacity_;

        char *array_;

        static const int factor = 2;
        static int tab[127];


        void Reallocation();

        void Reallocation(size_t new_cap);


        [[nodiscard]] bool Check(const String& str, size_t idx) const;

        [[nodiscard]] bool RCheck(const String& str, size_t idx) const;

        static void SetNull(const String& str);

    public:

        String() noexcept;

        String(const String& str);

        String(size_t size, char ch);

        explicit String(char ch);

        String(String&& str) noexcept;

        String(const std::initializer_list<char>& list);

        String(const String& str, size_t start, size_t len);

        String(const char *str);


        ~String();


        char* Data() noexcept;

        [[nodiscard]] const char* Data() const noexcept;

        [[nodiscard]] const char* CStr() const noexcept;


        [[nodiscard]] size_t Size() const noexcept;

        [[nodiscard]] size_t Length() const noexcept;

        [[nodiscard]] size_t Capacity() const noexcept;

        [[nodiscard]] bool Empty() const noexcept;


        char& Front();

        [[nodiscard]] char Front() const;


        char& Back();

        [[nodiscard]] char Back() const;


        char& At(size_t index);

        [[nodiscard]] char At(size_t index) const;


        void Swap(String& other) noexcept;


        size_t Copy(char *str, size_t len, size_t pos = 0) const;


        void Clear() noexcept;

        void Resize(size_t new_size, char ch = ' ');

        void Reserve(size_t new_cap);

        void ShrinkToFit();

        void push_back(char ch);

        char pop_back();


        [[nodiscard]] size_t Find(const String& str, size_t pos = 0) const;

        [[nodiscard]] size_t Find(size_t pos, const String& str, size_t start, size_t n) const;

        [[nodiscard]] size_t Find(char ch, size_t pos = 0) const;


        [[nodiscard]] size_t RFind(const String& str, size_t pos = 0) const;

        [[nodiscard]]size_t RFind(size_t pos, const String& str, size_t start, size_t n) const;

        [[nodiscard]] size_t RFind(char ch, size_t pos = 0) const;


        String& Erase(size_t num, size_t pos = 0);


        String& Assign(const String& other);

        String& Assign(const std::initializer_list<char>& list);

        String& Assign(const String& other, size_t num, size_t pos = 0);

        String& Assign(char ch, size_t num);


        String& Append(const String& other);

        String& Append(char ch, size_t num);

        String& Append(const std::initializer_list<char>& list);

        String& Append(const String& other, size_t num, size_t pos = 0);


        String& Insert(size_t idx, size_t n, char ch);

        String& Insert(size_t idx, const String& other);

        String& Insert(size_t idx, const String& str, size_t pos, size_t count);

        String& Insert(size_t idx, const std::initializer_list<char>& list);


        String& Replace(size_t start, size_t num, const String& other);

        String& Replace(size_t start, size_t num, const String& other, size_t pos, size_t len);

        String& Replace(size_t start, size_t num, char ch, size_t len);

        String& Replace(size_t start, size_t num, const std::initializer_list<char>& list);


        [[nodiscard]] String SubStr(size_t pos, size_t num) const;


        String& operator=(const String& other);

        String& operator=(String&& other) noexcept;


        char& operator[](size_t index);

        char operator[](size_t index) const;


        String& operator+=(const String& other);

        String& operator+=(char ch);

        String& operator+=(const std::initializer_list<char>& list);


        [[nodiscard]] int Compare(const String& other) const noexcept;

        [[nodiscard]] int Compare(size_t pos, size_t len, const String& other) const;

        [[nodiscard]] int Compare(size_t pos, size_t len, const String& other, size_t sub_pos, size_t sub_len) const;


        friend std::istream& operator>>(std::istream& in, String& str);
    };
    

    std::ostream& operator<<(std::ostream& out, const String& str);


    bool operator==(const String& str1, const String& str2);

    bool operator!=(const String& str1, const String& str2);

    bool operator<(const String& str1, const String& str2);

    bool operator<=(const String& str1, const String& str2);

    bool operator>(const String& str1, const String& str2);

    bool operator>=(const String& str1, const String& str2);

} // MyFpmiString

#endif //FPMI_STRING_H
