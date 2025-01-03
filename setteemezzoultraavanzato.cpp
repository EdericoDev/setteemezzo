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

float turnoGiocatore(string nome) {
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

    while (punteggio <= 7.5) {
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
                cout << "\nIl banco continua senza indugio!\n";
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
                    cout << "\nIl banco decide di fermarsi. Per un soffio!\n";
                    return punteggio;  
                }
                break;
        }
    }

    return punteggio;
}

bool eWeekend() {  
    time_t adesso = time(0);
    tm* orarioLocale = localtime(&adesso);
    int giornoDellaSettimana = orarioLocale->tm_wday; 
    return (giornoDellaSettimana == 0 || giornoDellaSettimana == 6); // 0 corrisponde a domenica mentre 6 a sabato.
}

int main() {
    srand(time(0)); 
    char giocaAncora = 's'; 
    
    int fichesGiocatore = 100; 
    int fichesBanco = 1000; 
    
    float valoreFichesInfrasettimanale = 0.5; // Le fiches valgono 0.50 euro se è un giorno infrasettimanale
    float valoreFichesWeekend = 0.7; // Le fiches valgono 0.70 euro se è un weekend
    float tassaPercentuale = 8.0; // tassa che si prende il casino 
    
    int giornoDellaSettimana;
    bool weekend = eWeekend();
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

    while (giocaAncora == 's') {
        cout << "Fiches attuali di " << nomeGiocatore << " : " << fichesGiocatore << "\n";
        cout << "Fiches attuali del banco: " << fichesBanco << "\n";

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

        float punteggioBanco = 0.0;
        if (punteggioGiocatore <= 7.5) {
            cout << "\n Adesso e' il turno del banco! \n";
            punteggioBanco = turnoBanco();
        }

        cout << "Risultati finali:\n";
        cout << nomeGiocatore << ": " << punteggioGiocatore << endl;
        cout << "banco: " << punteggioBanco << endl;

        if (punteggioGiocatore > 7.5 && punteggioBanco > 7.5) {
         cout << "Entrambi fuori gioco! Nessun vincitore.\n";
        }
        else if (punteggioGiocatore > 7.5) {
         cout << "Hai perso! Il banco vince.\n";
         fichesGiocatore -= scommessa;
         fichesBanco += scommessa;
         if (allIn) {
          cout << "Hai fatto all-in e hai perso! Esci dal gioco.\n";
          break; 
        }
        } 
        else if (punteggioBanco > 7.5) {
         cout << "Hai vinto! Il banco e' fuori gioco.\n";
          if (allIn) {
          fichesGiocatore += scommessa * 3;
          fichesBanco -= scommessa * 3;
          cout << "All-in! Hai triplicato la vincita!\n";
        } 
        else {
        fichesGiocatore += scommessa;
        fichesBanco -= scommessa;
        }
        }
         else if (punteggioGiocatore > punteggioBanco) {
         cout << "Hai vinto! Complimenti!\n";
         fichesGiocatore += scommessa;
         fichesBanco -= scommessa;
        }
         else if (punteggioGiocatore < punteggioBanco) {
         cout << "Hai perso! Il banco vince.\n";
         fichesGiocatore -= scommessa;
         fichesBanco += scommessa;
          if (allIn) {
            cout << "Hai fatto all-in e hai perso! Esci dal gioco.\n";
            break; 
        }
        }
         else {
         cout << "Pareggio! Nessuno vince o perde fiches.\n";
        }
        
        

        if (fichesBanco > 0) {
         cout << "\nDesideri fare un'altra partita? (s/n): ";
         cin >> giocaAncora;
         cout << "\n";
        } 
        
        if (fichesBanco <= 0) {
            cout << "\nIl banco ha esaurito le fiches! Complimenti, hai vinto la partita.\n";
        }
        
        if (fichesGiocatore <= 0) {
            cout << "\nHai esaurito le fiches! Non puoi piu' giocare.\n";
            break;
        }
        
        if (giocaAncora == 'n' || fichesBanco <= 0) {
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
