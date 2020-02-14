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

    /**
     * @brief Class that implements a node of a tree.
     *
     * General class that can be used in any tree, for example it could be used in the class bt that implements a
     * Binary Tree (our class @ref bst should in fact inherit from bt).
     */
    template <typename T>   // T must be an std::pair
    struct Node {
        /**
         * @brief Data stored in this @ref Node.
         *
         * Contains an std::pair<const Key,Val>, where Key is the key of this Node and Val is the value stored in this @ref Node.
         */
        T data;
        /** @brief Left child of this @ref Node. */
        std::unique_ptr<Node<T>> left;
        /** @brief Right child of this @ref Node. */
        std::unique_ptr<Node<T>> right;
        /** @brief Parent of this @ref Node. */
        Node<T>* parent;

        /**
         * @brief Void constructor.
         *  
         * Used only to create a void root when an object @ref bst is instantiated.
         */
        Node() :
            data{},
            left{nullptr},
            right{nullptr},
            parent{nullptr} {}

        /**
         * @brief Data copy constructor.
         * @param data the values to be store in the @ref Node.
         * @param parent the @ref Node parent of this @ref Node.
         *  
         * To create a @ref Node with given @ref data and @ref parent, and @ref left and @ref right initializated to `nullptr`.
         */
        Node(const T& data, Node<T>* parent) :
            data{data},
            left{nullptr},
            right{nullptr},
            parent{parent} {}

        /**
         * @brief Data move constructor.
         * @param data the values to be store in the @ref Node.
         * @param parent the @ref Node parent of this @ref Node.
         *
         * To create a @ref Node with given @ref data and @ref parent, and @ref left and @ref right initializated to `nullptr`.
         */
        Node(T&& data, Node<T>* parent) :
            data{std::move(data)},
            left{nullptr},
            right{nullptr},
            parent{parent} {}
        
//        /**
//         * @brief Full constructor.
//         * @param data the values to be store in the @ref Node.
//         * @param left the right child parent of this @ref Node.
//         * @param right the right child parent of this @ref Node.
//         * @param parent the @ref Node parent of this @ref Node.
//         *
//         * To create the @ref Node with all his members filled.
//         */
//        Node(T& data,
//             std::unique_ptr<Node<T>>& left,
//             std::unique_ptr<Node<T>>& right,
//             Node<T>* parent) :
//                data{data},
//                left{left},
//                right{right},
//                parent{parent} {}

        /**
         * @brief Debug function to print a @ref Node.
         *  
         * Prints the content of the @ref Node: the @ref data, the @ref left child and the @ref right child.
         */
        void printNode() {
            std::cout << "[" << this << "]    ";
            std::cout << "Key: " << data.first << ", Value: " << data.second << std::endl;
            if (left) {
                std::cout << "    Left  -> "
                          << "[" << left.get() << "]    "
                          << "Key: " << left .get()->data.first << ", Value: " << left .get()->data.second << std::endl;
            }
            if (right) {
                std::cout << "    Right -> "
                          << "[" << right.get() << "]    "
                          << "Key: " << right.get()->data.first << ", Value: " << right.get()->data.second << std::endl;
            }
        }
    };

}


#endif // NODE_HPP
