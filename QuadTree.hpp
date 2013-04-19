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
    //QuadTree<T> *root;
    QuadTreeNode *parent;
    QuadTreeNode *children[4];
    T data;
    bool hasdata;
    unsigned int level;
    QuadTreeNode();
    QuadTreeNode(unsigned int level, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, hasdata(false), level(level){}
    QuadTreeNode(T Data, unsigned int level, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, data(Data), hasdata(true),level(level){}
    ~QuadTreeNode(){
        for (size_t i=0; i<4; ++i)
            delete children[i];
    }
public:
    bool hasData(){return hasdata;}
    T& getData(){return data;}
    unsigned int getLevel(){return level;}
    void deleteChildren(){
        if (*this==NULL)
            return;
        else
            for (size_t i=0; i<4; ++i){
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
        root = new QuadTreeNode<T>(Data, 0);
    }
    ~QuadTree(){delete root;}
    void insert(T Data){
        pre_order_iterator iter;
        for(iter=pre_order_begin(); iter!=pre_order_end(); ++iter)
            ;
    }
    unsigned int depth(){}
    class iterator;
    class pre_order_iterator;
    class post_order_iterator;
    class sibling_iterator;
    class leaf_iterator;
    pre_order_iterator pre_order_begin(){return pre_order_iterator(root);};
    pre_order_iterator pre_order_end();
    post_order_iterator post_order_begin();
    post_order_iterator post_order_end();
    sibling_iterator sibling_begin(unsigned int level){
        QuadTreeNode<T> *temp=root;
        while(temp->children[0].getLevel() != level || temp != NULL)
            temp=temp->children[0];
        return sibling_iterator(temp);
    }
    sibling_iterator sibling_end(unsigned int level);
    leaf_iterator leaf_begin(){
        QuadTreeNode<T> *temp=root;
        while(!temp->children[0].isLeaf())
            temp=temp->children[0];
        return leaf_iterator(temp->children[0]);
    }
    leaf_iterator leaf_end(){return leaf_iterator(NULL);}
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
    bool operator==(const iterator& iter){
        return Node==iter.Node;
    }
    bool operator!=(const iterator& iter){
        return Node!=iter.Node;
    }
};

template <class T>
class QuadTree<T>::pre_order_iterator :public QuadTree<T>::iterator{
public:
    pre_order_iterator& operator++(){return pre_order_iterator(this->Node);}
    pre_order_iterator operator++(int){
        QuadTreeNode<T> *temp=this->Node;
        if(this->Node==NULL)
            return NULL;
        size_t i=0;
        while(temp->parent->children[i]!=temp)
            ++i;
        if(i<3 && temp->parent->children[i+1]!=NULL)
            this->Node=temp->parent->children[i+1];
        else
            this->Node=0;
    }
    pre_order_iterator& operator+=(unsigned int){return pre_order_iterator(this->Node);}
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
    for (size_t i=0; i<4; ++i)
        os << *Node.children[i];
    os << Node.data;
    if (!Node.isLeaf()) os << ",";
    return os;
}
    
#endif /* defined(__NHF___QuadTree__QuadTree__) */
