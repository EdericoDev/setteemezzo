#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

float estraiCarta() {
    int valore = rand() % 10 + 1; 
    if (valore > 7) {
        return 0.5; 
    } else {
        return valore; 
    }
}

float turnoGiocatore(const string& nome) {
    float punteggio = 0.0;
    char scelta = 's'; 

    cout << "\nTurno di " << nome << ":\n";

    while (scelta == 's') { 
        float carta = estraiCarta();
        cout << "Carta estratta: " << carta << endl;
        punteggio += carta;
        cout << "Punteggio attuale: " << punteggio << endl;

        if (punteggio > 7.5) {
            cout << "Sei fuori gioco!\n";
            break; 
        }

        cout << "\nVuoi estrarre un'altra carta? (s/n): ";
        cin >> scelta;
    }

    return punteggio;
}

float turnoMazziere() {
    float punteggio = 0.0;

    cout << "\nTurno del mazziere:\n";

    for (int i = 0; punteggio <= 7.5;) {
        float carta = estraiCarta(); 
        cout << "Carta estratta dal mazziere: " << carta << endl;
        punteggio += carta;
        cout << "Punteggio attuale del mazziere: " << punteggio << endl;

        if (punteggio > 7.5) {
            cout << "Il mazziere e' fuori gioco!\n";
            break;  
        }
        
        switch (int(punteggio)) {  
            case 1:
                cout << "\nIl mazziere continua immediatamente!\n";
                break;  

            case 2: 
            case 3:
            case 4:
                if (punteggio < 5.0) {
                    cout << "\nIl mazziere decide di continuare.\n";
                } else {
                    cout << "\nIl mazziere valuta il rischio e si ferma.\n";
                    return punteggio;  
                }
                break;

            case 5: 
            case 6:
            case 7:
                if (punteggio < 6.5) {
                    cout << "\nIl mazziere rischia e continua.\n";
                } else {
                    cout << "\nIl mazziere decide di fermarsi.\n";
                    return punteggio;  
                }
                break;
        }
    }

    return punteggio;
}

int main() {
    srand(time(0)); 
    char giocaAncora = 's'; 
    
    string nomeGiocatore;
        cout << "Benvenuto nel gioco del 7 e mezzo!\n";
        cout << "Inserisci il tuo nome: ";
        cin >> nomeGiocatore;

    while (giocaAncora == 's' || giocaAncora == 'S') {
        
        float punteggioGiocatore = turnoGiocatore(nomeGiocatore);

        float punteggioMazziere = 0.0;
        if (punteggioGiocatore <= 7.5) {
            punteggioMazziere = turnoMazziere();
        }

        cout << "\nEcco i risultati! \n";
        cout << nomeGiocatore << ": " << punteggioGiocatore << endl;
        cout << "Mazziere: " << punteggioMazziere << endl;

        if (punteggioGiocatore > 7.5 && punteggioMazziere > 7.5) {
            cout << "\nEntrambi fuori gioco! Nessun vincitore.\n";
        } else if (punteggioGiocatore > 7.5) {
            cout << "\nHai perso! Il mazziere vince.\n";
        } else if (punteggioMazziere > 7.5) {
            cout << "\nHai vinto! Il mazziere è fuori gioco.\n";
        } else if (punteggioGiocatore > punteggioMazziere) {
            cout << "\nHai vinto! Complimenti!\n";
        } else if (punteggioGiocatore < punteggioMazziere) {
            cout << "\nHai perso! Il mazziere vince.\n";
        } else {
            cout << "\nPareggio! Nessun vincitore.\n";
        }

        cout << "\nDesideri giocare ancora? (s/n): ";
        cin >> giocaAncora;
    }

    cout << "Grazie per aver giocato! Alla prossima!\n";
    return 0;
}


