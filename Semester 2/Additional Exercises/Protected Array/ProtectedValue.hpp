//
// Created by User on 4.6.2021 г..
//

#ifndef EXERCISES_PROTECTEDVALUE_HPP
#define EXERCISES_PROTECTEDVALUE_HPP

template<class T>
class ProtectedValue {
public:
    ProtectedValue(const T &value, const unsigned int &code);

    T getValue(const unsigned int &userCode) const;

private:
    T value;
    unsigned int code;
};

template<class T>
ProtectedValue<T>::ProtectedValue(const T &value, const unsigned int &code)
        : value(value), code(code) {
}

template<class T>
T ProtectedValue<T>::getValue(const unsigned int &userCode) const {
    if(userCode==this->code){
        return this->value;
    }
    return T();
}


#endif //EXERCISES_PROTECTEDVALUE_HPP
