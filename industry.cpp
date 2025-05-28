// TO DO, vedi indicazioni in industry.h
typedef int Quantity;
typedef std::string Label;

// Tipo item base
struct bItemNode{
    Label label;
    Quantity quantity;
};
typedef bItemNode* bItem;

// Array globale degli item base
struct bItemStorage{
    bItem items;
    int size;
    int capacity;
};

// Grafo CompositeItem - Contiene tutti gli item composti e le loro relative dipendenze
struct cItemVertex{
    struct cItemEdge{                   // Lista di Adiacenza degli Item composti richiesti
        cItemVertex* cItemRequired;     // Puntatore ad un Vertice del Grafo degli Item Composti
        Quantity quantityRequired;      // Quantita' richiesta di tale Item (etichetta arco)
        cItemEdge* next;        
    };
    typedef cItemEdge* cItemList;
    
    struct bItemEdge{                   // Lista di Adiacenza degli Item base richiesti
        bItem bItemRequired;            // Puntatore al nodo nella lista doppiamente collegata degli Item Base
        Quantity quantityRequired;      // Quantita' richiesta di tale Item (etichetta arco)
        bItemEdge* next;
    };
    typedef bItemEdge* bItemList;

    struct usedByNode{                  // Lista che memorizza le dipendenze
        cItemVertex* dependent;
        usedByNode* next;
    };
    typedef usedByNode* usedByList;

    Label label;           // Label del Vertice
    Quantity quantity;     // Quantita' del Nodo
    bool visited;          // Variabile isVisited

    cItemList compList;    // altri item composti se richiesti
    bItemList baseList;    // item base richiesti per questo item composto
    usedByList usedBy;     // dipendenze

    cItemVertex* next;
};
typedef cItemVertex* cItemGraph;