#include <iostream>
#include <memory>
#include <utility>
#include "BST.hpp"
#include "Iterator.hpp"
#include "Node.hpp"

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
    //APutils::Node<std::pair<int, int>> testNode2{};
    //testNode2 = testNodeMatteo;  // already NOT ALLOWED by the unique_ptr


    std::pair<int, int> rootPair(1,1);
    std::pair<const int, int> leftPair(0,0);
    const std::pair<const int, int> rightPair(2,2);
    APutils::Node<std::pair<int, int>> nodeRoot(rootPair, nullptr);
    //APutils::Node<std::pair<int, int>> nodeLeft(leftPair, &nodeRoot);
    //APutils::Node<std::pair<int, int>> nodeRight(rightPair,&nodeRoot);
    //nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(&nodeLeft);  // <- WRONG!!!
    //nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(&nodeRight); // <- WRONG!!!
    nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(leftPair, &nodeRoot));
    nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(rightPair, &nodeRoot));

    nodeRoot.left->printNode();
    nodeRoot.right->printNode();
    nodeRoot.printNode();


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
    std::cout << "Key: " << it2->first << std::endl;


    std::cout << std::endl << "INSERT TESTS" << std::endl;

    APbst::bst<int, int> tree{};
    
    auto insroot = tree.insert(rootPair);
    std::cout << "Insert root: " << (insroot.second ? "OK" : "FAILED") << std::endl;
    
    auto insleft = tree.insert(leftPair);
    std::cout << "Insert left: " << (insleft.second ? "OK" : "FAILED") << std::endl;
    
    auto insright = tree.insert(rightPair);
    std::cout << "Insert right: " << (insright.second ? "OK" : "FAILED") << std::endl;
    
    auto ins3 = tree.insert(std::pair<int, int>(3,3));
    std::cout << "Insert 3: " << (ins3.second ? "OK" : "FAILED") << std::endl;
    
    auto ins5 = tree.insert(std::pair<int, int>(5,5));
    std::cout << "Insert 5: " << (ins5.second ? "OK" : "FAILED") << std::endl;
    
    auto ins6 = tree.insert(std::pair<const int, int>(6,6));
    std::cout << "Insert 6: " << (ins6.second ? "OK" : "FAILED") << std::endl;
    
    auto ins8 = tree.insert(std::pair<const int, int>(8,8));
    std::cout << "Insert 8: " << (ins8.second ? "OK" : "FAILED") << std::endl;
    
    auto ins8_2 = tree.insert(std::pair<const int, int>(8,8));
    std::cout << "Insert 8: " << (ins8_2.second ? "OK" : "FAILED") << std::endl;
    
    auto ins4 = tree.insert({4, 4});
    std::cout << "Insert 4: " << (ins4.second ? "OK" : "FAILED") << std::endl;


    std::cout << std::endl << "EMPLACE TESTS" << std::endl;

    tree.emplace(7, 7);


    std::cout << std::endl << "ITERATION TESTS" << std::endl;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << "[" << &(*it) << "]    ";
        std::cout << "Key: " << it->first << std::endl;
    }

    std::cout << std::endl;

    for (APbst::bst<int,int>::const_iterator it = tree.begin(); it != tree.end(); ++it) {
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

    std::cout << std::endl << "[] TEST" << std::endl;

    // move:
    tree[1] = 11;  // update an existing value: calls the MOVE_INSERT since it creates a new pair using (1, 11) with the pair move constructor
    tree[10] = 10;  // insert a new value
    tree[9] = 9;  // insert a new value
    
    //copy:
    const int i = 2;
    tree[i] = 22;  // update an existing value: calls the MOVE_INSERT since it creates a new pair using (i, 22) with the pair copy constructor
    const int j = 12;
    tree[j] = 12;  // insert a new value
    
    tree[4] = tree[5];


    std::cout << std::endl << "PRINT TEST" << std::endl;

    std::cout << tree << std::endl;


    std::cout << std::endl << "FIND TEST" << std::endl;

    APbst::bst<int,int>::const_iterator it_1 = tree.find(5);
    //it_1->second = 78;  // NOT allowed
    std::cout << ((it_1 == tree.end()) ? "Key NOT found" : "Key found") << std::endl;

    auto it_2 = tree.find(6);
    it_2->second = 78;  // ALLOWED
    std::cout << ((it_2 == tree.end()) ? "Key NOT found" : "Key found") << std::endl;

    auto it_3 = tree.find(55);
    std::cout << ((it_3 == tree.end()) ? "Key NOT found" : "Key found") << std::endl;

    tree.find(5)->second = 78;
    std::cout << tree[5] << std::endl;

    // const APbst::bst<int,int> const_tree{};
    // const_tree.insert(rootPair);
    // const_tree.insert(leftPair);
    // const_tree.insert(rightPair);
    // auto it_const_1 = const_tree.find(1);
    // std::cout << ((it_const_1 == const_tree.end()) ? "Key NOT found" : "Key found") << std::endl;


    std::cout << std::endl << "ERASE TEST" << std::endl;

    APbst::bst<int, int> treeAP{};
    treeAP.emplace(8,8);
    treeAP.emplace(3,3);
    treeAP.emplace(10,10);
    treeAP.emplace(1,1);
    treeAP.emplace(6,6);
    treeAP.emplace(4,4);
    treeAP.emplace(7,7);
    treeAP.emplace(14,14);
    treeAP.emplace(13,13);
    std::cout << "Before erasing: " << std::endl;
    std::cout << treeAP << std::endl;
    treeAP.erase(4);
    std::cout << "After erasing 4 (is leaf): " << std::endl;
    std::cout << treeAP << std::endl;
//    treeAP.erase(14);
//    std::cout << "After erasing 14 (has only left child): " << std::endl;
//    std::cout << treeAP << std::endl;
//    treeAP.erase(3);
//    std::cout << "After erasing 3 (has two children, and the right one has another child): " << std::endl;
//    std::cout << treeAP << std::endl;


    std::cout << std::endl << "CLEAR TEST" << std::endl;

    tree.clear();

    for (const auto& it : tree) {
        std::cout << "[" << &(it) << "]    ";
        std::cout << "Key: " << it.first << std::endl;
    }
    std::cout << "Finished printing" << std::endl;




    return 0;
}
