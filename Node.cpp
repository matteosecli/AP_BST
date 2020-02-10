#include "Node.hpp"


//template <typename T>
//Node<T>::Node(T& data,
//              std::unique_ptr<Node<T>> left,
//              std::unique_ptr<Node<T>> right,
//              Node<T>* parent) :
//    data{data},
//    left{left},
//    right{right},
//    parent{parent} {}

template <typename T>
Node<T>::Node(T& data) :
    data{data} {}
