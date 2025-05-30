#include <iostream>
#include "industry.h"

using namespace industry;

void printIndustry(const Industry& indus);
int howMany(const Industry& indus, const std::string& name);

int main() {
    Industry indus = createEmptyIndustry();

    // === INSERIMENTO MATERIALI BASE ===
    std::cout << "[+] Inserimento materiali base\n";
    std::cout << (insertBasicItem(indus, "ferro")     ? "✅ ferro inserito\n"     : "❌ ferro errore\n");
    std::cout << (insertBasicItem(indus, "carbone")   ? "✅ carbone inserito\n"   : "❌ carbone errore\n");
    std::cout << (insertBasicItem(indus, "rame")      ? "✅ rame inserito\n"      : "❌ rame errore\n");
    std::cout << (insertBasicItem(indus, "cromo")     ? "✅ cromo inserito\n"     : "❌ cromo errore\n");
    std::cout << (insertBasicItem(indus, "nichel")    ? "✅ nichel inserito\n"    : "❌ nichel errore\n");
    std::cout << (insertBasicItem(indus, "manganese") ? "✅ manganese inserito\n" : "❌ manganese errore\n");
    std::cout << (insertBasicItem(indus, "silicio")   ? "✅ silicio inserito\n"   : "❌ silicio errore\n");
    std::cout << (insertBasicItem(indus, "alluminio") ? "✅ alluminio inserito\n" : "❌ alluminio errore\n");
    std::cout << (insertBasicItem(indus, "zinco")     ? "✅ zinco inserito\n"     : "❌ zinco errore\n");
    std::cout << (insertBasicItem(indus, "carbonio")  ? "✅ carbonio inserito\n"  : "❌ carbonio errore\n");

    // === MODIFICA QUANTITÀ BASE ===
    std::cout << "\n[+] Aggiunta quantità ai materiali base\n";
    std::cout << (addBasicItem(indus, "ferro", 50)     ? "✅ ferro +50\n" : "❌ ferro errore\n");
    std::cout << (addBasicItem(indus, "carbone", 30)   ? "✅ carbone +30\n" : "❌ carbone errore\n");
    std::cout << (addBasicItem(indus, "rame", 20)      ? "✅ rame +20\n" : "❌ rame errore\n");
    std::cout << (addBasicItem(indus, "cromo", 10)     ? "✅ cromo +10\n" : "❌ cromo errore\n");
    std::cout << (addBasicItem(indus, "nichel", 5)     ? "✅ nichel +5\n" : "❌ nichel errore\n");
    std::cout << (addBasicItem(indus, "carbonio", 30)   ? "✅ carbone +30\n" : "❌ carbone errore\n");

    // === INSERIMENTO LEGHE ===
    std::cout << "\n[+] Inserimento leghe\n";
    std::string lega1[] = {"ferro", "carbonio"};
    std::cout << (insertItem(indus, "acciaio", lega1, 2) ? "✅ acciaio inserito\n" : "❌ acciaio errore\n");

    std::string lega2[] = {"ferro", "carbonio", "cromo", "nichel"};
    std::cout << (insertItem(indus, "acciaio_inox", lega2, 4) ? "✅ acciaio_inox inserito\n" : "❌ acciaio_inox errore\n");

    std::string lega3[] = {"rame", "zinco"};
    std::cout << (insertItem(indus, "ottone", lega3, 2) ? "✅ ottone inserito\n" : "❌ ottone errore\n");

    std::string lega4[] = {"ferro", "carbonio", "manganese"};
    std::cout << (insertItem(indus, "acciaio_manganese", lega4, 3) ? "✅ acciaio_manganese inserito\n" : "❌ acciaio_manganese errore\n");

    // Fallimento (magnesio non presente)
    // std::string lega_fallita[] = {"alluminio", "rame", "magnesio"};
    // std::cout << (insertItem(indus, "lega_alluminio", lega_fallita, 3) ? "✅ lega_alluminio inserita\n" : "❌ lega_alluminio errore\n");

    // === TEST SU QUANTITÀ COMPONIBILI (devono fallire) ===
    // std::cout << "\n[~] Test falliti su composti (non modificabili direttamente)\n";
    // std::cout << (addBasicItem(indus, "acciaio", 10) ? "✅ acciaio +10\n" : "❌ acciaio errore\n");

    // === INSERIMENTO PEZZI INDUSTRIALI COMPOSITI ===
    std::cout << "\n[+] Inserimento componenti industriali\n";
    std::string comp1[] = {"acciaio", "rame"};
    std::cout << (insertItem(indus, "piastra_metallica", comp1, 2) ? "✅ piastra_metallica inserita\n" : "❌ piastra_metallica errore\n");

    std::string comp2[] = {"acciaio_inox", "manganese"};
    std::cout << (insertItem(indus, "componente_resistente", comp2, 2) ? "✅ componente_resistente inserito\n" : "❌ componente_resistente errore\n");

    std::string comp3[] = {"acciaio_manganese", "alluminio"};
    std::cout << (insertItem(indus, "struttura_leggera", comp3, 2) ? "✅ struttura_leggera inserita\n" : "❌ struttura_leggera errore\n");

    // Fallimento: magnesio non esiste
    std::string comp_fallito[] = {"lega_alluminio", "magnesio"};
    // std::cout << (insertItem(indus, "prodotto_invalido", comp_fallito, 2) ? "✅ prodotto_invalido inserito\n" : "❌ prodotto_invalido errore\n");

    // === TEST DIPENDENZE ===
    std::cout << "\n[🔍] Test dipendenze\n";
    list::List lres;
    if (listNeed(indus, "acciaio", lres)) {
        std::cout << "Dipendenze dirette di acciaio: " << list::toString(lres) << "\n";
    }

    std::cout << "\n[🔍] Test dipendenze\n";
    list::List l1;
    if (listNeed(indus, "piastra_metallica", l1)) {
        std::cout << "Dipendenze dirette di piastra_metallica: " << list::toString(l1) << "\n";
    }

    list::List l2 = list::createEmpty();
    if (listNeededBy(indus, "ferro", l2)) {
        std::cout << "Elementi che dipendono direttamente da ferro: " << list::toString(l2) << "\n";
    }

    list::List l3 = list::createEmpty();
    if (listNeededByChain(indus, "ferro", l3)) {
        std::cout << "Elementi che dipendono indirettamente da ferro: " << list::toString(l3) << "\n";
    }

    // === STAMPA INDUSTRIA COMPLETA ===
    std::cout << "\n[📦] Stato completo dell'industria:\n";
    printIndustry(indus);

    cout << "Ferro prima di howManyItem: "<< howMany(indus, "ferro") << endl;
    cout << "Carbonio prima di howManyItem: "<< howMany(indus, "carbonio") << endl;
    cout << "Acciaio prima di howManyItem: "<< howMany(indus, "acciaio") << endl;
    cout << "Acciao Inox prima di howManyItem: "<< howMany(indus, "acciaio_inox") << endl;
    cout << "Piastra Metallica prima di howManyItem: "<< howMany(indus, "piastra_metallica") << endl;
    cout << "Struttura Leggera prima di howManyItem: "<< howMany(indus, "struttura_leggera") << endl;


    // === TEST howManyItem ===
    std::cout << "\n[🔢] Test howManyItem\n";
    unsigned res;
    
    if (howManyItem(indus, "ferro", res)) {
        std::cout << "✅ Si possono produrre " << res << " unita' di 'ferro'\n";
    } else {
        std::cout << "❌ Errore nel calcolo di 'ferro'\n";
    }

    if (howManyItem(indus, "acciaio", res)) {
        std::cout << "✅ Si possono produrre " << res << " unita' di 'acciaio'\n";
    } else {
        std::cout << "❌ Errore nel calcolo di 'acciaio'\n";
    }

    if (howManyItem(indus, "acciaio_inox", res)) {
        std::cout << "✅ Si possono produrre " << res << " unita' di 'acciaio_inox'\n";
    } else {
        std::cout << "❌ Errore nel calcolo di 'acciaio_inox'\n";
    }

    if (howManyItem(indus, "piastra_metallica", res)) {
        std::cout << "✅ Si possono produrre " << res << " unita' di 'piastra_metallica'\n";
    } else {
        std::cout << "❌ Errore nel calcolo di 'piastra_metallica'\n";
    }

    if (howManyItem(indus, "struttura_leggera", res)) {
        std::cout << "✅ Si possono produrre " << res << " unita' di 'struttura_leggera'\n";
    } else {
        std::cout << "❌ Errore nel calcolo di 'struttura_leggera'\n";
    }

    if (howManyItem(indus, "lingotto_oro", res)) {
        std::cout << "❌ 'lingotto_oro' non dovrebbe esistere, ma la funzione ha restituito: " << res << "\n";
    } else {
        std::cout << "✅ 'lingotto_oro' non esiste: risultato corretto (res = 0)\n";
    }

    cout << endl;
    cout << "Ferro dopo howManyItem: "<< howMany(indus, "ferro") << endl;
    cout << "Carbonio dopo di howManyItem: "<< howMany(indus, "carbonio") << endl;
    cout << "Acciaio dopo di howManyItem: "<< howMany(indus, "acciaio") << endl;
    cout << "Acciao Inox prima di howManyItem: "<< howMany(indus, "acciaio_inox") << endl;
    cout << "Piastra Metallica prima di howManyItem: "<< howMany(indus, "piastra_metallica") << endl;
    cout << "Struttura Leggera prima di howManyItem: "<< howMany(indus, "struttura_leggera") << endl;

    // === RIMOZIONI ===
    std::cout << "\n[✂️] Rimozione elementi\n";

    std::cout << "- Rimozione materiale senza dipendenti (zinco): ";
    std::cout << (removeItem(indus, "zinco") ? "✅ Rimosso\n" : "❌ Non trovato\n");

    std::cout << "- Rimozione materiale con dipendenti (ferro): ";
    std::cout << (removeItem(indus, "ferro") ? "✅ Rimosso con dipendenti\n" : "❌ Non trovato\n");

    std::cout << "- Rimozione lega con dipendenti (acciaio): ";
    std::cout << (removeItem(indus, "acciaio") ? "✅ Rimosso con dipendenti\n" : "❌ Non trovato\n");

    std::cout << "- Rimozione prodotto composito (struttura_leggera): ";
    std::cout << (removeItem(indus, "struttura_leggera") ? "✅ Rimosso\n" : "❌ Non trovato\n");

    std::cout << "- Rimozione elemento inesistente (oro): ";
    std::cout << (removeItem(indus, "oro") ? "✅ Rimosso\n" : "❌ Non trovato\n");

    std::cout << "\n[✔️] Fine dei test.\n";
    return 0;
}