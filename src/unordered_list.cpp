#include "unordered_list.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


UnorderedArrayList::UnorderedArrayList(int cap)
    : UnorderedList("ArrayList"), capacity(cap), size(0)
{
    buf = new string[capacity];
}

int UnorderedArrayList::find_index(const string & word)
{
    for (int i = 0; i < size; i++) 
    {
        if (buf[i] == word) return i;
    }
    return -1;
}

void UnorderedArrayList::insert(const string & word)
{
    if (is_full()) 
    {
        error(word, "List is full.");
        return;
    }
    buf[size++] = word;
}

bool UnorderedArrayList::find(const string & word)
{
    int index = find_index(word);
    if (index == -1) 
    {
        return 0;
    } 
    else 
    {
        return 1;
    }
}

void UnorderedArrayList::remove(const string & word)
{
    int index = find_index(word);
    if (index == -1) 
    {
        cout << word << " not found. Cannot remove." << endl;
        return;
    }
    for (int i = index; i < size - 1; i++) 
    {
        buf[i] = buf[i + 1];
    }
    size--;
}

bool UnorderedArrayList::is_empty()
{
    return size == 0;
}

bool UnorderedArrayList::is_full()
{
    return size == capacity;
}

void UnorderedArrayList::print(ostream & out)
{
    for (int i = 0; i < size; i++) 
    {
        out << buf[i];
    }
    out << endl;
}

UnorderedArrayList::~UnorderedArrayList()
{
    delete[] buf;
}

void ListNode::print(ostream & out, ListNode * L)
{
    while (L != nullptr) 
    {
        out << L->data;
        L = L->next;
    }
    out << endl;
}

ListNode * ListNode::find(const string & word, ListNode * L)
{
    while (L != nullptr) 
    {
        if (L->data == word) return L;
        L = L->next;
    }
    return nullptr;
}

void ListNode::delete_list(ListNode * L)
{
    while (L != nullptr) 
    {
        ListNode * temp = L;
        L = L->next;
        delete temp;
    }
}

void ListNode::remove(const string & word, ListNode * & L)
{
    ListNode * curr = L;
    ListNode * prev = nullptr;
    while (curr != nullptr) 
    {
        if (curr->data == word) 
        {
            if(prev == nullptr)
            {
                L = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            prev = curr;
            curr = curr->next;
            delete curr;
            return;
        }
    }
}

UnorderedLinkedList::UnorderedLinkedList()
    : UnorderedList("LinkedList"), head(nullptr)
{
}

void UnorderedLinkedList::insert(const string & word)
{
    head = new ListNode(word, head);
}

bool UnorderedLinkedList::find(const string & word)
{
    ListNode * result = ListNode::find(word, head);
    if (result == nullptr) 
    {
        return 0;
    } 
    else 
    {
        return 1;
    }
}

void UnorderedLinkedList::remove(const string & word)
{
    ListNode::remove(word, head);
}

bool UnorderedLinkedList::is_empty()
{
    return head == nullptr;
}

bool UnorderedLinkedList::is_full()
{
    return false;
}

void UnorderedLinkedList::print(ostream & out)
{
    ListNode::print(out, head);
}

UnorderedLinkedList::~UnorderedLinkedList()
{
    ListNode::delete_list(head);
}

ostream & operator << (ostream & out, UnorderedList & L)
{
    L.print(out);
    return out;
}

void error(string word, string msg)
{
    cerr << "Error: " << msg << " Word: \"" << word << "\"." << endl;
}

void insert_all_words(int k, string file_name, UnorderedList & L)
{
    Timer t;
    double eTime;
    ifstream in (file_name);
    int limit = k + NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
    {
        L.insert(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void find_all_words(int k, string file_name, UnorderedList & L)
{   Timer t;
    double eTime;
    ifstream in (file_name);
    int limit = k + NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
    {
        L.find(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tF = " << eTime << endl;
}

void remove_all_words(int k, string file_name, UnorderedList & L)
{   Timer t;
    double eTime;
    ifstream in (file_name);
    int limit = k + NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
    {
        L.remove(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_UnorderedList_methods(string file_name, UnorderedList & L)
{
    cout << L.name << endl;
    for(int K =1; K<=10; ++K)
    {
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L)
        remove_all_words(K, file_name, L)
        if(!L.is_empty())
        {
            error(L.name, "is not empty");
        }
    }
}

void measure_lists(string input_file)
{
    UnorderedArrayList arraylist;
    UnorderedLinkedList linkedlist;
    cout << "Unordered array lists:" << endl;
    measure_UnorderedList_methods(input_file, arraylist);
    cout << "unordered linked list" << endl;
    measure_UnorderedList_methods(input_file, linkedlist);
}