#include <iostream>  // std::cout, std::cin
#include "mystring.h"

int main() {
  MyString::listCollection(std::cout);

  {  // MyString constructor and value assignment operator test
    std::cout << "### Test case 1 start ###" << std::endl;
    MyString s1;
    MyString s2("teszt string2");
    MyString s3(s2);
    std::cout << "--- constructors" << std::endl
              << s1 << std::endl
              << s2 << std::endl
              << s3 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s2 = s1;
    s1 = s3;
    s3 = "teszt string3";
    std::cout << "--- operator=" << std::endl
              << std::endl
              << s3 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s1 = s2 = s3 = "ertekeadasok sorozata";
    std::cout << "--- multiple operator=" << std::endl
              << s1 << std::endl
              << s2 << std::endl
              << s3 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    std::cout << "### Test case 1 end ###" << std::endl;
  }
  MyString::listCollection(std::cout);

  return 0;
}