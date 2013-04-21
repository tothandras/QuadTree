//
//  QuadTree.hpp
//  NHF - QuadTree
//

#ifndef __NHF___QuadTree__QuadTree__
#define __NHF___QuadTree__QuadTree__

#include <iostream>
template <typename T>
class QuadTree;

template <typename T>
class QuadTreeNode{
    // szülő
    QuadTreeNode *parent;
    // 4 gyerek
    QuadTreeNode *children[4];
    // generikus adat
    T data;
    // van-e adat? adattal lett létrehozva?
    bool hasdata;
    // szint
    unsigned int level;
    // nincs alapértelmezett konstruktora
    QuadTreeNode();
    // és csak a QuadTree tud létrehozni újabb csomópontot
    QuadTreeNode(unsigned int level, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, hasdata(false), level(level){}
    QuadTreeNode(T Data, unsigned int level, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, data(Data), hasdata(true),level(level){}
    // ha delete NULL hívódna meg, az nem gond, ezért nem vizsgálja
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
    void insert(T data){
        size_t i=0;
        while(children[i]!=NULL && i<4)
            ++i;
        children[i]=new QuadTreeNode(data, level+1, this);
    }
    bool isLeaf() const{return (children[0]==NULL && children[1]==NULL && children[2]==NULL && children[3]==NULL);}
    // rekurzív megoldás
    unsigned int depth() const{
        unsigned int depth[4], max=0;
        if(this==NULL) return 0;
        for(size_t i=0; i<4; ++i)
            depth[i]=this->children[i]->depth();
        for(size_t i=0; i<4; ++i)
            if(max<depth[i])
                max=depth[i];
        return max+1;
    }
    // reszfaban levo elemek megszamolasa
    unsigned int countElements() const{
        if (this==NULL) return 0;
        return children[0]->countElements()+children[1]->countElements()+children[2]->countElements()+children[3]->countElements()+ 1;
    }
    unsigned int countLeafs() const{
        if (this==NULL) return 0;
        if (isLeaf()) return 1;
        return children[0]->countLeafs()+children[1]->countLeafs()+children[2]->countLeafs()+children[3]->countLeafs();
    }
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
    void insert(T data){
        QuadTreeNode<T>* temp=root;
        unsigned int elements[4], min;
        bool inserted=false;
        
        while(!inserted){
            if(temp->children[0]==NULL || temp->children[1]==NULL || temp->children[2]==NULL || temp->children[3]==NULL){
                size_t i=0;
                for(i=0; temp->children[i]!=NULL; ++i);
                temp->children[i]=new QuadTreeNode<T>(data, temp->level+1, temp);
                inserted=true;
            }
            else{
                size_t i;
                for(i=0; i<4; ++i)
                    elements[i]=temp->children[i]->countElements();
                min=elements[0];
                for(i=0; i<4; ++i)
                    if(min>elements[i])
                        min=elements[i];
                for(i=0; min!=elements[i]; ++i);
                    temp=temp->children[i];
            }
        }
    }
    unsigned int depth(){return root->depth();}
    class iterator;
    iterator begin(){}
    iterator end(){}
    QuadTreeNode<T>* getRootNode(){return root;}
    friend class QuadTreeNode<T>;
    template <typename t>
    friend std::ostream& operator<<(std::ostream &,const QuadTree<t> &);
};

template <class T>
class QuadTree<T>::iterator{
protected:
    QuadTreeNode<T> *Node;
    iterator(QuadTreeNode<T> *Node=NULL): Node(Node){}
public:
    QuadTreeNode<T>& operator*(){return *Node;}
    QuadTreeNode<T>* operator&(){return Node;}
    QuadTreeNode<T>* operator->(){return Node;}
    iterator& operator++(){}
    iterator operator++(int){}
    bool operator==(const iterator& iter){
        return Node==iter.Node;
    }
    bool operator!=(const iterator& iter){
        return Node!=iter.Node;
    }
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
    for (size_t i=0; i<4; ++i){
        os << *Node.children[i];
        if (Node.children[i]!=NULL && !Node.isLeaf()) os << ", ";
    }
    os << Node.data;
    return os;
}
    
#endif /* defined(__NHF___QuadTree__QuadTree__) */
