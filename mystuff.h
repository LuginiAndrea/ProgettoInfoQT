#ifndef MYSTUFF_H
#define MYSTUFF_H
#include "string"
#include "QString"
#include "QFile"
#include "QVector"
#include "QTextStream"
#include "QDebug"
#include "QMessageBox"


//Implementare classe data

namespace myStuff {



class Data_ora {  //Terminata ---scrivere corpo in CPP

public:
    int _minuto;
    int _ora;
    int _giorno;
    int _mese;
    int _anno;

    Data_ora(int __giorno, int __mese, int __anno, int __ora, int __minuto) noexcept;
    Data_ora() noexcept;
    const Data_ora& operator= (const Data_ora& __other) noexcept;
    const QString Data_to_string () const noexcept;
    const QString Orario_to_string () const noexcept;

   //---------Operatori di relazione
   bool operator> (const Data_ora& __other) const noexcept;

   bool operator< (const Data_ora& __other) const noexcept;
   bool operator== (const Data_ora& __other) const noexcept;
   bool operator!= (const Data_ora& __other) const noexcept;
   const QString to_String() const;
   void operator= (const QString& __convert);
};




class Treno {   //Terminata ---scrivere corpo in CPP

public:

    std::size_t _posti_prima_classe;
    std::size_t _posti_rimanenti_prima_classe;
    std::size_t _posti_seconda_classe;
    std::size_t _posti_rimanenti_seconda_classe;
    std::size_t _numero_carrozze;
    int _piattaforma;
    Data_ora _giorno_orario;
    QVector<float> _durata_tratta; //Scritto come (ore, minuti---- es: 2.50 = 2 ore e 50 minuti)
    QVector<float> _costo_biglietto_tratte_prima_classe; //Costo per ogni tratta, es("Milano : Padova" ,"Padova : Modena", "Milano : Modena" = alla somma delle due prima)
    QVector<float> _costo_biglietto_tratte_seconda_classe; //Costo per ogni tratta, es("Milano : Padova" ,"Padova : Modena", "Milano : Modena" = alla somma delle due prima)
    QVector<QString> _stazioni_attraversate; //Tutte le stazioni separate dal carattere della virgola
    QString _codice_treno;
    QString _tipo_treno; //Frecciarossa, Regionale, ecc...
    QString _compagnia; //Nome della compagnia del treno (es:"Italo", "Trenitalia")


    //-----------------------------------------------------------Constructor
    Treno();

    Treno(std::size_t __posti_prima_classe, std::size_t __posti_seconda_classe, std::size_t __numero_carrozze,
          int __piattaforma, Data_ora giorno_orario, QVector<float>&& __durata_tratta, QVector<float>&& __costo_tratta, QVector<float>&&  __costo_biglietto_tratte_seconda_classe,
          QVector<QString>&& __stazioni_attraversate, QString&& __codice_treno, QString&& __tipo_treno, QString&& __compagnia ) noexcept;

    Treno (Treno&& __other) noexcept;
    Treno (const Treno& __other) noexcept;

    Treno(const QStringList& __to_copy);

    //----------Move assignment operator
    const Treno& operator= (Treno&& __other) noexcept;
    const Treno& operator=(const Treno& __other) noexcept;

    //---------Operatori di relazione
    bool operator> (const Treno& __other) const noexcept;
    bool operator<(const Treno &__other) const noexcept;
    bool operator== (const Treno& __other) const;
    bool operator!=(const Treno& __other) const;

    QStringList to_String_List() const {
        QStringList to_return;
        to_return << QString::number(_posti_prima_classe);
        to_return << QString::number(_posti_rimanenti_prima_classe);
        to_return << QString::number(_posti_seconda_classe);
        to_return << QString::number(_posti_rimanenti_seconda_classe);
        to_return << QString::number(_numero_carrozze);
        to_return << QString::number(_piattaforma);
        to_return << _giorno_orario.to_String();

        to_return << ""; //Prepariamo l'elemento dopo (evitiamo un out of range error)

        foreach(const auto& dato, _durata_tratta)
            to_return[7] += QString::number(dato) +","; //Separiamo da virgola

        to_return << "";

        foreach(const auto& dato, _costo_biglietto_tratte_prima_classe)
            to_return[8] += QString::number(dato)+",";

        to_return << "";

        foreach(const auto& dato, _costo_biglietto_tratte_seconda_classe)
            to_return[9] += QString::number(dato) +",";

        to_return << "";

        foreach(const auto& dato, _stazioni_attraversate)
            to_return[10] += dato +",";

        to_return << _codice_treno;
        to_return << _tipo_treno;
        to_return << _compagnia;

        return to_return;
    }

    void operator= (const QStringList& __to_copy) {

        QStringList tmp;

        _posti_prima_classe = __to_copy[0].toInt();
        _posti_rimanenti_prima_classe = __to_copy[1].toInt();
        _posti_seconda_classe = __to_copy[2].toInt();
        _posti_rimanenti_seconda_classe = __to_copy[3].toInt();
        _numero_carrozze = __to_copy[4].toInt();
        _piattaforma = __to_copy[5].toInt();
        _giorno_orario = __to_copy[6];

        tmp = __to_copy[7].split(",");

        foreach(const auto& dato, tmp)
            _durata_tratta.push_back(dato.toFloat());

        tmp = __to_copy[8].split(","); //Separiamo i valori con la virgola
        tmp.pop_back();

        foreach(const auto& dato, tmp)
            _costo_biglietto_tratte_prima_classe.push_back(dato.toFloat());

         tmp = __to_copy[9].split(","); //Separiamo i valori con la virgola
         tmp.pop_back();


        foreach(const auto& dato, tmp)
            _costo_biglietto_tratte_seconda_classe.push_back(dato.toFloat());

         tmp = __to_copy[10].split(","); //Separiamo i valori con la virgola
         tmp.pop_back();


        foreach(const auto& dato, tmp)
            _stazioni_attraversate.push_back(dato);

        _codice_treno = __to_copy[11];
        _tipo_treno = __to_copy[12];
        _compagnia = __to_copy[13];
    }

};



class user_treno {  //Aggiungere controllo anche per tratta

private:
 Treno* _treno_prenotato; //Il treno che è stato prenotato

public:
    QString _tratta; //La tratta dell'user (Stazioni separate da virgola)
    QString _codice_treno_puntato;
    QVector<bool> _prima_classe; //False = seconda classe, true = prima classe;
    user_treno(QString __tratta = "", QString __codice = "", Treno* __ptr = nullptr) {
        _treno_prenotato = __ptr;
        _tratta = __tratta;
        _codice_treno_puntato = __codice;
        _prima_classe.clear();
    }

    QStringList to_String_List () const {
        QStringList to_return;
        to_return << _tratta;
        to_return << _codice_treno_puntato;

        //to_return << ""; //Prepariamo l'elemento dopo (evitiamo un out of range error)
        to_return << "";
        foreach (const auto dato, _prima_classe)  //A int così avremo 1 e 0
            to_return[2] += QString::number(dato) +","; //Separiamo i valori con la virgola

        return to_return;
    }

    void operator= (const QStringList& __to_copy) {

        QStringList tmp;

        _tratta = __to_copy[0];
        _codice_treno_puntato = __to_copy[1];

        tmp = __to_copy[2].split(",");

        foreach(const auto& dato, tmp)
            _prima_classe.push_back(dato.toInt()); //Conversione automatica di int a bool

        _prima_classe.pop_back();



    }

    void set_ptr(Treno* __reference) { _treno_prenotato = __reference; }

    const Treno* get_ptr() const { return _treno_prenotato; }

    user_treno(const QStringList& __to_copy) {
        *this = __to_copy;
    }

    user_treno() {}
};




class User {

public:
    QString credenziali;
    float credito;
    QVector <user_treno> treni_prenotati; //Treni prenotati dall'user

    User();

    QStringList to_String_List () const;

    void operator= (const User& user) = delete; //Due utenti non possono essere uguali

};







void carica_treni_vector (QVector<Treno>& vettore_treni);
void scrivi_treni_vector(const QVector<Treno>& vettore_treni);
void carica_dati_user(User& now_user); //FATTA
void scrivi_dati_user(const User& now_user);
void load_user_trains (QVector<myStuff::user_treno>* vettore_treni_user, QVector<myStuff::Treno>* vettore_treni);
void messaggio (const QString& TITLE, const QString& MSG);


}
#endif // MYSTUFF_H
