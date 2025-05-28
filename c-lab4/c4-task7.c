/*
 (15 баллов) Напишите структуру двусвязного списка, содержащего упорядоченный в
каком-то порядке (не обязательно в естественном!) набор величин inf типа unsigned
int:
При создании списка принимается функция сравнения двух элементов (так же, как в
стандартной функции qsort). Напишите функции
• init инициализации переменной списка,
• clear очистки списка,
• empty проверки списка на пустоту,
• add добавления элемента в список,
• contains проверки наличия элемента в списке (линейный поиск),
• delete удаления элемента из списка (при наличии);
• getMin и getMax взятия минимального и максимального (в указанном порядке)
элементов из списка.
*/

#include <stdio.h>
#include <stdlib.h>

typedef int (*cmp_func)(const unsigned int *, const unsigned int *);

typedef struct Node {
    unsigned int inf;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    cmp_func cmp;
} DoublyLinkedList;

// Инициализация списка
void init(DoublyLinkedList *list, cmp_func cmp) {
    list->head = NULL;
    list->tail = NULL;
    list->cmp = cmp;
}

// Очистка списка
void clear(DoublyLinkedList *list) {
    Node *curr = list->head;
    while (curr) {
        Node *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    list->head = list->tail = NULL;
}

// Проверка пустоты
int empty(DoublyLinkedList *list) {
    return list->head == NULL;
}

// Добавление элемента в упорядоченный список
void add(DoublyLinkedList *list, unsigned int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->inf = value;
    newNode->prev = newNode->next = NULL;

    if (empty(list)) {
        list->head = list->tail = newNode;
        return;
    }

    // Найти позицию для вставки
    Node *curr = list->head;
    while (curr && list->cmp(&curr->inf, &value) < 0) {
        curr = curr->next;
    }

    if (curr == NULL) {
        // вставляем в конец
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    } else if (curr == list->head) {
        // вставляем в начало
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    } else {
        // вставляем между curr->prev и curr
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
}

// Проверка наличия элемента (линейный поиск)
int contains(DoublyLinkedList *list, unsigned int value) {
    Node *curr = list->head;
    while (curr) {
        if (curr->inf == value)
            return 1;
        curr = curr->next;
    }
    return 0;
}

// Удаление элемента (первого вхождения)
int delete(DoublyLinkedList *list, unsigned int value) {
    Node *curr = list->head;
    while (curr) {
        if (curr->inf == value) {
            if (curr->prev)
                curr->prev->next = curr->next;
            else
                list->head = curr->next;

            if (curr->next)
                curr->next->prev = curr->prev;
            else
                list->tail = curr->prev;

            free(curr);
            return 1; // удалено
        }
        curr = curr->next;
    }
    return 0; // не найдено
}

// Получение минимального элемента
unsigned int getMin(DoublyLinkedList *list) {
    return list->head->inf;
}

// Получение максимального элемента
unsigned int getMax(DoublyLinkedList *list) {
    return list->tail->inf;
}

// Пример функции сравнения: по возрастанию
int cmp_asc(const unsigned int *a, const unsigned int *b) {
    if (*a < *b) return -1;
    if (*a > *b) return 1;
    return 0;
}

// Пример использования
int main() {
    DoublyLinkedList list;
    init(&list, cmp_asc);

    add(&list, 5);
    add(&list, 2);
    add(&list, 9);
    add(&list, 1);
    add(&list, 2);

    printf("Min: %u\n", getMin(&list));
    printf("Max: %u\n", getMax(&list));

    printf("Contains 2? %s\n", contains(&list, 2) ? "Yes" : "No");
    printf("Contains 7? %s\n", contains(&list, 7) ? "Yes" : "No");

    delete(&list, 2);
    printf("Contains 2 after deletion? %s\n", contains(&list, 2) ? "Yes" : "No");

    clear(&list);
    printf("List empty after clear? %s\n", empty(&list) ? "Yes" : "No");

    return 0;
}
