#include <iostream>
#include <memory>
#include <utility>
#include "Node.hpp"
#include "Iterator.hpp"


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



int main() {

    //std::cout << "Hello World!" << std::endl;

	std::pair<int, int> testPair(3,4);
    APbst::Node<std::pair<int, int>> c;
    APbst::Node<std::pair<int, int>> testNode{testPair, &c};
    APbst::Node<std::pair<int,int>> testNodeMatteo(testPair, nullptr);
//    APbst::Node<std::pair<int,int>> testNodeMatteo3(testPair,nullptr,nullptr,nullptr);
//    APbst::Node<std::pair<int,int>> test2();
    testNode.printNode();
    testNodeMatteo.printNode();


    std::pair<int, int> rootPair(1,1);
    std::pair<int, int> leftPair(0,0);
    std::pair<int, int> rightPair(2,2);
    APbst::Node<std::pair<int, int>> nodeRoot(rootPair, nullptr);
    //APbst::Node<std::pair<int, int>> nodeLeft(leftPair, &nodeRoot);
    //APbst::Node<std::pair<int, int>> nodeRight(rightPair,&nodeRoot);
    //nodeRoot.left  = std::unique_ptr<APbst::Node<std::pair<int, int>>>(&nodeLeft);  // <- WRONG!!!
    //nodeRoot.right = std::unique_ptr<APbst::Node<std::pair<int, int>>>(&nodeRight); // <- WRONG!!!
    nodeRoot.left  = std::unique_ptr<APbst::Node<std::pair<int, int>>>(new APbst::Node<std::pair<int, int>>(leftPair, &nodeRoot));
    nodeRoot.right = std::unique_ptr<APbst::Node<std::pair<int, int>>>(new APbst::Node<std::pair<int, int>>(rightPair, &nodeRoot));

    nodeRoot.left->printNode();
    nodeRoot.right->printNode();
    nodeRoot .printNode();

    std::cout << std::endl << "ITERATORS TESTS:" << std::endl;

    APbst::__iterator<APbst::Node<std::pair<int, int>>,std::pair<int, int>> it(&nodeRoot);
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (*(it++)).first << std::endl;
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (*(it)).first << std::endl << std::endl;

    APbst::__iterator<APbst::Node<std::pair<int, int>>,std::pair<int, int>> it2(&nodeRoot);
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (++it2)->first << std::endl;
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << it2->first << std::endl << std::endl;

    return 0;
}
