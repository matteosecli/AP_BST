#ifndef NODE_HPP
#define NODE_HPP

#include <iostream> /* To use std::cout & co. */
#include <iomanip>  /* For std::setw() */
#include <memory>   /* For std::unique_ptr */
#include <utility>  /* For std::pair */


/** 
 * @brief Namespace that stands for "Advanced Programming Utils"
 * 
 * Namespace to hide Node and Iterator from the user, and to possibly put
 * some other useful classes.
 */
namespace APutils {

    /**
     * @brief Class that implements a node of a tree.
     *
     * General class that can be used in any tree, for example it could be used
     * in a class `bt` that implements a Binary Tree ( and then @ref APbst::bst
     * could inherit from `bt`).
     */
    template <typename T>
    struct Node {
        /**
         * @brief Data stored in this @ref Node.
         *
         * E.g. for a APbst::bst `std::pair<const Key,Value>`, where `Key` is the
         * key of this @ref Node and `Value` is the value stored in this @ref Node.
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
         * Used only to create a void `root` @ref Node when an object @ref APbst::bst is instantiated.
         */
        Node() noexcept :
            data{},
            left{nullptr},
            right{nullptr},
            parent{nullptr} {}

        /**
         * @brief Copy constructor with data.
         *
         * @param data The values to be stored in the @ref Node.
         * @param parent Raw pointer to the parent @ref Node of this @ref Node.
         *  
         * To create a @ref Node with given @ref data and @ref parent, and @ref left and @ref right initialized to `nullptr`.
         */
        Node(const T& data, Node<T>* parent) noexcept :
            data{data},
            left{nullptr},
            right{nullptr},
            parent{parent} {}

        /**
         * @brief Move constructor with data.
         *
         * @param data The values to be stored in the @ref Node.
         * @param parent Raw pointer to the parent @ref Node of this @ref Node.
         *
         * To create a @ref Node with given @ref data and @ref parent, and @ref left and @ref right initialized to `nullptr`.
         */
        Node(T&& data, Node<T>* parent) noexcept :
            data{std::move(data)},
            left{nullptr},
            right{nullptr},
            parent{parent} {}

        /**
         * @brief Utility function that prints a @ref Node.
         *
         * @param os The stream to which you'd like to print the @ref Node.
         * @param printChildren Whether to print the children of each node as well.
         *  
         * Prints the content of the @ref Node: the @ref data, the @ref left child and the @ref right child.
         */
        void printNode(std::ostream& os, const bool& printChildren) {
            os << "[" << this << "]    ";
            os << "Key: " << std::setw(4) << data.first
               << ", Value: " << std::setw(4) << data.second << std::endl;
            if (printChildren) {
                if (left) {
                    os << "    Left  -> "
                       << "[" << left.get() << "]    "
                       << "Key: " << std::setw(4) << left .get()->data.first
                       << ", Value: " << std::setw(4) << left .get()->data.second << std::endl;
                }
                if (right) {
                    os << "    Right -> "
                       << "[" << right.get() << "]    "
                       << "Key: " << std::setw(4) << right.get()->data.first
                       << ", Value: " << std::setw(4) << right.get()->data.second << std::endl;
                }
            }
        }
        /**
         * @brief Utility function that prints a @ref Node.
         *
         * Overloaded @ref printNode() that prints, without arguments, each node
         * and their children to `std::cout`.
         */
        void printNode() {
            printNode(std::cout, true);
        }
    };

}


#endif // NODE_HPP
