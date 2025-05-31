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

// Typedef Iniziali
typedef int Quantity; // Alias Int
typedef string Label; // Alias String
const int MAX = 100000000; // Big Int

struct cItemVertex; // forward declaration per utilizzarlo

typedef cItemVertex* cItemGraph;
const cItemGraph emptyGraph = nullptr; // Alias Nullptr

// Lista Ordinata che memorizza le dipendenze
struct usedByNode{
        cItemVertex* dependent; // Vertice dipendente
        usedByNode* next;       // next
        usedByNode* prev;       // prev
};
typedef usedByNode* usedByList;

// Tipo item Base
struct bItemNode{
    Label label;       // Label
    Quantity quantity; // Quantita' disponibile
    bool visited;      // Flag isVisited
    usedByList usedBy; // lista che memorizza le dipendenze
};
typedef bItemNode* bItem;

// Array ordinato globale degli item base
struct bItemStorage{
    bItem items;                       // Elementi di tipo bItemNode(Label, Quantity, isVisited, usedBy)
    int size;                          // Size
    int capacity;                      // MaxSize
};
typedef bItemStorage* bItemStoragePtr;

// Grafo CompositeItem - Contiene tutti gli item composti e le loro relative dipendenze
struct cItemVertex{
    struct cItemEdge{                   // Lista di Adiacenza degli Item composti richiesti
        cItemVertex* cItemRequired;     // Puntatore ad un Vertice del Grafo degli Item Composti
        Quantity quantityRequired;      // Quantita' richiesta di tale Item (etichetta arco)
        cItemEdge* next;                // Puntatore all'arco successivo
    };
    typedef cItemEdge* cItemList;
    
    struct bItemEdge{                   // Lista di Adiacenza degli Item base richiesti
        bItem bItemRequired;            // Puntatore all'elemento nell'Array Ordinato degli Item Base
        Quantity quantityRequired;      // Quantita' richiesta di tale Item (etichetta arco)
        bItemEdge* next;                // Puntatore all'arco successivo
    };
    typedef bItemEdge* bItemList;

    Label label;           // Label del Vertice
    Quantity quantity;     // Quantita' del Nodo
    bool visited;          // Flag isVisited

    cItemList compList;    // altri item composti se richiesti
    bItemList baseList;    // item base richiesti per questo item composto
    usedByList usedBy;     // lista che memorizza le dipendenze

    cItemVertex* next;     // Puntatore a vertice successivo
};

struct industry::st_Industry {
  cItemGraph composedItems;   // Grafo Item Complessi
  bItemStorage baseItems;     // Array Item Base
};

```
### 📄 Documentazione

``` text
    In questo laboratorio ci proponiamo di progettare e implementare una struttura dati
    a supporto della gestione dei processi produttivi di un’industria semplificata. 
    L’industria è in grado di fabbricare oggetti, detti item, i quali possono essere di due tipi:

    • Basic item: oggetti elementari, disponibili inizialmente in quantità finita, 
      che non dipendono da altri item per essere ottenuti;
    • Item composti: oggetti che possono essere prodotti solo a partire da uno 
      o più altri item (basic o composti), secondo una specifica relazione di dipendenza.

    Nella struttura dati vengono registrati gli item che l’industria può produrre e, per ciascuno, 
    l’elenco degli altri item necessari alla sua fabbricazione.

```
##### 🛠️ Operazioni Richieste
``` text

    • Creare una nuova industria inizialmente vuota.
    • Inserire nuovi item:
        – Basic item, cioè oggetti senza dipendenze;
        – Item composti, definiti a partire da un insieme non vuoto di altri item (le componenti).
    • Verificare la presenza di un item dato il suo nome.
    • Rimuovere un item, eliminando ricorsivamente anche tutti gli item che ne dipendono 
      direttamente o indirettamente.
    • Aggiornare la quantità di un basic item, sommando (o sottraendo) un valore intero specificato. 
      La quantità non può mai diventare negativa.
    • Ottenere le dipendenze dirette di un item: data la descrizione dell’industria, 
      è possibile ottenere la lista degli item necessari per produrre un certo item.
    • Ottenere gli item che dipendono da un dato item, sia in modo diretto (immediato)
      sia lungo una catena di dipendenze (indiretto).
    • Calcolare quante unità di un certo item è possibile produrre, date le quantità 
      attualmente disponibili dei basic item.

```
