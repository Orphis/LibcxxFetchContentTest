#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::string str = "Hello, World!";

  // Using std::find from the C++ standard library
  auto it = std::find(vec.begin(), vec.end(), 3);
  if (it != vec.end()) {
    std::cout << "Found: " << *it << std::endl;
  } else {
    std::cout << "Not found" << std::endl;
  }

  // Using std::reverse from the C++ standard library
  std::reverse(str.begin(), str.end());
  std::cout << "Reversed string: " << str << std::endl;

  try {
    throw std::runtime_error("An error occurred");
  } catch (const std::runtime_error &e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
  }

  return 0;
}