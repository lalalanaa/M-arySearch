#include <iostream>
#include <fstream>

using namespace std;

int* unosUlaz(int &n)
{
    cout << "unesite broj elemenata:" << endl;
    cin >> n;

    int *a = new int[n];

    cout << "unesite niz u neopadajucem poretku" << endl;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    return a;
}

int* unosDatoteka(int &n)
{
    n = 0;
    string s;
    int *K = new int [1001];
    cout << "unesite naziv fajla" << endl;
    cin >> s;
    ifstream file (s);

    if(!file.is_open())
    {
        cout << "ne postoji fajl sa unetim imenom, pokusajte ponovo" << endl;
        return nullptr;
    }

    while(!file.eof())
        file >> K[n++];

    return K;
}

int* unosPseudosluc(int k, int a, int b)
{
    srand((unsigned) time(nullptr));
    int j, pom, *K = new int [k];

    for(int i = 0; i < k; i++)
    {
        pom = a + rand() % (b - a);

        for(j = i - 1; j >= 0 and K[j] > pom; j--)
            K[j + 1] = K[j];
        K[j + 1] = pom;
    }

    return K;
}

int mPretraga(int m, int key, int *K, int n, int &br, int l = 0)
{
    int high = n - 1, low = l, g1, g2;
    int *mid = new int [m - 1];
    while(high >= low)
    {
        //cout << high << " " << low << endl << endl;

        if(high - low <= m)
        {
            for (int j = low; j < high; j++) {
                br++;
                if (key < K[j])
                    return -1;
                if (K[j] == key)
                    return j;
            }
            return -1;
        }

        if(key == K[high] || key == K[low])
            return (key == K[high]) ? high : low;

        for(int i = 1; i < m; i++)
            mid[i - 1] = low + (high - low) * i / m;

        for(int i = 0; i < m - 1; i++)
        {
            br++;
            if(K[mid[i]] == key)
                return mid[i];

            g1 = i ? mid[i - 1] : low;
            g2 = mid[i];

            //cout << g1 << ":" << K[g1] << " - " << g2 << ":" << K[g2] << endl;

            if(key < K[g1])
                return -1;
            br++;

            if(K[g2] < key)
                low = g2 + 1;

            if(K[g1] < key and key < K[g2])
            {
                high = g2 - 1;
                low = g1 + 1;
                break;
             }
        }
    }
    return -1;
}

void optPretraga(int m, int *K, int k, int *P, int p, int &br)
{
    int pom, posl = -1;
    for(int i = 0; i < p; i++)
    {
        br = 0;
        pom = mPretraga(m, P[i], K, k, br, posl > 0 ? posl : 0);
        if(pom != -1)
            posl = pom;
        cout << pom << " ";
    }
    cout << endl;
}

void ispisiNiz(int n, int *K)
{
    for(int i = 0; i < n; i++)
        cout << K[i] << " ";
    cout << endl;
}

float evaluacija(int m, int n, int *K, int p, int *P)
{
    int br = 0, sum = 0;
    for(int i = 0; i < p; i++, sum += br, br = 0)
        mPretraga(m, P[i], K, n, br);

    return (float)sum / p;
}

float evaluacijaOpt(int m, int n, int *K, int p, int *P)
{
    int br = 0, sum = 0, pom, posl = -1;
    for(int i = 0; i < p; i++, sum += br, br = 0)
    {
        pom = mPretraga(m, P[i], K, n, br, posl > 0 ? posl : 0);
        if(pom + 1)
            posl = pom;
    }
    return (float)sum / p;
}

void meni1()
{
    cout << "\nUnesite redni broj zeljene stavke:\n\t(1) Unos uredjenog niza kljuceva K duzine k sa standardnog ulaza"
            "\n\t(2) Unos uredjenog niza kljuceva K duzine k iz datoteke\n\t(3) Generisanje uredjenog niza kljuceva K duzine k"
            "\n\t(4) M-arna pretraga niza K\n\t(5) Optimizovana m-arna pretraga niza K na niz kljuceva P\n\t"
            "(6) Evaluacija m-arne pretrage\n\t(7) Evaluacija optimizovane m-arne pretrage\n\n\t(0) Kraj programa\n\n";
}


int main() {
    int izbor, a, b, n, m, p, l, kljuc, br = 0, *P = nullptr, *K = nullptr, *L = nullptr;

    cout << "Dobrodosli! :)" << endl;

    while(true)
    {
        meni1();
        cin >> izbor;
        switch (izbor)
        {
            case 0:
                if(!P)
                    delete [] P;
                if(!K)
                    delete [] K;
                cout << "Prijatan dan! :)";
                return 0;

            // provera da li je niz sortiran
            case 1:
                K = unosUlaz(n);
                cout << "niz uspesno unesen!" << endl << endl;
                break;

            case 2:
                K = unosDatoteka(n);
                if(K == nullptr)
                    break;
                cout << "ucitan je sledeci niz:" << endl;
                ispisiNiz(n, K);
                break;

            case 3:
                cout << "unesite broj elemenata, kao i donju i gornju granicu inervala:" << endl;
                cin >> n >> a >> b;

                K = unosPseudosluc(n, a, b);

                cout << "generisan je sledeci niz:" << endl;
                ispisiNiz(n, K);
                break;

            case 4:
                if(K == nullptr)
                {
                    cout << "niz nije unet! pokusajte ponovo" << endl;
                    break;
                }
                cout << "unesite parametar m u opsegu [2-6]:" << endl;
                cin >> m;
                while(m < 2 || m > 6)
                {
                    cout << "m nije u opsegu [2-6], pokusajte ponovo" << endl;
                    cin >> m;
                }
                cout << "unesite kljuc koji se pretrazuje" << endl;
                cin >> kljuc;

                a = mPretraga(m, kljuc, K, n, br);
                cout << "broj koraka je: " << br << endl;
                if(a + 1)
                {
                    cout << "trazeni kljuc se nalazi na indeksu " << a<< endl;
                    break;
                }
                cout << "trazeni kljuc se ne nalazi u nizu" << endl;
                break;

            case 5:
                if(K == nullptr)
                {
                    cout << "niz nije unet! pokusajte ponovo" << endl;
                    break;
                }
                cout << "unesite parametar m u opsegu [2-6]" << endl;
                cin >> m;
                while(m < 2 || m > 6)
                {
                    cout << "m nije u opsegu [2-6], pokusajte ponovo" << endl;
                    cin >> m;
                }
                P = unosUlaz(p);
                optPretraga(m, K, n, P, p, br);

                break;

            case 6:
                if(K == nullptr)
                {
                    cout << "niz nije unet! pokusajte ponovo" << endl;
                    break;
                }
                cout << "unesi 1 za unos niza preko konzole\nunesi 2 za generisanje pseudoslucajnog niza" << endl;
                cin >> a;
                while(a != 1 && a != 2)
                {
                    cout << "izabrali ste nepostojecu opciju, pokusajte ponovo" << endl;
                    cin >> a;
                }
                if(a == 1)
                    L = unosUlaz(l);
                else
                {
                    cout << "unesite broj elemenata:" << endl;
                    cin >> l;
                    L = unosPseudosluc(l, K[0], K[n/2]);
                    cout << "generisan je sledeci niz:" << endl;
                    ispisiNiz(l, L);
                }

                for(int i = 2; i <= 6; i++)
                    cout << "za m = " << i << " prosecan broj koraka je: " << evaluacija(i, n, K, l, L) << endl;
                break;

            case 7:
                if(K == nullptr)
                {
                    cout << "niz nije unet! pokusajte ponovo" << endl;
                    break;
                }
                cout << "unesite 1 za unos niza preko konzole\nunesite 2 za generisanje pseudoslucajnog niza\n";
                cin >> a;
                while(a != 1 && a != 2)
                {
                    cout << "izabrali ste nepostojecu opciju, pokusajte ponovo" << endl;
                    cin >> a;
                }
                if(a == 1)
                    L = unosUlaz(l);
                else
                {
                    cout << "unesite broj elemenata:" << endl;
                    cin >> l;
                    L = unosPseudosluc(l, K[0], K[n/2]);
                    ispisiNiz(l, L);
                }

                for(int i = 2; i <= 6; i++)
                    cout << "za m = " << i << " prosecan broj koraka je: " << evaluacijaOpt(i, n, K, l, L) << endl;
                break;

            case 8:
                cout << "hehe :)" << endl;
                break;

            default:
                cout << "izabrali ste nepostojecu opciju, pokusajte ponovo" << endl;
        }(br = 0);
    }
}