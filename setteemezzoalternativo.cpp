#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

float estrazioneCarta() {
    int carta = rand() % 10 + 1; 
    if (carta > 7) {
        return 0.5; 
    } else {
        return carta; 
    }
}

float effettoBiricchino(float carta) {
    if ((int)carta % 2 == 0) {
        cout << "Il jolly Biricchino ha raddoppiato la carta!\n";
        return carta * 2; 
    }
    return carta;
}

float effettoImperatore(float carta) {
    if ((int)carta % 2 != 0) {
        cout << "Il jolly Imperatore ha raddoppiato la carta!\n";
        return carta * 2; 
    }
    return carta;
}

int effettoCompitoInClasse(float punteggio) {
    if (punteggio >= 6) {
        cout << "Hai guadagnato 50 fiches perchè hai fatto 6 o piu'!\n";
        return 50; 
    } else if (punteggio == 7) {
        cout << "Per un soffio , hai guadagnato 150 fiches!\n";
        return 150; 
    }
    return 0; 
}

bool effettoMatto(float carta, int fiches) {
    float valoreMatto = rand() % 10 + 1;
    if (valoreMatto > 7) {
        valoreMatto = 0.5;
    }
    cout << "Il matto ha estratto il valore: " << valoreMatto << endl;

    if (valoreMatto == carta) {
        cout << "Hai beccato il valore del matto! Hai vinto 150 fiches!\n";
        fiches += 150;
        return true; 
    }

    return false; 
}

float turnoGiocatore(string nome, int fiches, int sceltaJolly) {
    float punteggio = 0.0;
    char scelta = 's'; 

    cout << "\nTurno di " << nome << ":\n";

    while (scelta == 's') { 
        float carta = estrazioneCarta();
        cout << "Carta estratta: " << carta << endl;

        switch (sceltaJolly) {
            case 1: 
                carta = effettoBiricchino(carta);
                break;
            case 2:
                carta = effettoImperatore(carta);
                break;
            case 3:
                {
                    int bonus = effettoCompitoInClasse(punteggio);
                    if (bonus > 0) {
                        cout << "Hai guadagnato " << bonus << " fiches!\n";
                        fiches += bonus;
                    }
                }
                break;
            case 4:
                if (effettoMatto(carta, punteggio)) {
                    return punteggio; 
                }
                break;
        }

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

float turnoBanco(int sceltaJolly) {
    float punteggio = 0.0;

    cout << "\nTurno del banco:\n";

    while (punteggio <= 7.5) {
        float carta = estrazioneCarta(); 
        cout << "Carta estratta dal banco: " << carta << endl;

        switch (sceltaJolly) {
            case 1:
                carta = effettoBiricchino(carta);
                break;
            case 2:
                carta = effettoImperatore(carta);
                break;
            case 3:
                {
                    int bonus = effettoCompitoInClasse(punteggio);
                    if (bonus > 0) {
                        cout << "Il banco ha guadagnato " << bonus << " fiches!\n";
                        fiches += bonus;
                    }
                }
                break;
            case 4:
                effettoMatto(carta, punteggio);
                break;
        }

        punteggio += carta;
        cout << "Punteggio attuale del banco: " << punteggio << endl;

        if (punteggio > 7.5) {
            cout << "Il banco è fuori gioco!\n";
            break;  
        }

        if (punteggio < 5.0) {
            cout << "\nIl banco decide di continuare.\n";
        } else if (punteggio < 6.5) {
            cout << "\nIl banco rischia e continua.\n";
        } else {
            cout << "\nIl banco si ferma.\n";
            break;
        }
    }

    return punteggio;
}

int scegliJolly() {
    cout << "\nScegli un jolly:\n";
    cout << "1: Biricchino\n";
    cout << "2: Imperatore\n";
    cout << "3: Compito in classe\n";
    cout << "4: Matto\n";
    cout << "Inserisci il numero del jolly che desideri: ";
    int scelta;
    cin >> scelta;
    return scelta;
}

int main() {
    srand(time(0)); 
    char giocaAncora = 's'; 
    
    string nomeGiocatore;
    cout << "Benvenuto nel gioco del 7 e mezzo!\n";
    cout << "Inserisci il tuo nome: ";
    cin >> nomeGiocatore;

    int fiches = 1000; 

    while (giocaAncora == 's') {
        
        int sceltaJolly = scegliJolly();

        float punteggioGiocatore = turnoGiocatore(nomeGiocatore, fiches, sceltaJolly);

        float punteggioBanco = 0.0;
        if (punteggioGiocatore <= 7.5) {
            punteggioBanco = turnoBanco(sceltaJolly);
        }

        cout << "\nEcco i risultati! \n";
        cout << nomeGiocatore << ": " << punteggioGiocatore << " punti\n";
        cout << "Banco: " << punteggioBanco << " punti\n";

        if (punteggioGiocatore > 7.5 && punteggioBanco > 7.5) {
            cout << "\nEntrambi fuori gioco! Nessun vincitore.\n";
        } else if (punteggioGiocatore > 7.5) {
            cout << "\nHai perso! Il banco vince.\n";
        } else if (punteggioBanco > 7.5) {
            cout << "\nHai vinto! Il banco è fuori gioco.\n";
            fiches += 100;
        } else if (punteggioGiocatore > punteggioBanco) {
            cout << "\nHai vinto! Complimenti!\n";
            fiches += 100;
        } else if (punteggioGiocatore < punteggioBanco) {
            cout << "\nHai perso! Il banco vince.\n";
        } else {
            cout << "\nPareggio! Nessun vincitore.\n";
        }

        cout << "Le tue fiches attuali: " << fiches << endl;

        cout << "\nDesideri giocare ancora? (s/n): ";
        cin >> giocaAncora;
    }

    cout << "Grazie per aver giocato! Alla prossima!\n";
    return 0;
}
