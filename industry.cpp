#include "industry.h"
#include <iostream>
using namespace std;
using namespace industry;

/**********************************************************************/
/*                     Definizione Struttura Dati                     */
/**********************************************************************/

// Typedef Iniziali
typedef int Quantity;
typedef string Label;

struct cItemVertex; // forward declaration per utilizzarlo

typedef cItemVertex* cItemGraph;
const cItemGraph emptyGraph = nullptr;

// Lista Ordinata che memorizza le dipendenze
struct usedByNode{
        cItemVertex* dependent; 
        usedByNode* next;
        usedByNode* prev;
};
typedef usedByNode* usedByList;

// Tipo item Base
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


/**********************************************************************/
/*                       Funzioni Ausiliarie                          */
/**********************************************************************/

bool bIsEmpty(const bItemStorage& s){
    return s.size == 0;
}

bool cIsEmpty(const cItemGraph& g){
    return g == emptyGraph;
}

// Funzione Ausiliaria BinarySearch
bItem findBasicItem(const bItemStorage& s, int start, int end, Label l){
    if(bIsEmpty(s)){return nullptr;} // Caso Array vuoto
    if(start > end){ // caso base
        return nullptr;
    }

    int mid = (start+end)/2; // calcolo mid

    if(s.items[mid].label == l){return &s.items[mid];} // Se trovo l'elemento
    if(l > s.items[mid].label){
        return findBasicItem(s, mid + 1, end, l); // Cerco a destra
    } else{
        return findBasicItem(s, start, mid - 1, l); // Cerco a sinistra
    }
}

// Funzione Ausiliaria FindVertex
cItemGraph findCompItem(const cItemGraph& g, Label l){
    if(cIsEmpty(g)){return emptyGraph;} // Caso grafo vuoto

    cItemGraph cur = g;
    while(cur){
        if(cur->label == l){return cur;}
        cur = cur->next;
    }

    return emptyGraph;
}

void addBItemEdge(cItemGraph& g, bItem b, Quantity q) {
    cItemVertex::bItemList newEdge = new cItemVertex::bItemEdge;
    newEdge->bItemRequired = b;
    newEdge->quantityRequired = q;
    newEdge->next = nullptr;

    // Inserimento ordinato per label nella lista di adiacenza
    if(!g->baseList || g->baseList->bItemRequired->label > b->label){  // HeadInsert
        newEdge->next = g->baseList;
        g->baseList = newEdge;
    } else{
        cItemVertex::bItemList cur = g->baseList;
        while(cur->next && cur->next->bItemRequired->label < b->label){cur = cur->next;}
        newEdge->next = cur->next;
        cur->next = newEdge;
    }

    usedByList newList = new usedByNode;
    newList->dependent = g;
    newList->next = b->usedBy;
    newList->prev = nullptr;

    // Inserimento ordinato per label nella lista di dipendenza
    if(!b->usedBy || b->usedBy->dependent->label > g->label){  // HeadInsert
        newList->next = b->usedBy;
        if(b->usedBy){b->usedBy->prev = newList;}
        b->usedBy = newList;
    } else{
        usedByList cur = b->usedBy;
        while(cur->next && cur->next->dependent->label < g->label){cur = cur->next;}
        newList->next = cur->next;
        if(cur->next){cur->next->prev = newList;}
        cur->next = newList;
        newList->prev = cur;
    }
}

void addCItemEdge(cItemGraph& g, cItemGraph c, Quantity q){
    cItemVertex::cItemList newEdge = new cItemVertex::cItemEdge;
    newEdge->cItemRequired = c;
    newEdge->quantityRequired = q;
    newEdge->next = nullptr;

    // Inserimento ordinato per label nella lista di adiacenza
    if(!g->compList || g->compList->cItemRequired->label > c->label){ // HeadInsert
        newEdge->next = g->compList;
        g->compList = newEdge;
    } else{
        cItemVertex::cItemList cur = g->compList;
        while(cur->next && cur->next->cItemRequired->label < c->label){cur = cur->next;}
        newEdge->next = cur->next;
        cur->next = newEdge;
    }

    usedByList newList = new usedByNode;
    newList->dependent = g;
    newList->next = c->usedBy;
    newList->prev = nullptr;

    // Inserimento ordinato per label nella lista di dipendenza
    if(!c->usedBy || c->usedBy->dependent->label > g->label){  // HeadInsert
        newList->next = c->usedBy;
        if(c->usedBy){c->usedBy->prev = newList;}
        c->usedBy = newList;
    } else{
        usedByList cur = c->usedBy;
        while(cur->next && cur->next->dependent->label < g->label){cur = cur->next;}
        newList->next = cur->next;
        if(cur->next){cur->next->prev = newList;}
        cur->next = newList;
        newList->prev = cur;
    }
}

void printIndustry(const Industry& indus){ // Ricopiata nel main, sarebbe necessario includerla nel .h
    bItemStorage& s = indus->baseItems;
    cItemGraph& g = indus->composedItems;
    
    bool isFirst = true;
    cout << endl;
    cout << "/**********************************************************************/" << endl;
    cout << "/*************************** Basic Items ******************************/" << endl;
    cout << "/**********************************************************************/" << endl;
    cout << endl;

    for(int i = 0; i < s.size; i++){
        if(!isFirst){cout << ", ";}
        isFirst = false;

        cout << s.items[i].label;
    }

    cout << endl;

    cout << endl;
    cout << "/**********************************************************************/" << endl;
    cout << "/************************* Composite Items ****************************/" << endl;
    cout << "/**********************************************************************/" << endl;
    cout << endl;

    isFirst = true;
    cItemGraph cur = g;
    while(cur){
        if(!isFirst){cout << ", ";}
        isFirst = false;

        cout << cur->label;
        cur = cur->next;
    }

    cout << endl;
    
    cout << endl;
}

// Funzione Ausiliaria per trovare l'indice nell'array
int findBasicItemIndex(const bItemStorage& s, int start, int end, const Label l){
    if(start > end || bIsEmpty(s)){return -1;}

    int mid = (start + end)/2;

    if(s.items[mid].label == l){return mid;}
    if(l > s.items[mid].label){
        return findBasicItemIndex(s, mid + 1, end, l);
    } else{
        return findBasicItemIndex(s, start, mid - 1, l);
    }
}

bool deleteB(bItemStorage& s, const Label& name){
    int pos = findBasicItemIndex(s, 0, s.size - 1, name);
    if(pos == -1){return false;} // Se posizione non valida

    // Svolgo lo shift a sinistra per l'eliminazione dell'elemento
    for(int i = pos; i < s.size - 1; i++){
        s.items[i] = s.items[i + 1];
    }

    s.size--;
    return true;
}

bool deleteC(cItemGraph& g, const Label& name){
    if(cIsEmpty(g)){return false;}

    // Se il nodo da eliminare e' il primo
    if(g->label == name){
        cItemGraph temp = g;
        g = g->next;

        // Dealloca compList
        while(temp->compList){
            cItemVertex::cItemList next = temp->compList->next;
            delete temp->compList;
            temp->compList = next;
        }

        // Dealloca baseList
        while(temp->baseList){
            cItemVertex::bItemList next = temp->baseList->next;
            delete temp->baseList;
            temp->baseList = next;
        }

        delete temp;
        return true;
    }

    // Oppure cerco il nodo nella lista
    cItemGraph prev = g;
    cItemGraph cur = g->next;

    while(cur){
        if(cur->label == name){
            prev->next = cur->next;

            // Dealloca compList
            while(cur->compList){
                cItemVertex::cItemList next = cur->compList->next;
                delete cur->compList;
                cur->compList = next;
            }

            // Dealloca baseList
            while(cur->baseList){
                cItemVertex::bItemList next = cur->baseList->next;
                delete cur->baseList;
                cur->baseList = next;
            }

            delete cur;
            return true;
        }

        prev = cur;
        cur = cur->next;
    }

    return false; // Item non trovato
}

/**********************************************************************/
/*                    Implementazione Funzioni                        */
/**********************************************************************/

// Crea e restituisce un'istanza vuota di Industry.
Industry industry::createEmptyIndustry(){
    Industry newIndustry = new st_Industry();

    newIndustry->composedItems = nullptr; // Lista Item Composti

    newIndustry->baseItems.items = nullptr; // Array Item Base
    newIndustry->baseItems.size = 0;
    newIndustry->baseItems.capacity = 0;

    return newIndustry;
}

// Inserisce un nuovo basic item di nome 'name' nell'industria.
// Se esiste gia' un item con quel nome, la funzione restituisce false e non fa nulla.
// Altrimenti inserisce l'item e restituisce true.
// Si assume che, quando viene inserito un basic item, la quantita iniziale sia 0.
bool industry::insertBasicItem(Industry& indus, std::string name){
    bItemStorage& s = indus->baseItems;

    // Creazione di uno storage se vuoto
    if(bIsEmpty(s)){
        s.capacity = 10;
        s.size = 0;
        s.items = new bItemNode[s.capacity];

        s.items[0].label = name;
        s.items[0].quantity = 0;
        s.items[0].usedBy = nullptr;

        s.size++;

        return true;
    }

    if(findBasicItem(s, 0, s.size - 1, name) != nullptr){return false;} // Verifico se e' gia' presente

    // Aumento la capacita' se necessario
    if(s.size == s.capacity){
    int newCapacity = s.capacity * 2;
    bItem newArray = new bItemNode[newCapacity];

    int i = 0, j = 0;
    bool inserted = false;

    while(i < s.size){ // Gestisco la copia e inserendo adeguatamente il valore
        if(!inserted && s.items[i].label > name){ // Quando trovo la posizione giusta per inserirlo
            newArray[j].label = name;
            newArray[j].quantity = 0;
            newArray[j].usedBy = nullptr;
            
            j++;
            inserted = true;
        }

        newArray[j++] = s.items[i++]; // Copio l'array
    }

    // Se e' un elemento che va inserito nel'ultima posizione:
    if(!inserted){
        newArray[j].label = name;
        newArray[j].quantity = 0;
        newArray[j].usedBy = nullptr;
    }

    delete[] s.items; // Elimino l'array originale

    s.items = newArray;
    s.capacity = newCapacity;
    s.size++; // incremento la size

    return true;
}

    // Svolgo lo shift a destra per l'inserimento del nuovo elemento
    int i = s.size - 1;
    while(i >= 0 && s.items[i].label > name){
        s.items[i + 1] = s.items[i];
        i--;
    }

    s.items[i + 1].label = name;
    s.items[i + 1].quantity = 0;
    s.items[i + 1].usedBy = nullptr;

    s.size++;

    return true;
}

// Inserisce un nuovo item di nome 'name' nell'industria.
// 'components' e' un array NON VUOTO di lunghezza 's' che contiene i nomi degli item
// da cui dipende il nuovo item.
// Se esiste gia' un item con quel nome, la funzione restituisce false e non fa nulla.
// Se uno qualsiasi degli item indicati in 'components' non esiste nell'industria,
// la funzione restituisce false e non fa nulla.
// Altrimenti inserisce l'item e restituisce true.
bool industry::insertItem(Industry& indus, std::string name, std::string* components, size_t s){
    bItemStorage& arr = indus->baseItems;
    cItemGraph& g = indus->composedItems;

    if(findCompItem(g, name)){return false;} // Se esiste gia' questo componente -> false

    // Creo degli array temporanei di supporto per evitare ricerche ripetute
    bItem* B = new bItem[s];
    cItemGraph* C = new cItemGraph[s];
    
    // Verifico che gli item passati da input esistano -> true ? false
    for(int i = 0; i < s; i++){
        B[i] = findBasicItem(arr, 0, arr.size - 1, components[i]);
        C[i] = findCompItem(g, components[i]);

        if(!B[i] && !C[i]){
            delete[] B;
            delete[] C;
            
            return false;
        }
    }

    // A questo punto creo il nuovo vertice
    cItemGraph newVertex = new cItemVertex;

    newVertex->label = name;
    newVertex->quantity = 0;
    newVertex->visited = false;

    newVertex->baseList = nullptr;
    newVertex->compList = nullptr;
    newVertex->usedBy = nullptr;    
    newVertex->next = g;
    
    g = newVertex; // HeadInsert

    // Gestisco le liste di adiacenza
    for(int i = 0; i < s; i++){
        if(B[i]){
            addBItemEdge(newVertex, B[i], 1);
        } else{
            addCItemEdge(newVertex, C[i], 1);
        }
    }

    return true;
}

// Restituisce true se esiste un item con il nome 'name' nell'industria, false altrimenti.
bool industry::isPresentItem(const Industry& indus, std::string name){
    if(findBasicItem(indus->baseItems, 0, indus->baseItems.size - 1, name)){return true;}
    if(findCompItem(indus->composedItems, name)){return true;}

    return false;
}

// Rimuove l'item di nome 'name' dall'industria.
// Se esiste almeno un altro item che dipende direttamente o indirettamente da 'name',
// verra' rimosso anche quello.
// Se non esiste un item con quel nome, la funzione restituisce false e non fa nulla.
// Altrimenti, rimuove l'item (e quelli dipendenti) e restituisce true.
bool industry::removeItem(Industry& indus, std::string name){
    bItemStorage& arr = indus->baseItems;
    cItemGraph& g = indus->composedItems;

    bItem b = findBasicItem(arr, 0, arr.size - 1, name);
    cItemGraph c = findCompItem(g, name);

    if(!b && !c){return false;} // Item non trovato

    if(b){
        if(b->usedBy == nullptr){
            deleteB(arr, name);
        } else{
            usedByList cur = b->usedBy;
            b->usedBy = nullptr; 

            while(cur){
                Label depName = cur->dependent->label;
                usedByList next = cur->next;
                delete cur;

                removeItem(indus, depName);
                cur = next;
            }

            deleteB(arr, name);
        }
    } else{
        if(c->usedBy == nullptr){
            deleteC(g, name);
        } else{
            usedByList cur = c->usedBy;
            c->usedBy = nullptr; 

            while(cur){
                Label depName = cur->dependent->label;
                usedByList next = cur->next;
                delete cur;
                
                removeItem(indus, depName);
                cur = next;
            }

            deleteC(g, name);
        }
    }

    return true;
}

// Aumenta o diminuisce la quantita dell'item di base di nome 'name' di un valore 'v'.
// Se 'v' e' negativo e la quantita corrente e' Q, la nuova quantita sara' max(Q + v, 0).
// La quantita non puo' mai diventare negativa.
// Se non esiste un basic item con quel nome, la funzione restituisce false e non fa nulla.
// Altrimenti restituisce true.
bool industry::addBasicItem(Industry& indus, std::string name, int v){
    bItemStorage& s = indus->baseItems;
    bItem item = findBasicItem(s, 0, s.size - 1, name);

    if(!item){return false;} // Se l'item cercato non esiste -> false
    
    // Calcolo la variazione di quantita' come richiesto da specifica
    if(v < 0){
        item->quantity = (item->quantity + v > 0) ? (item->quantity + v) : 0;
    } else{
        item->quantity += v;
    }

    return true;
}

// Riempie la lista 'lres' (in ordine lessicografico) con i nomi degli item
// da cui l'item di nome 'name' dipende direttamente.
// Se l'item non esiste, la funzione restituisce false e imposta 'lres' a nullptr.
// Altrimenti restituisce true.
bool industry::listNeed(const Industry& indus, std::string name, list::List& lres){
    cItemGraph& g = indus->composedItems;

    lres = list::createEmpty(); // Inizializzo la lista di output

    cItemGraph c = findCompItem(g, name);
    if(cIsEmpty(c)){return false;} // caso base, elemento non trovato

    // Liste di adiacenza (ordinate)
    cItemVertex::bItemList bList = c->baseList;
    cItemVertex::cItemList cList = c->compList;

    while(bList && cList){
        Label bName = bList->bItemRequired->label;
        Label cName = cList->cItemRequired->label;
        if(bName < cName){
            list::addBack(bName, lres);
            bList = bList->next;
        } else{
            list::addBack(cName, lres);
            cList = cList->next;
        }
    }
    while (bList){
        list::addBack(bList->bItemRequired->label, lres);
        bList = bList->next;
    }
    while (cList){
        list::addBack(cList->cItemRequired->label, lres);
        cList = cList->next;
    }

    return true;
}

// Riempie la lista 'lres' (in ordine lessicografico) con i nomi degli item
// che dipendono direttamente dall'item di nome 'name'.
// Se l'item non esiste, la funzione restituisce false e imposta 'lres' a nullptr.
// Altrimenti restituisce true.
bool industry::listNeededBy(const Industry& indus, std::string name, list::List& lres){
    bItemStorage& s = indus->baseItems;
    cItemGraph& g = indus->composedItems;

    lres = list::createEmpty(); // Inizializzo la lista di output

    cItemGraph c = findCompItem(g, name);
    bItem b = findBasicItem(s, 0, s.size, name);

    if(!c && !b){return false;} // caso base, elemento non trovato

    if(b){
       usedByList cur = b->usedBy;
       while(cur){
        list::addBack(cur->dependent->label, lres);
        cur = cur->next;
       }
    } else{
        usedByList cur = c->usedBy;
        while(cur){
            list::addBack(cur->dependent->label, lres);
            cur = cur->next;
        }
    }

    return true;
}

// Riempie la lista 'lres' (in ordine lessicografico) con i nomi degli item
// che dipendono (direttamente o indirettamente) dall'item di nome 'name'.
// Esempio: se o1 dipende da o2 e o2 dipende da o3,
// allora listNeededByChain("o3") restituira' o2 e o1.
// Se invece si usa listNeededBy("o3"), la lista non includera' o1
// perche' non dipende direttamente da o3.
// Se l'item non esiste, la funzione restituisce false e imposta 'lres' a nullptr.
// Altrimenti restituisce true.
bool industry::listNeededByChain(const Industry& indus, std::string name, list::List& lres){return false;}

// Calcola e memorizza in 'res' il numero massimo di item di nome 'name'
// che si possono costruire con le quantita attualmente disponibili dei basic item.
// Se l'item non esiste, la funzione restituisce false e imposta 'res' a 0.
// Altrimenti restituisce true.
bool industry::howManyItem(const Industry& indus, std::string name, unsigned& res){return false;}