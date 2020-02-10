#ifndef NODE_HPP
#define NODE_HPP

#include <utility>  /** @brief For std::pair */
#include <memory>   /** @brief For std::unique_ptr */


template <typename T>   // T must be an std::pair
class Node {
  private:
    T data;             // Contains an std::pair<Key,Val>
//    std::unique_ptr<Node<T>> left, right;
//    Node<T>* parent;       // To navigate the tree (???)
  public:
    Node();
//    Node(T&,
//         std::unique_ptr<Node<T>>,
//         std::unique_ptr<Node<T>>,
//         Node<T>*);
    Node(T&);
};

#endif // NODE_HPP
