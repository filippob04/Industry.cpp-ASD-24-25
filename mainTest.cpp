#include <iostream>
#include "industry.h"

int main() {
    using namespace std;
    using namespace industry;
    cout << boolalpha;

    Industry indus;
    unsigned i = 1;
    bool bres = false, breq = false;
    unsigned ires = 0, ireq = 0;

    indus = createEmptyIndustry();

    cout << "*************** Test " << i++ << ": insertBasicItem 'ferro' ****************" << endl;
    bres = insertBasicItem(indus, "ferro");
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": addBasicItem 'ferro', +50 ****************" << endl;
    bres = addBasicItem(indus, "ferro", 50);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": insertBasicItem 'carbonio' ****************" << endl;
    bres = insertBasicItem(indus, "carbonio");
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": insertItem 'acciaio' = ferro + carbonio ****************" << endl;
    std::string comp1[] = {"ferro", "carbonio"};
    bres = insertItem(indus, "acciaio", comp1, 2);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'acciaio' ****************" << endl;
    try {
        bres = howManyItem(indus, "acciaio", ires);
        breq = true;
        ireq = 0; // 50 ferro, 0 carbonio ⇒ 0 acciaio
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": addBasicItem 'carbonio', +50 ****************" << endl;
    bres = addBasicItem(indus, "carbonio", 50);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'acciaio' (dopo aggiunta carbonio) ****************" << endl;
    try {
        bres = howManyItem(indus, "acciaio", ires);
        breq = true;
        ireq = 50; // ora ho 50 ferro + 50 carbonio ⇒ 50 acciaio
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": insertItem 'bullone' = acciaio ****************" << endl;
    std::string comp2[] = {"acciaio"};
    bres = insertItem(indus, "bullone", comp2, 1);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'bullone' ****************" << endl;
    try {
        bres = howManyItem(indus, "bullone", ires);
        breq = true;
        ireq = 50; // 50 acciaio ⇒ 50 bulloni
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": howManyItem 'motore' (non esistente) ****************" << endl;
    try {
        bres = howManyItem(indus, "motore", ires);
        breq = false;
        if (bres == breq)
            cout << "  Result: PASSED (not available)\n\n";
        else
            cout << "  Result: FAILED (unexpectedly available)\n\n";
    } catch (...) {
        cout << "  Result: PASSED (exception correctly thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": insertItem 'motore' = bullone + acciaio ****************" << endl;
    std::string comp3[] = {"bullone", "acciaio"};
    bres = insertItem(indus, "motore", comp3, 2);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'motore' ****************" << endl;

    try {
        unsigned resFerroPrima = 0, resCarbonioPrima = 0, resAcciaioPrima = 0, resBullonePrima = 0;
        unsigned resMotore = 0;
        unsigned resFerroDopo = 0, resCarbonioDopo = 0, resAcciaioDopo = 0, resBulloneDopo = 0;

        if(howManyItem(indus, "ferro", resFerroPrima))
            cout << "Ferro disponibile prima: " << resFerroPrima << endl;
        else
            cout << "Errore calcolo ferro prima" << endl;

        if(howManyItem(indus, "carbonio", resCarbonioPrima))
            cout << "Carbonio disponibile prima: " << resCarbonioPrima << endl;
        else
            cout << "Errore calcolo carbonio prima" << endl;

        if(howManyItem(indus, "acciaio", resAcciaioPrima))
            cout << "Acciaio disponibile prima: " << resAcciaioPrima << endl;
        else
            cout << "Errore calcolo acciaio prima" << endl;

        if(howManyItem(indus, "bullone", resBullonePrima))
            cout << "Bulloni disponibili prima: " << resBullonePrima << endl;
        else
            cout << "Errore calcolo bullone prima" << endl;

        bres = howManyItem(indus, "motore", resMotore);
        breq = true;
        ireq = 50; // aspettati 50 motori

        cout << "Motori producibili: " << resMotore << endl;

        if(howManyItem(indus, "ferro", resFerroDopo))
            cout << "Ferro disponibile dopo: " << resFerroDopo << endl;
        else
            cout << "Errore calcolo ferro dopo" << endl;

        if(howManyItem(indus, "carbonio", resCarbonioDopo))
            cout << "Carbonio disponibile dopo: " << resCarbonioDopo << endl;
        else
            cout << "Errore calcolo carbonio dopo" << endl;

        if(howManyItem(indus, "acciaio", resAcciaioDopo))
            cout << "Acciaio disponibile dopo: " << resAcciaioDopo << endl;
        else
            cout << "Errore calcolo acciaio dopo" << endl;

        if(howManyItem(indus, "bullone", resBulloneDopo))
            cout << "Bulloni disponibili dopo: " << resBulloneDopo << endl;
        else
            cout << "Errore calcolo bullone dopo" << endl;

        if (bres == breq && resMotore == ireq)
            cout << "  Result: PASSED (produced " << resMotore << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << resMotore << ", expected " << ireq << ")\n\n";

    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": addBasicItem 'ferro', +50 ****************" << endl;
    bres = addBasicItem(indus, "ferro", 50);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": addBasicItem 'carbonio', +50 ****************" << endl;
    bres = addBasicItem(indus, "carbonio", 50);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'motore' dopo aggiunta materie prime ****************" << endl;
    try {
        bres = howManyItem(indus, "motore", ires);
        breq = true;
        ireq = 100; // ora ho risorse per produrre altri 50 motori
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "[✔️] Fine dei test." << endl;
    return 0;
}