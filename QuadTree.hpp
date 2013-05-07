///  Tóth András (O8POUA)
///  NHF 2013 - QuadTree (Négy elágazású duplán láncolt generikus fa)

template <typename T>
class QuadTree;

template <typename T>
class QuadTreeNode;

template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTree<T> &);

template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTreeNode<T> &);

/// Point (pont) osztály. A négy elágazású generikus fát ilyen pontokkal tölthetjük fel.
template <class T>
class Point{
    /// Az adat helye.
    double x, y;
    /// Az adat.
    T data;
public:
    /// Default konstruktor.
    Point(): x(0), y(0) {}
    /// Konstruktor adattal.
    Point(T data, double x=0, double y=0): data(data), x(x), y(y) {}
    
    friend class QuadTree<T>;
    friend class QuadTreeNode<T>;
};

/// QuadTreeNode (négy elágazású generikus fa csomópontja) osztály. A négy elágazású generikus fa ilyen csomópontokból épül fel.
template <class T>
class QuadTreeNode{
    /// Szülő.
    QuadTreeNode *parent;
    /// Négy gyerek.
    QuadTreeNode *children[4];
    /// Pont, melyben az adatot tárolhatjuk.
    Point<T> *point;
    /// Pontok száma.
    size_t number_of_points;
    /// A területre jellemző adatok. (x ; y) pont a téglalap bal alsó pontja.
    double x, y, width, height;
    /// Melyik szinten található a fában? A gyökér van az 1. szinten.
    unsigned level;
    /// Milyen mélységig nőhet a fa? Ezzel a statikus változóval lehet beállítani.
    static unsigned MAX_LEVEL;
    /// Nincs paraméter nélküli konstruktora.
    QuadTreeNode();
    /// QuadTree és QuadTreeNode hozhat csak létre új csomópontot. (Adat nélkül)
    QuadTreeNode(double width, double height, double x=0, double y=0, unsigned level=1, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, width(width), height(height), x(x), y(y), level(level), point(NULL), number_of_points(0){}
    /// Destruktor. (delete NULL; esetén nincs probléma, nem kell vizsgálni)
    ~QuadTreeNode(){
        for (size_t i=0; i<4; ++i)
            delete children[i];
        delete[] point;
    }
    /// Terület felbontása négy egybevágó téglalapra.
    void split(){
        /// Bal felső.
        children[0]=new QuadTreeNode<T>(width/2, height/2, x, y+height/2, level+1, this);
        /// Jobb felső.
        children[1]=new QuadTreeNode<T>(width/2, height/2, x+width/2, y+height/2, level+1, this);
        /// Jobb alsó.
        children[2]=new QuadTreeNode<T>(width/2, height/2, x+width/2, y, level+1, this);
        /// Bal alsó.
        children[3]=new QuadTreeNode<T>(width/2, height/2, x, y, level+1, this);
    }
    /// Új pont / adat beszúrása.
    /// @param Új pont.
    void insert(Point<T> new_point){
        /// Ha nincs meglévő adat:
        if (!hasData()){
            this->point = new Point<T>[1];
            point[0] = new_point;
            number_of_points=1;
        }
        /// Ha van meglévő adat és még nem érte el a maximális mélységet a fa:
        else if (hasData() && level != MAX_LEVEL){
            /// Felbontás.
            split();
            /// Beszúrjuk a meglévő adatot.
            size_t i=3;
            if (x <= x+width/2 && y > y+height/2) i=0;
            else if (x > x+width/2 && y >= y+height/2) i=1;
            else if (x > x+width/2 && y <= y+height/2) i=2;
            children[i]->insert(*point);
            delete[] point;
            point=NULL;
            number_of_points=0;
            /// Beszúrjuk az új adatot.
            i=3;
            if (new_point.x <= x+width/2 && new_point.y > y+height/2) i=0;
            else if (new_point.x > x+width/2 && new_point.y >= y+height/2) i=1;
            else if (new_point.x > x+width/2 && new_point.y <= y+height/2) i=2;
            children[i]->insert(new_point);
        }
        /// Ha van meglévő adat, de elérte a maximális mélységet a fa:
        else{
            Point<T> *temp = new Point<T>[number_of_points+1];
            size_t i;
            for (i=0; i<number_of_points; ++i)
                temp[i]=point[i];
            temp[number_of_points]=new_point;
            ++number_of_points;
            delete[] point;
            point = temp;
        }
    }
public:
    /// @return A csomópont rendelkezik-e adattal?
    bool hasData() const{
        return number_of_points==0 ? false : true;
    }
    /// @return Melyik szinten van?
    unsigned getLevel() const{
        return level;
    }
    
    /// Csomópontról eldönti hogy levél-e.
    /// @return Levél?
    bool isLeaf() const{
        return (children[0]==NULL && children[1]==NULL && children[2]==NULL && children[3]==NULL);
    }

    friend class QuadTree<T>;
    friend std::ostream& operator<< <T>(std::ostream &, const QuadTreeNode &);
};

/// Milyen mélységig nőhet a fa? Ezzel a statikus változóval lehet beállítani.
template <class T>
unsigned QuadTreeNode<T>::MAX_LEVEL=10;

/// QuadTree (négy elágazású generikus fa) osztály. A négy elágazású generikus fa QuadTreeNode-okból épül fel.
template <class T>
class QuadTree{
    /// Fa gyökerére mutató pointer.
    QuadTreeNode<T> *root;
public:
    /// Konstruktor.
    QuadTree(double width=100, double height=100){
        root = new QuadTreeNode<T>(width, height);
    }
    /// Destruktor.
    ~QuadTree(){delete root;}
    /// @return - Gyökérre mutató pointer.
    QuadTreeNode<T>* getRootNode(){return root;}
    /// Új elem beszúrása.
    /// @param Új pont / adat.
    void insert(Point<T> data){
        /// Ha a pont kívül esik a területről, akkor kivételt dob.
        if (data.x > root->x+root->width || data.y > root->y+root->height)
            throw std::out_of_range("");
        QuadTreeNode<T> *temp=root;
        while (!temp->isLeaf()){
            size_t i=3;
            if (data.x <= temp->x+temp->width/2 && data.y > temp->y+temp->height/2) i=0;
            else if (data.x > temp->x+temp->width/2 && data.y >= temp->y+temp->height/2) i=1;
            else if (data.x > temp->x+temp->width/2 && data.y <= temp->y+temp->height/2) i=2;
            temp=temp->children[i];
        }
        temp->insert(data);
    }
    /// Fa mélységének visszaadása.
    /// @return Fa mélysége.
    unsigned depth() const{
        if (root==NULL) return 0;
        unsigned max=0;
        for (iterator iter=begin(); iter!=end(); ++iter){
            if (max < (*iter).level)
                max=(*iter).level;
        }
        return max;
    }
    
    /// Fában lévő elemek megszámolása.
    /// @return Fa elemszáma.
    unsigned countNodes() const{
        unsigned nodes=0;
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
    /// @return Az utolsó elem után mutat.
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
    /// @return Következő elem 
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
    /// @return Következő elem.
    iterator operator++(int){return ++(*this);}
    /// Egyenlőség operátor
    /// @return Igaz, ha megegyezik az csomópont.
    bool operator==(const iterator& iter){
        return Node==iter.Node;
    }
    /// @return Igaz, ha nem egyezik meg a csomópont.
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

/// Csomópont kiírása.
template <class T>
std::ostream& operator<<(std::ostream & os, const QuadTreeNode<T> & node){
    if (node.hasData()){
        for (size_t i=0; i<node.number_of_points; ++i){
            for (unsigned i=0; i<node.level; ++i) os << ' ';
            os << "(" << node.point[i].x << ";" << node.point[i].y << "): " << node.point[i].data << std::endl;
        }
    }
    return os;
}