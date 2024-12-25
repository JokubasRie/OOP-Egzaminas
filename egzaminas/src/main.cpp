#include "functions.h"

int main() {
    map<string, int> zodziuKiekis;
    map<string, set<int>> zodziuEilutes;

    string ivestiesFailas = "tekstas.txt";
    string isvestiesFailas = "rezultatai.txt";

    skaitytiTeksta(ivestiesFailas, zodziuKiekis, zodziuEilutes);
    rasytiRezultatus(isvestiesFailas, zodziuKiekis, zodziuEilutes);

    cout << "Rezultatai irasyti i faila: " << isvestiesFailas << endl;

    vector<string> urlSarasas;

    string ivestiesUrlFailas = "tekstasUrl.txt";
    string isvestiesUrlFailas = "rezultataiUrl.txt";

    urlSkaitymas(ivestiesUrlFailas, urlSarasas);

    urlIsvedimas(isvestiesUrlFailas, urlSarasas);
    
    return 0;
}
