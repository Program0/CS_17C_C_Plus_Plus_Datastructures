/* 
 * File:   KeyValueNode.h
 * Author: super0
 *
 * Created on December 19, 2015, 8:26 PM
 */

#ifndef KEYVALUENODE_H
#define	KEYVALUENODE_H

template <typename K, typename V> class PairList;
template <typename K, typename V> class PairListIterator;

template<class K, class V>
class KeyValueNode {
public:
    friend class PairListIterator<K,V>;
    friend class PairList<K,V>;
    KeyValueNode();

    KeyValueNode(const K& keyEntry, const V& valueEntry, KeyValueNode* node) : 
        key(keyEntry), value(valueEntry), next(node) {}
private:
    K key;
    V value;
    KeyValueNode * next;
};

#endif	/* KEYVALUENODE_H */

