#include "functions.h"

bool arSkyrybosZenklas(char c) {
    return ispunct(static_cast<unsigned char>(c)) != 0;
}

void skaitytiTeksta(const string& failoPavadinimas, map<string, int>& zodziuKiekis, map<string, set<int>>& zodziuEilutes) {
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return;
    }

    string eilute, zodis;
    int eilutesNumeris = 1;

    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        while (ss >> zodis) {
            string valytasZodis;
            for (char simbolis : zodis) {
                if (!arSkyrybosZenklas(simbolis)) {
                    valytasZodis += tolower(static_cast<unsigned char>(simbolis));
                }
            }

            bool yraRaide = any_of(valytasZodis.begin(), valytasZodis.end(),
                [](char c) { return isalpha(static_cast<unsigned char>(c)); });

            if (yraRaide) {
                zodziuKiekis[valytasZodis]++; ų
                zodziuEilutes[valytasZodis].insert(eilutesNumeris);

            }
        }
        eilutesNumeris++;
    }
    failas.close();
}

size_t apskaiciuotiUTF8Ilgi(const string& zodis) {
    size_t ilgis = 0;
    for (size_t i = 0; i < zodis.size(); ++i) {
        if ((zodis[i] & 0xC0) != 0x80) {
            ilgis++;
        }
    }
    return ilgis;
}

void rasytiRezultatus(const string& failoPavadinimas, const map<string, int>& zodziuKiekis, const map<string, set<int>>& zodziuEilutes) {
    ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
        return;
    }

    failas << "Zodis           | Pasikartojimai  | Eilutes\n";
    failas << "----------------|-----------------|--------\n";

    for (const auto& pora : zodziuKiekis) {
        if (pora.second > 1) {
            failas << pora.first;

            size_t zodzioIlgis = apskaiciuotiUTF8Ilgi(pora.first);
            failas << string(16 - zodzioIlgis, ' ');

            failas << "| " << pora.second;

            size_t pasikartojimaiIlgis = to_string(pora.second).length();
            failas << string(16 - pasikartojimaiIlgis, ' ');

            failas << "| ";

            const auto& eilutes = zodziuEilutes.at(pora.first);
            for ( const int nr : eilutes){
                failas << setw(2) << left << nr << " ";
            }
            
            failas << endl;
        }
    }

    failas.close();
}

void urlSkaitymas(const string& failoPavadinimas, vector<string>& urlSarasas) {
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return;
    }

    string eilute;
    regex urlRegex(R"((https?:\/\/[^\s]+|www\.[^\s]+|[a-zA-Z0-9\-]+\.[a-zA-Z]{2,}))");
    smatch urlAtitikmuo;

    while (getline(failas, eilute)) {
        string::const_iterator pradzia = eilute.begin();
        string::const_iterator pabaiga = eilute.end();

        while (regex_search(pradzia, pabaiga, urlAtitikmuo, urlRegex)) {
            urlSarasas.push_back(urlAtitikmuo[0]);
            pradzia = urlAtitikmuo.suffix().first;
        }
    }
    failas.close();
}


void urlIsvedimas(const string& failoPavadinimas, const vector<string>& urlSarasas) {
    ofstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
        return;
    }

    failas << "Rasti URL adresai:\n";
    for (const auto& url : urlSarasas) {
        failas << url << endl;
    }

    cout << "URL adresai buvo irasyti i faila: " << failoPavadinimas << endl;
    failas.close();
}