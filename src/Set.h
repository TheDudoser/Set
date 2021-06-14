#pragma once

#include <iostream>

using namespace std;

// Упорядоченное множество, двусвязный список

// при работе с этим классом не получилось вынести реализации методов класса в отдельный файл из-за template,
// который странно работает

// шаблон используется для создания фактического класса, когда я его использую и поэтому
// является нормальной практикой реализации всего в h файле
template < typename data >

class Set {
    struct element {
        data inf;
        element* next;
        element* past;
    };
    element* Head;
    element* Tail;
public:

    // конструктор
    Set() {
        Head = NULL;
        Tail = NULL;
    };

    // конструктор копирования
    Set(const Set &set) {
        // Выполняем копирование значений
        Head = set.Head;
        Tail = set.Tail;

    }

    // перегрузка присваивания Set и Set
    Set& operator= (const Set set)
    {
        // Выполняем копирование значений
        Head = set.Head;
        Tail = set.Tail;

        // Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
        return *this;
    }

    // перегрузка присваивания Set и data
    Set& operator= (data d)
    {
        this + d;

        return *this;
    }

    // пересечение множеств
    Set operator* (Set s) {
        element *cur1;
        element *cur2;
        element *cur3;
        element *cur4;
        Set intersection;
        // если одно из множеств пусто
        if (this->Head == NULL || s.Head == NULL)
            return intersection;
        else { // если в обоих множествах по одному эл-ту
            if (Head->next == Head && s.Head->next == s.Head) {
                if (s.Head->inf == this->Head->inf)
                    intersection + Head->inf;
                return intersection;
            } else { // поиск эл-та из одного мн-ва в другом
                if (length() < s.length()) {
                    cur1 = Head;
                    cur3 = s.Head;
                    cur4 = cur3->next;
                    while (cur1 != Tail) {
                        while (cur4 != s.Head && cur1->inf != cur3->inf) {
                            cur3 = cur3->next;
                            cur4 = cur4->next;
                        }
                        if (cur1->inf == cur3->inf)
                            intersection + cur3->inf;
                        cur1 = cur1->next;
                        cur3 = s.Head;
                        cur4 = cur3->next;
                    }
                    if (cur1 == Tail) {
                        while (cur1->inf != cur3->inf && cur4 != s.Head) {
                            cur3 = cur3->next;
                            cur4 = cur4->next;
                        }
                        if (cur1->inf == cur3->inf)
                            intersection + cur3->inf;
                    }
                } else {
                    cur1 = Head;
                    cur2 = cur1->next;
                    cur3 = s.Head;
                    while (cur3 != s.Tail) {
                        while (cur1->inf != cur3->inf && cur2 != Head) {
                            cur1 = cur1->next;
                            cur2 = cur2->next;
                        }
                        if (cur1->inf == cur3->inf)
                            intersection + cur3->inf;
                        cur1 = Head;
                        cur2 = cur1->next;
                        cur3 = cur3->next;
                    }
                    if (cur3 == s.Tail) {
                        while (cur1->inf != cur3->inf && cur2 != Head) {
                            cur1 = cur1->next;
                            cur2 = cur2->next;
                        }
                        if (cur1->inf == cur3->inf)
                            intersection + cur3->inf;
                    }
                }
                return intersection;
            }
        }
    }

    // пересечение множества с элементом
    Set operator* (data a) { // исходное множество при этом не меняется
        element *cur1;
        element *cur2;
        Set s;
        // если у нас пустое множество
        if (this->Head == NULL) {
            return s;
        } else {
            cur1 = Head;
            cur2 = Head->next;
            if (cur1 == cur2) { //если один элемент, то ничего удалять из текущего множества не нужно
                if (cur1->inf == a)
                    return s + a;
            } else {
                while (cur2 != Head && (cur2->inf != a)) {
                    cur1 = cur2;
                    cur2 = cur1->next;
                }
            } if (cur2->inf == a) {
                return s + a;
            } else if (cur2 == Head) { // если дошли до конца множества
                return s;
            }
        }
    }

    // пересечение эл-та и мн-ва
    friend Set operator* (data a, Set& s) {
        return s * a;
    }

    // поиск эл-та
    bool search (data a) {
        element *cur1;
        element *cur2;
        // если у нас пустое множество
        if (this->Head == NULL) {
            return false;
        } else {
            cur1 = Head;
            cur2 = Head->next;
            if (cur1 == cur2) { //если один элемент
                if (cur1->inf == a)
                    return true;
                else return false;
            } else {
                while (cur2 != Head && (cur2->inf != a)) {
                    cur1 = cur2;
                    cur2 = cur1->next;
                }
            } if (cur2->inf == a) { // если нашли элемент, который больше добавляемого
                return true;
            } else if (cur2 == Head) { // если дошли до конца множества
                    return false;
            }
        }
    }

    // объединение множеств
    Set operator+ (Set s) {
        element *cur1;
        element *cur2;
        Set intersection;
        // если одно из множеств пусто
        if (this->Head == NULL) {
            intersection = s;
            return intersection;
        } else if (s.Head == NULL) {
            intersection = *this;
            return intersection;
        } else { // если оба множества не пустые
            cur1 = Head;
            cur2 = s.Head;
            while (cur1 != Tail) {
                intersection + cur1->inf;
                cur1 = cur1->next;
            }
            intersection + cur1->inf;
            while (cur2 != s.Tail) {
                intersection + cur2->inf;
                cur2 = cur2->next;
            }
            intersection + cur2->inf;
        }
        return intersection;
    }

    // объединение множества и эл-та (добавление эл-та в мн-во)
    Set operator+ (data a) {
        element* cur1;
        element* cur2;
        Set unification = *this;
        // если у нас пустое множество
        if (unification.Head == NULL) {
            unification.Head = new element;
            unification.Head->inf = a;
            unification.Head->next = unification.Head;
            unification.Head->past = unification.Head;
            unification.Tail = unification.Head;
            return unification;
        } else {
            cur1 = unification.Head;
            cur2 = unification.Head->next;
            if (cur1 == cur2) { //если один элемент
                cur2 = new element;
                cur2->inf = a;
                cur2->past = unification.Head;
                cur2->next = unification.Head;
                cur1->next = cur2;
                unification.Tail = cur2;
                unification.Head->past = unification.Tail;
                return unification;
            } else {
                while (cur2 != unification.Head && (cur2->inf < a)) {
                    cur1 = cur2;
                    cur2 = cur2->next;
                }
                if (cur1 == unification.Tail) { // если дошли до конца множества
                    cur2 = new element;
                    cur2->inf = a;
                    cur1->next = cur2;
                    cur2->past = cur1;
                    cur2->next = unification.Head;
                    unification.Tail = cur2;
                    unification.Head->past = unification.Tail;
                    return unification;
                }
                else if (cur1->inf > a) { // если нашли элемент, который больше добавляемого
                    unification.Tail->next = new element;
                    unification.Tail->next->inf = a;
                    unification.Tail->next->past = unification.Tail;
                    unification.Tail->next->next = cur1;
                    unification.Head = unification.Tail->next;
                    cur1->past = unification.Tail->next;
                    return unification;
                } else if (cur2->inf > a && a != unification.Head->inf) { // если нашли элемент, который больше добавляемого
                    cur1->next = new element;
                    cur1->next->inf = a;
                    cur1->next->past = cur1;
                    cur1->next->next = cur2;
                    cur2->past = cur1->next;
                    return unification;
                }
                if (cur2->inf > a && a == unification.Head->inf)
                    return unification;
                if (cur2->inf == a) {
                    return unification;
                }
            }

        }
    }

    // объединение эл-та и мн-ва (добавление эл-та в мн-во)
    friend Set operator+ (data a, Set& s) {
        return s + a;
    }

    // исключение множества из другого множества
    Set operator- (Set s) {
        element *cur1;
        element *cur2;
        Set intersection;
        // если одно из множеств пусто
        if (this->Head != NULL && s.Head == NULL) {
            intersection = s + *this;
        } else
            if (this->Head == NULL) {
                intersection = *this;
            }
            else { // если оба множества не пустые
            cur1 = Head;
            cur2 = s.Head;
            while (cur1 != Tail) {
                intersection + cur1->inf;
                cur1 = cur1->next;
            }
            intersection + cur1->inf;
            while (cur2 != s.Tail) {
                intersection - cur2->inf;
                cur2 = cur2->next;
            }
            intersection - cur2->inf;
        }
        return intersection;
    }

    // исключение элемента из множества (удаление эл-та)
    int operator- (data a) {
        element* cur1;
        element* cur2;
        // если у нас пустое множество
        if (Head == NULL)
            return 0;
        else {
            cur1 = Head;
            cur2 = Head->next;
            if (cur1 == cur2) { //если один элемент
                if (cur1->inf == a) {
                    delete cur1;
                    Head = NULL;
                    Tail = NULL;
                    return 1;
                } else return 0;
            } else {
                if (cur1->inf == a) { // удаление первого эл-та
                    Tail->next = cur2;
                    cur2->past = Tail;
                    Head = cur2;
                    delete cur1;
                    return 1;
                }
                while (cur2 != Head && (cur2->inf != a)) {
                    cur1 = cur2;
                    cur2 = cur2->next;
                }
                if (cur2->inf == a) { // если нашли элемент, который больше добавляемого
                    cur1->next = cur2->next;
                    cur1->next->past = cur1;
                    if (cur2 == Tail)
                        Tail = cur1;
                    delete cur2;
                    return 1;
                } else if (cur2 == Head) { // если дошли до конца множества
                    return 0;
                }
            }
        }
    }

    // длина множества
    int length () {
        if (Head == NULL)
            return 0;
        element* cur1 = Head;
        element* cur2 = cur1->next;
        int count = 0;
        if (cur1 == cur2)
            return 1;
        else {
            count += 1;
            while (cur2 != Head) {
                cur1 = cur2;
                cur2 = cur1->next;
                count += 1;
            }
            return count;
        }
    }

    // вывод множества
    friend ostream &operator<<(ostream &out, Set s) {
        if (s.Head == NULL)
            out << "Множество пустое!" << endl;
        else {
            element *cur1 = s.Head;
            element *cur2 = cur1->next;
            if (cur1 == cur2) {
                out << "Размер множества: " << s.length() << endl;
                out << cur1->inf << endl;
            }
            else {
                out << "Размер множества: " << s.length() << endl;
                while (cur2 != s.Head) {
                    out << cur1->inf << ' ';
                    cur1 = cur2;
                    cur2 = cur2->next;
                }
                out << cur1->inf << endl;
            }
        }
    }

    ~Set() {
        Head = NULL;
        Tail = NULL;
    }
};
