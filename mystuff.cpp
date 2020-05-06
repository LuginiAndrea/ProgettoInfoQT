#include "mystuff.h"
#include "QDateTime"
#include "QString"
#include "QDateTime"


using namespace myStuff;


//CLASSE DATA-ORA

//Constructor

Data_ora::Data_ora(int __giorno, int __mese, int __anno, int __ora, int __minuto) noexcept{
    _giorno = __giorno;
    _mese = __mese;
    _anno = __anno;
    _minuto = __minuto;
    _ora = __ora;
}

Data_ora::Data_ora() noexcept {
    QDateTime dataTime = QDateTime::currentDateTime();
    _giorno = dataTime.toString("d").toInt();
    _mese = dataTime.toString("m").toInt();
    _anno = dataTime.toString("yyyy").toInt();
    _ora = dataTime.toString("h").toInt();
    _minuto = dataTime.toString("m").toInt();
}


//Assignment operator

const Data_ora& Data_ora::operator= (const Data_ora& __other) noexcept {
    _giorno = __other._giorno;
    _mese = __other._mese;
    _anno = __other._anno;
    _minuto = __other._minuto;
    _ora = __other._ora;
    return *this;
}


bool Data_ora::operator> (const Data_ora& __other) const noexcept{

    if (__other._anno > _anno) return false;

    else {

        if (__other._anno < _anno) return true;

        else {
            if (__other._mese > _mese) return false;

            else {

                if (__other._mese < _mese) return true;

                else {

                    if (__other._giorno > _giorno) return false;

                    else {

                        if (__other._giorno < _giorno) return true;

                        else {

                            if (__other._ora > _ora) return false;

                            else {

                                if (__other._ora < _ora) return true;

                                else {
                                    if (__other._minuto > _minuto) return false;

                                    else {

                                        if (__other._minuto < _minuto) return true;
                                        else return false;
                                   }
                                }
                            }
                         }
                      }
                   }
              }
         }
     }

 }

bool Data_ora::operator== (const Data_ora& __other) const noexcept {

    if (_anno == __other._anno)
        if (_mese == __other._mese)
            if (_giorno == __other._giorno)
                if (_ora == __other._ora)
                    if (_minuto == __other._minuto)
                        return true;
   return false;

}

const QString Data_ora::to_String() const {
    return (QString::number(_anno) + "," + QString::number(_mese) + "," + QString::number(_giorno) + "," + QString::number(_ora) + "," + QString::number(_minuto));
}

bool Data_ora::operator< (const Data_ora& __other) const noexcept {
    return !(*this > __other); //Contrario del maggiore
}

bool Data_ora::operator!= (const Data_ora& __other) const noexcept {
    return  !(*this == __other);
}

const QString Data_ora::Data_to_string () const noexcept {
     return  (QString::number(_giorno) + " / " + QString::number(_mese) + " / " + QString::number(_anno));
}

const QString Data_ora::Orario_to_string () const noexcept {
     return  (QString::number(_ora) + " : " + QString::number(_minuto));
}

void Data_ora::operator= (const QString& __convert) {
    QStringList dati = __convert.split(",");
    _anno = dati[0].toInt();
    _mese = dati[1].toInt();
    _giorno = dati[2].toInt();
    _ora = dati[3].toInt();
    _minuto = dati[4].toInt();
}

void Data_ora::operator=(const QDateTime& dataTime) {
    _giorno = dataTime.toString("d").toInt();
    _mese = dataTime.toString("m").toInt();
    _anno = dataTime.toString("yyyy").toInt();
    _ora = dataTime.toString("h").toInt();
    _minuto = dataTime.toString("m").toInt();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//---------------------------Treno-----------------------------------------


//Constructors

Treno::Treno() {}
Treno::Treno(std::size_t __posti_prima_classe, std::size_t __posti_seconda_classe, std::size_t __numero_carrozze,
              int __piattaforma, Data_ora __giorno_ora, QVector<float>&& __durata_tratta, QVector<float>&& __costo_tratta_prima_classe, QVector<float>&&  __costo_biglietto_tratte_seconda_classe,
              QVector<QString>&& __stazioni_attraversate, QString&& __codice_treno, QString&& __tipo_treno, QString&& __compagnia ) noexcept{

    _posti_prima_classe = __posti_prima_classe;
    _posti_seconda_classe = __posti_seconda_classe;
    _numero_carrozze = __numero_carrozze;
    _durata_tratta = std::move (__durata_tratta);
    _piattaforma = __piattaforma;
    _giorno_orario = __giorno_ora;
    _costo_biglietto_tratte_prima_classe = std::move (__costo_tratta_prima_classe);
    _costo_biglietto_tratte_seconda_classe = std::move ( __costo_biglietto_tratte_seconda_classe);
    _tipo_treno = __tipo_treno;
    _compagnia = __compagnia;
    _codice_treno = __codice_treno;
    _stazioni_attraversate = std::move (__stazioni_attraversate);
}

Treno::Treno(Treno&& __other) noexcept{

    _posti_prima_classe = __other._posti_prima_classe;
   _posti_rimanenti_prima_classe = __other._posti_rimanenti_prima_classe;
   _posti_seconda_classe = __other._posti_seconda_classe;
   _posti_rimanenti_seconda_classe = __other._posti_rimanenti_seconda_classe;
   _numero_carrozze = __other._numero_carrozze;
   _durata_tratta = __other._durata_tratta;
   _piattaforma = __other._piattaforma;
   _giorno_orario = __other._giorno_orario;
   _costo_biglietto_tratte_prima_classe = std::move (__other._costo_biglietto_tratte_prima_classe);
   _costo_biglietto_tratte_seconda_classe = std::move ( __other._costo_biglietto_tratte_seconda_classe);
   _stazioni_attraversate = std::move (__other._stazioni_attraversate);
   _tipo_treno = std::move(__other._tipo_treno);
   _compagnia = std::move (__other._compagnia);
   _codice_treno = std::move(__other._codice_treno);

   }


Treno::Treno(const Treno& __other) noexcept{

    _posti_prima_classe = __other._posti_prima_classe;
   _posti_rimanenti_prima_classe = __other._posti_rimanenti_prima_classe;
   _posti_seconda_classe = __other._posti_seconda_classe;
   _posti_rimanenti_seconda_classe = __other._posti_rimanenti_seconda_classe;
   _numero_carrozze = __other._numero_carrozze;
   _durata_tratta = __other._durata_tratta;
   _piattaforma = __other._piattaforma;
   _giorno_orario = __other._giorno_orario;
   _costo_biglietto_tratte_prima_classe = __other._costo_biglietto_tratte_prima_classe;
   _costo_biglietto_tratte_seconda_classe =  __other._costo_biglietto_tratte_seconda_classe;
   _stazioni_attraversate = __other._stazioni_attraversate;
   _tipo_treno = __other._tipo_treno;
   _compagnia = __other._compagnia;
   _codice_treno = __other._codice_treno;

   }

/////////////////////////////////////////////////////////////////////


//------------------Move assignment operator

const Treno& Treno::operator=(Treno&& __other) noexcept{
    _posti_prima_classe = __other._posti_prima_classe;
    _posti_rimanenti_prima_classe = __other._posti_rimanenti_prima_classe;
    _posti_seconda_classe = __other._posti_seconda_classe;
    _posti_rimanenti_seconda_classe = __other._posti_rimanenti_seconda_classe;
    _numero_carrozze = __other._numero_carrozze;
    _durata_tratta = std::move(__other._durata_tratta);
    _costo_biglietto_tratte_prima_classe = std::move (__other._costo_biglietto_tratte_prima_classe);
    _costo_biglietto_tratte_seconda_classe = std::move ( __other._costo_biglietto_tratte_seconda_classe);
    _stazioni_attraversate = std::move (__other._stazioni_attraversate);
    _tipo_treno = std::move(__other._tipo_treno);
    _compagnia = std::move (__other._compagnia);
    _piattaforma = __other._piattaforma;
    _giorno_orario = __other._giorno_orario;
    _codice_treno = std::move(__other._codice_treno);
    return *this;
}

const Treno& Treno::operator=(const Treno& __other) noexcept{

    _posti_prima_classe = __other._posti_prima_classe;
   _posti_rimanenti_prima_classe = __other._posti_rimanenti_prima_classe;
   _posti_seconda_classe = __other._posti_seconda_classe;
   _posti_rimanenti_seconda_classe = __other._posti_rimanenti_seconda_classe;
   _numero_carrozze = __other._numero_carrozze;
   _durata_tratta = __other._durata_tratta;
   _piattaforma = __other._piattaforma;
   _giorno_orario = __other._giorno_orario;
   _costo_biglietto_tratte_prima_classe = __other._costo_biglietto_tratte_prima_classe;
   _costo_biglietto_tratte_seconda_classe =  __other._costo_biglietto_tratte_seconda_classe;
   _stazioni_attraversate = __other._stazioni_attraversate;
   _tipo_treno = __other._tipo_treno;
   _compagnia = __other._compagnia;
   _codice_treno = __other._codice_treno;
   return *this;
}



bool Treno::operator>(const Treno &__other) const noexcept { return (_giorno_orario > __other._giorno_orario); }
bool Treno::operator<(const Treno &__other) const noexcept { return !(*this > __other); }
bool Treno::operator==(const Treno& __other) const {
    if (_piattaforma == __other._piattaforma)
        if (_giorno_orario == __other._giorno_orario) return  true;
    return false;
}

bool Treno::operator!=(const Treno& __other) const {
    return !(*this == __other);
}



/////////////////////////////////////////////////////////////////////


void User::to_String_List(QStringList &__to_return) const {

    __to_return << QString::number(credito);
    QStringList temp;
        foreach (const auto& elem, treni_prenotati) {
             elem.to_String_List(temp);
             __to_return += temp;

        }

}

//////////////////////////////////////////////////////////////////

void myStuff::carica_dati_user(User& now_user) {

    QStringList tmp = now_user.credenziali.split(",");
    QFile file("Files/UsersData/" + tmp[0] + tmp [1] +".txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        myStuff::messaggio("ERRORE!", "Errore nell'apertura del file");
        file.close();
        exit(EXIT_FAILURE);
    }

    else {
        tmp.clear();
        tmp << "";
        tmp << "";
        tmp << "";
        QTextStream stream(&file);
        user_treno tempTrain;

        now_user.credito = stream.readLine().toFloat();

        while(!stream.atEnd()) {
            tmp [0] = stream.readLine();
            tmp [1] = stream.readLine();
            tmp [2] = stream.readLine();
            tempTrain = tmp;
            now_user.treni_prenotati.push_back(tempTrain);
            for (auto val:tmp )
                myStuff::messaggio("Val2",val);
        }

        file.close();
    }

}


void myStuff::scrivi_dati_user(const User& now_user) {

    myStuff::messaggio("o","scrivo");
    QStringList tmp = now_user.credenziali.split(",");
    QFile file("Files/UsersData/" + tmp[0] + tmp [1] +".txt");

    if (!file.open(QIODevice::WriteOnly| QIODevice::Text)) {
        myStuff::messaggio("ERRORE!", "Errore nell'apertura del file");
        file.close();
        exit(EXIT_FAILURE);
    }

    else {
           file.resize(0);
           QTextStream stream(&file);
           myStuff::messaggio("",stream.readLine());
           tmp.clear();
           stream << "\n";
           now_user.to_String_List(tmp);

           foreach (const auto& val, tmp) {
               myStuff::messaggio("Val1",val);
               stream << val << "\n";
            }

           file.close();
   }


}


void myStuff::load_user_trains (QVector<myStuff::user_treno>& vettore_treni_user, QVector<myStuff::Treno>& vettore_treni) { //Carica il vettore dei treni di un user

    for (auto& treno : vettore_treni)
        for (auto& user_treno_var : vettore_treni_user)
            if (user_treno_var._codice_treno_puntato == treno._codice_treno) //Se tra i codici memorizzati nel vettore dell'user corrisponde nel vettore dei treni
                 user_treno_var.set_ptr(&treno);                            //Il puntatore della lista punta a quel treno

    for (auto it = vettore_treni_user.begin(); it != vettore_treni_user.end(); ++it) //Scorre tutto il vettore e se un treno puntato non corrisponde eliminiamo l'elemento dal vettore
        if (it->get_ptr() == nullptr) vettore_treni_user.erase(it); //It è un iteratore, un "super-puntatore" che serve a riferirisi a dei punti del contenitore al quale appartengono
}




void myStuff::messaggio (const QString& TITLE, const QString& MSG) {
    QMessageBox msg;
    msg.setText(MSG);
    msg.setWindowTitle(TITLE);
    msg.exec();
}












































