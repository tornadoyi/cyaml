#include <iostream>
#include "cyaml/cyaml.h"

std::string yaml_str = R"(
jason:
  sex: male
  age: 18
  weight: 150.3
  married: true
  hobbies:
    - swim
    - game

lesarel:
  sex: female
  age: 16
  weight: 90.26
  hobbies:
    - book
    - travel
)";

int main() {

  cyaml::Document doc;
  auto r = doc.parse(yaml_str);
  if(!r.success) {
    std::cerr << "failed to parse yaml" << std::endl;
  }

  const auto& root = doc.root();
  for(auto it = root.begin(); it != root.end(); ++it) {
    std::cout << it->first << std::endl;
    const auto& human = *it->second;
    std::cout << " sex: " << human["sex"].as<std::string>() << std::endl;
    std::cout << " age: " << human["age"].as<int>() << std::endl;
    std::cout << " weight: " << human["weight"].as<double>() << std::endl;
    std::cout << " married: " << (int)human["married"].as<bool>(false) << std::endl;
    std::cout << " hobbies: " << std::endl;
    for(auto it2 = human["hobbies"].begin(); it2 != human["hobbies"].end(); ++it2) {
      std::cout << "  - " << (*it2).as<std::string>() << std::endl;
    }
    
  }
  return 0;
}