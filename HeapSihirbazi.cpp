//Created by Emre Öztemiz 26.04.2025
// --------------------------------------------------------------
// HeapSihirbazi.cpp - İsim konusunda Flutter Deve Hörgücü yapısında çok kaldığımın farkındayım. :)
// 
// Bu kod insanlığa bir armağandır. 🌍
// Herkesin özgürce kullanabilmesi, öğrenmesi ve geliştirebilmesi için
// GNU Genel Kamu Lisansı (GPL) altında lisanslanmıştır.
//
// İster değiştirin, ister paylaşın, ister daha iyisini inşa edin:
// Bilgi paylaştıkça çoğalır! 🚀
//
// -- Katkıda bulunan herkese şimdiden teşekkürler. 💙
// --------------------------------------------------------------

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <limits>

#ifdef _WIN32
#define TEMIZLE "cls"
#else
#define TEMIZLE "clear"
#endif

using namespace std;

// Küresel Değişkenler
bool adimAdimIlerle = false;
double beklemeSuresi = 1.0;
bool minHeap = true;
int karsilastirmalar = 0;
int degisimler = 0;

// Ekranı Temizle
void ekraniTemizle() {
    system(TEMIZLE);
}

// Bekleme veya Adım Adım İlerleme
void bekle() {
    if (adimAdimIlerle) {
        cout << "\nDevam etmek için Enter'a basın...";
        cin.ignore();
        cin.get();
    } else {
        this_thread::sleep_for(chrono::duration<double>(beklemeSuresi));
    }
}

// Heap'i Ağaç Şeklinde Yazdır
void kupYazdir(const vector<int>& heap, int vurgulu = -1) {
    int n = heap.size();
    int seviyeler = log2(n) + 1;
    int genislik = pow(2, seviyeler + 1);

    cout << "\nHeap Ağacı:\n";
    int index = 0;
    for (int i = 0; i < seviyeler; ++i) {
        int dugumler = pow(2, i);
        int bosluk = genislik / (dugumler + 1);

        cout << string(bosluk / 2, ' ');

        for (int j = 0; j < dugumler && index < n; ++j) {
            if (index == vurgulu)
                cout << "[" << heap[index] << "]" << string(bosluk, ' ');
            else
                cout << " " << heap[index] << " " << string(bosluk, ' ');
            ++index;
        }
        cout << "\n\n";
    }
}

// Heapify İşlemi
void heapify(vector<int>& heap, int n, int i) {
    int hedef = i;
    int sol = 2 * i + 1;
    int sag = 2 * i + 2;

    if (sol < n) {
        karsilastirmalar++;
        if ((minHeap && heap[sol] < heap[hedef]) || (!minHeap && heap[sol] > heap[hedef])) {
            hedef = sol;
        }
    }

    if (sag < n) {
        karsilastirmalar++;
        if ((minHeap && heap[sag] < heap[hedef]) || (!minHeap && heap[sag] > heap[hedef])) {
            hedef = sag;
        }
    }

    if (hedef != i) {
        degisimler++;
        ekraniTemizle();
        cout << heap[i] << " ile " << heap[hedef] << " değiştiriliyor...\n";
        swap(heap[i], heap[hedef]);
        kupYazdir(heap, hedef);
        bekle();
        heapify(heap, n, hedef);
    }
}

// Min veya Max Heap Kurulumu
void heapOlustur(vector<int>& heap) {
    int n = heap.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        ekraniTemizle();
        cout << "Heapify işlemi: İndeks " << i << "\n";
        kupYazdir(heap, i);
        bekle();
        heapify(heap, n, i);
    }
}

// Heap Sort İşlemi
vector<int> heapSort(vector<int> dizi) {
    vector<int> sirali;
    int n = dizi.size();

    heapOlustur(dizi);

    for (int i = n - 1; i >= 0; --i) {
        ekraniTemizle();
        cout << (minHeap ? "Min" : "Max") << " öğe çıkarılıyor: " << dizi[0] << "\n";
        degisimler++;
        swap(dizi[0], dizi[i]);
        kupYazdir(dizi, 0);
        bekle();
        heapify(dizi, i, 0);
        sirali.push_back(dizi[i]);
    }

    if (minHeap) reverse(sirali.begin(), sirali.end());
    return sirali;
}

// Ana Fonksiyon
int main() {
    ekraniTemizle();

    cout << "Heap Türünü Seçin:\n";
    cout << "1. Min Heap\n";
    cout << "2. Max Heap\n";
    int heapTuru;
    while (!(cin >> heapTuru) || (heapTuru != 1 && heapTuru != 2)) {
        cout << "Lütfen 1 ya da 2 girin: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    minHeap = (heapTuru == 1);

    cout << "\nAdım adım ilerlemek ister misiniz? (1=Evet, 0=Hayır): ";
    while (!(cin >> adimAdimIlerle)) {
        cout << "Lütfen 1 ya da 0 girin: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (!adimAdimIlerle) {
        cout << "\nHer adım arasındaki bekleme süresini (saniye cinsinden) girin (örneğin 1.0): ";
        while (!(cin >> beklemeSuresi) || beklemeSuresi < 0) {
            cout << "Geçerli bir bekleme süresi girin: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    ekraniTemizle();
    int n;
    cout << "Eleman sayısını girin: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Pozitif bir sayı girin: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> dizi(n);
    cout << "Elemanları girin:\n";
    for (int i = 0; i < n; ++i) {
        while (!(cin >> dizi[i])) {
            cout << "Geçerli bir sayı girin: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    vector<int> sirali = heapSort(dizi);

    ekraniTemizle();
    cout << "✅ Heap Sıralama Tamamlandı!\n\n";
    cout << "Sıralı Dizi: ";
    for (int val : sirali) {
        cout << val << " ";
    }
    cout << "\n\n";

    cout << "📊 Toplam Karşılaştırma: " << karsilastirmalar << "\n";
    cout << "🔁 Toplam Değişim: " << degisimler << "\n";
    cout << "🧠 Ortalama Karşılaştırma: " << (double)karsilastirmalar / n << "\n";
    cout << "🔎 Minimum Değer: " << *min_element(sirali.begin(), sirali.end()) << "\n";
    cout << "🔎 Maksimum Değer: " << *max_element(sirali.begin(), sirali.end()) << "\n";

    return 0;
}
