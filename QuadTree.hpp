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
    T getData(){return data;}
    void addData(T Data){data=Data;}
    void addChildren(T Data){
        for (unsigned int i=0; i<4; ++i){
            if (children[i]==NULL){
                children[i] = new QuadTreeNode(Data, level+1, root, this);
            }
        }
        addChildren(Data);
    }
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
    friend class QuadTreeNode<T>;
    template <typename t>
    friend std::ostream& operator<<(std::ostream &,const QuadTree<t> &);
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
