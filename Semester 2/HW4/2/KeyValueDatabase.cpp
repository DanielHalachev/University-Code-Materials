
#include <stdexcept>
#include <sstream>
#include "KeyValueDatabase.hpp"

KeyValueDatabase::KeyValueDatabase(const std::string &name, const std::string &location, const std::string &extension)
        : Object(name, location, extension) {
}

void KeyValueDatabase::add_entry(const std::pair<std::string, int> &entry) {
    // compare the entry key with all other existing keys
    for (const auto &pair:this->map) {
        // if there's a match, abort
        if (entry.first == pair.first) {
            throw std::invalid_argument("Key already exists");
        }
    }
    // if the key isn't there, add the pair
    this->map.push_back(entry);
}

int KeyValueDatabase::get_value(const std::string &key) const {
    // search for the key in the vector
    for (const auto &pair:this->map) {
        if (key == pair.first) {
            return pair.second;
        }
    }
    // if a match isn't found, return error
    throw std::invalid_argument("Key not found");
}

bool KeyValueDatabase::operator==(const Comparable *other) const {
    // can't compare to non-existent objects
    if (other == nullptr) {
        return false;
    }
    // convert the pointer to KeyValueDatabase to gain access to vector
    auto database = dynamic_cast<KeyValueDatabase *>(const_cast<Comparable *>(other));
    // if the sizes don't match, it's already a mismatch
    if (this->map.size() != database->map.size()) {
        return false;
    }
    // in case the sizes match, compare every pair
    for (unsigned int i = 0; i < this->map.size(); i++) {
        // if a mismatch is found, that's not what we want
        if (this->map[i] != database->map[i]) {
            return false;
        }
    }
    // in case a mismatch hasn't been found, the objects are identical
    return true;
}

bool KeyValueDatabase::operator!=(const Comparable *other) const {
    // this code doesn't call operator== in order to save resources
    // can't compare to non-existent objects
    if (other == nullptr) {
        return false;
    }
    // convert the pointer to KeyValueDatabase to gain access to vector
    auto database = dynamic_cast<KeyValueDatabase *>(const_cast<Comparable *>(other));
    // if the sizes don't match, that's what we want
    if (this->map.size() != database->map.size()) {
        return true;
    }
    // in case the sizes match, compare every pair
    for (unsigned int i = 0; i < this->map.size(); i++) {
        // if a mismatch is found, that's not what we want
        if (this->map[i] != database->map[i]) {
            return true;
        }
    }
    // in case a mismatch hasn't been found, that's not what we want
    return false;
}

std::string KeyValueDatabase::debug_print() const {
    std::string content;
    for (const auto &pair:this->map) {
        // {<first>:<second>}
        content += "{" + pair.first + ":" + std::to_string(pair.second) + "}\n";
    }
    return content;
}

std::string KeyValueDatabase::to_string() const {
    std::string content;
    content += this->name + "\n";
    content += this->location + "\n";
    content += this->extension + "\n";
    for (const auto &pair:this->map) {
        // <first>:<second> + "\n"
        content += pair.first + ":" + std::to_string(pair.second) + "\n";
    }
    return content;
}

void KeyValueDatabase::from_string(const std::string &dataString) {
    // remove previous information
    this->map.clear();
    // get the file data
    std::istringstream f(dataString);
    std::string line;
    getline(f, this->name);
    getline(f, this->location);
    getline(f, this->extension);
    // extract every pair
    while (std::getline(f, line)) {
        auto position = line.find(':');
        this->map.emplace_back(line.substr(0, position), std::stoi(line.substr(position + 1)));
    }
}

Object *KeyValueDatabase::clone() const {
    return new KeyValueDatabase(*this);
}
