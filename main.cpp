#include <iostream>
#include "industry.h"

using namespace industry;
void printIndustry(const Industry& indus);

int main() {
    Industry indus = createEmptyIndustry();

    // Inserimento item base
    std::cout << (insertBasicItem(indus, "ferro") ? "ferro OK\n" : "ferro ERRORE\n");
    std::cout << (insertBasicItem(indus, "carbone") ? "carbone OK\n" : "carbone ERRORE\n");
    std::cout << (insertBasicItem(indus, "rame") ? "rame OK\n" : "rame ERRORE\n");

    // Modifica quantità item base
    std::cout << (addBasicItem(indus, "ferro", 10) ? "ferro +10 OK\n" : "ferro +10 ERRORE\n");
    std::cout << (addBasicItem(indus, "carbone", 5) ? "carbone +5 OK\n" : "carbone +5 ERRORE\n");
    std::cout << (addBasicItem(indus, "rame", -3) ? "rame -3 OK\n" : "rame -3 ERRORE\n");  // deve rimanere 0 se negativo

    // Controllo presenza item
    std::cout << (isPresentItem(indus, "ferro") ? "ferro presente\n" : "ferro assente\n");
    std::cout << (isPresentItem(indus, "acciaio") ? "acciaio presente\n" : "acciaio assente\n");

    // Inserimento item composto: acciaio = ferro + carbone
    std::string comp1[] = {"ferro", "carbone"};
    std::cout << (insertItem(indus, "acciaio", comp1, 2) ? "acciaio OK\n" : "acciaio ERRORE\n");

    // Tentativo di modifica quantità su item composto (deve fallire)
    std::cout << (addBasicItem(indus, "acciaio", 5) ? "acciaio +5 OK\n" : "acciaio +5 ERRORE\n");

    // Inserimento item composto: piastra = acciaio + rame
    std::string comp2[] = {"acciaio", "rame"};
    std::cout << (insertItem(indus, "piastra", comp2, 2) ? "piastra OK\n" : "piastra ERRORE\n");

    // Inserimento fallito: componente mancante petrolio
    std::string comp3[] = {"ferro", "petrolio"};
    std::cout << (insertItem(indus, "motore", comp3, 2) ? "motore ERRORE\n" : "motore fallito OK\n");

    list::List lres;
    if (listNeed(indus, "acciaio", lres)) {
        std::cout << "Dipendenze dirette di acciaio: " << list::toString(lres) << std::endl;
    } else {
        std::cout << "Elemento 'acciaio' non trovato." << std::endl;
    }

        std::cout << "\nTest listNeededBy su item base:\n";
    list::List deps1 = list::createEmpty();
    if (listNeededBy(indus, "ferro", deps1)) {
        std::cout << "Elementi che dipendono da 'ferro': " << list::toString(deps1) << std::endl;
    } else {
        std::cout << "'ferro' non trovato.\n";
    }

    std::cout << "\nTest listNeededBy su item composto:\n";
    list::List deps2 = list::createEmpty();
    if (listNeededBy(indus, "acciaio", deps2)) {
        std::cout << "Elementi che dipendono da 'acciaio': " << list::toString(deps2) << std::endl;
    } else {
        std::cout << "'acciaio' non trovato.\n";
    }

    std::cout << "\nTest listNeededBy su item inesistente:\n";
    list::List deps3 = list::createEmpty();
    if (listNeededBy(indus, "oro", deps3)) {
        std::cout << "Elementi che dipendono da 'oro': " << list::toString(deps3) << std::endl;
    } else {
        std::cout << "'oro' non trovato.\n";
    }
    
    // Stampa finale dello stato dell'industry
    printIndustry(indus);
    return 0;
}