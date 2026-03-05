#include <iostream>
#include <stdio.h>
using namespace std;

struct Adres
{
    string ulica = "";
    int nrDomu = 0;
    string miasto = "";
    int kodPocztowy = 0;
};

struct Pracownik
{
    string imie = "";
    string nazwisko = "";
    long pesel = 0;
    long telefon = 0;
    string stanowisko = "";
    int pensja = 0;
    long ID = 0;
    Adres adres;
    Pracownik *next = nullptr;
    Pracownik *prev = nullptr;
};

Pracownik *head = nullptr;
Pracownik *last = nullptr;

void menu()
{
    cout << "**Menu glowne**\n";
    cout << " 1 -> dodaj nowgo pracownika\n";
    cout << " 2 -> wyswietl pracownikow\n";
    cout << " 3 -> wyszukaj pracownika\n";
    cout << " 4 -> usun pracownika\n";
    cout << " 9 -> zakoncz program\n";
}

void menuSzukanie()
{
    cout << "1->wyszukaj po imieniu\n";
    cout << "2->wyszukaj po nazwisku\n";
    cout << "3->wyszukaj numerze PESEL\n";
}

void menuUsuwanie()
{
    cout << "1->usun po numerze ID\n";
    cout << "2->usun po nuemrze PESEL\n";
}

void wyswietlanieUsuwanie()
{
    Pracownik *temp = head;
    if (temp == nullptr)
    {
        cout << "Nie ma zadnego pracownika na liscie!\n";
    }
    while (temp != nullptr)
    {
        cout << "ID : " << temp->ID << " | " << temp->imie << " " << temp->nazwisko << " PESEL: " << temp->pesel << endl;
        cout << "---------------------------" << endl;
        temp = temp->next;
    }
}

bool sprawdzPesel(long pesel)
{
    Pracownik *temp = head;
    while (temp != nullptr)
    {
        if (temp->pesel == pesel)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void nowyPracownik()
{
    Pracownik *pracownik = new Pracownik();
    pracownik->next = nullptr;
    pracownik->prev = nullptr;

    string imie, nazwisko, ulica, miasto;
    long pesel, telefon, ID;
    int nrDomu, kodPocztowy;
    static long idCounter = 1;

    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;

    do
    {
        cout << "Podaj pesel: ";
        cin >> pesel;
        if (sprawdzPesel(pesel))
        {
            cout << "Istnieje juz taki pesel podaj inny!\n";
        }
    } while (sprawdzPesel(pesel));

    cout << "Podaj telefon: ";
    cin >> telefon;
    cout << "Podaj ulice: ";
    cin >> ulica;
    cout << "Podaj nr domu: ";
    cin >> nrDomu;
    cout << "Podaj miasto: ";
    cin >> miasto;
    cout << "Podaj kod pocztowy: ";
    cin >> kodPocztowy;

    pracownik->imie = imie;
    pracownik->nazwisko = nazwisko;
    pracownik->pesel = pesel;
    pracownik->telefon = telefon;
    pracownik->ID = idCounter++;
    pracownik->adres.ulica = ulica;
    pracownik->adres.nrDomu = nrDomu;
    pracownik->adres.miasto = miasto;
    pracownik->adres.kodPocztowy = kodPocztowy;

    if (head == nullptr)
    {
        head = pracownik;
        last = pracownik;
    }
    else
    {
        last->next = pracownik;
        pracownik->prev = last;
        last = pracownik;
    }
}

void wyswietlListe()
{
    Pracownik *temp = head;
    int numer = 1;
    if (temp == nullptr)
    {
        cout << "Nie ma zadnego pracownika na liscie!\n";
    }
    while (temp != nullptr)
    {
        cout << "Pracownik nr " << numer << endl;
        cout << temp->ID << " | " << temp->imie << " " << temp->nazwisko << " PESEL: " << temp->pesel << endl;
        cout << "Adres: " << temp->adres.ulica << " " << temp->adres.nrDomu << " " << temp->adres.kodPocztowy << " " << temp->adres.miasto << " tel: " << temp->telefon << endl;
        cout << "---------------------------" << endl;
        temp = temp->next;
        numer++;
    }
}

void szukajPoImieniu(string imie)
{
    Pracownik *temp = head;
    bool znaleziono = false;
    while (temp != nullptr)
    {
        if (temp->imie == imie)
        {
            cout << temp->ID << " | " << temp->imie << " " << temp->nazwisko << " PESEL: " << temp->pesel << endl;
            cout << "Adres: " << temp->adres.ulica << " " << temp->adres.nrDomu << " " << temp->adres.kodPocztowy << " " << temp->adres.miasto << " tel: " << temp->telefon << endl;
            cout << "---------------------------" << endl;
            znaleziono = true;
        }
        temp = temp->next;
    }
    if (!znaleziono)
    {
        cout << "Brak pracownika o podanym imieniu: " << imie << endl;
    }
}

void szukajPoNazwisku(string nazwisko)
{
    Pracownik *temp = head;
    bool znaleziono = false;
    while (temp != nullptr)
    {
        if (temp->nazwisko == nazwisko)
        {
            cout << temp->ID << " | " << temp->imie << " " << temp->nazwisko << " PESEL: " << temp->pesel << endl;
            cout << "Adres: " << temp->adres.ulica << " " << temp->adres.nrDomu << " " << temp->adres.kodPocztowy << " " << temp->adres.miasto << " tel: " << temp->telefon << endl;
            cout << "---------------------------" << endl;
            znaleziono = true;
        }
        temp = temp->next;
    }
    if (!znaleziono)
    {
        cout << "Brak pracownika o podanym nazwisku: " << nazwisko << endl;
    }
}

void szukajPesel(long pesel)
{
    Pracownik *temp = head;
    bool znaleziono = false;
    while (temp != nullptr)
    {
        if (temp->pesel == pesel)
        {
            cout << temp->ID << " | " << temp->imie << " " << temp->nazwisko << " PESEL: " << temp->pesel << endl;
            cout << "Adres: " << temp->adres.ulica << " " << temp->adres.nrDomu << " " << temp->adres.kodPocztowy << " " << temp->adres.miasto << " tel: " << temp->telefon << endl;
            cout << "---------------------------" << endl;
            znaleziono = true;
        }
        temp = temp->next;
    }
    if (!znaleziono)
    {
        cout << "Brak pracownika o podanym peselu: " << pesel << endl;
    }
}

void usunPoId(int ID)
{
    Pracownik *temp = head;
    if (head == nullptr)
    {
        cout << "Nie ma zadnego pracownika na liscie!\n";
    }
    while (temp != nullptr)
    {
        if (temp->ID == ID)
        {
            break;
        }
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        cout << "Brak pracownika o podanym ID : " << ID << endl;
        return;
    }

    // pierwszy element listy
    if (temp == head)
    {
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            last = nullptr;
        }
        delete temp;
        return;
    }
    // ostatni element listy
    if (temp == last)
    {
        last = last->prev;
        if (last != nullptr)
        {
            last->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete temp;
        return;
    }
    // ze srodka listy
    if (temp->prev != nullptr)
    {
        temp->prev->next = temp->next;
    }
    if (temp->next != nullptr)
    {
        temp->next->prev = temp->prev;
    }
    delete temp;

    cout << "Pracownik o ID : " << ID << " zostal usuniety\n";
}
void usunPoPesel(long pesel)
{
    Pracownik *temp = head;
    if (head == nullptr)
    {
        cout << "Nie ma zadnego pracownika na liscie!\n";
    }

    while (temp != nullptr)
    {
        if (temp->pesel == pesel)
        {
            break;
        }
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        cout << "Nie ma pracownika o podanym peselu: " << pesel << endl;
        return;
    }
    // pierwszy element listy
    if (temp == head)
    {
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            last = nullptr;
        }
        delete temp;
        return;
    }
    // ostatni element listy
    if (temp == last)
    {
        last = last->prev;
        if (last != nullptr)
        {
            last->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete temp;
        return;
    }
    // ze srodka listy
    if (temp->prev != nullptr)
    {
        temp->prev->next = temp->next;
    }
    if (temp->next != nullptr)
    {
        temp->next->prev = temp->prev;
    }
    delete temp;

    cout << "Pracownik o peselu : " << pesel << " zostal usuniety\n";
}

int main()
{
    int choice;
    for (int i = 0;; i++)
    {
        menu();
        cout << "Podaj wybor: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            cout << "Wpisz dane nowego pracownika:\n";
            nowyPracownik();
            cout << "\nNowy Pracownik został dodany!\n";
            break;
        }
        case 2:
        {
            cout << "Lista pracownikow:\n";
            wyswietlListe();
            break;
        }
        case 3:
        {
            int choiceLook;
            string nazwa;
            long numer;
            cout << "Jak chcesz wyszukac pracownika?\n";
            menuSzukanie();
            cout << "Podaj wybor: ";
            cin >> choiceLook;
            cout << endl;
            if (choiceLook == 1)
            {
                cout << "Wpisz imie: ";
                cin >> nazwa;
                szukajPoImieniu(nazwa);
            }
            else if (choiceLook == 2)
            {
                cout << "Wpisz nazwisko: ";
                cin >> nazwa;
                szukajPoNazwisku(nazwa);
            }
            else if (choiceLook == 3)
            {
                cout << "Wpisz PESEL: ";
                cin >> numer;
                szukajPesel(numer);
            }
            else
            {
                cout << "Niepoprawny wybor\n";
            }
            break;
        }
        case 4:
        {
            int choiceDelete, numerek;
            long drugiNumer;
            menuUsuwanie();
            cout << "Podaj wybor: ";
            cin >> choiceDelete;
            cout << endl;
            wyswietlanieUsuwanie();
            if (choiceDelete == 1)
            {
                cout << "Podaj ID pracownika do usuniecia: ";
                cin >> numerek;
                usunPoId(numerek);
            }
            else if (choiceDelete == 2)
            {
                cout << "Podaj PESEL pracownika dp usuniecia: ";
                cin >> drugiNumer;
                usunPoPesel(drugiNumer);
            }
            else
            {
                cout << "Niepoprawny wybor\n";
            }
            break;
        }
        case 9:
            return 0;
        }
        cout << "\nNacisnij enter aby kontynuowac\n";
        cin.ignore();
        getchar();
    }
}