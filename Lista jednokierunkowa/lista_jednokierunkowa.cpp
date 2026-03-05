#include <iostream>
#include <stdio.h>
using namespace std;

void insertNode(int key, string data);
void displayList();


struct Node
{ // kod 10_01
    int key = -1;
    string data = "";
    Node *next = nullptr;
};

Node *head = nullptr; // globalny wskaznik zawsze pokazujacy pierszy wezel
Node *lastAdded = nullptr;

void menu()
{
    cout << "Menu:\n";
    cout << "1-dodaj element\n";
    cout << "2-usun element\n";
    cout << "3-pokaz liste\n";
    cout << "4-zmodyfikuj liste\n";
    cout << "9-wyjdz i nie wracaj\n";
}

void deleteNode (Node* elementToRemove){
    if (head==nullptr){
        cout << "Nic tu nie ma smieciu\n";
        return;
    }
    //usuwanie pierwszego elementu
    if (head==elementToRemove){
        head=head->next;
        delete elementToRemove;
        if(head=nullptr) lastAdded=nullptr;
        return;
    }
    //usuwanie ostatniego elementu
    Node* prev = head;
    if(elementToRemove==lastAdded){
        while(prev->next!=elementToRemove){
            prev=prev->next;
        }
        prev->next=nullptr;
        delete elementToRemove;
        lastAdded=prev;
    }
    //usuwanie elementu ze srodka listy
    if(prev!=elementToRemove && elementToRemove->next!=nullptr){
        while(prev->next!=elementToRemove){
            prev=prev->next;
        }
        prev->next=elementToRemove->next;
        delete elementToRemove;
    }



}
void insertNode(int key, string data)
{
    Node *newNode = new Node();
    newNode->key = key;
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode; // jak nic nie ma, stworzy pierszy wezel
        lastAdded = newNode;
    }
    else
    {
        // Node* temp = head; //zawsze idz od poczatku
        // while (temp->next != nullptr) { //az natrafisz na koniec listy
        // temp = temp->next; //jesli jeszcze nie koniec, idziemy dalej po wskaznikach
        //}
        lastAdded->next = newNode;
    }
    lastAdded = newNode;
}

void displayList()
{
    Node *temp = head;
    int index=1;
    if(head==nullptr){
        cout << "Lista jest pusta\n";
    }
    while (temp != nullptr)
    {
        cout << index << " | Key: " << temp->key << ", Data: " << temp->data << endl;
        temp = temp->next;
        index ++;
    }
}

int main()
{
    int n, key, choice;
    string data;
    for (int i = 0;; i++)
    {
        //system("cls");
        menu();
        cout << "Podaj co wybierasz szkodniku:";
        cin >> choice;
        cout << endl;
        if(choice<=0 || choice > 4 && choice < 9|| choice > 9 ) {
            cout << "Nieprawidlowy wybor\n";
        }

        switch (choice)
        {
        case 1:
        {
            cout << "Enter the number of nodes: ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter key and data for node " << i + 1 << ": " << endl;
                cout << "Please write integer number: ";
                cin >> key;
                cout << "Please write any string: ";
                cin >> data;
                insertNode(key, data);
            }
            break;
        }
        case 2:{
            int index;
            Node* elementToRemove = head;
            displayList();
            cout << "Podaj numer elementu do usuniecia: ";
            cin >> index;
            cout << endl;

            if(index<=0){
                cout << "Nieprawidlowy numer\n";
                break;
            }

            for(int i=1; elementToRemove!=nullptr && i<index ; i++){
                elementToRemove = elementToRemove->next;
            }
            deleteNode(elementToRemove);
            cout << "Element usunieto\n";

            break;
        }
        case 3:
        {
            cout << "The entire list:" << endl;
            displayList();
            break;
        }
        case 4:
        { 
            displayList();
            int indexM;
            Node* elementM = head;
            cout << "Wybierz element do modyfkikacji: ";
            cin >> indexM;
            cout << endl;
            for(int i=1; elementM!=nullptr && i<indexM ; i++){
                elementM = elementM->next;
            }
            cout << "Please write new integer number: ";
            cin >> key;
            cout << "Please write new string: ";
            cin >> data;
            elementM->key=key;
            elementM->data=data;
            cout << "Zmodyfikowano pomyslnie\n";
            break;
        }
        case 9:
            return 0;
        }
        cout << "\nNacisnij enter aby kontynuowac\n";
        cin.ignore();
        getchar();
    }
}