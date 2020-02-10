#include <iostream>
#include <memory>
#include <utility>
#include "Node.hpp"


//template <typename KT, typename VT, typename cmp = std::less<KT>>
//class bst{
//	cmp op; // operator of comparison
//  public:
//    bst(cmp x): op{x} {}

//	using node_type = Node<std::pair<const KT, VS>>;

//	std::pair<iterator, bool> insert(const pair_type& x);
//	std::pair<iterator, bool> insert(pair_type&& x);

//	template<class... Types>
//	std::pair<iterator,bool> emplace(Types&&... args);

//	void clear();

//	iterator begin();
//	const_iterator begin() const;
//	const_iterator cbegin() const;

//	iterator end();
//	const_iterator end() const;
//	const_iterator cend() const;

//	iterator find(const key_type& x); // find a node and eventually change the value
//	const_iterator find(const key_type& x) const; // find if a node just exists

//	void balance();

//	value_type& operator[](const key_type& x);  // copy semantic
//	value_type& operator[](key_type&& x);  // move semantic

//	insert({x, VT{}}) // default constructor of type VT

//  friend
//	std::ostream& operator<<(std::ostream& os, const bst& x);

//	void erase(const key_type& x);
//}


// template <typename node_t, typename T>
// class _iterator{
// 	node_t* current;
//   public:
//   	using value_type = T;
//   	using reference = value_type&;
//   	using pointer = value_type*
//   	using iterator_category;
//   	using difference_type=std::ptrdiff_t // two iterators are equal if they point to the same node
//     reference operator*() const{
//         return .....;
//     }
// }

template <typename T>
class Node2{
  private:
	T _data;
	std::unique_ptr<Node2<T>> _left;
	std::unique_ptr<Node2<T>> _right;
	Node2<T>* _parent; // to navigate the tree
	
  public:
	Node2() = delete;
    Node2(T& data, Node2* parent) :
	  _data{data}, _left{nullptr}, _right{nullptr}, _parent{parent} {}
	Node2(T& data) : _data{data} {}
};


int main() {

    std::cout << "Hello World!" << std::endl;

	std::pair<int, int> testPair(3,4);
	Node2<std::pair<int, int>>* c;
	Node2<std::pair<int, int>> testNode{testPair, c};
	Node2<std::pair<int, int>> testNode2(testPair);
//    Node<std::pair<int,int>> testNode(testPair,nullptr,nullptr,nullptr);
//    Node<std::pair<int,int>> testNode(testPair);
//    Node<std::pair<int,int>> test2();

    return 0;
}
