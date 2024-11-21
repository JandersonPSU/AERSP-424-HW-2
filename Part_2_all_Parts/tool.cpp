#include "tool.hpp"

// Constructor
tool::tool() {
    std::cout << "Tool Created" << std::endl;
}

// Destructor
tool::~tool() {}

// Setter
void tool::setName(const std::string& new_name) {
    name = new_name;
}

// Getter
std::string tool::getName() const {
    return name;
}
