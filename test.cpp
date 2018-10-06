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
  {  // Utilities (concat, size, write/read), operator[]
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
    std::cout << "--- change s1 (s1[7] = 'c')" << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s1[7] = 'g';
    MyString::MyStringChar c0(s1[7]);
    std::cout << "--- change s1 back (s1[7] = 'g'" << std::endl
              << "c0(s1[7]): " << c0 << std::endl
              << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    std::cout << "--- calling char() on operator[]" << std::endl
              << "s1[15]: " << s1[15] << std::endl
              << "s2[7]: " << s2[7] << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    std::cout << "--- calling operator& on operator[]" << std::endl
              << "&s1[13]: " << &s1[13] << std::endl
              << "---" << std::endl;
    const MyString s3("valami const");
    std::cout << "--- calling char() on const operator[]" << std::endl
              << "s3[7]: " << s3[7] << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    s1[13] = s3[7];
    std::cout << "--- s1[13]=s3[7]" << std::endl
              << "s1: " << s1 << std::endl
              << "---" << std::endl;
    MyString::listCollection(std::cout);
    MyString::MyStringChar c3(s1[13]);      // move const
    MyString::constMyStringChar c4(s3[3]);  // move const
    MyString::MyStringChar c1(c3);          // copy const
    MyString::constMyStringChar c5(c3);     // copy const
    MyString::constMyStringChar c2(c4);     // copy const
    std::cout << "--- (normal) s1[13] copy ctr" << std::endl
              << "c1: " << c1 << std::endl
              << "c1: " << &c1 << std::endl
              << "--- (const) s3[5] copy ctr" << std::endl
              << "c2: " << c2 << std::endl
              << "c2: " << &c2 << std::endl
              << "---" << std::endl;
    try {
      MyString s1("valami");
      MyString s2, s4;
      MyString s3("val");
      s3 = s3 + "ami";
      s2 = "valami";
      s1[4] = s1[3];
      MyString s5("igen");
      s5 = s5 + "i";
      MyString s6("igen");
      s6 = s6 + MyString("I");
      s6 = MyString("hosszu a nagy coverage miatt");
      s1 = "nagyon hosszu string hogy nagyobb legyen a coverage :D";
      MyString::listCollection(std::cout);
      s1[1500] = 'C';
    } catch (std::out_of_range& e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }
  MyString::listCollection(std::cout);

  return 0;
}