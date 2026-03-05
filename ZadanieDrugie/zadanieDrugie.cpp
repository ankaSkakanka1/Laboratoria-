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

void czySprzezony(Graf **tablica, int n)
{

    bool nastepniki[20][20] = {false};
    bool czyBylaWielokrotna[20][20] = {false};
    for(int i=0;i<n;i++){
        Graf *p = tablica[i];
        while(p){
            int j = p->v;
            if(czyBylaWielokrotna[i][j]){
                cout << "Graf nie jest sprzezony(krawedz wielokrotna)";
                exit(0);
            }
            czyBylaWielokrotna[i][j]=true;
            nastepniki[i][j]=true;
            p=p->next;
        }
    }

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
    bool nas_plus[20][20] = {false};
    bool nas_minus[20][20] = {false};

    for (int i = 0; i < n; i++)
    {
        Graf* p = tablica[i];
        while (p)
        {
            nas_plus[i][p->v] = true;
            nas_minus[p->v][i] = true;
            p = p->next;
        }
    }

    for (int x = 0; x < n; x++)
    {
        for (int y = x + 1; y < n; y++)
        {
            bool wsp = false;

            for (int k = 0; k < n; k++)
                if (nas_plus[x][k] && nas_plus[y][k])
                {
                    wsp = true;
                    break;
                }

            if (wsp)
            {
                bool rowne = true;
                for (int k = 0; k < n; k++)
                    if (nas_plus[x][k] != nas_plus[y][k])
                    {
                        rowne = false;
                        break;
                    }

                if (!rowne)
                {
                    cout << " -> Graf nie jest liniowy" << endl;
                    return;
                }

                bool wsp_prev = false;
                for (int k = 0; k < n; k++)
                    if (nas_minus[x][k] && nas_minus[y][k])
                    {
                        wsp_prev = true;
                        break;
                    }

                if (wsp_prev)
                {
                    cout << " -> Graf nie jest liniowy" << endl;
                    return;
                }
            }
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

    int Hn = 2 * n; 
    int parent[40]; 
    for (int i = 0; i < Hn; i++) parent[i] = i;

    for (int a = 0; a < n; a++)
    {
        Graf *p = tablica[a];
        while (p)
        {
            int b = p->v;
            if (b < 0 || b >= n) { p = p->next; continue; } 
            int koniecA = 2 * a + 1;
            int poczatekB = 2 * b;
            unite(parent, koniecA, poczatekB);
            p = p->next;
        }
    }

    int w_u[20], w_v[20];
    for (int i = 0; i < n; i++)
    {
        w_u[i] = findp(parent, 2 * i);
        w_v[i] = findp(parent, 2 * i + 1);
    }

    int mapRep[40];
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

    int out_u[400], out_v[400], out_k = 0;
    for (int i = 0; i < n; i++)
   {
       int a = mapRep[ w_u[i] ];
       int b = mapRep[ w_v[i] ];

       out_u[out_k] = a;
       out_v[out_k] = b;
       out_k++;
   }

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

    czySprzezony(tablica,n);
    czyLiniowy(tablica,n);
    przeksztalcenieGrafu(tablica,n);

}


