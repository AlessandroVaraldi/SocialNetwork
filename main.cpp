#include <iostream>
#include <vector>
#include "Logger.h"
#include "News.h"
#include "User.h"
#include "Simple_User.h"
#include "Company_User.h"

using namespace std;

int main(int argc, char* argv[]) {
    int access, like_dislike;
    string simple_user_ID, company_user_ID, group_user_ID, user_type, ID, date, answer, publisher_ID, message;
    string name,surname,address,product,activity,gender;
    string fields_to_assign[7];
    for(int i = 0; i < 6; i++){
        fields_to_assign[i] = "";
    }

    Logger logger(argv[1],argv[2],argv[3]);

    if(!logger.areFilesOpen()){
       cerr <<  "Errore: i file non sono stati aperti correttamente" << endl;
       return -1;
    }

    if(!logger.isUserFileCorrect()){
        cerr << "Errore: errore di formattazione nel file utenti alla linea: " << logger.errorLine() << endl;
        return -1;
    }
    if(!logger.isRelFileCorrect()){
        cerr << "Errore: errore di formattazione nel file relazioni alla linea: " << logger.errorLine() << endl;
        return -1;
    }
    if(!logger.isNewsFileCorrect()){
        cerr << "Errore: errore di formattazione nel file news alla linea: " << logger.errorLine() << endl;
        return -1;
    }

    do {
        cout << endl << endl;
        cout << "===PROGETTO DEL CORSO DI ALGORITMI E CALCOLATORI 2017-2018===" << endl;
        cout << "di Alessandro Varaldi e Alessio Naclerio" << endl << endl;
        cout << "Menu':" << endl;
        cout << "[1]- Numero utenti totali, differeniziati in base alla loro categoria d'appartenenza;" << endl;
        cout << "[2]- Numero di amici per un utente semplice;" << endl;
        cout << "[3]- Numero di parenti per un utente semplice;" << endl;
        cout << "[4]- Numero di utenti nati dopo una data;" << endl;
        cout << "[5]- Numero di dipendenti per un'azienda;" << endl;
        cout << "[6]- Numero di consociate per un'azienda;" << endl;
        cout << "[7]- Numero di utenti per un gruppo;" << endl;
        cout << "[8]- Azienda con maggior numero di dipendenti;" << endl;
        cout << "[9]- Azienda con maggior numero di dipendenti considerando anche le consociate;" << endl;
        cout << "[10]- Notizia con piu' likes;" << endl;
        cout << "[11]- Notizia con piu' dislikes;" << endl;
        cout << "[12]- Utente con il maggior numero di amici;" << endl;
        cout << "[13]- Utente con il maggior numero di conoscenti;" << endl;
        cout << "[14]- Eta' media degli utenti semplici;" << endl;
        cout << "[15]- Costruzione albero genealogico a partire da un utente semplice specifico;" << endl;
        cout << "[16]- Costruzione di tutti gli alberi genealogici;" << endl;
        cout << "[17]- Ricerca lupi solitari; " << endl;
        cout << "[18]- Classifica simpatia delle aziende; " << endl;
        cout << "[19]- Classifica simpatia delle aziende considerando anche il rapporto delle consociate; " << endl;
        cout << "[20]- Modifica utente;"<< endl;
        cout << "[21]- Aggiungi utente;" << endl;
        cout << "[22]- Rimuovi utente;"<< endl;
        cout << "[23]- Aggiungi like/dislike ad una news;"<< endl;
        cout << "[24]- Rimuovi like/dislike ad una news;"<< endl;
        cout << "[0]- Per terminare il programma;" << endl;

        cin >> access;

        switch (access) {
            case 0:
                if (logger.updateFiles(argv[1], argv[2], argv[3])) {
                    cout << "Procedura di aggiornamento file in corso...";
                    return 0;
                }else{
                    cerr << "Impossibile aprire i file per l'aggiornamento.";
                    return -1;
                }

            case 1:
                cout << "Gli utenti totali sono: " << logger.simpleUsersNumber()+logger.companyUsersNumber()+logger.groupUsersNumber()
                     << endl << "di cui:" << endl <<  "   semplici: " << logger.simpleUsersNumber() << endl
                     << "   aziende: " << logger.companyUsersNumber() << endl
                     << "   gruppi: " << logger.groupUsersNumber() << endl;
                break;

            case 2:
                cout << "Inserire l'ID dell'utente desiderato: " << endl;
                cin >> simple_user_ID;
                if(logger.findUser(simple_user_ID)) {
                    if(logger.friendsNumberSimpleUser(simple_user_ID) != -1) {
                        cout << "L'utente desiderato ha: " << logger.friendsNumberSimpleUser(simple_user_ID) << " amici"
                             << endl;
                    }else{
                       cerr << "L'ID specificato non appartiene ad un utente semplice " << endl;
                    }
                }else {
                    cerr << "L'ID specificato non appartiene a nessun utente." << endl;
                }
                break;

            case 3:
                cout << "Inserire l'ID dell'utente desiderato: " << endl;
                cin >> simple_user_ID;
                if(logger.findUser(simple_user_ID)) {
                    if (logger.relativesNumberSimpleUser(simple_user_ID) != -1) {
                        cout << "L'utente desiderato ha: " << logger.relativesNumberSimpleUser(simple_user_ID)
                             << " parenti" << endl;
                    }else{
                        cerr << "L'ID specificato non appartiene ad un utente semplice " << endl;
                    }
                }else {
                    cerr << "L'ID specificato non appartiene a nessun utente." << endl;
                }
                break;

            case 4:
                    cout << "Inserire la data nel formato dd/mm/yyyy: ";
                    cin >> date;
                    cout << "gli utenti nati dopo la data selezionata sono: " << logger.bornAfterDate(date) << endl;
                break;

            case 5:
                cout << "Inserire l'ID dell'utente azienda desiderato: " << endl;
                cin >> company_user_ID;
                if(logger.findUser(company_user_ID)) {
                    if(logger.employeesNumberCompanyUser(company_user_ID) != -1) {
                        cout << "L'utente desiderato ha: " << logger.employeesNumberCompanyUser(company_user_ID) << "dipendenti" << endl;
                    }else{
                        cerr << "L'ID specificato non e' un utente azienda " << endl;
                    }
                }else {
                    cerr << "L'ID specificato non appartiene a nessun utente azienda.";
                }
                break;

            case 6:
                cout << "Inserire l'ID dell'utente azienda desiderato: " << endl;
                cin >> company_user_ID;
                if(logger.findUser(company_user_ID)) {
                    if(logger.employeesNumberCompanyUser(company_user_ID) != -1) {
                        cout << "L'utente desiderato ha: " << logger.partnersNumberCompanyUser(company_user_ID) << "consociate " << endl;
                    }else{
                        cerr << "L'ID specificato non e' un utente azienda " << endl;
                    }
                }else {
                    cerr << "L'ID specificato non appartiene a nessun utente azienda.";
                }
                break;
            case 7:
                cout << "Inserire l'ID dell'utente gruppo desiderato: " << endl;
                cin >> group_user_ID;
                if(logger.findUser(group_user_ID)) {
                    if(logger.membersNumberGroupUser(group_user_ID)  != -1) {
                        cout << "L'utente desiderato ha: " << logger.membersNumberGroupUser(group_user_ID) << "membri" << endl;
                    }else{
                        cerr << "L'utente specificato non e' un utente gruppo." << endl;
                    }
                }else {
                    cerr << "L'ID specificato non appartiene a nessun utente gruppo." << endl;
                }
                break;
            case 8:
                logger.mostEmployees();
                break;
            case 9:
                //cout << "L'utente azienda con più dipendenti considerando anche le consociate e': " << (logger.mostEmployeesPartners())->getID() << endl;
                break;
            case 10:
                logger.mostLikes();
                break;
            case 11:
                logger.mostDislikes();
                break;
            case 12:
                logger.mostFriends();
                break;
            case 13:
                logger.mostAcquaintances();
                break;
            case 14:
                cout << "L'eta' media degli utenti semplici e': " << logger.ageAverage() << endl;
                break;
            case 15:
                cout << "Inserisci l'utente per cui fare l'albero genealogico" << endl;
                cin >> simple_user_ID;
                logger.familyTree(simple_user_ID,"albero.txt");
                break;
            case 16:
                //logger.familyTree()
                break;
            case 17:
                cout << "L'utente semplice più alto in classifica secondo i parametri di solitudine imposti e': " << (*((logger.loneWolves()).data()))->getName() << endl;
                break;
            case 18:
                cout << "L'utente azienda più alto in classifica secondo i parametri di simpatia imposti e': " << (*((logger.nicestCompany()).data()))->getName() << endl;
                break;
            case 19:
                cout << "L'utente azienda più alto in classifica secondo i parametri di simpatia imposti considerando anche le consociate e': " << (*((logger.nicestCompanyPartners()).data()))->getID();
                break;
            case 20:
                cout << "specificare il tipo di utente si vuole modificare" << endl;
                cin >> user_type;
                if(user_type == "simple"){
                    cout << "inserire l' ID dell'utente:" << endl;
                    cin >> ID;
                    cout << "campo1: nome, campo2: cosgnome, campo3: data (dd/mm/yyyy), campo4: indirizzo(via-numero-citta'-regione-paese), campo5:genere, campo6: ID" << endl;
                    for(int i = 0; i < 6; i++){
                        cout << "inserire sì se si vuole modificare il campo " << i + 1 << ", altrimenti no" << endl;
                        cin >> answer;
                        if(answer == "sì") {
                            cout << "inserire il campo numero " << i + 1 << endl;
                            cin >> fields_to_assign[i];
                        }
                    }
                    logger.modifySimpleUser(ID,fields_to_assign);
                    fields_to_assign->clear(); //buggato che non cancella l'ID dall'array
                }
                if(user_type == "company"){
                    cout << "inserire l' ID dell'utente:" << endl;
                    cin >> ID;
                    cout << "campo1: nome, campo2: data (dd/mm/yyyy), campo3: indirizzo(via-numero-citta'-regione-paese), campo4: prodotto, campo5: ID" << endl;
                    for(int i = 0; i < 6; i++){
                        cout << "inserire sì se si vuole modificare il campo " << i + 1 << ", altrimenti no" << endl;
                        cin >> answer;
                        if(answer == "sì") {
                            cout << "inserire il campo numero " << i + 1 << endl;
                            cin >> fields_to_assign[i];
                        }
                    }
                    logger.modifyCompanyUser(ID,fields_to_assign);
                    fields_to_assign->clear(); //buggato che non cancella l'ID dall'array
                }
                if(user_type == "group"){
                    cout << "inserire l' ID dell'utente:" << endl;
                    cin >> ID;
                    cout << "campo1: nome, campo2: data (dd/mm/yyyy), campo3: indirizzo(via-numero-citta'-regione-paese), campo4: attività, campo5: ID" << endl;
                    for(int i = 0; i < 6; i++){
                        cout << "inserire sì se si vuole modificare il campo " << i + 1 << ", altrimenti no" << endl;
                        cin >> answer;
                        if(answer == "sì") {
                            cout << "inserire il campo numero " << i + 1 << endl;
                            cin >> fields_to_assign[i];
                        }
                    }
                    logger.modifyGroupUser(ID,fields_to_assign);
                    fields_to_assign->clear(); //buggato che non cancella l'ID dall'array
                }
                break;
            case 21:
                cout << "specificare il tipo di utente si vuole aggiungere" << endl;
                cin >> user_type;
                if(user_type == "simple"){
                    do{
                        cout << "Inserire un'ID valido e non gia' presente: " << endl;
                        cin >> ID;
                    }while(logger.findUser(ID) || !logger.isID(ID));
                    do{
                        cout << "Inserire un nome valido: " << endl;
                        cin >> name;
                    }while(!logger.isNameOrSurname(name));
                    do{
                        cout << "Inserire un cognome valido: " << endl;
                        cin >> name;
                    }while(!logger.isNameOrSurname(surname));
                    cout << "inserire sì per inserire una data, no altrimenti" << endl;
                    cin >> answer;
                    if(answer == "sì"){
                        do{
                            cout << "Inserire una data valida: " << endl;
                            cin >> date;
                        }while(!logger.isDate(date) );
                    }else{ date = "";}
                    cout << "inserire sì per inserire un indirizzo, no altrimenti" << endl;
                    cin >> answer;
                    if(answer == "sì"){
                        do{
                            cout << "Inserire un indirizzo valido: " << endl;
                            cin >> address;
                        }while(!logger.isAddress(address));
                    }else{ address = "";}
                    cout << "Inserire un genere: " << endl;
                    cin >> gender;
                    logger.addSimpleUser(ID,name,surname,date,address,gender);
                }
                if(user_type == "company"){
                    do{
                        cout << "Inserire un'ID valido e non gia' presente: " << endl;
                        cin >> ID;
                    }while(logger.findUser(ID) || !logger.isID(ID));
                    do{
                        cout << "Inserire un nome valido: " << endl;
                        cin >> name;
                    }while(!logger.isNameOrSurname(name));
                    cout << "inserire sì per inserire una data, no altrimenti" << endl;
                    cin >> answer;
                    if(answer == "sì"){
                        do{
                            cout << "Inserire una data valida: " << endl;
                            cin >> date;
                        }while(!logger.isDate(date) );
                    }else{ date = "";}
                    cout << "inserire sì per inserire un indirizzo, no altrimenti" << endl;
                    cin >> answer;
                    if(answer == "sì"){
                        do{
                            cout << "Inserire un indirizzo valido: " << endl;
                            cin >> address;
                        }while(!logger.isAddress(address));
                    }else{ address = "";}
                    cout << "Inserire un prodotto: " << endl;
                    cin >> product;
                    logger.addCompanyUser(ID,name,date,address,product);
                }
                if(user_type == "group"){
                    do{
                        cout << "Inserire un'ID valido e non gia' presente: " << endl;
                        cin >> ID;
                    }while(logger.findUser(ID) || !logger.isID(ID));
                    do{
                        cout << "Inserire un nome valido: " << endl;
                        cin >> name;
                    }while(!logger.isNameOrSurname(name));
                    cout << "inserire sì per inserire una data, no altrimenti" << endl;
                    cin >> answer;
                    if(answer == "sì"){
                        do{
                            cout << "Inserire una data valida: " << endl;
                            cin >> date;
                        }while(!logger.isDate(date) );
                    }else{ date = "";}
                    cout << "inserire sì per inserire un indirizzo, no altrimenti" << endl;
                    cin >> answer;
                    if(answer == "sì"){
                        do{
                            cout << "Inserire un indirizzo valido: " << endl;
                            cin >> address;
                        }while(!logger.isAddress(address));
                    }else{ address = "";}
                    cout << "Inserire un'attivita': " << endl;
                    cin >> activity;
                    logger.addGroupUser(ID,name,date,address,activity);
                }
                break;
            case 22:
                cout << "specificare il tipo di utente si vuole rimuovere" << endl;
                cin >> user_type;
                cout << "Inserire un' ID: " << endl;
                cin >>  ID;
                if(user_type == "simple"){
                    logger.removeSimpleUser(ID);
                }
                if(user_type == "company"){
                    logger.removeCompanyUser(ID);
                }
                if(user_type == "group"){
                    logger.removeGroupUser(ID);
                }
                break;
            case 23:
                cout << "Inserire 0 per aggiungere un like, 1 per un dislike: " << endl;
                cin >> like_dislike;
                switch (like_dislike) {
                    case 0:
                        cout << "Inserire l'ID di cui si vuole aggiungere un like: " << endl;
                        cin >> ID;
                        cout << "Inserire l'ID di chi l'ha pubblicata: " << endl;
                        cin >> publisher_ID;
                        cout << "Inserire il messaggio della news: " << endl;
                        cin >> message;
                        cout << "Inserire la data: " << endl;
                        cin >> date;
                        logger.addLikeToNews(ID, publisher_ID, date, message);
                        break;
                    case 1:
                        cout << "Inserire l'ID di cui si vuole aggiungere un dislike: " << endl;
                        cin >> ID;
                        cout << "Inserire l'ID di chi l'ha pubblicata: " << endl;
                        cin >> publisher_ID;
                        cout << "Inserire il messaggio della news: " << endl;
                        cin >> message;
                        cout << "Inserire la data: " << endl;
                        cin >> date;
                        logger.addDislikeToNews(ID, publisher_ID, date, message);
                        break;
                    default:
                        break;
                }
            case 24:
                cout << "Inserire 0 per aggiungere un like, 1 per un dislike: " << endl;
                cin >> like_dislike;
                switch (like_dislike) {
                    case 0:
                        cout << "Inserire l'ID di cui si vuole rimuovere un like: " << endl;
                        cin >> ID;
                        cout << "Inserire l'ID di chi l'ha pubblicata: " << endl;
                        cin >> publisher_ID;
                        cout << "Inserire il messaggio della news: " << endl;
                        cin >> message;
                        cout << "Inserire la data: " << endl;
                        cin >> date;
                        logger.removeLikeToNews(ID, publisher_ID, date, message);
                        break;
                    case 1:
                        cout << "Inserire l'ID di cui si vuole rimuovere un dislike: " << endl;
                        cin >> ID;
                        cout << "Inserire l'ID di chi l'ha pubblicata: " << endl;
                        cin >> publisher_ID;
                        cout << "Inserire il messaggio della news: " << endl;
                        cin >> message;
                        cout << "Inserire la data: " << endl;
                        cin >> date;
                        logger.removeDislikeToNews(ID, publisher_ID, date, message);
                        break;
                    default:
                        break;
                }

            default: break;
        }
    }while(access != -1);


    return 0;
}