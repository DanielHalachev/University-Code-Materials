
#ifndef HW4_DOCUMENT_HPP
#define HW4_DOCUMENT_HPP


#include <vector>
#include "Object.hpp"

class Document : public Object {
public:
    Document(const std::string &name, const std::string &location, const std::string &extension);

    void write_line(const std::string &line);

    std::string read_line();

    std::string read_line(const unsigned int &line);

    // inherited virtual functions
    Object *clone() const override;

    bool operator==(const Comparable *other) const override;

    bool operator!=(const Comparable *other) const override;

    std::string debug_print() const override;

    std::string to_string() const override;

    void from_string(const std::string &myString) override;

private:
    // stores each individual line of the document as a string
    std::vector<std::string> lines;
    // stores the index of the last line that has been read, 0 at the start
    unsigned int currentLine;
};


#endif //HW4_DOCUMENT_HPP
