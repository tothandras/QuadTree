//
//  QuadTree.h
//  NHF - QuadTree
//
//  Created by Tóth András on 2013.04.12..
//  Copyright (c) 2013 Tóth András. All rights reserved.
//

#ifndef __NHF___QuadTree__QuadTree__
#define __NHF___QuadTree__QuadTree__

#include <iostream>
template <typename T>
class QuadTree;

template <typename T>
class QuadTreeNode{
    QuadTree<T> *root;
    QuadTreeNode *parent;
    QuadTreeNode *children[4];
    T data;
    bool hasdata;
    unsigned int level;
    QuadTreeNode();
    QuadTreeNode(unsigned int level, QuadTree<T> *root, QuadTreeNode *parent=NULL): root(root), parent(parent), children{NULL, NULL, NULL, NULL}, hasdata(false), level(level){}
    QuadTreeNode(T Data, unsigned int level, QuadTree<T> *root, QuadTreeNode *parent=NULL): root(root), parent(parent), children{NULL, NULL, NULL, NULL}, data(Data), hasdata(true),level(level){}
    ~QuadTreeNode(){
        for (unsigned int i=0; i<4; ++i)
            delete children[i];
    }
public:
    bool hasData(){return hasdata;}
    T& getData(){return data;}
    unsigned int get_level(){return level;}
    void deleteChildren(){
        if (*this==NULL)
            return;
        else
            for (unsigned int i=0; i<4; ++i){
                children[i]->deleteChildren();
                children[i]=NULL;
            }
        delete data;
    }
    bool isLeaf() const{return (children[0]==NULL && children[1]==NULL && children[2]==NULL && children[3]==NULL);}
    friend class QuadTree<T>;
    template <typename t>
    friend std::ostream& operator<<(std::ostream & os, const QuadTreeNode<t> & Node);
};

template <typename T>
class QuadTree{
    QuadTreeNode<T> *root;
public:
    QuadTree(T Data){
        root = new QuadTreeNode<T>(Data, 0, this);
    }
    ~QuadTree(){delete root;}
    void insert(T Data){
        
    }
    unsigned int depth(){}
    class iterator;
    class pre_order_iterator;
    class post_order_iterator;
    class sibling_iterator;
    class leaf_iterator;
    pre_order_iterator pre_order_begin();
    pre_order_iterator pre_order_end();
    post_order_iterator post_order_begin();
    post_order_iterator post_order_end();
    sibling_iterator sibling_begin();
    sibling_iterator sibling_end();
    leaf_iterator leaf_begin();
    leaf_iterator leaf_end();
    QuadTreeNode<T>* getRootNode(){return root;}
    friend class QuadTreeNode<T>;
    template <typename t>
    friend std::ostream& operator<<(std::ostream &,const QuadTree<t> &);
};

template <class T>
class QuadTree<T>::iterator{
    QuadTreeNode<T> *Node;
public:
    iterator(QuadTreeNode<T> *Node=NULL): Node(Node){}
    QuadTreeNode<T>& operator*(){return *Node;}
    QuadTreeNode<T>* operator&(){return Node;}
    QuadTreeNode<T>* operator->(){return Node;}
    virtual iterator& operator++();
    virtual iterator operator++(int);
    virtual iterator& operator+=(unsigned int);
    bool operator==(const iterator& iter){
        return Node==iter.Node;
    }
    bool operator!=(const iterator& iter){
        return Node!=iter.Node;
    }
};

template <class T>
class QuadTree<T>::leaf_iterator :public QuadTree<T>::iterator{
public:
};

template <typename T>
std::ostream& operator<<(std::ostream & os, const QuadTree<T> & QuadTree){
    if (QuadTree.root==NULL)
        return os;
    os << *QuadTree.root;
    return os;
}
    
template <typename T>
std::ostream& operator<<(std::ostream & os, const QuadTreeNode<T> & Node){
    if (&Node==NULL)
        return os;
    for (int i=0; i<4; ++i)
        os << *Node.children[i];
    os << Node.data;
    if (!Node.isLeaf()) os << ",";
    return os;
}
    
#endif /* defined(__NHF___QuadTree__QuadTree__) */
