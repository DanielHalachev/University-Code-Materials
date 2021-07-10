
#include <stdexcept>
#include <sstream>
#include "Document.hpp"

Document::Document(const std::string &name, const std::string &location, const std::string &extension)
        : Object(name, location, extension), currentLine(0) {
}

void Document::write_line(const std::string &line) {
    this->lines.push_back(line);
}

std::string Document::read_line() {
    // if the last line that has been read is equal or bigger than the size
    // then abort
    if (currentLine >= this->lines.size()) {
        throw std::out_of_range("End of file reached");
    }
    // go to the next line that hasn't been read and mark it as read
    this->currentLine++;
    // get the line
    return this->lines[this->currentLine - 1];
}

std::string Document::read_line(const unsigned int &line) {
    // if the last line that has been read is bigger than the size
    // then abort
    // equals is allowed because we don't increase the currentLine variable
    if (line > this->lines.size() || line == 0) {
        throw std::out_of_range("End of file reached");
    }
    // set the "cursor" to this line
    this->currentLine = line;
    // get the line
    return this->lines[this->currentLine - 1];
}

bool Document::operator==(const Comparable *other) const {
    // can't compare with non-existent objects
    if (other == nullptr) {
        return false;
    }
    // transform into a document in order to access the lines vector
    auto document = dynamic_cast<Document *>(const_cast<Comparable *>(other));
    // if the sizes don't match, it's already a mismatch
    if (this->lines.size() != document->lines.size()) {
        return false;
    }
    // in case the sizes are the same, compare line by line
    for (unsigned int i = 0; i < this->lines.size(); i++) {
        if (this->lines[i] != document->lines[i]) {
            // in case a mismatch has been found, that's not what we want
            return false;
        }
    }
    // if no collisions are found, this means that everything's the same
    return true;
}

bool Document::operator!=(const Comparable *other) const {
    // this code doesn't call operator== in order to save resources
    // can't compare with non-existent objects
    if (other == nullptr) {
        return false;
    }
    // transform into a document in order to access the lines vector
    auto document = dynamic_cast<Document *>(const_cast<Comparable *>(other));
    // if the sizes don't match, it's already a mismatch--> that's what we want
    if (this->lines.size() != document->lines.size()) {
        return true;
    }
    // in case the sizes are the same, compare line by line
    for (unsigned int i = 0; i < this->lines.size(); i++) {
        // in case a mismatch has been found, that's what we want
        if (this->lines[i] != document->lines[i]) {
            return true;
        }
    }
    // if no collisions are found, that's not what we want
    return false;
}

std::string Document::debug_print() const {
    std::string content;
    for (unsigned int i = 0; i < this->lines.size(); i++) {
        // Line <line number>:<content>
        content += "Line " + std::to_string(i + 1) + ":" + this->lines[i] + "\n";
    }
    return content;
}

std::string Document::to_string() const {
    std::string content;
    content += this->name + "\n";
    content += this->location + "\n";
    content += this->extension + "\n";
    // append every line to the string and add a new line symbol
    for (const auto &line : this->lines) {
        content += line + "\n";
    }
    return content;
}

void Document::from_string(const std::string &myString) {
    this->lines.clear();
    std::istringstream f(myString);
    std::string line;
    // get the file information
    getline(f, this->name);
    getline(f, this->location);
    getline(f, this->extension);
    // get each line
    while (std::getline(f, line)) {
        this->lines.push_back(line);
    }
}

Object *Document::clone() const {
    return new Document(*this);
}

