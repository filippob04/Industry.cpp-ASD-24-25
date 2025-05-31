#include <iostream>
#include "industry.h"

void printIndustry(const industry::Industry& indus);

int main() {
    using namespace std;
    using namespace industry;
    cout << boolalpha;

    Industry indus;
    unsigned i = 1;
    bool bres = false, breq = false;
    unsigned ires = 0, ireq = 0;

    indus = createEmptyIndustry();
    cout << endl;
    cout << " /* Inizio dei test */" << endl;
    cout << endl;

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

    cout << "*************** Test " << i++ << ": insertBasicItem 'carbone' ****************" << endl;
    bres = insertBasicItem(indus, "carbone");
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": insertItem 'lingotto di ferro' = ferro + carbone ****************" << endl;
    std::string comp1[] = {"ferro", "carbone"};
    bres = insertItem(indus, "lingotto di ferro", comp1, 2);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'lingotto di ferro' ****************" << endl;
    try {
        bres = howManyItem(indus, "lingotto di ferro", ires);
        breq = true;
        ireq = 0; // 50 ferro, 0 carbonio ⇒ 0 acciaio
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": addBasicItem 'carbone', +50 ****************" << endl;
    bres = addBasicItem(indus, "carbone", 50);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'lingotto di ferro' (dopo aggiunta carbone) ****************" << endl;
    try {
        bres = howManyItem(indus, "lingotto di ferro", ires);
        breq = true;
        ireq = 50; // ora ho 50 ferro + 50 carbonio ⇒ 50 acciaio
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": insertItem 'pepita di ferro' = lingotto di ferro ****************" << endl;
    std::string comp2[] = {"lingotto di ferro"};
    bres = insertItem(indus, "pepita di ferro", comp2, 1);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'pepita di ferro' ****************" << endl;
    try {
        bres = howManyItem(indus, "pepita di ferro", ires);
        breq = true;
        ireq = 50; // 50 acciaio ⇒ 50 bulloni
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": howManyItem 'catena' (non esistente) ****************" << endl;
    try {
        bres = howManyItem(indus, "catena", ires);
        breq = false;
        if (bres == breq)
            cout << "  Result: PASSED (not available)\n\n";
        else
            cout << "  Result: FAILED (unexpectedly available)\n\n";
    } catch (...) {
        cout << "  Result: PASSED (exception correctly thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": insertItem 'catena' = pepita di ferro + lingotto di ferro ****************" << endl;
    std::string comp3[] = {"pepita di ferro", "lingotto di ferro"};
    bres = insertItem(indus, "catena", comp3, 2);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'catena' ****************" << endl;
    try {
        bres = howManyItem(indus, "catena", ires);
        breq = true;
        ireq = 25; 
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    cout << "*************** Test " << i++ << ": addBasicItem 'ferro', +50 ****************" << endl;
    bres = addBasicItem(indus, "ferro", 50);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": addBasicItem 'carbone', +50 ****************" << endl;
    bres = addBasicItem(indus, "carbone", 50);
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": howManyItem 'catena' dopo aggiunta materie prime ****************" << endl;
    try {
        bres = howManyItem(indus, "catena", ires);
        breq = true;
        ireq = 50; // ora ho risorse per produrre altri 50 motori
        if (bres == breq && ires == ireq)
            cout << "  Result: PASSED (produced " << ires << ")\n\n";
        else
            cout << "  Result: FAILED (produced " << ires << ", expected " << ireq << ")\n\n";
    } catch (...) {
        cout << "  Result: FAILED (exception thrown)\n\n";
    }

    list::List lst = list::createEmpty();
    cout<<"*************** Test "<<i++<<": listNeed(ferro) ****************"<<endl;
    bres=listNeed(indus, "ferro", lst);
    breq=false;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeed(lingotto di ferro) ****************"<<endl;
    bres=listNeed(indus, "lingotto di ferro", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeed(catena) ****************"<<endl;
    bres=listNeed(indus, "catena", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeed(oro) ****************"<<endl;
    bres=listNeed(indus, "oro", lst);
    breq=false;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;
    
    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeededBy(ferro) ****************"<<endl;
    bres=listNeededBy(indus, "ferro", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeededBy(lingotto di ferro) ****************"<<endl;
    bres=listNeededBy(indus, "lingotto di ferro", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeededBy(catena) ****************"<<endl;
    bres=listNeededBy(indus, "catena", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeededByChain(ferro) ****************"<<endl;
    bres=listNeededByChain(indus, "ferro", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeededByChain(lingotto di ferro) ****************"<<endl;
    bres=listNeededByChain(indus, "lingotto di ferro", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeededByChain(pepita di ferro) ****************"<<endl;
    bres=listNeededByChain(indus, "pepita di ferro", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;

    list::clear(lst);
    cout<<"*************** Test "<<i++<<": listNeededByChain(catena) ****************"<<endl;
    bres=listNeededByChain(indus, "catena", lst);
    breq=true;
    if(bres==breq){
        cout<<"  Result: PASSED"<<endl;
        cout << list::toString(lst);
        cout<< endl;
    }else {
        cout<<"  Result: FAILED"<<endl;
        cout<<"  Expected Returned Value: "<<breq<<endl;
        cout<<"  Obtained Returned Value: "<<bres<<endl;
    }
    cout<<endl;
    
    cout << endl;
    printIndustry(indus);
    cout << endl;

    cout << "*************** Test " << i++ << ": removeItem 'pepita di ferro' ****************" << endl;
    bres = removeItem(indus, "pepita di ferro");
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";
    
    cout << "*************** Test " << i++ << ": isPresentItem 'pepita di ferro' ****************" << endl;
    bres = isPresentItem(indus, "pepita di ferro");
    breq = false;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": removeItem 'ferro' ****************" << endl;
    bres = removeItem(indus, "ferro");
    breq = true;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": isPresentItem 'ferro' ****************" << endl;
    bres = isPresentItem(indus, "ferro");
    breq = false;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";

    cout << "*************** Test " << i++ << ": isPresentItem 'lingotto di ferro' ****************" << endl;
    bres = isPresentItem(indus, "lingotto di ferro");
    breq = false;
    if (bres == breq) cout << "  Result: PASSED\n\n";
    else cout << "  Result: FAILED\n\n";
    
    cout << endl;
    printIndustry(indus);
    cout << endl;
    
    cout << " /* Fine dei test */" << endl;
    cout << endl;
    return 0;
}