#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include "vector.hpp"

int main(void) {
  // {
  //   std::ifstream source("Makefile", std::ios::binary);
  //   ft::vector<char> v((std::istreambuf_iterator<char>(source)),
  //                      std::istreambuf_iterator<char>());
  //   for (ft::vector<char>::iterator itr = v.begin(); itr != v.end(); itr++)
  //     std::cout << *itr << "\n";
  // }
  // {
  //   ft::vector<char> v;
  //   std::ifstream source("Makefile", std::ios::binary);
  //   v.assign(std::istreambuf_iterator<char>(source),
  //            std::istreambuf_iterator<char>());
  //   for (ft::vector<char>::iterator itr = v.begin(); itr != v.end(); itr++)
  //     std::cout << *itr << "\n";
  // }
  ft::vector<int> v;
  for (int i = 0; i < 100000; ++i) {
    // std::cout << i << ", ";
    // if (i % 50000 == 0) std::cout << "\n";
    v.push_back(i);
  }
}
