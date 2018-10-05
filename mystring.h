#ifndef MYSTRING_H
#define MYSTRING_H 1

#include <cctype>
#include <cstring>
#include <iostream>
#include <map>

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
    ~MyStringObj();
    MyStringObj& operator=(const char*);
    MyStringObj& operator=(const MyStringObj&);
    MyStringObj operator+(const char*) const;
    MyStringObj& operator+=(const char*);
    MyStringObj& operator+=(char);
    MyStringObj operator+(const MyStringObj&) const;
    MyStringObj& operator+=(const MyStringObj&);
    constexpr size_t size() const { return stored; };
    char* operator[](size_t);
    const char* operator[](size_t) const;
    std::ostream& write(std::ostream&) const;
    std::istream& read(std::istream&);
    const char* getConstChar() const { return data; }
  };

  struct cStringLess {
    inline bool operator()(const char* str1, const char* str2) {
      return strcmp(str2, str1) > 0;
    }
  };

 public:
  static std::map<const char*, MyStringObj*, cStringLess> StringCollection;

 public:
  class MyStringChar {
    MyString* owner;
    size_t pointed;

   public:
    MyStringChar(MyString* ptr, size_t pointed)
        : owner{ptr}, pointed{pointed} {}
    MyStringChar(const MyStringChar& o) : owner{o.owner}, pointed{o.pointed} {}
    operator char() { return owner->getValue(pointed); }
    MyStringChar& operator=(char);
    MyStringChar& operator=(const MyStringChar&);
  };

 private:
  MyStringObj* str;
  char getValue(size_t index) { return *(*str)[index]; }

 public:
  MyString();
  MyString(const char*);
  MyString(const MyString&);
  MyString& operator=(const char*);
  MyString& operator=(const MyString&);
  MyString operator+(const char*);
  MyString& operator+=(const char*);
  MyString operator+(const MyString&);
  MyString& operator+=(const MyString&);
  MyStringChar operator[](size_t);
  const MyStringChar operator[](size_t) const;
  size_t size() const { return str->size(); }
};

std::ostream& operator<<(std::ostream&, const MyString&);
std::istream& operator>>(std::istream&, MyString&);

#endif
