#include <iostream>
#include <memory>
#include <utility>
#include "BST.hpp"
#include "Iterator.hpp"
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



int main() {

    //std::cout << "Hello World!" << std::endl;

	std::pair<int, int> testPair(3,4);
    APutils::Node<std::pair<int, int>> c;
    APutils::Node<std::pair<int, int>> testNode{testPair, &c};
    APutils::Node<std::pair<int,int>> testNodeMatteo(testPair, nullptr);
//    APutils::Node<std::pair<int,int>> testNodeMatteo3(testPair,nullptr,nullptr,nullptr);
//    APutils::Node<std::pair<int,int>> test2();
    testNode.printNode();
    testNodeMatteo.printNode();


    std::pair<int, int> rootPair(1,1);
    std::pair<const int, int> leftPair(0,0);
    std::pair<const int, int> rightPair(2,2);
    APutils::Node<std::pair<int, int>> nodeRoot(rootPair, nullptr);
    //APutils::Node<std::pair<int, int>> nodeLeft(leftPair, &nodeRoot);
    //APutils::Node<std::pair<int, int>> nodeRight(rightPair,&nodeRoot);
    //nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(&nodeLeft);  // <- WRONG!!!
    //nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(&nodeRight); // <- WRONG!!!
    nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(leftPair, &nodeRoot));
    nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(rightPair, &nodeRoot));

    nodeRoot.left->printNode();
    nodeRoot.right->printNode();
    nodeRoot .printNode();

    std::cout << std::endl << "ITERATORS TESTS:" << std::endl;

    APutils::__iterator<APutils::Node<std::pair<int, int>>,std::pair<int, int>> it(&nodeRoot);
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (*(it++)).first << std::endl;
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (*(it)).first << std::endl << std::endl;

    APutils::__iterator<APutils::Node<std::pair<int, int>>,std::pair<int, int>> it2(&nodeRoot);
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (++it2)->first << std::endl;
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << it2->first << std::endl << std::endl;


    std::cout << "INSERT TESTS" << std::endl;

    APbst::bst<int, int> tree{};
    tree.insert(rootPair);
    tree.insert(leftPair);
    tree.insert(rightPair);
    tree.insert(std::pair<int, int>(3,3));
    auto ins5 = tree.insert(std::pair<int, int>(5,5));
    std::cout << "Insert 5: " << (ins5.second ? "OK" : "FAILED") << std::endl;
    tree.insert(std::pair<const int, int>(6,6));
    auto ins8 = tree.insert(std::pair<const int, int>(8,8));
    std::cout << "Insert 8: " << (ins8.second ? "OK" : "FAILED") << std::endl;
    auto ins8_2 = tree.insert(std::pair<const int, int>(8,8));
    std::cout << "Insert 8: " << (ins8_2.second ? "OK" : "FAILED") << std::endl;


    std::cout << std::endl << "ITERATION TESTS" << std::endl;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << "[" << &(*it) << "]    ";
        std::cout << "Key: " << it->first << std::endl;
    }
    std::cout << std::endl;
    /* C++-14 loop.
     * Use the following:
     *   - 'const auto& it' to observe the elements by const reference.
     *   - 'auto it'        to observe the elements by copying them (if copy is cheap).
     *   - 'auto& it'       to modify the elements in place by non-const reference.
     *   - 'auto&& it'      to modify the elements by proxy iterators, which are not
     *                      implemented in our case, so it works the same way as
     *                      'auto& it'.
     * Since 'it' is not a pointer in any of the above cases, there's no need to
     * dereference `it` (it's directly of type T of Node<T>).
     */
    for (const auto& it : tree) {
        std::cout << "[" << &(it) << "]    ";
        std::cout << "Key: " << it.first << std::endl;
    }



    return 0;
}
