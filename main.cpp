#include <iostream>
#include <memory>
#include <utility>

/*
template <typename KT, typename VT, typename cmp = std::less<KT>>
class bst{
	cmp op; // operator of comparison
  public:
    bst(cmp x): op{x} {}

	using node_type = Node<std::pair<const KT, VS>>;

	std::pair<iterator, bool> insert(const pair_type& x);
	std::pair<iterator, bool> insert(pair_type&& x);

	template<class... Types>
	std::pair<iterator,bool> emplace(Types&&... args);
	
	void clear();

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	iterator find(const key_type& x); // find a node and eventually change the value
	const_iterator find(const key_type& x) const; // find if a node just exists

	void balance();

	value_type& operator[](const key_type& x);  // copy semantic
	value_type& operator[](key_type&& x);  // move semantic

	insert({x, VT{}}) // default constructor of type VT

  friend
	std::ostream& operator<<(std::ostream& os, const bst& x);

	void erase(const key_type& x);
}*/

template <typename T>
class Node{
  private:
	T _data;
	std::unique_ptr<Node<T>> _left;
	std::unique_ptr<Node<T>> _right;
	Node<T>* _parent; // to navigate the tree

  public:
	Node() = delete;
    Node(T& data, Node* parent) :
	  _data{data}, _left{nullptr}, _right{nullptr}, _parent{parent} {}
	Node(T& data) : _data{data} {}
};

//template <typename node_t, typename T>
//class _iterator{
//	node_t* current;
//  public:
//  	using value_type = T;
//  	using reference = value_type&;
//  	using pointer = value_type*
//  	using iterator_category;
//  	using difference_type=std::ptrdiff_t // two iterators are equal if they point tot he same node
//    reference operator*() const{
//        return .....;
//    }
//}

int main() {

    std::cout << "Hello World!" << std::endl;

	std::pair<int, int> testPair(3,4);
	Node<std::pair<int, int>>* c;
	Node<std::pair<int, int>> testNode{testPair, c};
	Node<std::pair<int, int>> testNode2(testPair);

    return 0;
}
