#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "mylib.h"

// Funkcijų deklaracijos
void skaitytiTeksta(const string& failoPavadinimas, map<string, int>& zodziuKiekis, map<string, set<int>>& zodziuEilutes);
void rasytiRezultatus(const string& failoPavadinimas, const map<string, int>& zodziuKiekis, const map<string, set<int>>& zodziuEilutes);
void urlSkaitymas(const string& failoPavadinimas, vector<string>& urlSarasas);
void urlIsvedimas(const string& failoPavadinimas, const vector<string>& urlSarasas);

#endif // FUNCTIONS_H
#pragma once
