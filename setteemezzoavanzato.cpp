#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

float estrazioneCarta() {
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
        float carta = estrazioneCarta();
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

float turnoBanco() {
    float punteggio = 0.0;

    cout << "\nTurno del banco:\n";

    for (int i = 0; punteggio <= 7.5;) {
        float carta = estrazioneCarta(); 
        cout << "Carta estratta dal banco: " << carta << endl;
        punteggio += carta;
        cout << "Punteggio attuale del banco: " << punteggio << endl;

        if (punteggio > 7.5) {
            cout << "Il banco e' fuori gioco!\n";
            break;  
        }
        
        switch (int(punteggio)) {  
            case 1:
                cout << "\nIl banco continua immediatamente!\n";
                break;  

            case 2: 
            case 3:
            case 4:
                if (punteggio < 5.0) {
                    cout << "\nIl banco decide di continuare.\n";
                } else {
                    cout << "\nIl banco valuta il rischio e si ferma.\n";
                    return punteggio;  
                }
                break;

            case 5: 
            case 6:
            case 7:
                if (punteggio < 6.5) {
                    cout << "\nIl banco rischia e continua.\n";
                } else {
                    cout << "\nIl banco decide di fermarsi.\n";
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

    while (giocaAncora == 's') {
        
        float punteggioGiocatore = turnoGiocatore(nomeGiocatore);

        float punteggioBanco = 0.0;
        if (punteggioGiocatore <= 7.5) {
            punteggioBanco = turnoBanco();
        }

        cout << "\nEcco i risultati! \n";
        cout << nomeGiocatore << ": " << punteggioGiocatore << endl;
        cout << "banco: " << punteggioBanco << endl;

        if (punteggioGiocatore > 7.5 && punteggioBanco > 7.5) {
            cout << "\nEntrambi fuori gioco! Nessun vincitore.\n";
        } else if (punteggioGiocatore > 7.5) {
            cout << "\nHai perso! Il banco vince.\n";
        } else if (punteggioBanco > 7.5) {
            cout << "\nHai vinto! Il banco e' fuori gioco.\n";
        } else if (punteggioGiocatore > punteggioBanco) {
            cout << "\nHai vinto! Complimenti!\n";
        } else if (punteggioGiocatore < punteggioBanco) {
            cout << "\nHai perso! Il banco vince.\n";
        } else {
            cout << "\nPareggio! Nessun vincitore.\n";
        }

        cout << "\nDesideri giocare ancora? (s/n): ";
        cin >> giocaAncora;
    }

    cout << "Grazie per aver giocato! Alla prossima!\n";
    return 0;
}


