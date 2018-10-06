#include <iostream>  // std::cout, std::cin
#include <sstream>   // read
#include "mystring.h"

int main() {
  MyString::listCollection(std::cout);

  {  // MyString constructor and value assignment operator test
    std::cout << "### Test case 1 start ###" << std::endl;
    MyString s1;
    MyString s2("teszt string2");
    MyString s3(s2);
    std::cout << "--- constructors" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "s3: " << s3 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s2 = s1;
    s1 = s3;
    s3 = "teszt string3";
    std::cout << "--- operator=" << std::endl
              << std::endl
              << "s3: " << s3 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s1 = s2 = s3 = "ertekeadasok sorozata";
    std::cout << "--- multiple operator=" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "s3: " << s3 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    MyString s4 = "valami string";
    MyString s5 = "valami string";
    std::cout << "--- same string" << std::endl
              << "s4: " << s4 << std::endl
              << "s5: " << s5 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    std::cout << "### Test case 1 end ###" << std::endl;
  }
  MyString::listCollection(std::cout);
  {  // Utilities (concat, size, write/read)
    MyString s1 = MyString("valami") + " masik valami";
    MyString s2 = s1 + MyString(" + meg tobb string");
    std::cout << "--- concat strings (+) " << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s1 += s2;
    s2 += " kene meg valamit hozzaadni";
    std::cout << "--- concat strings (+=)" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    std::cout << "--- string size" << std::endl
              << "s1 size: " << s1.size() << std::endl
              << "s2 size: " << s2.size() << std::endl
              << "---" << std::endl;
    std::stringstream ss("valami-stringstreambol ez mar nem fog belekerulni");
    ss >> s2 >> s1;
    std::cout << "--- read strings" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
  }
  {  // MyStringChar test with operator[]
    MyString s1 = "teszt egyezo szoveggel";
    MyString s2 = "teszt egyezo szoveggel";
    std::cout << "--- init strings" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s1[7] = 'c';
    std::cout << "--- change s1" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s1[7] = 'g';
    std::cout << "--- change s1 back" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    std::cout << "--- calling const operator[]" << std::endl
              << "s1[15]: " << s1[15] << std::endl
              << "s2[7]: " << s2[7] << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
  }
  MyString::listCollection(std::cout);

  return 0;
}