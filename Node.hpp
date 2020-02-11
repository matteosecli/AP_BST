#ifndef NODE_HPP
#define NODE_HPP

#include <utility>  /* For std::pair */
#include <memory>   /* For std::unique_ptr */


/** 
 * @brief Another namespace
 * 
 * Namespace to hide Node and Iterator from the user
 */
namespace APutils {

    // Chiedere: l'utente può vedere Node? Sennò la mettiamo nel BST.
    template <typename T>   // T must be an std::pair
    struct Node {
        T data;             // Contains an std::pair<const Key,Val>
        std::unique_ptr<Node<T>> left;
        std::unique_ptr<Node<T>> right;
        Node<T>* parent;       // To navigate the tree (???)
        Node() :
            data{},
            left{nullptr},
            right{nullptr},
            parent{nullptr} {}
        Node(T& data,
             std::unique_ptr<Node<T>>& left,
             std::unique_ptr<Node<T>>& right,
             Node<T>* parent) :
                data{data},
                left{left},
                right{right},
                parent{parent} {}
        Node(T& data, Node<T>* parent) :
            data{data},
            left{nullptr},
            right{nullptr},
            parent{parent} {}
        void printNode() {
            std::cout << "[" << this << "]    ";
            std::cout << "Key: " << data.first << ", Value: " << data.second << std::endl;
            if (left) {
                //std::cout << "[" << left << "]    ";
                std::cout << "    Left  -> ";
                left->printNode();
            }
            if (right) {
                //std::cout << "[" << right << "]    ";
                std::cout << "    Right -> ";
                right->printNode();
            }
        }
    };

}


#endif // NODE_HPP
