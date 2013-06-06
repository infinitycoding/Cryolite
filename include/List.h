
#ifndef _list_h_
#define _list_h_

template <typename T>

class List
{
    public:

        List();
        ~List();

        void ListPushBack(T *element);
        void ListPushFront(T *element);
        void ListInsertAfter(T *element);
        void ListInsertBefore(T *element);

        T *ListPopBack();
        T *ListPopFront();
        T *ListRemove();
        T *ListGetCurrent();

        void ListNext();
        void ListPrevious();


        void ListSetLast();
        void ListSetFirst();
        bool ListIsEmpty();
        bool ListIsLast();


        size_t ListSize();

        struct ListNode
        {
            struct ListNode *next;
            struct ListNode *prev;
            T *element;
        };

        void ListSplice(struct ListNode *start, struct ListNode *end, struct ListNode *target);
        T *ListRemoveNode(struct ListNode *node);

        void (*structCleaner)(T *element);
    private:
        struct ListNode *head;
        struct ListNode *current;

};



template <typename T>
List<T>::List()
{
    struct ListNode *dummy = new struct ListNode;
    this->head = dummy;
    this->current = dummy;
    dummy->next = dummy;
    dummy->prev = dummy;
    dummy->element = NULL;
    this->structCleaner = NULL;
}


template <typename T>
List<T>::~List()
{
    while(!this->ListIsEmpty())
    {
        if(structCleaner)
        {
            T *element = ListPopFront();
            structCleaner(element);
            delete element;
        }
        else
        {
            delete ListPopFront();
        }
    }
}

template <typename T>
void List<T>::ListPushBack(T *element)
{
    struct ListNode *node = new struct ListNode;
    node->element = element;
    node->next = node;
    node->prev = node;
    ListSplice(node, node, this->head->prev);
}

template <typename T>
void List<T>::ListPushFront(T *element)
{
    struct ListNode *node = new struct ListNode;
    node->element = element;
    node->next = node;
    node->prev = node;
    ListSplice(node, node, this->head);
}

template <typename T>
void List<T>::ListInsertAfter(T *element)
{
    struct ListNode *node = new struct ListNode;
    node->element = element;
    node->next = node;
    node->prev = node;
    ListSplice(node, node, this->current);
}

template <typename T>
void List<T>::ListInsertBefore(T *element)
{
    struct ListNode *node = new struct ListNode;
    node->element = element;
    node->next = node;
    node->prev = node;
    ListSplice(node, node, this->current->prev);
}

template <typename T>
T *List<T>::ListPopBack()
{
    struct ListNode *last = this->head->prev;
    return ListRemoveNode(last);
}

template <typename T>
T *List<T>::ListPopFront()
{
    struct ListNode *first = this->head->next;
    return ListRemoveNode(first);
}

template <typename T>
T *List<T>::ListRemoveNode(struct ListNode *node)
{
    T *element = node->element;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    return element;
}

template <typename T>
T *List<T>::ListRemove()
{
    T *element = ListGetCurrent();
    struct ListNode *node = this->current;
    this->current = this->current->next;
        node->prev->next = node->next;
        node->next->prev = node->prev;
    delete node;
    return element;
}

template <typename T>
size_t List<T>::ListSize()
{
    struct ListNode *node = this->head->next;
    struct ListNode *head = this->head;
    size_t size = 0;
        while (node != head) {
            node = node->next;
            size++;
        }
    return size;
}

template <typename T>
T *List<T>::ListGetCurrent()
{
    return this->current->element;
}

template <typename T>
void List<T>::ListNext()
{
    this->current = this->current->next;
}

template <typename T>
void List<T>::ListPrevious()
{
    this->current = this->current->prev;
}

template <typename T>
bool List<T>::ListIsLast()
{
    return (this->current == this->head);
}

template <typename T>
void List<T>::ListSetFirst()
{
    this->current = this->head->next;
}

template <typename T>
void List<T>::ListSetLast()
{
    this->current = this->head->prev;
}

template <typename T>
bool List<T>::ListIsEmpty()
{
    return (this->head == this->head->next);
}

template <typename T>
void List<T>::ListSplice(struct ListNode *start, struct ListNode *end, struct ListNode *target)
{
    start->prev->next = end->next;
    end->next->prev = start->prev;
    start->prev = target;
    end->next = target->next;
    target->next->prev = end;
    target->next = start;
}

#endif
