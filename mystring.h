#ifndef MYSTRING_H
#define MYSTRING_H 1

#include <cctype>     // isspace()
#include <cstring>    // strcmp, strlen ...
#include <iostream>   // std::cout, std::cin
#include <map>        // StringCollection
#include <stdexcept>  // std::out_of_range

class MyString {
 public:
  class MyStringChar;

 private:
  class MyStringObj {
    char* data;
    size_t maxsize, stored;

   public:
    size_t referred;
    MyStringObj();
    MyStringObj(const char*);
    MyStringObj(const MyStringObj&);
    constexpr MyStringObj(MyStringObj&&) = default;
    ~MyStringObj() noexcept;
    MyStringObj& operator=(const MyStringObj&);
    MyStringObj operator+(const char*) const;
    MyStringObj& operator+=(const char*);
    MyStringObj& operator+=(char);
    MyStringObj operator+(const MyStringObj&) const;
    MyStringObj& operator+=(const MyStringObj&);
    constexpr size_t size() const noexcept { return stored; };
    char* operator[](size_t);
    std::ostream& write(std::ostream&) const;
    std::istream& read(std::istream&);
    constexpr const char* getConstChar() const noexcept { return data; }
  };

  struct cStringLess {
    inline bool operator()(const char* str1, const char* str2) {
      return strcmp(str2, str1) > 0;
    }
  };

 private:
  static std::map<const char*, MyStringObj*, cStringLess> StringCollection;

 public:
  class constMyStringChar {
    const MyString* owner;
    size_t pointed;

   public:
    constexpr constMyStringChar(const MyString* ptr, size_t pointed) noexcept
        : owner{ptr}, pointed{pointed} {}
    constexpr constMyStringChar(const constMyStringChar& o) noexcept
        : owner{o.owner}, pointed{o.pointed} {}
    constexpr constMyStringChar(const MyStringChar& o) noexcept
        : owner{o.getOwner()}, pointed{o.getIndex()} {}
    constexpr constMyStringChar(constMyStringChar&&) noexcept = default;
    constexpr operator char() const noexcept {
      return owner->getValue(pointed);
    }
    constexpr const char* operator&() const noexcept {
      return (*(owner->str))[pointed];
    };
    constexpr const MyString* getOwner() const noexcept { return owner; }
    constexpr size_t getIndex() const noexcept { return pointed; }
  };
  class MyStringChar {
    MyString* owner;
    size_t pointed;

   public:
    constexpr MyStringChar(MyString* ptr, size_t pointed) noexcept
        : owner{ptr}, pointed{pointed} {}
    constexpr MyStringChar(const MyStringChar& o) noexcept
        : owner{o.owner}, pointed{o.pointed} {}
    constexpr MyStringChar(MyStringChar&&) noexcept = default;
    constexpr operator char() const noexcept {
      return owner->getValue(pointed);
    }
    MyStringChar& operator=(char);
    MyStringChar& operator=(const MyStringChar&);
    MyStringChar& operator=(const constMyStringChar& o) {
      owner = const_cast<MyString*>(o.getOwner());
      pointed = o.getIndex();
      return *this;
    }
    constexpr const char* operator&() const noexcept {
      return (*(owner->str))[pointed];
    };
    constexpr MyString* getOwner() const noexcept { return owner; }
    constexpr size_t getIndex() const noexcept { return pointed; }
  };

 private:
  MyStringObj* str;
  constexpr inline char getValue(size_t index) const noexcept {
    return *(*str)[index];
  }

 public:
  MyString();
  MyString(const char*);
  MyString(const MyString&);
  constexpr MyString(MyString&&) noexcept = default;
  ~MyString() noexcept;
  MyString& operator=(const char*);
  MyString& operator=(const MyString&);

 private:
  MyString(const MyStringObj&);
  MyString& operator=(const MyStringObj&);

 public:
  MyString operator+(const char*);
  MyString& operator+=(const char*);
  MyString operator+(const MyString&);
  MyString& operator+=(const MyString&);
  MyStringChar operator[](size_t) noexcept;
  const constMyStringChar operator[](size_t) const noexcept;
  constexpr size_t size() const { return str->size(); }
  void write(std::ostream&) const;
  void read(std::istream&);

  static void listCollection(std::ostream&);
};

std::ostream& operator<<(std::ostream&, const MyString&);
std::istream& operator>>(std::istream&, MyString&);

#endif
