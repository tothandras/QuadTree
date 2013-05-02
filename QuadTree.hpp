//  Tóth András
//  QuadTree.hpp
//  NHF - QuadTree

#include <iostream>

template <typename T>
class QuadTree;

template <typename T>
class QuadTreeNode;

template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTree<T> &);

template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTreeNode<T> &);

template <typename T>
class QuadTreeNode{
    /// Szülő.
    QuadTreeNode *parent;
    /// Négy gyerek.
    QuadTreeNode *children[4];
    /// Adat.
    T data;
    /// Van-e adattagja?
    bool hasdata;
    /// Fában lévő szintje
    unsigned int level;
    /// Nincs paraméter nélküli konstruktora.
    QuadTreeNode();
    /// QuadTree hozhat létre új csomópontot. (Adat nélkül)
    QuadTreeNode(unsigned int level=0, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, hasdata(false), level(level){}
    /// QuadTree hozhat létre új csomópontot. (Adattal)
    QuadTreeNode(T Data, unsigned int level=0, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, data(Data), hasdata(true),level(level){}
    /// Destruktor. (delete NULL; esetén nincs probléma, nem kell vizsgálni)
    ~QuadTreeNode(){
        for (size_t i=0; i<4; ++i)
            delete children[i];
    }
public:
    /// @return - A csomópont rendelkezik-e adattal?
    bool hasData(){return hasdata;}
    /// @return - Adat
    T& getData(){
        if (hasData())
            return data;}
    /// @return - Melyik szinten van?
    unsigned int getLevel() const{return level;}
    /// Gyerekek törlése úgy, hogy a gyerekek gyerekei is törlődnek.
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
    /// Adat beszúrása.
    /// @param - Adat
    void insert(T data){
        size_t i=0;
        while(children[i]!=NULL && i<4)
            ++i;
        children[i]=new QuadTreeNode(data, level+1, this);
    }
    /// Csomópontról eldönti hogy levél-e.
    /// @return - Levél?
    bool isLeaf() const{return (children[0]==NULL && children[1]==NULL && children[2]==NULL && children[3]==NULL);}
    /// Fa/részfa mélységének visszaadása rekurzív függvényhívással.
    /// @return - Fa/részfa mélysége
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
    /// Fában/részfában lévő elemek megszámolása rekurzív függvényhívással.
    /// @return - Fa/részfa elemszáma
    unsigned int countNodes() const{
        if (this==NULL) return 0;
        return children[0]->countNodes()+children[1]->countNodes()+children[2]->countNodes()+children[3]->countNodes()+ 1;
    }
    /// Fában/részfában lévő levelek megszámolása rekurzív függvényhívással.
    /// @return - Fa/részfa levélszáma
    unsigned int countLeafs() const{
        if (this==NULL) return 0;
        if (isLeaf()) return 1;
        return children[0]->countLeafs()+children[1]->countLeafs()+children[2]->countLeafs()+children[3]->countLeafs();
    }
    
    friend class QuadTree<T>;
    friend std::ostream& operator<< <T>(std::ostream &, const QuadTreeNode<T> &);
};

template <typename T>
class QuadTree{
    /// Fa gyökerére mutató pointer.
    QuadTreeNode<T> *root;
public:
    /// Konstruktor. (Adat nélkül)
    QuadTree(){
        root = new QuadTreeNode<T>();
    }
    /// Konstruktor. (Adattal)
    QuadTree(T Data){
        root = new QuadTreeNode<T>(Data);
    }
    /// Destruktor.
    ~QuadTree(){delete root;}
    /// @return - Gyökérre mutató pointer.
    QuadTreeNode<T>* getRootNode(){return root;}
    /// Új elem beszúrása
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
                    elements[i]=temp->children[i]->countNodes();
                min=elements[0];
                for(i=0; i<4; ++i)
                    if(min>elements[i])
                        min=elements[i];
                for(i=0; min!=elements[i]; ++i);
                    temp=temp->children[i];
            }
        }
    }
    /// Fa mélységének visszaadása rekurzív függvényhívással.
    /// @return - Fa mélysége
    unsigned int depth(){return root->depth();}
    
    /// Fa iterátor.
    class iterator;
    iterator begin() const{
        QuadTreeNode<T> *temp=root;
        while (!temp->isLeaf())
            temp=temp->children[0];
        return iterator(temp);
    }
    iterator end() const{return iterator(NULL);}
    
    friend class QuadTreeNode<T>;
    friend std::ostream& operator<< <T>(std::ostream &,const QuadTree<T> &);
};

/* Munka alatt */
template <class T>
class QuadTree<T>::iterator{
protected:
    QuadTreeNode<T> *Node;
public:
    iterator(QuadTreeNode<T> *Node=NULL): Node(Node){}
    iterator& operator=(QuadTreeNode<T> r){
      return this->Node=r.Node;
    }
    QuadTreeNode<T>& operator*(){return *Node;}
    QuadTreeNode<T>* operator&(){return Node;}
    QuadTreeNode<T>* operator->(){return Node;}
    iterator& operator++(){
        size_t i=0;
        if (Node->parent==NULL){
            Node=Node->parent;
            return *this;
        }
        while (Node!=Node->parent->children[i])
            ++i;
        if (i<3 && Node->parent->children[i+1]->isLeaf())
            Node=Node->parent->children[i+1];
        else if (i<3){
            QuadTreeNode<T> *temp=Node->parent->children[i+1];
            while(!temp->isLeaf())
                temp=temp->children[0];
            Node=temp;
        }
        else
            Node=Node->parent;
        return *this;
    }
    iterator operator++(int){return ++(*this);}
    bool operator==(const iterator& iter){
        return Node==iter.Node;
    }
    bool operator!=(const iterator& iter){
        return Node!=iter.Node;
    }
};

/// Fa kiírása rekurzívan.
template <typename T>
std::ostream& operator<<(std::ostream & os, const QuadTree<T> & quadtree){
    if (quadtree.root==NULL)
        return os;
    typename QuadTree<T>::iterator iter=quadtree.begin();
    while (iter!=quadtree.end()) os<< *(iter++);
    return os;
}

/// Részfa kiírása rekurzívan
template <typename T>
std::ostream& operator<<(std::ostream & os, const QuadTreeNode<T> & node){
    if (&node==NULL)
        return os;
    for (unsigned int i=node.getLevel(); i!=0; --i) os << ' ';
    os << node.data << std::endl;
    /*for (size_t i=0; i<4; ++i){
        os << *Node.children[i];
    }*/
    return os;
}