#include <iostream>
#include "Set.h"
#include <vector>

using namespace std;

// Упорядоченное множество, двусвязный список
// Тест на решето эратосфена

// пересечение множеств (done)
// пересечение множества с элементом (done)
// поиск эл-та (done)
// объединение множеств (done)
// объединение множества и эл-та (добавление эл-та в мн-во) (done)
// исключение множества из другого множества (done)
// исключение элемента из множества (удаление эл-та) (done)
// длина множества (done)
// вывод множества (done)

vector<int> Erat(int n) {
    vector<int> vec;
    int *a = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
        a[i] = i;

    for (int p = 2; p < n + 1; p++) {
        if (a[p] != 0) {
            vec.push_back(a[p]);
            //cout << a[p] << endl;
            for (int j = p * p; j < n + 1; j += p)
                a[j] = 0;
        }
    }
    return vec;
}

// Тест с решетом Эратосфена (done)
void sieveEratosthenes(int n) {
    Set<int> s;

    for (int i = 2; i < n; i++) {
      s = s+i;
    }
    int p = 2;

    while(p != n) {
        for (int i = p + 1; i < n; ++i) {
            if (i % p == 0)
               s = s - i;
        }
        ++p;
    }

/*    for (int i = p; i < n; ++i) {
        s - i;
    }*/

/*    while (p != n && p != 0) {
        for (int j = 2 * p; j < n; j+=p) {
            s - j;
            if (j > n)
                break;
        }
        count += 1;
        p = vec[count];
    }*/
    cout << s;

}

int main() {
//    Set<int> s;
//    cout << s << boolalpha << s.search(0) << endl;
//    s + 1;
//    cout << s << s.search(0) << endl;
//    s + 3;
//    cout << s << s.search(0) << endl;
//    s + 3;
//    s + 2;
//    cout << s << s.search(2) << endl;
//    s - 2;
//    cout << s << s.search(2) << endl;
//    s - 3;
//    cout << s << s.search(2) << endl;
//    s - 3;
//    cout << s << s.search(2) << endl;
//    s - 1;
//    cout << s << s.search(2) << endl;
//    s - 1;
//    cout << s << s.search(2) << endl;
//
//    s + 1;
//    s + 4;
//
//    cout << "=====Пересечения множеств: " << endl;
//    cout << s * 1 << endl;
//    cout << s * 0;

    Set<int> s;
  int n=100;
    for (int i = 2; i < n; i++) {
        s = i+s;
        s = s+ (25-i%25);
    }
    int p = 2;
    //cout << s;
    while(p != n) {
        for (int i = p + 1; i < n; ++i) {
            if (i % p == 0)
                s = s - i;
        }
        ++p;
    }
    cout<<"s "<<s<<endl;
    Set<int> s1(s);
    cout<<"s1: "<<s1<<endl;
    Set<int> s3;
    s=s3-s1+s3;
    cout<<"s: "<<s<<endl;
    cout<<"s1: "<<s1<<endl;

    //int n = 200;
/*    vector<int> vec = Erat(n);
    cout << "\nРешето не на множестве: " << endl;
    for (int i : vec) {
        cout << i << ' ';
    }*/

    cout << endl;
    cout << "\nРешето на множестве: " << endl;
    sieveEratosthenes(n);

    return 0;
}
