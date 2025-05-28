# 📚 Repository Laboratorio Individuale - ASD

💻 Computer Science - UniGe 🇮🇹

## 🧑‍💻 Owner

- [Baldini Filippo](mailto:6393212@studenti.unige.it)

## 🔗 Link Utili

- [Repository Universitaria Generale](https://github.com/filippob04/uni-24-25)
- [Repository ASD Generale](https://github.com/filippob04/ASD-24-25)

``` CPP

/**********************************************************************/
/*                     Definizione Struttura Dati                     */
/**********************************************************************/

typedef int Quantity;
typedef string Label;

struct cItemVertex; 
typedef cItemVertex* cItemGraph;

const cItemGraph emptyGraph = nullptr;

// Lista Ordinata che memorizza le dipendenze
struct usedByNode{
        cItemVertex* dependent; 
        usedByNode* next;
        usedByNode* prev;
};
typedef usedByNode* usedByList;

// Tipo item base
struct bItemNode{
    Label label;
    Quantity quantity;
    usedByList usedBy; // lista che memorizza le dipendenze
};
typedef bItemNode* bItem;

// Array globale degli item base
struct bItemStorage{
    bItem items;
    int size;
    int capacity;
};
typedef bItemStorage* bItemStoragePtr;

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

    Label label;           // Label del Vertice
    Quantity quantity;     // Quantita' del Nodo
    bool visited;          // Variabile isVisited

    cItemList compList;    // altri item composti se richiesti
    bItemList baseList;    // item base richiesti per questo item composto
    usedByList usedBy;     // lista che memorizza le dipendenze

    cItemVertex* next;
};

struct industry::st_Industry {
  cItemGraph composedItems;   // Grafo Item Complessi
  bItemStorage baseItems;     // Array Item Base
};

```