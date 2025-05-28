#include <iostream>
#include "industry.h"

using namespace industry;

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

    return 0;
}