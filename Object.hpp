template <typename T>
class QuadTree;

template <typename T>
class QuadTreeNode;


template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTree<T> &);

template <typename T>
std::ostream& operator<<(std::ostream &,const QuadTreeNode<T> &);

class Point{
    int x, y;
public:
    Point(int x=0, int y=0): x(x), y(y){}
    //int getX(){return x;}
    //int getY(){return y;}
    bool operator==(Point obj){
        return (x==obj.x && y==obj.y);
    }
    friend QuadTree<Point>;
    friend QuadTreeNode<Point>;
};

template <>
class QuadTreeNode<Point>{
    /// Szülő.
    QuadTreeNode *parent;
    /// Négy gyerek.
    QuadTreeNode *children[4];
    /// A 2D terület mérete.
    int width, height;
    /// Pont.
    Point data;
    /// Van-e adattagja?
    bool hasdata;
    /// Fában lévő szintje
    unsigned int level;
    /// Nincs paraméter nélküli konstruktora.
    QuadTreeNode();
    /// QuadTree hozhat létre új csomópontot. (Adat nélkül)
    QuadTreeNode<Point>(unsigned int level=0, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, hasdata(false), level(level){}
    /// QuadTree hozhat létre új csomópontot. (Adattal)
    QuadTreeNode(Point Data, unsigned int level=0, QuadTreeNode *parent=NULL): parent(parent), children{NULL, NULL, NULL, NULL}, data(Data), hasdata(true),level(level){}
    /// Destruktor. (delete NULL; esetén nincs probléma, nem kell vizsgálni)
    ~QuadTreeNode(){
        for (size_t i=0; i<4; ++i)
            delete children[i];
    }
public:
    /// @return - A csomópont rendelkezik-e adattal?
    bool hasData() const{return hasdata;}
    /// @return - Adat
    Point getData() const{
        if (hasData())
            return data;
        else throw "This node has no data.";
    }
    /// @return - Melyik szinten van?
    unsigned int getLevel() const{return level;}
    /// Adat beszúrása.
    /// @param - Adat
    void insert(Point point){
        if (point==data)
            return;
        //bool top = point.y >
        //bool left
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
    
    friend class QuadTree<Point>;
    friend std::ostream& operator<< <Point>(std::ostream &, const QuadTreeNode<Point> &);
};

template <>
class QuadTree<Point>{
    /// Fa gyökerére mutató pointer.
    QuadTreeNode<Point> *root;
public:
    QuadTree(){
        root = new QuadTreeNode<Point>(0, NULL);
    }
    /// Konstruktor. (Adattal)
    QuadTree(Point Data){
        root = new QuadTreeNode<Point>(Data);
    }
    /// Destruktor.
    ~QuadTree(){delete root;}
    /// @return - Gyökérre mutató pointer.
    QuadTreeNode<Point>* getRootNode(){return root;}
    /// Új elem beszúrása
    void insert(Point Data){
        root->insert(Data);
    }
    /// Fa mélységének visszaadása rekurzív függvényhívással.
    /// @return - Fa mélysége
    unsigned int depth(){return root->depth();}
    
     /// Fa iterátor.
    class iterator;
    /// @return - Legbaloldalibb levél.
    template <class T>
    typename QuadTree<T>::iterator begin() const{
        QuadTreeNode<Point> *temp=root;
        while (!temp->isLeaf())
            temp=temp->children[0];
        return QuadTree<T>::iterator(temp);
    }
    /// @return - Az utolsó elem után mutat.
    template <class T>
    typename QuadTree<T>::iterator end() const{return QuadTree<T>::iterator(NULL);}
    
    friend class QuadTreeNode<Point>;
    friend std::ostream& operator<< <Point>(std::ostream &,const QuadTree<Point> &);
};