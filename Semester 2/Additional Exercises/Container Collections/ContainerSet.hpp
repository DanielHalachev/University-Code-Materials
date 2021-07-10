//
// Created by User on 8.6.2021 г..
//

#ifndef EXERCISES_CONTAINERSET_HPP
#define EXERCISES_CONTAINERSET_HPP

#include "Container.hpp"

template<class T>
class ContainerSet : public Container<T> {
    ContainerSet() = default;

    bool add(const T &object) override;
};

template<class T>
bool ContainerSet<T>::add(const T &object) {
    if (this->member(object)) {
        return false;
    }
    Container<T>::add(object);
}


#endif //EXERCISES_CONTAINERSET_HPP
