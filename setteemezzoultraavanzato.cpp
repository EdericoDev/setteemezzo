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
                cout << "\nIl mazziere continua senza indugio!\n";
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
                    cout << "\nIl mazziere decide di fermarsi. Per un soffio!\n";
                    return punteggio;  
                }
                break;
        }
    }

    return punteggio;
}

bool eWeekend(int& giornoDellaSettimana) {
    time_t adesso = time(0);
    tm* orarioLocale = localtime(&adesso);
    giornoDellaSettimana = orarioLocale->tm_wday; 
    return (giornoDellaSettimana == 0 || giornoDellaSettimana == 6); // 0 corrisponde a domenica mentre 6 a sabato.
}

int main() {
    srand(time(0)); 
    char giocaAncora = 's'; 
    
    int fichesGiocatore = 100; 
    int fichesMazziere = 1000; 
    
    const float valoreFichesInfrasettimanale = 0.5; // Le fiches valgono 0.50 euro se è un giorno infrasettimanale
    const float valoreFichesWeekend = 0.7; // Le fiches valgono 0.70 euro se è un giorno infrasettimanale
    const float tassaPercentuale = 8.0; // tassa che si prende il casino 
    
    int giornoDellaSettimana;
    bool weekend = eWeekend(giornoDellaSettimana);
    float valoreFichesInEuro;
    if (weekend) {
    valoreFichesInEuro = valoreFichesWeekend; 
    } 
	else {
    valoreFichesInEuro = valoreFichesInfrasettimanale; 
    }
    
    string nomeGiocatore;
        cout << "Benvenuto nel gioco del 7 e mezzo, Come ti chiami?\n\n";
        cin >> nomeGiocatore;
        
    cout << "Oggi e' ";

    switch (giornoDellaSettimana) {
        case 0: cout << "Domenica"; break;
        case 1: cout << "Lunedi"; break;
        case 2: cout << "Martedi"; break;
        case 3: cout << "Mercoledi"; break;
        case 4: cout << "Giovedi"; break;
        case 5: cout << "Venerdi"; break;
        case 6: cout << "Sabato"; break;
        default: cout << "Errore"; break;
    }

    cout << ", quindi le fiches valgono " << valoreFichesInEuro << " euro!\n\n";

    while (giocaAncora == 's' || giocaAncora == 'S') {
        cout << "Fiches attuali di " << nomeGiocatore << " : " << fichesGiocatore << "\n";
        cout << "Fiches attuali del mazziere: " << fichesMazziere << "\n";

        if (fichesGiocatore <= 0) {
            cout << "\nHai esaurito le fiches! Non puoi più giocare.\n";
            break;
        }

        if (fichesMazziere <= 0) {
            cout << "\nIl mazziere ha esaurito le fiches! Complimenti, hai vinto la partita.\n";
            break;
        }

        int scommessa = 0;
        cout << "Quante fiches vuoi scommettere? ";
        cin >> scommessa;

        while (scommessa <= 0 || scommessa > fichesGiocatore) {
            cout << "Scommessa non valida. Inserisci un valore tra 1 e " << fichesGiocatore << ": ";
            cin >> scommessa;
        }

        bool allIn = (scommessa == fichesGiocatore); 

        cout << "\n Adesso e' il tuo turno! \n";
        float punteggioGiocatore = turnoGiocatore("Giocatore");

        float punteggioMazziere = 0.0;
        if (punteggioGiocatore <= 7.5) {
            cout << "\n Adesso e' il turno del mazziere! \n";
            punteggioMazziere = turnoMazziere();
        }

        cout << "Risultati finali:\n";
        cout << nomeGiocatore << ": " << punteggioGiocatore << endl;
        cout << "Mazziere: " << punteggioMazziere << endl;

        if (punteggioGiocatore > 7.5 && punteggioMazziere > 7.5) {
         cout << "Entrambi fuori gioco! Nessun vincitore.\n";
        } else if (punteggioGiocatore > 7.5) {
         cout << "Hai perso! Il mazziere vince.\n";
         fichesGiocatore -= scommessa;
         fichesMazziere += scommessa;
         if (allIn) {
          cout << "Hai fatto all-in e hai perso! Esci dal gioco.\n";
          break; 
        }
        } else if (punteggioMazziere > 7.5) {
         cout << "Hai vinto! Il mazziere e' fuori gioco.\n";
          if (allIn) {
          fichesGiocatore += scommessa * 3;
          fichesMazziere -= scommessa * 3;
          cout << "All-in! Hai triplicato la vincita!\n";
        } else {
        fichesGiocatore += scommessa;
        fichesMazziere -= scommessa;
        }
        } else if (punteggioGiocatore > punteggioMazziere) {
         cout << "Hai vinto! Complimenti!\n";
         fichesGiocatore += scommessa;
         fichesMazziere -= scommessa;
        } else if (punteggioGiocatore < punteggioMazziere) {
         cout << "Hai perso! Il mazziere vince.\n";
         fichesGiocatore -= scommessa;
         fichesMazziere += scommessa;
          if (allIn) {
            cout << "Hai fatto all-in e hai perso! Esci dal gioco.\n";
            break; 
        }
        } else {
         cout << "Pareggio! Nessuno vince o perde fiches.\n";
        }

        if (fichesMazziere > 0) {
         cout << "\nDesideri fare un'altra partita? (s/n): ";
         cin >> giocaAncora;
         cout << "\n";
        } else {
        cout << "Non è possibile giocare ancora, il mazziere e' a corto di fiches.\n";
        break; 
        }
        
        if (giocaAncora == 'n' || fichesMazziere <= 0) {
         float valoreVincita = fichesGiocatore * valoreFichesInEuro;
         float tassa = valoreVincita * tassaPercentuale / 100;
         float vincitaReale = valoreVincita - tassa;

        cout << "\nValore in euro delle tue fiches (" << fichesGiocatore << ") : " << valoreVincita << " euro\n";
        cout << "Tassa sulle vincite del casino' (" << tassaPercentuale << ") : " << tassa << " euro\n";
        cout << "Vincita reale: " << vincitaReale << " euro\n";
        break;
        }
    }
	   
    cout << "Grazie per aver giocato! Alla prossima!\n";
    return 0;
}


