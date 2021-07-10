
#ifndef HW4_OBJECT_HPP
#define HW4_OBJECT_HPP


#include "Comparable.hpp"
#include "Debug.hpp"
#include "Serializable.hpp"

class Object : public Comparable, public Debug, public Serializable {
public:
    Object(const std::string &name = "", const std::string &location = "", const std::string &extension = "");

    std::string get_name() const;

    std::string get_location() const;

    std::string get_extension() const;

    std::string get_fullpath() const;

    virtual Object *clone() const = 0;

    // inherited virtual functions
    bool operator==(const Comparable *other) const override = 0;

    bool operator!=(const Comparable *other) const override = 0;

    std::string debug_print() const override = 0;

    std::string to_string() const override = 0;

    void from_string(const std::string &myString) override = 0;

    ~Object() override = default;

protected:
    std::string name;
    std::string location;
    std::string extension;

};


#endif //HW4_OBJECT_HPP
