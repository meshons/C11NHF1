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
    ~MyStringObj() noexcept;
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

 private:
  static std::map<const char*, MyStringObj*, cStringLess> StringCollection;

 public:
  class constMyStringChar {
    const MyString* owner;
    size_t pointed;

   public:
    constMyStringChar(const MyString* ptr, size_t pointed)
        : owner{ptr}, pointed{pointed} {}
    constMyStringChar(const constMyStringChar& o)
        : owner{o.owner}, pointed{o.pointed} {}
    constMyStringChar(const MyStringChar& o)
        : owner{o.getOwner()}, pointed{o.getIndex()} {}
    operator char() const { return owner->getValue(pointed); }
    const char* operator&() const { return (*(owner->str))[pointed]; };
    const MyString* getOwner() const { return owner; }
    size_t getIndex() const { return pointed; }
  };
  class MyStringChar {
    MyString* owner;
    size_t pointed;

   public:
    MyStringChar(MyString* ptr, size_t pointed)
        : owner{ptr}, pointed{pointed} {}
    MyStringChar(const MyStringChar& o) : owner{o.owner}, pointed{o.pointed} {}
    explicit MyStringChar(const constMyStringChar& o) : pointed{o.getIndex()} {
      owner = const_cast<MyString*>(o.getOwner());
    }
    operator char() const { return owner->getValue(pointed); }
    MyStringChar& operator=(char);
    MyStringChar& operator=(const MyStringChar&);
    MyStringChar& operator=(const constMyStringChar& o) {
      owner = const_cast<MyString*>(o.getOwner());
      pointed = o.getIndex();
      return *this;
    }
    const char* operator&() const { return (*(owner->str))[pointed]; };
    MyString* getOwner() const { return owner; }
    size_t getIndex() const { return pointed; }
  };

 private:
  MyStringObj* str;
  inline char getValue(size_t index) const { return *(*str)[index]; }

 public:
  MyString();
  MyString(const char*);
  MyString(const MyString&);
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
  MyStringChar operator[](size_t);
  const constMyStringChar operator[](size_t) const;
  size_t size() const { return str->size(); }
  void write(std::ostream&) const;
  void read(std::istream&);

  static void listCollection(std::ostream&);
};

std::ostream& operator<<(std::ostream&, const MyString&);
std::istream& operator>>(std::istream&, MyString&);

#endif
