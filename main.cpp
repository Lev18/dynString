#include "dynStr.h"

#include <iostream> 


int main () {
  MyString str;
  MyString str2("helkkkkkkkkkkkkkkkkklkkko");
  MyString str3(std::string("heljjjjjjjjjjjjjjjjldooooo"));
  std::cout << str3 << std::endl;
  str += "helldddddddddddddddddddddeee";
  std::cout << str <<std::endl;
  str += str2;
  std::cout << str << std::endl;
  str += 'a';
  std::cout << str << std::endl;
  std::cin >> str2; 
  std::cout << str2 << std::endl;

  return 0;
}