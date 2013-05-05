///  Tóth András (O8POUA)
///  NHF 2013 - QuadTree

#include <iostream>

template <typename T>
class QuadTree;

template <typename T>
class QuadTreeNode;

template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTree<T> &);

template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTreeNode<T> &);

template <class T>
class Point{
    unsigned int x, y;
    T data;
public:
    Point(): x(0), y(0) {}
    Point(T data, unsigned int x=0, unsigned int y=0): data(data), x(x), y(y) {}
    friend class QuadTree<T>;
    friend class QuadTreeNode<T>;
};

template <class T>
class QuadTreeNode{
    /// Szülő.
    QuadTreeNode *parent;
    /// Négy gyerek.
    QuadTreeNode *children[4];
    /// Adat.
    Point<T> data;
    /// 
    unsigned int x, y, width, height;
    /// Van-e adattagja?
    bool hasdata;
    /// Fában lévő szintje
    unsigned int level;
    /// Nincs paraméter nélküli konstruktora.
    QuadTreeNode();
    /// QuadTree hozhat létre új csomópontot. (Adat nélkül)
    QuadTreeNode(unsigned int width, unsigned int height, unsigned int x=0, unsigned int y=0, unsigned int level=0, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, hasdata(false), width(width), height(height), x(x), y(y), level(level){}
    /// QuadTree hozhat létre új csomópontot. (Adattal)
    QuadTreeNode(Point<T> data, unsigned int width, unsigned int height, unsigned int x=0, unsigned int y=0, unsigned int level=0, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, data(data), hasdata(true), width(width), height(height), x(x), y(y), level(level){}
    /// Destruktor. (delete NULL; esetén nincs probléma, nem kell vizsgálni)
    ~QuadTreeNode(){
        for (size_t i=0; i<4; ++i)
            delete children[i];
    }
    ///
    ///
    void split(){
        children[0]=new QuadTreeNode<T>(width/2, height/2, x, y+height/2, level+1, this);
        children[1]=new QuadTreeNode<T>(width/2, height/2, x+width/2, y+height/2, level+1, this);
        children[2]=new QuadTreeNode<T>(width/2, height/2, x+width/2, y, level+1, this);
        children[3]=new QuadTreeNode<T>(width/2, height/2, x, y, level+1, this);
    }
    /// Adat beszúrása.
    /// @param - Adat
    void insert(Point<T> data){
        if (data.x > x+width || data.y > y+height) throw std::out_of_range("");
        if (!hasData()){
            this->data=data;
            hasdata=true;
            return;
        }
        split();
        size_t i=3;
        if (data.x < width/2 && data.y > height/2) i=0;
        else if (data.x > width/2 && data.y > height/2) i=1;
        else if (data.x > width/2 && data.y < height/2) i=2;
        children[i]->insert(data);
    }
public:
    /// @return - A csomópont rendelkezik-e adattal?
    bool hasData() const{return hasdata;}
    /// @return - Adat
    T getData() const{
        if (hasData())
            return data;
        else throw "This node has no data.";
    }
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
    
    /// Csomópontról eldönti hogy levél-e.
    /// @return - Levél?
    bool isLeaf() const{return (children[0]==NULL && children[1]==NULL && children[2]==NULL && children[3]==NULL);}

    friend class QuadTree<T>;
    friend std::ostream& operator<< <T>(std::ostream &, const QuadTreeNode &);
};

template <class T>
class QuadTree{
    /// Fa gyökerére mutató pointer.
    QuadTreeNode<T> *root;
public:
    /// Konstruktor. (Adat nélkül)
    QuadTree(unsigned int width=100, unsigned int height=100){
        root = new QuadTreeNode<T>(width, height);
    }
    /// Konstruktor. (Adattal)
    QuadTree(T Data, unsigned int width=100, unsigned int height=100){
        root = new QuadTreeNode<T>(Point<T>(Data), width, height);
    }
    /// Destruktor.
    ~QuadTree(){delete root;}
    /// @return - Gyökérre mutató pointer.
    QuadTreeNode<T>* getRootNode(){return root;}
    /// Új elem beszúrása
    void insert(Point<T> data){
        root->insert(data);
    }
    /// Fa mélységének visszaadása.
    /// @return - Fa mélysége
    unsigned int depth() const{
        unsigned int max=1;
        for (iterator iter=begin(); iter!=end(); ++iter){
            if (max < (*iter).level+1)
                max=(*iter).level+1;
        }
        return max;
    }
    
    /// Fában lévő elemek megszámolása.
    /// @return - Fa elemszáma
    unsigned int countNodes() const{
        if (this==NULL) return 0;
        unsigned int nodes=0;
        for (iterator iter=begin(); iter!=end(); ++iter) ++nodes;
        return nodes;
    }
    
    /// Fa iterátor.
    class iterator;
    /// @return - Legbaloldalibb levél.
    iterator begin() const{
        QuadTreeNode<T> *temp=root;
        while (!temp->isLeaf())
            temp=temp->children[0];
        return iterator(temp);
    }
    /// @return - Az utolsó elem után mutat.
    iterator end() const{return iterator(NULL);}
    
    friend class QuadTreeNode<T>;
    friend std::ostream& operator<< <T>(std::ostream &,const QuadTree<T> &);
};

template <class T>
class QuadTree<T>::iterator{
protected:
    QuadTreeNode<T> *Node;
public:
    /// Konstruktor
    iterator(QuadTreeNode<T> *Node=NULL): Node(Node){}
    QuadTreeNode<T>& operator*(){return *Node;}
    QuadTreeNode<T>* operator&(){return Node;}
    QuadTreeNode<T>* operator->(){return Node;}
    /// Preinkrement iterátor???
    /// @return - Következő elem 
    iterator& operator++(){
        size_t i=0;
        /// Ha a gyökér elemnél vagyunk (csak annak nincs szülője), akkor végigértünk az összes elemen.
        if (Node->parent==NULL){
            Node=Node->parent;
            return *this;
        }
        /// A szülő hányadig gyerekén állunk?
        while (Node!=Node->parent->children[i])
            ++i;
        /// Ha a következő gyerek levél, akkor ez lesz a következő elem.
        if (i<3 && Node->parent->children[i+1]->isLeaf())
            Node=Node->parent->children[i+1];
        /// Ha a következő gyerek nem levél, akkor a következő elem a legbaloldalibb levél a következő gyerek alatt.
        else if (i<3){
            QuadTreeNode<T> *temp=Node->parent->children[i+1];
            while(!temp->isLeaf())
                temp=temp->children[0];
            Node=temp;
        }
        /// Egyébként a szülő a következő elem.
        else
            Node=Node->parent;
        return *this;
    }
    /// @return - Következő elem.
    iterator operator++(int){return ++(*this);}
    /// Egyenlőség operátor
    /// @return - Igaz, ha megegyezik az csomópont.
    bool operator==(const iterator& iter){
        return Node==iter.Node;
    }
    /// @return - Igaz, ha nem egyezik meg a csomópont.
    bool operator!=(const iterator& iter){
        return Node!=iter.Node;
    }
};

/// Fa kiírása iterátor használatával.
template <class T>
std::ostream& operator<<(std::ostream & os, const QuadTree<T> & quadtree){
    if (quadtree.root==NULL)
        return os;
    typename QuadTree<T>::iterator iter=quadtree.begin();
    while (iter!=quadtree.end()){
        os << *iter;
        ++iter;
    }
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream & os, const QuadTreeNode<T> & node){
    if (node.hasData())
        os << node.data.data << std::endl;
    return os;
}