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
  stored = strlen(str);
  if (stored + 1 < maxsize)
    strcpy(data, str);
  else {
    maxsize = stored * 1.5 + 1;
    delete[] data;
    data = new char[maxsize];
    strcpy(data, str);
  }
  data[stored] = 0;
  return *this;
}
MyString::MyStringObj& MyString::MyStringObj::operator=(
    const MyString::MyStringObj& o) {
  if (this != &o) {
    stored = o.stored;
    if (stored + 1 < maxsize)
      strcpy(data, o.data);
    else {
      maxsize = stored * 1.5 + 1;
      delete[] data;
      data = new char[maxsize];
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

char* MyString::MyStringObj::operator[](size_t index) { return &data[index]; }

const char* MyString::MyStringObj::operator[](size_t index) const {
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
  if (iter == StringCollection.end()) {
    str = iter->second;
    ++(iter->second->referred);
  } else {
    str = new MyStringObj;
    StringCollection.insert(std::map<const char*, MyStringObj*>::value_type(
        str->getConstChar(), str));
  }
}

MyString::MyString(const char* str) {
  auto iter = StringCollection.find("");
  if (iter == StringCollection.end()) {
    this->str = iter->second;
    ++(iter->second->referred);
  } else {
    this->str = new MyStringObj(str);
    StringCollection.insert(std::map<const char*, MyStringObj*>::value_type(
        this->str->getConstChar(), this->str));
  }
}

MyString::MyString(const MyString& o) : str{o.str} { ++(str->referred); }

MyString& MyString::operator=(const char* str) {
  MyStringObj* tmp;

  auto iter = StringCollection.find(str);
  if (iter == StringCollection.end()) {
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
  return *this;
}

MyString& MyString::operator=(const MyString& o) {
  if (this->str->referred == 1) {
    StringCollection.erase(StringCollection.find(this->str->getConstChar()));
  } else
    --(this->str->referred);

  this->str = o.str;
  ++(this->str->referred);
  return *this;
}