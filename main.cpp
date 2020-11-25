
//
//  main.cpp
//  projekatNTP
//
//  Created by Adin Jahic,Lamija Imamovic,Nejra Halilovic on 03/06/2020.
//  Copyright © 2020 Adin Jahic,Lamija Imamovic,Nejra Halilovic. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;
struct date {
public:
    int dan;
    int mjesec;
    int godina;
public:
    friend ostream &operator<<(ostream& output, const date& datum){
        output <<datum.dan<<"/"<<datum.mjesec<<"/"<<datum.godina<<"."<<endl;
        return output;
    };
};
struct Knjiga : public date{
public:
    date datumIzdavanja;
    vector <string> KodKogaJe;
    string ImeKnjige;
    string PisacKnjige;
    int IDKnjige;
    int Kolicina;
    int KolicinaZaduzenih = 0;
    int track;
    bool zaduzena;
public:
    Knjiga(){};
    Knjiga(int ID,int Kol,string ime,string pisac,int d,int m,int g)
    :IDKnjige(ID),Kolicina(Kol),ImeKnjige(ime),PisacKnjige(pisac){
        datumIzdavanja.dan = d;
        datumIzdavanja.mjesec = m;
        datumIzdavanja.godina = g;
    };
    string DajIme()const{return ImeKnjige;};
    string DajPisca()const{return PisacKnjige;};
    int DajID()const{return IDKnjige;};
    int DajKolicinu()const{return Kolicina;};
    int DajKolZaduzenih()const{return KolicinaZaduzenih;};
    date DajDatum()const{return datumIzdavanja;};

    void ispisi(){
        cout << *this <<endl;
    }
    friend ostream &operator<<(ostream& output, Knjiga& obj){
        output<<"Ime: "<<obj.DajIme()<<endl;
        output<<"Pisac: "<<obj.DajPisca()<<endl;
        output<<"ID: "<<obj.DajID()<<endl;
        output<<"Kolicina: "<<obj.DajKolicinu()<<endl;
        output<<"Datum Izdavanja: "<<obj.DajDatum()<<endl;
        output<<"Broj Zaduzenih knjiga: "<<obj.KolicinaZaduzenih<<endl;
        output<<"Zaduzena kod: "<<endl;
        for(int i = 0 ; i < obj.KodKogaJe.size(); i++){
            output << obj.KodKogaJe[i]<<endl;
        }
        return output;
    }


};
struct Biblioteka : public Knjiga{
private:

    Knjiga** lista;
    const int MaxBrojKnjiga;
    int current = 0;
    int suma = 0;
public:
    Biblioteka(int broj):MaxBrojKnjiga(broj),lista(new Knjiga*[broj]){

    };
    void kreirajKnjigu(Knjiga nova){
        lista[current++] = new Knjiga(nova.DajID(),nova.DajKolicinu(),nova.DajIme(),nova.DajPisca(),nova.datumIzdavanja.dan,nova.datumIzdavanja.mjesec,nova.datumIzdavanja.godina);
    };

    void zaduziKnjigu(int id,string ime){
        for(int i = 0 ; i < MaxBrojKnjiga; i++){
            if(lista[i]->DajID() == id){

                if(lista[i]->KolicinaZaduzenih < lista[i]->DajKolicinu()){
                    lista[i]->KolicinaZaduzenih++;
                    lista[i]->zaduzena = true;
                    lista[i]->KodKogaJe.push_back(ime);
                }
                else{
                    cout <<"Nema Knjiga vise za zaduziti!"<<endl;
                }
            }
        }};
    void razduziKnjigu(int id,string ime){
        for(int i = 0 ; i < MaxBrojKnjiga; i++){
            if(lista[i]->DajID() == id){
                lista[i]->zaduzena = false;
                lista[i]->KolicinaZaduzenih--;
                for(int j = 0 ; j < lista[i]->KodKogaJe.size() ; j++){
                    if (lista[i]->KodKogaJe[j] == ime) {
                        lista[i]->KodKogaJe.erase(lista[i]->KodKogaJe.begin()+j);
                    }
                }
            }
        }};
    void ispisiZaduzene(){
        for(int i = 0 ; i < MaxBrojKnjiga; i++){
            if(lista[i]->zaduzena == true)
                cout <<*lista[i];
            cout<<"------>"<<endl;
        }};
    void ispisiSlobodne(){
        for(int i = 0 ; i < MaxBrojKnjiga; i++){
            if(lista[i]->zaduzena == false)
                cout <<*lista[i];
            cout <<"----->"<<endl;
        }};
    void ispisiSve(){
        for(int i = 0 ; i < MaxBrojKnjiga; i++){
                cout <<*lista[i]<<endl;
            cout <<"------>"<<endl;
        }};
    void ispisiNeku(int id){
        for(int i = 0 ; i < MaxBrojKnjiga; i++){
            if(lista[i]->DajID() == id){
                cout <<*lista[i]<<endl;
                cout <<"-------->"<<endl;
                break;
            }
        }
    }
    int SumaKnjiga(){
        for(int i = 0 ; i < MaxBrojKnjiga; i++){
            suma+=lista[i]->DajKolicinu();
        }
        return suma;
    }
    void ispisinafajl(){
        ofstream mojFajl;
        mojFajl.open("Lista.txt",ios::app);
        for(int i = 0 ; i < MaxBrojKnjiga ; i++){
            mojFajl << *lista[i]<<endl;
            mojFajl <<"---------------------->"<<endl;
        }
        cout <<"Ispisano na fajl!"<<endl;
        mojFajl.close();
    }
};
void formirajInterface(Biblioteka &neka,int velicina);
int main(int argc, const char * argv[]) {
    cout <<"Unesi Broj Knjiga za Biblioteku: ";
    int broj;
    cin >> broj;
    Biblioteka velika(broj);
    formirajInterface(velika,broj);
}




void formirajInterface(Biblioteka &neka,int velicina){
    cout <<"------------------------------------------------>"<<endl;
    cout <<"Dobrodosli u Library Sistem 2020"<<endl;
    cout <<"Created by Adin Jahic,Lamija Imamovic,Nejra Halilovic"<<endl;
    cout <<"------------------------------------------------>"<<endl;
    cout <<"Mogucnosti: "<<endl;
    cout <<"a) Unesi Knjige"<<endl;
    cout <<"b) Exportuj u fajl"<<endl;
    cout <<"c) Zaduzi knjigu"<<endl;
    cout <<"d) Razduzi knjigu"<<endl;
    cout <<"e) Ispisi sve knjige"<<endl;
    cout <<"f) Ispisi zaduzene"<<endl;
    cout <<"g) Ispisi razduzene"<<endl;
    cout <<"h) Ispisi Neku knjigu"<<endl;
    cout <<"i) Ispisi Kolicinu svih knjiga"<<endl;
    cout <<"x) IZADJI IZ MENIA"<<endl;
    cout <<"------------------------------------->"<<endl;
    char izbor;
    cout <<"Unesi izbor: ";
    cin >>izbor;
    cout <<"------------------------------------->"<<endl;
    switch (izbor) {
        case 'a': {
            for(int i = 0 ; i < velicina;i++){
                cout <<i+1<<".Knjiga: "<<endl;
                cout <<"Unesi pisca knjige: ";
                string pisac;
                getchar();
                getline(cin,pisac);
                cout <<"Unesi ime knjige: ";
                string ime;
                getline(cin,ime);
                int d,m,g;
                cout<<"Unesi datum izdavanja: ";
                cin >>d>>m>>g;
                int kol;
                cout <<"Unesi kolicinu Knjige: ";
                cin >>kol;
                Knjiga nova(i+1,kol,ime,pisac,d,m,g);
                neka.kreirajKnjigu(nova);
                cout <<"----->"<<endl;
            }
            formirajInterface(neka,velicina);
            break;
        }
        case 'b': { //file export
            neka.ispisinafajl();
            formirajInterface(neka,velicina);
            break;
        }
        case 'c':{ //zaduziKnjigu
            int id;
            string ime;
            cout <<"Unesi ID Knjige za zaduzit: ";
            cin >>id;
            cout <<"Unesi ime na koje se knjiga zaduzuje: ";
            getchar();
            getline(cin,ime);
            neka.zaduziKnjigu(id,ime);
            formirajInterface(neka,velicina);
            break;
        }
        case 'd':{ //razduziKnjigu
            string ime;
            int id;
            cout <<"Unesi ID Knjige za razduzit: ";
            cin  >>id;
            cout <<"Unesi ime na koje se knjiga razduzuje: ";
            getchar();
            getline(cin,ime);
            neka.razduziKnjigu(id,ime);
            formirajInterface(neka,velicina);
            break;
        }
        case 'e':{ //ispisiSve
            neka.ispisiSve();
            formirajInterface(neka,velicina);
            break;
        }
        case 'f':{ //ispisiZaduzene
            neka.ispisiZaduzene();
            formirajInterface(neka,velicina);
            break;
        }
        case 'g':{ //ispisiRazduzene
            neka.ispisiSlobodne();
            formirajInterface(neka,velicina);
            break;
        }
        case 'h':{ //ispisiNeku
            int id;
            cout <<"Unesi ID Knjige za ispis: ";
            cin >>id;
            neka.ispisiNeku(id);
            formirajInterface(neka,velicina);
            break;
        }
        case 'i':{ //suma svih
            cout <<"Suma svih je: "<<neka.SumaKnjiga()<<endl;
            formirajInterface(neka,velicina);
            break;
        }
        case 'x':{ //exitcase
            cout <<"Hvala na koristenju!"<<endl;
            break;
        }

    }
}


