/*Лабораторная работа 4. Вариант 12.

Задание: Сформируйте два связных списка из N и M элементов соответственно, содержащих случайные целочисленные значения от 1 до K(N, M и K вводятся с клавиатуры и должны быть натуральными).
 Значения в списках могут повторяться и должны располагаться в порядке не возрастания (значение следующего элемента списка меньше или равно текущего).
 Сформированные списки выведите на экран. Затем сформируйте новый список из элементов исходных, выполнив по каждому из них один проход.
 В новом списке должен быть сохранен порядок не возрастания. Новый список выведите на экран. Пример: N=4, M=3, K=10. Значения первого списка: 5 3 3 2.
 Значения второго списка: 8 5 4. Значения нового списка: 8 5 5 4 3 3 2.
 
Предварительный проект:
 N - кол-во элементов первого списка
 M - кол-во эл-ов второго списка
 K - граница случайных чисел

1. Создание списка
2. Поиск места вставки, поиск адреса элемента после которого надо вставить
3. Поиск последнего элемента списка
4. Заполнение случайными значениями
5. Вывод на экран 
6. Объединить два списка
7. Освободить память
8. Вывод на экран


поделить функцию insortlist на вставку элемента и поиска последнего элемента
поменять параметры в unionlist*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Определение структуры для элемента связного списка
struct Node {
    int val;
    Node* next;
};

// Функция для создания нового элемента списка
Node* create(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node)); //память для нового узла
    newNode->val = val; //присваивание значения
    newNode->next = NULL; //ууказываем в NULL
    return newNode;
}

// Функция поиска места для вставки нового значения. Принимает голову и значение.
// Возвращает адрес элемента, после которого осуществляется вставка
Node * find(Node * head, int val){
    Node* p = NULL;
    while (head != NULL) {
        if (head->val < val) {
            return p;
        }
        p = head;
        head = head->next;
    }
    return p;
}

//Функция поиска последнего элемента списка. Принимает голову.
//Возвращает адрес последнего элемента.
Node * last_el(Node * head){
    while (head && head->next) {
        head = head->next;
    }
    return head;
}

// Функция вставки узла в список в порядке невозрастания
Node* insertNode(Node* head, int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;

    if (head == NULL) { // Если список пуст
        return new_node;
    }

    Node* position = find(head, val);

    if (!position) { // Вставка в начало списка
        new_node->next = head;
        head = new_node;
    } else { // Вставка после найденной позиции
        new_node->next = position->next;
        position->next = new_node;
    }

    return head;
}

//функция для создания отсортированного списка с случайными значениями
Node* SortList(Node * head, int sz, int K){
    for (int i = 0; i < sz; i++) {
        int value = rand() % K + 1;
        head = insertNode(head, value);
    }
    return head;
}

// Функция для вывода связного списка
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}


// Функция добавления элемента из одного списка в конец другого
Node* append(Node* head, Node* element) {
    if (element == NULL) { // Если добавляемый элемент отсутствует
        return head;
    }

    element->next = NULL; // Убедимся, что элемент "изолирован"

    if (head == NULL) { // Если список пуст
        return element;
    }

    Node* tail = last_el(head); // Ищем конец списка
    tail->next = element; // Добавляем элемент в конец списка

    return head; // Возвращаем обновлённый список
}


// Функция для объединения двух списков
Node* unionlist(Node** head1, Node** head2, Node** merged) {
    while (*head1 != NULL && *head2 != NULL) {
        if ((*head1)->val > (*head2)->val) {
            Node* temp = *head1;        // Сохраняем текущий элемент
            *head1 = (*head1)->next;    // Перемещаем указатель head1
            *merged = append(*merged, temp); // Добавляем элемент в объединённый список
        } else {
            Node* temp = *head2;        // Сохраняем текущий элемент
            *head2 = (*head2)->next;    // Перемещаем указатель head2
            *merged = append(*merged, temp); // Добавляем элемент в объединённый список
        }
    }

    // Если один из списков закончился, добавляем оставшиеся элементы
    while (*head1 != NULL) {
        Node* temp = *head1;
        *head1 = (*head1)->next;
        *merged = append(*merged, temp);
    }
    while (*head2 != NULL) {
        Node* temp = *head2;
        *head2 = (*head2)->next;
        *merged = append(*merged, temp);
    }

    return *merged; // Возвращаем указатель на объединённый список
}


//функция освобождения памяти
Node* delall(Node* head)
{
    Node* p = head;
    while (head != NULL)
    {
        head = head->next;
        free(p);
        p = head;
    }
    return NULL;
}

int main() {
    int N, M, K, val;
    Node* head;

    // Ввод данных
    printf("N, M и K: ");
    scanf("%d %d %d", &N, &M, &K);

    if (N <= 0 || M <= 0 || K <= 0) {
        printf("Все значения должны быть натуральными числами.\n");
        return 1;
    }

    srand(time(NULL));
    //Создание списков
    Node* list1 = NULL;
    Node* list2 = NULL;

    //Заполнение списков
    list1 = SortList(list1, N, K);
    list2 = SortList(list2, M, K);

    // Вывод на экран списков
    printf("Первый список: ");
    printList(list1);

    printf("Второй список: ");
    printList(list2);

    // Объединение списков
    Node* merged_list = NULL;
    Node* uni_l = unionlist(&list1, &list2, &merged_list);

    // Вывод на экран сформированного списка
    printf("Новый список: ");
    printList(uni_l);

    // Освобождение памяти
    uni_l = delall(uni_l);

    return 0;
}
