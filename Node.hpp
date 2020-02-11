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

    /** @brief Class that implements a node of a tree.
     *
     *  General class that can be used in any tree, for example it could be used in the class bt that implements a 
     *  Binary Tree (our class `bst` should in fact inherit from bt).
     */
    template <typename T>   // T must be an std::pair
    struct Node {
        /** @brief Data stored in this `Node`.
         *
         *  Contains an std::pair<const Key,Val>, where Key is the key of this Node and Val is the value stored in this Node.
         */
        T data;
        /** @brief Left child of this Node. */
        std::unique_ptr<Node<T>> left;
        /** @brief Right child of this Node. */
        std::unique_ptr<Node<T>> right;
        /** @brief Parent of this Node. */
        Node<T>* parent;

        /** @brief Void constructor.
         *  
         *  Used only to create a void root when an object `bst` is instantiated.
         */
        Node() :
            data{},
            left{nullptr},
            right{nullptr},
            parent{nullptr} {}

        /** @brief Data constructor.
         *  @param data the values to be store in the `Node`.
         *  @param parent the `Node` parent of this `Node`.
         *  
         *  To create a `Node` with given `data` and `parent`, and `left` and `right` initializated to `nullptr`.
         */
        Node(T& data, Node<T>* parent) :
            data{data},
            left{nullptr},
            right{nullptr},
            parent{parent} {}
        
        /** @brief Full constructor.
         *  @param data the values to be store in the `Node`.
         *  @param left the right child parent of this `Node`.
         *  @param right the right child parent of this `Node`.
         *  @param parent the `Node` parent of this `Node`.
         *  
         *  To create the `Node` with all his members filled.
         */
        Node(T& data,
             std::unique_ptr<Node<T>>& left,
             std::unique_ptr<Node<T>>& right,
             Node<T>* parent) :
                data{data},
                left{left},
                right{right},
                parent{parent} {}

        /** @brief Debug function to print a `Node`.
         *  
         *  Prints the content of the `Node`: the `data`, the `left` child and the `right` child.
         */
        void printNode() {
            std::cout << "[" << this << "]    ";
            std::cout << "Key: " << data.first << ", Value: " << data.second << std::endl;
            if (left) {
                std::cout << "    Left  -> ";
                left->printNode();
            }
            if (right) {
                std::cout << "    Right -> ";
                right->printNode();
            }
        }
    };

}


#endif // NODE_HPP
