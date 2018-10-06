#include "mystring.h"

std::map<const char*, MyString::MyStringObj*, MyString::cStringLess>
    MyString::StringCollection;

inline MyString::MyStringObj::MyStringObj()
    : maxsize{10}, stored{0}, referred{1} {
  data = new char[maxsize];
}
inline MyString::MyStringObj::MyStringObj(const char* str) : referred{1} {
  stored = strlen(str);
  maxsize = stored * 1.5 + 1;
  data = new char[maxsize];
  strcpy(data, str);
  data[stored] = 0;
}
inline MyString::MyStringObj::MyStringObj(const MyString::MyStringObj& o)
    : maxsize{o.maxsize}, stored{o.stored}, referred{1} {
  data = new char[maxsize];
  strcpy(data, o.data);
  data[stored] = 0;
}
inline MyString::MyStringObj::~MyStringObj() { delete[] data; }
MyString::MyStringObj& MyString::MyStringObj::operator=(const char* str) {
  size_t newsize = strlen(str);
  if (newsize + 1 < maxsize) {
    if (newsize * 4 + 1 < maxsize) {
      char* tmp = new char[maxsize / 2];
      maxsize /= 2;
      delete[] data;
      data = tmp;
    }
    strcpy(data, str);
    stored = newsize;
  } else {
    size_t newmaxsize = newsize * 1.5 + 1;
    char* tmp = new char[newmaxsize];
    delete[] data;
    data = tmp;
    maxsize = newmaxsize;
    stored = newsize;
    strcpy(data, str);
  }
  data[stored] = 0;
  return *this;
}
MyString::MyStringObj& MyString::MyStringObj::operator=(
    const MyString::MyStringObj& o) {
  if (this != &o) {
    size_t newsize = o.stored;
    if (newsize + 1 < maxsize) {
      if (newsize * 4 + 1 < maxsize) {
        char* tmp = new char[maxsize / 2];
        maxsize /= 2;
        delete[] data;
        data = tmp;
      }
      strcpy(data, o.data);
      stored = newsize;
    } else {
      size_t newmaxsize = newsize * 1.5 + 1;
      char* tmp = new char[newmaxsize];
      delete[] data;
      data = tmp;
      maxsize = newmaxsize;
      stored = newsize;
      strcpy(data, o.data);
    }
  }
  data[stored] = 0;
  return *this;
}
MyString::MyStringObj& MyString::MyStringObj::operator+=(
    const MyString::MyStringObj& o) {
  if (stored + o.stored + 1 < maxsize)
    strcpy(data + stored, o.data);
  else {
    maxsize = (stored + o.stored) * 1.5 + 1;
    char* newdata = new char[maxsize];
    strcpy(newdata, data);
    strcpy(newdata + stored, o.data);
    delete[] data;
    data = newdata;
  }
  stored += o.stored;
  data[stored] = 0;
  return *this;
}
MyString::MyStringObj MyString::MyStringObj::operator+(
    const MyString::MyStringObj& o) const {
  return MyStringObj(*this) += o;
}
MyString::MyStringObj& MyString::MyStringObj::operator+=(const char* str) {
  size_t len = strlen(str);
  if (stored + len + 1 < maxsize)
    strcpy(data + stored, str);
  else {
    maxsize = (stored + len) * 1.5 + 1;
    char* newdata = new char[maxsize];
    strcpy(newdata, data);
    strcpy(newdata + stored, str);
    delete[] data;
    data = newdata;
  }
  stored += len;
  data[stored] = 0;
  return *this;
}
MyString::MyStringObj& MyString::MyStringObj::operator+=(char c) {
  if (stored + 2 < maxsize)
    data[stored] = c;
  else {
    maxsize = (stored + 1) * 1.5 + 1;
    char* newdata = new char[maxsize];
    strcpy(newdata, data);
    newdata[stored] = c;
    delete[] data;
    data = newdata;
  }
  data[++stored] = 0;
  return *this;
}
MyString::MyStringObj MyString::MyStringObj::operator+(const char* str) const {
  return MyStringObj(*this) += str;
}

char* MyString::MyStringObj::operator[](size_t index) {
  if (index >= stored)
    throw std::out_of_range("Requested char* at index is out of range.");
  return &data[index];
}

const char* MyString::MyStringObj::operator[](size_t index) const {
  if (index >= stored)
    throw std::out_of_range("Requested char* at index is out of range.");
  return &data[index];
}

std::ostream& MyString::MyStringObj::write(std::ostream& os) const {
  os << data;
  return os;
}
std::istream& MyString::MyStringObj::read(std::istream& is) {
  *this = MyStringObj();
  int x = is.get();
  while (!isspace(x) && x != EOF) {
    *this += static_cast<char>(x);
    x = is.get();
  }
  is.putback(x);
  return is;
}

MyString::MyString() {
  auto iter = StringCollection.find("");
  if (iter != StringCollection.end()) {
    str = iter->second;
    ++(iter->second->referred);
  } else {
    str = new MyStringObj;
    StringCollection.insert(std::map<const char*, MyStringObj*>::value_type(
        str->getConstChar(), str));
  }
}

MyString::MyString(const char* str) {
  auto iter = StringCollection.find(str);
  if (iter != StringCollection.end()) {
    this->str = iter->second;
    ++(iter->second->referred);
  } else {
    this->str = new MyStringObj(str);
    StringCollection.insert(std::map<const char*, MyStringObj*>::value_type(
        this->str->getConstChar(), this->str));
  }
}

MyString::MyString(const MyString& o) : str{o.str} { ++(str->referred); }
MyString::MyString(const MyStringObj& o) {
  auto iter = StringCollection.find(o.getConstChar());
  if (iter != StringCollection.end()) {
    str = iter->second;
    ++(iter->second->referred);
  } else {
    str = new MyStringObj(o);
    StringCollection.insert(std::map<const char*, MyStringObj*>::value_type(
        str->getConstChar(), str));
  }
}

MyString& MyString::operator=(const char* str) {
  if (strcmp(str, this->str->getConstChar()) != 0) {
    MyStringObj* tmp;

    auto iter = StringCollection.find(str);
    if (iter != StringCollection.end()) {
      tmp = iter->second;
      ++(iter->second->referred);
    } else {
      tmp = new MyStringObj(str);
      StringCollection.insert(std::map<const char*, MyStringObj*>::value_type(
          tmp->getConstChar(), tmp));
    }

    if (this->str->referred == 1) {
      StringCollection.erase(StringCollection.find(this->str->getConstChar()));
    } else
      --(this->str->referred);

    this->str = tmp;
  }
  return *this;
}

MyString& MyString::operator=(const MyString& o) {
  if (this != &o && str != o.str) {
    if (this->str->referred == 1) {
      StringCollection.erase(StringCollection.find(this->str->getConstChar()));
    } else
      --(this->str->referred);

    this->str = o.str;
    ++(this->str->referred);
  }
  return *this;
}

MyString& MyString::operator=(const MyStringObj& o) {
  if (strcmp(str->getConstChar(), o.getConstChar()) != 0) {
    MyStringObj* tmp;
    auto iter = StringCollection.find(o.getConstChar());
    if (iter != StringCollection.end()) {
      tmp = iter->second;
      ++(iter->second->referred);
    } else {
      tmp = new MyStringObj(o);
      StringCollection.insert(std::map<const char*, MyStringObj*>::value_type(
          tmp->getConstChar(), tmp));
    }
    if (this->str->referred == 1) {
      StringCollection.erase(StringCollection.find(this->str->getConstChar()));
    } else
      --(this->str->referred);

    this->str = tmp;
  }
  return *this;
}

MyString MyString::operator+(const char* str) {
  return MyString(*(this->str) + str);
}
MyString& MyString::operator+=(const char* str) {
  *this = *(this->str) + str;
  return *this;
}

MyString MyString::operator+(const MyString& o) {
  return MyString(*(this->str) + *(o.str));
}
MyString& MyString::operator+=(const MyString& o) {
  *this = *(this->str) + *(o.str);
  return *this;
}

MyString::MyStringChar MyString::operator[](size_t index) {
  return MyString::MyStringChar(this, index);
}
const MyString::constMyStringChar MyString::operator[](size_t index) const {
  return MyString::constMyStringChar(this, index);
}

inline void MyString::write(std::ostream& os) const { str->write(os); }
inline void MyString::read(std::istream& is) {
  MyStringObj tmp;
  tmp.read(is);
  *this = tmp;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
  str.write(os);
  return os;
}
std::istream& operator<<(std::istream& is, MyString& str) {
  str.read(is);
  return is;
}

MyString::MyStringChar& MyString::MyStringChar::operator=(char c) {
  if (c != char(*this)) {
    MyStringObj tmp(*(owner->str));
    *(tmp[pointed]) = c;
    *(this->owner) = tmp;
  }
  return *this;
}
MyString::MyStringChar& MyString::MyStringChar::operator=(
    const MyString::MyStringChar& o) {
  *this = char(o);
  return *this;
}
