#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define A_SIZE 20
#define G_SIZE 10
#define MAX_W 10

//Max deger icin sonsuz sayi
#define INF INT_MAX

void generate(int a[], int size);
void function1(int a[], int size);
int function2(int a[], int size);
void function3(int g[][G_SIZE], int d[][G_SIZE], int size);
void print1(int a[], int size);
void print2(int g[][G_SIZE], int size);
void print3(int g[][G_SIZE], int size, int t);

int main() {
    int a[A_SIZE];
    int g[G_SIZE][G_SIZE] = {//10 a 10 luk bir matrik olu�turuyor
    { 0, 10,  3,  0,  0,  5,  0, 17,  0, 22},
    {10,  0,  5,  0,  2,  0, 13,  0,  0,  0},
    { 3,  5,  0,  2,  0,  4,  0, 21,  0, 11},
    { 0,  0,  2,  0,  7,  0,  6,  0,  0,  0},
    { 0,  2,  0,  7,  0,  6,  0,  0, 19,  0},
    { 5,  0,  4,  0,  6,  0,  9,  3,  0,  0},
    { 0, 13,  0,  6,  0,  9,  0,  4,  0,  0},
    {17,  0, 21,  0,  0,  3,  4,  0,  8,  0},
    { 0,  0,  0,  0, 19,  0,  0,  8,  0,  5},
    {22,  0, 11,  0,  0,  0,  0,  0,  5,  0}
    };
    int d[G_SIZE][G_SIZE];//10 a 10 luk bir dizi olu�turuyor
    int t;

    // Rastgele sayi uretici icin seed
    srand(time(NULL));

    // Calisma suresinin hesaplanmasi
    clock_t start, end;
    double time;

    start = clock(); 

    generate(a, A_SIZE); // a dizisi ve a dizisinin boyutu(20) g�nderiliyor
    printf("A:\n");
    print1(a, A_SIZE);

    function1(a, A_SIZE); // bu fonksiyon a dizisini siralama i�lemi yapmaktadir
    printf("\nFunction1 Sonuc:\n");
    print1(a, A_SIZE);

    t = function2(a, A_SIZE);
    printf("\nFunction2 Sonuc: %d\n", t);

    printf("\nG:\n");
    print2(g, G_SIZE);

    function3(g, d, G_SIZE);// g , d matrisini ve kaca kaclik olduklarini yolluyor
    printf("\nFunction3 Sonuc:\n");
    print2(d, G_SIZE);

    printf("\n%d icin sonuc:\n", t);
    print3(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCalisma Suresi: %f sn\n", time);

    return 0;
}

void generate(int a[], int size) {
    for (int i = 0; i < size; i++) {
        a[i] = rand() % MAX_W; // size boyutunda d�nerken her i de�eri icin a daki i indisine rand() fonksiyonu ca�iriliyor max_w 10 2 ile carpiyor ve 10 cikariyor burada gereksiz bir i�lem oldu�u icin direkt olarak max_w kullanilabilir 
    }
}

void function1(int a[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (a[j] > a[j + 1]) {//e�er j indisindeki sayi j+1 indisinden b�y�k ise temp de�i�kenini kullanarak bu ikisini yer de�i�tiriyor 
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

/*int function2(int a[], int size) {
    int t = 0, current_sum = 0, count=0;
    for (int i = 0; i < size; i++) {
        if (current_sum + a[i] > 0) {//current_sum + a[i] 0 dan b�y�k ise yapiyor burada dikkat etmemiz gereken bizim sayilarimiz zaten ya 0 yada pozitif  
            current_sum += a[i]; // ne yapiyor current_sum a a[i] sayisini ekliyor kodu d�zenleyelim += a[i] ayni i�e yarayacak
        }
        else {
            current_sum = 0;
        }
        if (current_sum > t) {
            t = current_sum;
            count++;
        }
    }
    return t/count;
}*/


int function2(int a[], int size) {// bu fonksiyon dizideki pozitif sayilarin ortalamasini almaktadir t kullanilmadi�i icin kaldirilmi�tir 
    int  current_sum = 0, count=0;
    for (int i = 0; i < size; i++) {
        if (a[i] != 0) {
            current_sum += a[i];
			count++; 
        }

    }
    return current_sum/count;
}

void function3(int g[][G_SIZE], int d[][G_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {//matrisin k��egenindeki  de�erleri sifirliyor
                d[i][j] = 0;
            }
            else if (g[i][j] != 0) {//g matrisinde g[i][j] indislerinde 0 dan farkli bir sayi varsa 
                d[i][j] = g[i][j];//bu sayiyiyi d[i][j] lokasyonuna ta�imaktadir
            }
            else {
                d[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                	//d[i][k] nin sonsuz mu olup olmadi�ina ve d[k][j] nin sonsuz olup olmadi�ina  ve d[i][k]+d[k][j] nin d[i][j] den k�c�k olup olmadi�ina bakiyor
                    d[i][j] = d[i][k] + d[k][j];//e�er ko�ullar sa�liyor ise d[i][j] yerine d[i][k]+d[k][j] de�erini koyuyuor
                }
            }
        }
    }
}

void print1(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
        if ((i + 1) % 10 == 0)  {//bu for d�ng�s� 10 kere d�nd�kten sonra bir alt satira gecmek icin  bu if d�ng�s� gercekle�ecek ve bir alt satira gececek
            printf("\n");
        }
    }
}



void print2(int g[][G_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (g[i][j] == INF) {
                printf("INF ");
            }
            else {
                printf("%3d ", g[i][j]);
            }
        }
        printf("\n");
    }
}

void print3(int d[][G_SIZE], int size, int t) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j && d[i][j] < t) {
                printf("%c -> %c: %d\n", 'A' + i, 'A' + j, d[i][j]);
            }
        }
    }
}
