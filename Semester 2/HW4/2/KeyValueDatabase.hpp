
#ifndef HW4_KEYVALUEDATABASE_HPP
#define HW4_KEYVALUEDATABASE_HPP

#include <vector>
#include "Object.hpp"

class KeyValueDatabase : public Object {
public:
    KeyValueDatabase(const std::string &name, const std::string &location, const std::string &extension);

    void add_entry(const std::pair<std::string, int> &entry);

    int get_value(const std::string &key) const;

    // inherited virtual functions
    Object *clone() const override;

    bool operator==(const Comparable *other) const override;

    bool operator!=(const Comparable *other) const override;

    std::string debug_print() const override;

    std::string to_string() const override;

    void from_string(const std::string &dataString) override;

private:
    std::vector<std::pair<std::string, int>> map;
};


#endif //HW4_KEYVALUEDATABASE_HPP
