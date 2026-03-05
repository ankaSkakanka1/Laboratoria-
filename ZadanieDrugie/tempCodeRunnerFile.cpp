#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <filesystem>
using namespace std;

struct Graf
{
    Graf *next;
    int v;
};

void czySprzezony(int v, Graf **tablica, int n)
{
    bool nastepniki[20][20] = {false};
    for (int i = 0; i < n; i++)
    {
        Graf *p = tablica[i];
        while (p)
        {
            nastepniki[i][p->v] = true;
            p = p->next;
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            bool wspolny = false, rozne = false;
            for (int k=0;k<n;k++){
                if(nastepniki[i][k] && nastepniki[j][k]) wspolny =true;
                if(nastepniki[i][k] != nastepniki[j][k]) rozne = true;
                
            }
            if(wspolny && rozne){
                cout << " -> Graf nie jest sprzezony" << endl;
                exit(0);
            }
            
        }
    }
    cout << " -> Graf jest sprzezony" << endl;
    
}

void czyLiniowy(Graf **tablica, int n)
{
    int stopien_in[20] = {0};
    int stopien_out[20] = {0};

    // 1️⃣ Obliczamy stopnie wyjściowe i wejściowe
    for (int i = 0; i < n; i++)
    {
        Graf *p = tablica[i];
        while (p)
        {
            stopien_out[i]++;       // krawędź wychodzi z i
            if (p->v >= 0 && p->v < n)
                stopien_in[p->v]++; // krawędź wchodzi do p->v
            p = p->next;
        }
    }

    // 2️⃣ Sprawdzamy warunek liniowości
    for (int i = 0; i < n; i++)
    {
        int suma = stopien_in[i] + stopien_out[i];
        if (suma > 2)
        {
            cout << " -> Graf nie jest liniowy" << endl;
            return;
        }
    }

    cout << " -> Graf jest liniowy" << endl;
}

int findp(int parent[], int x)
{
    if (parent[x] == x) return x;
    parent[x] = findp(parent, parent[x]);
    return parent[x];
}
void unite(int parent[], int a, int b)
{
    int ra = findp(parent, a);
    int rb = findp(parent, b);
    if (ra != rb) parent[rb] = ra;
}

void przeksztalcenieGrafu(Graf **tablica, int n)
{
    cout << " -> Przeksztalcanie (sprzezony -> oryginalny)..." << endl;

    if (n <= 0) {
        cout << " -> Brak wierzcholkow." << endl;
        return;
    }

    int Hn = 2 * n; // maks liczba wierzcholkow w H (poczatki i konce)
    int parent[40]; // max 2*20 = 40
    for (int i = 0; i < Hn; i++) parent[i] = i;

    // 1) Dla kazdej krawedzi (a -> b) w G scal koniec a (2*a+1) z poczatkiem b (2*b)
    for (int a = 0; a < n; a++)
    {
        Graf *p = tablica[a];
        while (p)
        {
            int b = p->v;
            if (b < 0 || b >= n) { p = p->next; continue; } // bezpieczenstwo
            int koniecA = 2 * a + 1;
            int poczatekB = 2 * b;
            unite(parent, koniecA, poczatekB);
            p = p->next;
        }
    }

    // 2) Dla kazdego wierzcholka i w G utworz luk (find(2*i) -> find(2*i+1))
    int w_u[20], w_v[20];
    for (int i = 0; i < n; i++)
    {
        w_u[i] = findp(parent, 2 * i);
        w_v[i] = findp(parent, 2 * i + 1);
    }

    // 3) Zbierz unikalne reprezentanty wystepujace w raw_u/raw_v i przeindeksuj je 0..W-1
    int mapRep[40]; // mapRep[oldRep] = newIndex or -1
    for (int i = 0; i < Hn; i++) mapRep[i] = -1;
    int repLista[40]; int repCount = 0;
    for (int i = 0; i < n; i++)
    {
        int a = w_u[i];
        int b = w_v[i];
        if (mapRep[a] == -1)
        {
            mapRep[a] = repCount;
            repLista[repCount++] = a;
        }
        if (mapRep[b] == -1)
        {
            mapRep[b] = repCount;
            repLista[repCount++] = b;
        }
    }

    // 4) Utworz liste unikalnych lukow po przeindeksowaniu (usun duplikaty)
    int out_u[400], out_v[400], out_k = 0;
    for (int i = 0; i < n; i++)
    {
        int a = mapRep[ w_u[i] ];
        int b = mapRep[ w_v[i] ];
        // sprawdz duplikat
        bool dup = false;
        for (int j = 0; j < out_k; j++)
        {
            if (out_u[j] == a && out_v[j] == b) { dup = true; break; }
        }
        if (!dup)
        {
            out_u[out_k] = a;
            out_v[out_k] = b;
            out_k++;
        }
    }

    // 5) Zapisz wynik do pliku wynik.txt w formacie w: W k: K
    ofstream plik_wynik("wynik.txt", ios::out);
    if (!plik_wynik.good())
    {
        cout << "Nie udalo sie otworzyc/utworzyc wynik.txt" << endl;
        return;
    }

    plik_wynik << "w: " << repCount << " k: " << out_k << endl;
    for (int i = 0; i < out_k; i++)
    {
        plik_wynik << out_u[i] << " -> " << out_v[i] << endl;
    }
    plik_wynik.close();

    cout << " -> Zapisano wynik do wynik.txt  (w: " << repCount << " k: " << out_k << ")" << endl;
}

    
int main()
{
    cout << "Program do analizy grafu skierowanego" << endl;
    // wczytywanie pliku
    string nazwaPliku;
    fstream plik;
    cout << "-> Aktualny katalog: " << filesystem::current_path() << endl;
    cout << "-> Podaj nazwe pliku : ";
    cin >> nazwaPliku;
    plik.open(nazwaPliku, ios::in);
    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku";
        exit(0);
    }

    // lista sasiedztwa
    int n, k, v1, v2;
    Graf **tablica;
    Graf *p, *r;
    string znak1, znak2;
    plik >> znak1 >> n >> znak2 >> k;
    if (n <= 0 || k < 0)
    {
        cout << "Niepoprawne dane";
        exit(0);
    }

    if (n > 20)
    {
        cout << "Za duza liczba wierzcholkow";
        exit(0);
    }

    tablica = new Graf *[n];
    for (int i = 0; i < n; i++)
        tablica[i] = nullptr;
    for (int i = 0; i < k; i++)
    {
        char strzalka[3];
        plik >> v1 >> strzalka >> v2;
        p = new Graf;
        p->v = v2;
        p->next = tablica[v1];
        tablica[v1] = p;
    }
    cout << "-> Wczytano graf z pliku : " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "tablica[" << i << "] = ";
        p = tablica[i];
        if (p == nullptr)
            cout << " wierzcholek izolowany";
        while (p)
        {
            cout << p->v << " ";
            p = p->next;
        }
        cout << endl;
    }

    czySprzezony(n,tablica,n);
    czyLiniowy(tablica,n);
    przeksztalcenieGrafu(tablica,n);

}


