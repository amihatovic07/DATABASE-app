#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

const int MAX_TABLICA = 20;
const int MAX_STUPACA = 20;
const int MAX_REDOVA = 200;
const int MAX_FK = 20;


// ======================================================
// STRUKTURE
// ======================================================

struct Red {
    string vrijednosti[MAX_STUPACA];
};


struct ForeignKey {

    string stupac;

    string referenciranaTablica;

    string referenciraniStupac;
};


struct Tablica {

    string naziv;

    string stupci[MAX_STUPACA];

    int brojStupaca = 0;


    Red redovi[MAX_REDOVA];

    int brojRedova = 0;


    // PRIMARY KEY
    int primaryKeyIndex = -1;


    // FOREIGN KEY
    ForeignKey foreignKeys[MAX_FK];

    int brojForeignKeys = 0;
};


struct BazaPodataka {

    string naziv;

    Tablica tablice[MAX_TABLICA];

    int brojTablica = 0;
};


// ======================================================
// POMOCNE FUNKCIJE
// ======================================================

string malim(string tekst) {

    transform(
        tekst.begin(),
        tekst.end(),
        tekst.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        }
    );

    return tekst;
}


void ocistiUnos() {

    cin.clear();

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );
}


bool stringUBroj(
    const string& tekst,
    double& broj
) {

    try {

        size_t pozicija;

        broj = stod(
            tekst,
            &pozicija
        );


        return pozicija == tekst.length();
    }

    catch (...) {

        return false;
    }
}


// ======================================================
// PRONALAZENJE TABLICE
// ======================================================

int pronadiTablicu(
    const BazaPodataka& baza,
    const string& naziv
) {

    for (
        int i = 0;
        i < baza.brojTablica;
        i++
    ) {

        if (
            malim(baza.tablice[i].naziv)
            ==
            malim(naziv)
        ) {

            return i;
        }
    }

    return -1;
}


// ======================================================
// PRONALAZENJE STUPCA
// ======================================================

int pronadiStupac(
    const Tablica& tablica,
    const string& naziv
) {

    for (
        int i = 0;
        i < tablica.brojStupaca;
        i++
    ) {

        if (
            malim(tablica.stupci[i])
            ==
            malim(naziv)
        ) {

            return i;
        }
    }

    return -1;
}


// ======================================================
// ISPIS TABLICE
// ======================================================

void ispisiTablicu(
    const Tablica& tablica
) {

    cout << "\n========================================\n";

    cout
        << "TABLICA: "
        << tablica.naziv
        << "\n";

    cout << "========================================\n";


    if (tablica.brojStupaca == 0) {

        cout << "Tablica nema stupaca.\n";

        return;
    }


    for (
        int i = 0;
        i < tablica.brojStupaca;
        i++
    ) {

        cout
            << "| "
            << tablica.stupci[i];

        if (
            i ==
            tablica.primaryKeyIndex
        ) {

            cout << " [PK]";
        }
    }

    cout << " |\n";


    cout << "----------------------------------------\n";


    for (
        int i = 0;
        i < tablica.brojRedova;
        i++
    ) {

        for (
            int j = 0;
            j < tablica.brojStupaca;
            j++
        ) {

            cout
                << "| "
                << tablica.redovi[i].vrijednosti[j];
        }

        cout << " |\n";
    }


    cout << "========================================\n";

    cout
        << "Broj redova: "
        << tablica.brojRedova
        << "\n";
}


// ======================================================
// ISPIS SVIH TABLICA
// ======================================================

void ispisiSveTablice(
    const BazaPodataka& baza
) {

    cout << "\n========================================\n";

    cout
        << "BAZA: "
        << baza.naziv
        << "\n";

    cout << "========================================\n";


    if (baza.brojTablica == 0) {

        cout << "Baza trenutno nema tablica.\n";

        return;
    }


    for (
        int i = 0;
        i < baza.brojTablica;
        i++
    ) {

        cout
            << i + 1
            << ". "
            << baza.tablice[i].naziv
            << " ("
            << baza.tablice[i].brojRedova
            << " redova)\n";
    }
}


// ======================================================
// PRIMARY KEY PROVJERA
// ======================================================

bool primaryKeyPostoji(
    const Tablica& tablica,
    const string& vrijednost
) {

    if (
        tablica.primaryKeyIndex == -1
    ) {

        return false;
    }


    for (
        int i = 0;
        i < tablica.brojRedova;
        i++
    ) {

        if (
            tablica.redovi[i]
                .vrijednosti[
                    tablica.primaryKeyIndex
                ]
            ==
            vrijednost
        ) {

            return true;
        }
    }
    return false;
}


// ======================================================
// POSTOJI LI VRIJEDNOST U STUPCU
// ======================================================

bool vrijednostPostoji(
    const Tablica& tablica,
    int stupac,
    const string& vrijednost
) {

    for (
        int i = 0;
        i < tablica.brojRedova;
        i++
    ) {

        if (
            tablica.redovi[i]
                .vrijednosti[stupac]
            ==
            vrijednost
        ) {

            return true;
        }
    }

    return false;
}


// ======================================================
// KREIRANJE TABLICE
// ======================================================

void kreirajTablicu(
    BazaPodataka& baza
) {

    if (
        baza.brojTablica >=
        MAX_TABLICA
    ) {

        cout << "Dosegnut maksimalan broj tablica!\n";

        return;
    }


    Tablica nova;


    cout << "\nNaziv nove tablice: ";

    getline(
        cin >> ws,
        nova.naziv
    );


    if (
        pronadiTablicu(
            baza,
            nova.naziv
        ) != -1
    ) {

        cout << "Tablica s tim nazivom vec postoji!\n";

        return;
    }


    cout
        << "Broj stupaca (1-"
        << MAX_STUPACA
        << "): ";


    cin >> nova.brojStupaca;


    if (
        nova.brojStupaca < 1 ||
        nova.brojStupaca > MAX_STUPACA
    ) {

        cout << "Neispravan broj stupaca!\n";

        return;
    }


    for (
        int i = 0;
        i < nova.brojStupaca;
        i++
    ) {

        cout
            << "Naziv "
            << i + 1
            << ". stupca: ";

        getline(
            cin >> ws,
            nova.stupci[i]
        );


        for (
            int j = 0;
            j < i;
            j++
        ) {

            if (
                malim(nova.stupci[i])
                ==
                malim(nova.stupci[j])
            ) {

                cout
                    << "Stupac s tim nazivom vec postoji!\n";

                i--;

                break;
            }
        }
    }


    string odgovor;


    cout
        << "Zelite li definirati PRIMARY KEY? (da/ne): ";

    cin >> odgovor;


    if (
        malim(odgovor) == "da"
    ) {

        string pk;


        cout << "Naziv PK stupca: ";

        cin >> pk;


        int index =
            pronadiStupac(
                nova,
                pk
            );


        if (index != -1) {

            nova.primaryKeyIndex =
                index;

            cout
                << "PRIMARY KEY postavljen na: "
                << pk
                << "\n";
        }

        else {

            cout
                << "Stupac nije pronaden. "
                << "PK nije postavljen.\n";
        }
    }


    baza.tablice[
        baza.brojTablica
    ] = nova;


    baza.brojTablica++;


    cout
        << "Tablica "
        << nova.naziv
        << " je kreirana!\n";
}


// ======================================================
// BRISANJE TABLICE
// ======================================================

void obrisiTablicu(
    BazaPodataka& baza
) {

    string naziv;


    cout << "Naziv tablice za brisanje: ";

    getline(
        cin >> ws,
        naziv
    );


    int index =
        pronadiTablicu(
            baza,
            naziv
        );


    if (index == -1) {

        cout << "Tablica ne postoji!\n";

        return;
    }
    // Ne dopustamo brisanje ako druga tablica
    // ima FK prema ovoj tablici.

    for (
        int i = 0;
        i < baza.brojTablica;
        i++
    ) {

        if (i == index) {

            continue;
        }


        for (
            int j = 0;
            j <
            baza.tablice[i].brojForeignKeys;
            j++
        ) {

            if (
                malim(
                    baza.tablice[i]
                        .foreignKeys[j]
                        .referenciranaTablica
                )
                ==
                malim(naziv)
            ) {

                cout
                    << "Tablicu nije moguce obrisati.\n";

                cout
                    << "Na nju postoji FOREIGN KEY iz tablice: "
                    << baza.tablice[i].naziv
                    << "\n";

                return;
            }
        }
    }


    for (
        int i = index;
        i < baza.brojTablica - 1;
        i++
    ) {

        baza.tablice[i] =
            baza.tablice[i + 1];
    }


    baza.brojTablica--;


    cout << "Tablica je obrisana.\n";
}


// ======================================================
// DODAVANJE FOREIGN KEY-a
// ======================================================

void dodajForeignKey(
    BazaPodataka& baza
) {

    string nazivTablice;


    cout
        << "Tablica kojoj dodajemo FOREIGN KEY: ";

    getline(
        cin >> ws,
        nazivTablice
    );


    int index =
        pronadiTablicu(
            baza,
            nazivTablice
        );


    if (index == -1) {

        cout << "Tablica ne postoji!\n";

        return;
    }


    Tablica& tablica =
        baza.tablice[index];


    if (
        tablica.brojForeignKeys >=
        MAX_FK
    ) {

        cout << "Previse FOREIGN KEY ogranicenja!\n";

        return;
    }


    string stupac;


    cout << "FK stupac: ";

    getline(
        cin >> ws,
        stupac
    );


    int fkIndex =
        pronadiStupac(
            tablica,
            stupac
        );


    if (fkIndex == -1) {

        cout << "Stupac ne postoji!\n";

        return;
    }


    string ciljnaTablica;


    cout << "Referencirana tablica: ";

    getline(
        cin >> ws,
        ciljnaTablica
    );


    int ciljIndex =
        pronadiTablicu(
            baza,
            ciljnaTablica
        );


    if (ciljIndex == -1) {

        cout << "Referencirana tablica ne postoji!\n";

        return;
    }


    string ciljniStupac;


    cout << "Referencirani stupac: ";

    getline(
        cin >> ws,
        ciljniStupac
    );


    int ciljniIndex =
        pronadiStupac(
            baza.tablice[ciljIndex],
            ciljniStupac
        );


    if (ciljniIndex == -1) {

        cout << "Referencirani stupac ne postoji!\n";

        return;
    }


    // Za ovaj mini DBMS zahtijevamo da FK
    // pokazuje na PRIMARY KEY.

    if (
        baza.tablice[ciljIndex]
            .primaryKeyIndex
        !=
        ciljniIndex
    ) {

        cout
            << "FOREIGN KEY mora referencirati "
            << "PRIMARY KEY ciljne tablice.\n";

        return;
    }


    ForeignKey fk;


    fk.stupac =
        stupac;

    fk.referenciranaTablica =
        ciljnaTablica;

    fk.referenciraniStupac =
        ciljniStupac;


    tablica.foreignKeys[
        tablica.brojForeignKeys
    ] = fk;


    tablica.brojForeignKeys++;


    cout << "FOREIGN KEY je dodan!\n";
}


// ======================================================
// PROVJERA FOREIGN KEY-a
// ======================================================

bool provjeriForeignKeys(
    const BazaPodataka& baza,
    const Tablica& tablica,
    const Red& red
) {

    for (
        int i = 0;
        i < tablica.brojForeignKeys;
        i++
    ) {

        const ForeignKey& fk =
            tablica.foreignKeys[i];


        int lokalniIndex =
            pronadiStupac(
                tablica,
                fk.stupac
            );


        int ciljnaTablicaIndex =
            pronadiTablicu(
                baza,
                fk.referenciranaTablica
            );


        if (
            lokalniIndex == -1 ||
            ciljnaTablicaIndex == -1
        ) {

            return false;
        }


        const Tablica& ciljnaTablica =
            baza.tablice[
                ciljnaTablicaIndex
            ];


        int ciljniStupacIndex =
            pronadiStupac(
                ciljnaTablica,
                fk.referenciraniStupac
            );


        if (ciljniStupacIndex == -1) {

            return false;
        }


        string vrijednost =
            red.vrijednosti[
                lokalniIndex
            ];


        if (
            !vrijednostPostoji(
                ciljnaTablica,
                ciljniStupacIndex,
                vrijednost
            )
        ) {

            cout
                << "FOREIGN KEY greska!\n";

            cout
                << vrijednost
                << " ne postoji u "
                << ciljnaTablica.naziv
                << "."
                << fk.referenciraniStupac
                << "\n";

            return false;
        }
    }


    return true;
}
// ======================================================
// DODAVANJE REDA
// ======================================================

void dodajRed(
    BazaPodataka& baza
) {

    string naziv;


    cout << "Naziv tablice: ";

    getline(
        cin >> ws,
        naziv
    );


    int index =
        pronadiTablicu(
            baza,
            naziv
        );


    if (index == -1) {

        cout << "Tablica ne postoji!\n";

        return;
    }


    Tablica& tablica =
        baza.tablice[index];


    if (
        tablica.brojRedova >=
        MAX_REDOVA
    ) {

        cout << "Tablica je puna!\n";

        return;
    }


    Red noviRed;


    cout << "\nUNOS NOVOG REDA\n";


    for (
        int i = 0;
        i < tablica.brojStupaca;
        i++
    ) {

        cout
            << tablica.stupci[i]
            << ": ";

        getline(
            cin >> ws,
            noviRed.vrijednosti[i]
        );
    }


    // PK provjera

    if (
        tablica.primaryKeyIndex != -1
    ) {

        string pkVrijednost =
            noviRed.vrijednosti[
                tablica.primaryKeyIndex
            ];


        if (pkVrijednost.empty()) {

            cout
                << "PRIMARY KEY ne smije biti prazan!\n";

            return;
        }


        if (
            primaryKeyPostoji(
                tablica,
                pkVrijednost
            )
        ) {

            cout
                << "PRIMARY KEY mora biti jedinstven!\n";

            return;
        }
    }


    // FK provjera

    if (
        !provjeriForeignKeys(
            baza,
            tablica,
            noviRed
        )
    ) {

        return;
    }


    tablica.redovi[
        tablica.brojRedova
    ] = noviRed;


    tablica.brojRedova++;


    cout << "Red je dodan!\n";
}


// ======================================================
// BRISANJE REDA
// ======================================================

void obrisiRed(
    BazaPodataka& baza
) {

    string naziv;


    cout << "Naziv tablice: ";

    getline(
        cin >> ws,
        naziv
    );


    int index =
        pronadiTablicu(
            baza,
            naziv
        );


    if (index == -1) {

        cout << "Tablica ne postoji!\n";

        return;
    }


    Tablica& tablica =
        baza.tablice[index];


    if (
        tablica.primaryKeyIndex == -1
    ) {

        cout
            << "Za sigurno brisanje tablica mora imati PRIMARY KEY.\n";

        return;
    }


    string vrijednost;


    cout << "Vrijednost PRIMARY KEY-a: ";

    getline(
        cin >> ws,
        vrijednost
    );


    int redIndex = -1;


    for (
        int i = 0;
        i < tablica.brojRedova;
        i++
    ) {

        if (
            tablica.redovi[i]
                .vrijednosti[
                    tablica.primaryKeyIndex
                ]
            ==
            vrijednost
        ) {

            redIndex = i;

            break;
        }
    }


    if (redIndex == -1) {

        cout << "Red nije pronaden!\n";

        return;
    }


    // REFERENCIJALNI INTEGRITET
    // Provjeravamo koristi li druga tablica ovaj PK.

    for (
        int i = 0;
        i < baza.brojTablica;
        i++
    ) {

        for (
            int j = 0;
            j <
            baza.tablice[i].brojForeignKeys;
            j++
        ) {

            ForeignKey& fk =
                baza.tablice[i]
                    .foreignKeys[j];


            if (
                malim(
                    fk.referenciranaTablica
                )
                ==
                malim(tablica.naziv)
            ) {

                int fkStupac =
                    pronadiStupac(
                        baza.tablice[i],
                        fk.stupac
                    );


                if (
                    fkStupac != -1 &&
                    vrijednostPostoji(
                        baza.tablice[i],
                        fkStupac,
                        vrijednost
                    )
                ) {

                    cout
                        << "Brisanje nije dozvoljeno!\n";

                    cout
                        << "Vrijednost je referencirana "
                        << "FOREIGN KEY-em iz tablice "
                        << baza.tablice[i].naziv
                        << ".\n";

                    return;
                }
            }
        }
    }


    for (
        int i = redIndex;
        i < tablica.brojRedova - 1;
        i++
    ) {

        tablica.redovi[i] =
            tablica.redovi[i + 1];
    }


    tablica.brojRedova--;


    cout << "Red je obrisan!\n";
}
// ======================================================
// USPOREDBA VRIJEDNOSTI
// ======================================================

bool usporediVrijednosti(
    const string& lijevo,
    const string& op,
    const string& desno
) {

    double brojLijevo;
    double brojDesno;


    bool lijevoJeBroj =
        stringUBroj(
            lijevo,
            brojLijevo
        );


    bool desnoJeBroj =
        stringUBroj(
            desno,
            brojDesno
        );


    // Ako su obje vrijednosti brojevi,
    // koristimo numericku usporedbu.

    if (
        lijevoJeBroj &&
        desnoJeBroj
    ) {

        if (op == "=" || op == "==")
            return brojLijevo == brojDesno;

        if (op == "!=")
            return brojLijevo != brojDesno;

        if (op == ">")
            return brojLijevo > brojDesno;

        if (op == "<")
            return brojLijevo < brojDesno;

        if (op == ">=")
            return brojLijevo >= brojDesno;

        if (op == "<=")
            return brojLijevo <= brojDesno;
    }


    // Inace usporedujemo stringove.

    if (op == "=" || op == "==")
        return lijevo == desno;

    if (op == "!=")
        return lijevo != desno;

    if (op == ">")
        return lijevo > desno;

    if (op == "<")
        return lijevo < desno;

    if (op == ">=")
        return lijevo >= desno;

    if (op == "<=")
        return lijevo <= desno;


    return false;
}


// ======================================================
// SELEKCIJA SIGMA
// ======================================================

Tablica selekcija(
    const Tablica& izvor,
    const string& stupac,
    const string& op,
    const string& vrijednost
) {

    Tablica rezultat =
        izvor;


    rezultat.naziv =
        "SELEKCIJA_" +
        izvor.naziv;


    rezultat.brojRedova = 0;


    int index =
        pronadiStupac(
            izvor,
            stupac
        );


    if (index == -1) {

        cout << "Stupac ne postoji!\n";

        return rezultat;
    }


    for (
        int i = 0;
        i < izvor.brojRedova;
        i++
    ) {

        if (
            usporediVrijednosti(
                izvor.redovi[i]
                    .vrijednosti[index],

                op,

                vrijednost
            )
        ) {

            rezultat.redovi[
                rezultat.brojRedova
            ] = izvor.redovi[i];


            rezultat.brojRedova++;
        }
    }


    return rezultat;
}


// ======================================================
// PROJEKCIJA PI
// ======================================================

Tablica projekcija(
    const Tablica& izvor,
    string odabraniStupci[],
    int brojOdabranih
) {

    Tablica rezultat;


    rezultat.naziv =
        "PROJEKCIJA_" +
        izvor.naziv;


    int indeksi[MAX_STUPACA];


    for (
        int i = 0;
        i < brojOdabranih;
        i++
    ) {

        indeksi[i] =
            pronadiStupac(
                izvor,
                odabraniStupci[i]
            );


        if (indeksi[i] == -1) {

            cout
                << "Stupac "
                << odabraniStupci[i]
                << " ne postoji!\n";

            rezultat.brojStupaca = 0;

            return rezultat;
        }


        rezultat.stupci[i] =
            odabraniStupci[i];
    }


    rezultat.brojStupaca =
        brojOdabranih;


    for (
        int i = 0;
        i < izvor.brojRedova;
        i++
    ) {

        for (
            int j = 0;
            j < brojOdabranih;
            j++
        ) {

            rezultat.redovi[i]
                .vrijednosti[j]
            =
            izvor.redovi[i]
                .vrijednosti[
                    indeksi[j]
                ];
        }
    }


    rezultat.brojRedova =
        izvor.brojRedova;


    return rezultat;
}
// ======================================================
// JEDNAKOST REDOVA
// ======================================================

bool jednakiRedovi(
    const Red& a,
    const Red& b,
    int brojStupaca
) {

    for (
        int i = 0;
        i < brojStupaca;
        i++
    ) {

        if (
            a.vrijednosti[i]
            !=
            b.vrijednosti[i]
        ) {

            return false;
        }
    }


    return true;
}


// ======================================================
// POSTOJI LI RED
// ======================================================

bool redPostoji(
    const Tablica& tablica,
    const Red& red
) {

    for (
        int i = 0;
        i < tablica.brojRedova;
        i++
    ) {

        if (
            jednakiRedovi(
                tablica.redovi[i],
                red,
                tablica.brojStupaca
            )
        ) {

            return true;
        }
    }


    return false;
}


// ======================================================
// KOMPATIBILNOST RELACIJA
// ======================================================

bool kompatibilneRelacije(
    const Tablica& A,
    const Tablica& B
) {

    if (
        A.brojStupaca !=
        B.brojStupaca
    ) {

        return false;
    }


    for (
        int i = 0;
        i < A.brojStupaca;
        i++
    ) {

        if (
            malim(A.stupci[i])
            !=
            malim(B.stupci[i])
        ) {

            return false;
        }
    }


    return true;
}


// ======================================================
// UNIJA
// ======================================================

Tablica unija(
    const Tablica& A,
    const Tablica& B
) {

    Tablica rezultat;


    rezultat.naziv =
        "UNIJA_" +
        A.naziv +
        "_" +
        B.naziv;


    if (
        !kompatibilneRelacije(
            A,
            B
        )
    ) {

        cout
            << "Relacije nisu kompatibilne za uniju!\n";

        return rezultat;
    }


    rezultat.brojStupaca =
        A.brojStupaca;


    for (
        int i = 0;
        i < A.brojStupaca;
        i++
    ) {

        rezultat.stupci[i] =
            A.stupci[i];
    }


    for (
        int i = 0;
        i < A.brojRedova;
        i++
    ) {

        if (
            !redPostoji(
                rezultat,
                A.redovi[i]
            )
        ) {

            rezultat.redovi[
                rezultat.brojRedova++
            ] = A.redovi[i];
        }
    }


    for (
        int i = 0;
        i < B.brojRedova;
        i++
    ) {

        if (
            !redPostoji(
                rezultat,
                B.redovi[i]
            )
        ) {

            if (
                rezultat.brojRedova <
                MAX_REDOVA
            ) {

                rezultat.redovi[
                    rezultat.brojRedova++
                ] = B.redovi[i];
            }
        }
    }


    return rezultat;
}


// ======================================================
// PRESJEK
// ======================================================

Tablica presjek(
    const Tablica& A,
    const Tablica& B
) {

    Tablica rezultat;


    rezultat.naziv =
        "PRESJEK_" +
        A.naziv +
        "_" +
        B.naziv;


    if (
        !kompatibilneRelacije(
            A,
            B
        )
    ) {

        cout
            << "Relacije nisu kompatibilne za presjek!\n";

        return rezultat;
    }


    rezultat.brojStupaca =
        A.brojStupaca;


    for (
        int i = 0;
        i < A.brojStupaca;
        i++
    ) {

        rezultat.stupci[i] =
            A.stupci[i];
    }


    for (
        int i = 0;
        i < A.brojRedova;
        i++
    ) {

        if (
            redPostoji(
                B,
                A.redovi[i]
            )
            &&
            !redPostoji(
                rezultat,
                A.redovi[i]
            )
        ) {

            rezultat.redovi[
                rezultat.brojRedova++
            ] = A.redovi[i];
        }
    }


    return rezultat;
}


// ======================================================
// RAZLIKA
// ======================================================

Tablica razlika(
    const Tablica& A,
    const Tablica& B
) {

    Tablica rezultat;


    rezultat.naziv =
        "RAZLIKA_" +
        A.naziv +
        "_" +
        B.naziv;


    if (
        !kompatibilneRelacije(
            A,
            B
        )
    ) {

        cout
            << "Relacije nisu kompatibilne za razliku!\n";

        return rezultat;
    }


    rezultat.brojStupaca =
        A.brojStupaca;


    for (
        int i = 0;
        i < A.brojStupaca;
        i++
    ) {

        rezultat.stupci[i] =
            A.stupci[i];
    }


    for (
        int i = 0;
        i < A.brojRedova;
        i++
    ) {

        if (
            !redPostoji(
                B,
                A.redovi[i]
            )
        ) {

            rezultat.redovi[
                rezultat.brojRedova++
            ] = A.redovi[i];
        }
    }


    return rezultat;
}
// ======================================================
// KARTEZIJEV PRODUKT
// ======================================================

Tablica kartezijevProdukt(
    const Tablica& A,
    const Tablica& B
) {

    Tablica rezultat;


    rezultat.naziv =
        A.naziv +
        "_X_" +
        B.naziv;


    if (
        A.brojStupaca +
        B.brojStupaca
        >
        MAX_STUPACA
    ) {

        cout
            << "Rezultat ima previse stupaca!\n";

        return rezultat;
    }


    for (
        int i = 0;
        i < A.brojStupaca;
        i++
    ) {

        rezultat.stupci[
            rezultat.brojStupaca++
        ] =
        A.naziv +
        "." +
        A.stupci[i];
    }


    for (
        int i = 0;
        i < B.brojStupaca;
        i++
    ) {

        rezultat.stupci[
            rezultat.brojStupaca++
        ] =
        B.naziv +
        "." +
        B.stupci[i];
    }


    for (
        int i = 0;
        i < A.brojRedova;
        i++
    ) {

        for (
            int j = 0;
            j < B.brojRedova;
            j++
        ) {

            if (
                rezultat.brojRedova >=
                MAX_REDOVA
            ) {

                cout
                    << "Rezultat je skracen na "
                    << MAX_REDOVA
                    << " redova.\n";

                return rezultat;
            }


            int k = 0;


            for (
                int a = 0;
                a < A.brojStupaca;
                a++
            ) {

                rezultat.redovi[
                    rezultat.brojRedova
                ].vrijednosti[k++] =
                    A.redovi[i]
                        .vrijednosti[a];
            }


            for (
                int b = 0;
                b < B.brojStupaca;
                b++
            ) {

                rezultat.redovi[
                    rezultat.brojRedova
                ].vrijednosti[k++] =
                    B.redovi[j]
                        .vrijednosti[b];
            }


            rezultat.brojRedova++;
        }
    }


    return rezultat;
}


// ======================================================
// EQUI JOIN
//
// A JOIN B
// ON A.stupac = B.stupac
// ======================================================

Tablica joinTablice(
    const Tablica& A,
    const Tablica& B,
    const string& stupacA,
    const string& stupacB
) {

    Tablica rezultat;


    rezultat.naziv =
        "JOIN_" +
        A.naziv +
        "_" +
        B.naziv;


    int indexA =
        pronadiStupac(
            A,
            stupacA
        );


    int indexB =
        pronadiStupac(
            B,
            stupacB
        );


    if (
        indexA == -1 ||
        indexB == -1
    ) {

        cout << "JOIN stupac ne postoji!\n";

        return rezultat;
    }


    if (
        A.brojStupaca +
        B.brojStupaca
        >
        MAX_STUPACA
    ) {

        cout
            << "JOIN rezultat ima previse stupaca!\n";

        return rezultat;
    }


    // Nazivi stupaca A

    for (
        int i = 0;
        i < A.brojStupaca;
        i++
    ) {

        rezultat.stupci[
            rezultat.brojStupaca++
        ] =
        A.naziv +
        "." +
        A.stupci[i];
    }


    // Nazivi stupaca B

    for (
        int i = 0;
        i < B.brojStupaca;
        i++
    ) {

        rezultat.stupci[
            rezultat.brojStupaca++
        ] =
        B.naziv +
        "." +
        B.stupci[i];
    }


    for (
        int i = 0;
        i < A.brojRedova;
        i++
    ) {

        for (
            int j = 0;
            j < B.brojRedova;
            j++
        ) {

            if (
                A.redovi[i]
                    .vrijednosti[indexA]
                ==
                B.redovi[j]
                    .vrijednosti[indexB]
            ) {

                if (
                    rezultat.brojRedova >=
                    MAX_REDOVA
                ) {

                    return rezultat;
                }


                int k = 0;


                for (
                    int a = 0;
                    a < A.brojStupaca;
                    a++
                ) {

                    rezultat.redovi[
                        rezultat.brojRedova
                    ].vrijednosti[k++] =
                        A.redovi[i]
                            .vrijednosti[a];
                }


                for (
                    int b = 0;
                    b < B.brojStupaca;
                    b++
                ) {

                    rezultat.redovi[
                        rezultat.brojRedova
                    ].vrijednosti[k++] =
                        B.redovi[j]
                            .vrijednosti[b];
                }


                rezultat.brojRedova++;
            }
        }
    }


    return rezultat;
}
// ======================================================
// SPREMANJE REZULTATA KAO NOVE TABLICE
// ======================================================

void spremiRezultatUBazu(
    BazaPodataka& baza,
    Tablica rezultat
) {

    if (
        rezultat.brojStupaca == 0
    ) {

        cout << "Nema valjanog rezultata za spremanje.\n";

        return;
    }


    if (
        baza.brojTablica >=
        MAX_TABLICA
    ) {

        cout << "Baza je puna!\n";

        return;
    }


    string odgovor;


    cout
        << "Zelite li rezultat spremiti "
        << "kao novu tablicu? (da/ne): ";

    cin >> odgovor;


    if (
        malim(odgovor) != "da"
    ) {

        return;
    }


    string naziv;


    cout << "Naziv nove tablice: ";

    getline(
        cin >> ws,
        naziv
    );


    if (
        pronadiTablicu(
            baza,
            naziv
        ) != -1
    ) {

        cout
            << "Tablica s tim nazivom vec postoji!\n";

        return;
    }


    rezultat.naziv =
        naziv;


    // Rezultat relacijske operacije nema
    // automatski naslijedena ogranicenja.

    rezultat.primaryKeyIndex = -1;

    rezultat.brojForeignKeys = 0;


    baza.tablice[
        baza.brojTablica++
    ] = rezultat;


    cout
        << "Rezultat je spremljen kao tablica "
        << naziv
        << ".\n";
}


// ======================================================
// SPREMANJE BAZE
//
// Svaka tablica se sprema u posebnu datoteku.
// Schema se sprema u schema.txt.
// ======================================================
// ======================================================
// SPREMANJE BAZE
//
// Svaka tablica se sprema u posebnu datoteku.
// Schema se sprema u schema.txt.
// ======================================================

void spremiBazu(
    const BazaPodataka& baza
) {

    ofstream schema("schema.txt");


    if (!schema) {

        cout << "Greska pri spremanju sheme!\n";

        return;
    }


    schema
        << baza.naziv
        << "\n";


    schema
        << baza.brojTablica
        << "\n";


    for (
        int i = 0;
        i < baza.brojTablica;
        i++
    ) {

        const Tablica& t =
            baza.tablice[i];


        // ----------------------------------
        // SPREMANJE SHEME TABLICE
        // ----------------------------------

        schema
            << t.naziv
            << "\n";


        schema
            << t.brojStupaca
            << "\n";


        for (
            int j = 0;
            j < t.brojStupaca;
            j++
        ) {

            schema
                << t.stupci[j]
                << "\n";
        }


        schema
            << t.primaryKeyIndex
            << "\n";


        schema
            << t.brojForeignKeys
            << "\n";


        for (
            int j = 0;
            j < t.brojForeignKeys;
            j++
        ) {

            schema
                << t.foreignKeys[j].stupac
                << ";"
                << t.foreignKeys[j].referenciranaTablica
                << ";"
                << t.foreignKeys[j].referenciraniStupac
                << "\n";
        }


        // ----------------------------------
        // SPREMANJE PODATAKA TABLICE
        // ----------------------------------

        ofstream out(
            t.naziv + ".txt"
        );


        if (!out) {

            cout
                << "Greska pri spremanju tablice "
                << t.naziv
                << "!\n";

            continue;
        }


        // Header

        for (
            int j = 0;
            j < t.brojStupaca;
            j++
        ) {

            out
                << t.stupci[j];


            if (
                j < t.brojStupaca - 1
            ) {

                out << ";";
            }
        }


        out << "\n";


        // Redovi

        for (
            int r = 0;
            r < t.brojRedova;
            r++
        ) {

            for (
                int c = 0;
                c < t.brojStupaca;
                c++
            ) {

                out
                    << t.redovi[r]
                        .vrijednosti[c];


                if (
                    c < t.brojStupaca - 1
                ) {

                    out << ";";
                }
            }


            out << "\n";
        }


        out.close();
    }


    schema.close();


    cout
        << "Cijela baza je uspjesno spremljena.\n";
}


// ======================================================
// UCITAVANJE BAZE
// ======================================================

bool ucitajBazu(
    BazaPodataka& baza
) {

    ifstream schema(
        "schema.txt"
    );


    if (!schema) {

        return false;
    }


    // ----------------------------------
    // NAZIV BAZE
    // ----------------------------------

    getline(
        schema,
        baza.naziv
    );


    string linija;


    // ----------------------------------
    // BROJ TABLICA
    // ----------------------------------

    getline(
        schema,
        linija
    );


    try {

        baza.brojTablica =
            stoi(linija);
    }

    catch (...) {

        return false;
    }


    if (
        baza.brojTablica < 0 ||
        baza.brojTablica > MAX_TABLICA
    ) {

        return false;
    }


    // ----------------------------------
    // UCITAVANJE SVIH TABLICA
    // ----------------------------------

    for (
        int i = 0;
        i < baza.brojTablica;
        i++
    ) {

        Tablica& t =
            baza.tablice[i];


        // Naziv tablice

        getline(
            schema,
            t.naziv
        );


        // Broj stupaca

        getline(
            schema,
            linija
        );


        try {

            t.brojStupaca =
                stoi(linija);
        }

        catch (...) {

            return false;
        }


        if (
            t.brojStupaca < 0 ||
            t.brojStupaca > MAX_STUPACA
        ) {

            return false;
        }


        // Nazivi stupaca

        for (
            int j = 0;
            j < t.brojStupaca;
            j++
        ) {

            getline(
                schema,
                t.stupci[j]
            );
        }


        // PRIMARY KEY

        getline(
            schema,
            linija
        );


        try {

            t.primaryKeyIndex =
                stoi(linija);
        }

        catch (...) {

            return false;
        }


        // FOREIGN KEY broj

        getline(
            schema,
            linija
        );


        try {

            t.brojForeignKeys =
                stoi(linija);
        }

        catch (...) {

            return false;
        }


        if (
            t.brojForeignKeys < 0 ||
            t.brojForeignKeys > MAX_FK
        ) {

            return false;
        }


        // FOREIGN KEY podaci

        for (
            int j = 0;
            j < t.brojForeignKeys;
            j++
        ) {

            getline(
                schema,
                linija
            );


            stringstream ss(
                linija
            );


            getline(
                ss,
                t.foreignKeys[j].stupac,
                ';'
            );


            getline(
                ss,
                t.foreignKeys[j]
                    .referenciranaTablica,
                ';'
            );


            getline(
                ss,
                t.foreignKeys[j]
                    .referenciraniStupac,
                ';'
            );
        }


        // ----------------------------------
        // UCITAVANJE PODATAKA TABLICE
        // ----------------------------------

        ifstream in(
            t.naziv + ".txt"
        );


        t.brojRedova = 0;


        if (!in) {

            // Tablica postoji u shemi,
            // ali nema datoteku s podacima.

            continue;
        }


        // Preskacemo header

        getline(
            in,
            linija
        );


        // Ucitavanje redova

        while (
            getline(in, linija) &&
            t.brojRedova < MAX_REDOVA
        ) {

            if (
                linija.empty()
            ) {

                continue;
            }


            stringstream ss(
                linija
            );


            for (
                int c = 0;
                c < t.brojStupaca;
                c++
            ) {

                getline(
                    ss,
                    t.redovi[
                        t.brojRedova
                    ].vrijednosti[c],
                    ';'
                );
            }


            t.brojRedova++;
        }


        in.close();
    }


    schema.close();


    return true;
}
// ======================================================
// IZBORNICI
// ======================================================

void glavniIzbornik() {

    cout << "\n========================================\n";
    cout << "          MINI RELATIONAL DBMS\n";
    cout << "========================================\n";

    cout << "1. Prikazi tablice\n";
    cout << "2. Kreiraj tablicu\n";
    cout << "3. Obrisi tablicu\n";
    cout << "4. Dodaj red\n";
    cout << "5. Obrisi red\n";
    cout << "6. Prikazi sadrzaj tablice\n";
    cout << "7. Dodaj FOREIGN KEY\n";
    cout << "8. Relacijska algebra\n";
    cout << "9. Spremi bazu\n";
    cout << "10. Izlaz\n";

    cout << "========================================\n";
}


void algebraIzbornik() {

    cout << "\n========================================\n";
    cout << "          RELACIJSKA ALGEBRA\n";
    cout << "========================================\n";

    cout << "1. Selekcija (SIGMA)\n";
    cout << "2. Projekcija (PI)\n";
    cout << "3. Unija\n";
    cout << "4. Presjek\n";
    cout << "5. Razlika\n";
    cout << "6. Kartezijev produkt\n";
    cout << "7. JOIN\n";
    cout << "8. Natrag\n";

    cout << "========================================\n";
}
// ======================================================
// MAIN
// ======================================================

int main() {

    BazaPodataka baza;


    cout << "========================================\n";
    cout << "        MINI RELATIONAL DBMS v2\n";
    cout << "========================================\n";


    // Pokusaj ucitavanja postojece baze

    if (
        ucitajBazu(
            baza
        )
    ) {

        cout
            << "Postojeca baza je ucitana: "
            << baza.naziv
            << "\n";

        cout
            << "Broj tablica: "
            << baza.brojTablica
            << "\n";
    }

    else {

        cout
            << "Nije pronadena postojeca baza.\n";

        cout
            << "Kreiramo novu bazu.\n";


        cout << "Naziv baze: ";

        getline(
            cin >> ws,
            baza.naziv
        );
    }


    while (true) {

        glavniIzbornik();


        string izbor;


        cout << "Vas izbor: ";

        cin >> izbor;


        // ==================================================
        // 1. PRIKAZ TABLICA
        // ==================================================

        if (izbor == "1") {

            ispisiSveTablice(
                baza
            );
        }


        // ==================================================
        // 2. KREIRAJ TABLICU
        // ==================================================

        else if (izbor == "2") {

            kreirajTablicu(
                baza
            );
        }


        // ==================================================
        // 3. OBRISI TABLICU
        // ==================================================

        else if (izbor == "3") {

            obrisiTablicu(
                baza
            );
        }


        // ==================================================
        // 4. DODAJ RED
        // ==================================================

        else if (izbor == "4") {

            dodajRed(
                baza
            );
        }


        // ==================================================
        // 5. OBRISI RED
        // ==================================================

        else if (izbor == "5") {

            obrisiRed(
                baza
            );
        }


        // ==================================================
        // 6. PRIKAZ SADRZAJA
        // ==================================================

        else if (izbor == "6") {

            string naziv;


            cout << "Naziv tablice: ";

            getline(
                cin >> ws,
                naziv
            );


            int index =
                pronadiTablicu(
                    baza,
                    naziv
                );


            if (index == -1) {

                cout << "Tablica ne postoji!\n";
            }

            else {

                ispisiTablicu(
                    baza.tablice[index]
                );
            }
        }


        // ==================================================
        // 7. FOREIGN KEY
        // ==================================================

        else if (izbor == "7") {

            dodajForeignKey(
                baza
            );
        }


        // ==================================================
        // 8. RELACIJSKA ALGEBRA
        // ==================================================

        else if (izbor == "8") {

            while (true) {

                algebraIzbornik();


                string algebra;


                cout << "Vas izbor: ";

                cin >> algebra;


                // ==========================================
                // SELEKCIJA
                // ==========================================

                if (algebra == "1") {

                    string nazivTablice;
                    string stupac;
                    string op;
                    string vrijednost;


                    cout << "Tablica: ";

                    getline(
                        cin >> ws,
                        nazivTablice
                    );


                    int index =
                        pronadiTablicu(
                            baza,
                            nazivTablice
                        );


                    if (index == -1) {

                        cout
                            << "Tablica ne postoji!\n";

                        continue;
                    }


                    cout << "Stupac: ";

                    getline(
                        cin >> ws,
                        stupac
                    );


                    cout
                        << "Operator (=, !=, >, <, >=, <=): ";

                    cin >> op;


                    cout << "Vrijednost: ";

                    getline(
                        cin >> ws,
                        vrijednost
                    );


                    Tablica rezultat =
                        selekcija(
                            baza.tablice[index],
                            stupac,
                            op,
                            vrijednost
                        );


                    cout
                        << "\nSIGMA "
                        << stupac
                        << " "
                        << op
                        << " "
                        << vrijednost
                        << " ("
                        << nazivTablice
                        << ")\n";


                    ispisiTablicu(
                        rezultat
                    );


                    spremiRezultatUBazu(
                        baza,
                        rezultat
                    );
                }


                // ==========================================
                // UNIJA / PRESJEK / RAZLIKA /
                // KARTEZIJEV PRODUKT
                // ==========================================

                else if (
                    algebra == "3" ||
                    algebra == "4" ||
                    algebra == "5" ||
                    algebra == "6"
                ) {

                    string nazivA;
                    string nazivB;


                    cout << "Prva tablica: ";

                    getline(
                        cin >> ws,
                        nazivA
                    );


                    cout << "Druga tablica: ";

                    getline(
                        cin >> ws,
                        nazivB
                    );


                    int indexA =
                        pronadiTablicu(
                            baza,
                            nazivA
                        );


                    int indexB =
                        pronadiTablicu(
                            baza,
                            nazivB
                        );


                    if (
                        indexA == -1 ||
                        indexB == -1
                    ) {

                        cout
                            << "Jedna od tablica ne postoji!\n";

                        continue;
                    }


                    Tablica rezultat;


                    if (algebra == "3") {

                        rezultat =
                            unija(
                                baza.tablice[indexA],
                                baza.tablice[indexB]
                            );
                    }


                    else if (algebra == "4") {

                        rezultat =
                            presjek(
                                baza.tablice[indexA],
                                baza.tablice[indexB]
                            );
                    }


                    else if (algebra == "5") {

                        rezultat =
                            razlika(
                                baza.tablice[indexA],
                                baza.tablice[indexB]
                            );
                    }


                    else {

                        rezultat =
                            kartezijevProdukt(
                                baza.tablice[indexA],
                                baza.tablice[indexB]
                            );
                    }


                    ispisiTablicu(
                        rezultat
                    );


                    spremiRezultatUBazu(
                        baza,
                        rezultat
                    );
                }


                // ==========================================
                // JOIN
                // ==========================================

                else if (algebra == "7") {

                    string nazivA;
                    string nazivB;

                    string stupacA;
                    string stupacB;


                    cout << "Prva tablica: ";

                    getline(
                        cin >> ws,
                        nazivA
                    );


                    cout << "Druga tablica: ";

                    getline(
                        cin >> ws,
                        nazivB
                    );


                    int indexA =
                        pronadiTablicu(
                            baza,
                            nazivA
                        );


                    int indexB =
                        pronadiTablicu(
                            baza,
                            nazivB
                        );


                    if (
                        indexA == -1 ||
                        indexB == -1
                    ) {

                        cout
                            << "Jedna od tablica ne postoji!\n";

                        continue;
                    }


                    cout
                        << "JOIN stupac iz "
                        << nazivA
                        << ": ";

                    getline(
                        cin >> ws,
                        stupacA
                    );


                    cout
                        << "JOIN stupac iz "
                        << nazivB
                        << ": ";

                    getline(
                        cin >> ws,
                        stupacB
                    );


                    Tablica rezultat =
                        joinTablice(
                            baza.tablice[indexA],
                            baza.tablice[indexB],
                            stupacA,
                            stupacB);


                    cout
                        << "\n"
                        << nazivA
                        << " JOIN "
                        << nazivB
                        << "\nON "
                        << nazivA
                        << "."
                        << stupacA
                        << " = "
                        << nazivB
                        << "."
                        << stupacB
                        << "\n";


                    ispisiTablicu(
                        rezultat
                    );


                    spremiRezultatUBazu(
                        baza,
                        rezultat
                    );
                }


                // ==========================================
                // NATRAG
                // ==========================================

                else if (algebra == "8") {

                    break;
                }


                else {

                    cout << "Pogresan izbor!\n";
                }
            }
        }


        // ==================================================
        // 9. SPREMI BAZU
        // ==================================================

        else if (izbor == "9") {

            spremiBazu(
                baza
            );
        }


        // ==================================================
        // 10. IZLAZ
        // ==================================================

        else if (izbor == "10") {

            string odgovor;


            cout
                << "Zelite li spremiti bazu prije izlaska? "
                << "(da/ne): ";

            cin >> odgovor;


            if (
                malim(odgovor) == "da"
            ) {

                spremiBazu(
                    baza
                );
            }


            cout << "\nDovidenja!\n";

            break;
        }


        else {

            cout << "Pogresan izbor!\n";
        }
    }


    return 0;
}
