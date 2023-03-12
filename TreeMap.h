#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "ScapegoatTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    bool pop(const K &key);

    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &floorEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();

    void pollLastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    ScapegoatTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    stree.removeAllNodes();
    /* TODO */
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    KeyValuePair<K,V> variable(key);
    KeyValuePair<K, V> temp =  stree.get(variable);
    return temp.getValue();
    
    /* TODO */
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
    KeyValuePair<K,V> variable(key);
    return stree.remove(variable);
    /* TODO */
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {
    KeyValuePair<K, V> variable(key, value);
    return stree.insert(variable);
    /* TODO */
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    const KeyValuePair<K, V> temp =  stree.getCeiling(key);
    return temp;
    /* TODO */
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {
    const KeyValuePair<K, V> temp =  stree.getFloor(key);
    return temp;
    /* TODO */
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    const KeyValuePair<K, V> temp =  stree.getMin();
    return temp;
    /* TODO */
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    const KeyValuePair<K, V> temp =  stree.getMax();
    return temp;
    /* TODO */
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {
    KeyValuePair<K, V> temp =  stree.getMin();
    stree.remove(temp);
    /* TODO */
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {
    KeyValuePair<K, V> temp =  stree.getMax();
    stree.remove(temp);
    /* TODO */
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {
    std::vector<KeyValuePair<K, V> > sub;

    KeyValuePair<K, V> current = stree.get(fromKey);
   
    while(current.getKey() < toKey){
        
        sub.push_back(current);
        current = stree.getNext(current); 

    }
    sub.push_back(current);

    return sub;
    /* TODO */
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# ScapegoatTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

#endif //TREEMAP_H

