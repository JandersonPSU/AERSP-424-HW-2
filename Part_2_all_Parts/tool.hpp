#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <string>

class tool {
private:
    std::string name;

public:
    // Constructor
    tool();

    // Destructor
    ~tool();

    // Setter
    void setName(const std::string& new_name);

    // Getter
    std::string getName() const;
};

#endif // TOOL_H
