#include <iostream>  // std::cout, std::cin
#include "mystring.h"

int main() {
  {  // MyString constructor test
    std::cout << "### Test case 1 start ###" << std::endl;
    MyString s1;
    MyString s2("teszt string2");
    MyString s3(s2);
    std::cout << s1 << s2 << std::endl << s3 << std::endl;
    std::cout << "### Test case 1 end ###" << std::endl;
  }

  return 0;
}