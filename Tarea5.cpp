#include<iostream>

using namespace std;
//registro que almacena los datos de la veterinaria
struct info{
    int id;
    string owner;
    string race;
    float weight;
    int age;
};
//nodo
struct Node{
    info data;
    Node *next;
};

class CircularList{
    private:
    Node *head;

    public:
    CircularList();
    ~CircularList();
    void deleteList(Node *);
    void addPet(info);
    void addInfo();
    void printById(int);
    bool deleteById(int);
};
//constructor
CircularList::CircularList(){
    head = NULL;
}
//destructor
CircularList::~CircularList(){
    if(head){
        deleteList(head);
        head = NULL;
    }
}
//función auxiliar para destructor
void CircularList::deleteList(Node *h){
    if(h->next != head)
        deleteList(h->next);
    delete h;
}
//función insertar
void CircularList::addPet(info data){
    Node *nd, *aux;
    nd = new Node();
    nd->data = data;
    if(!head){
        head = nd;
        head->next = head;
    }
    else{
        nd->next = head;
        aux = head;
        while(aux->next != head)
            aux = aux->next;
        aux->next = nd;
    }
}
//función agregar datos
void CircularList::addInfo(){
    cout << endl;
    info dataPet;
    cout << "Id: ";
    cin >> dataPet.id; cin.ignore();
    cout << "Propietario: ";
    getline(cin, dataPet.owner); 
    cout << "Raza: ";
    getline(cin, dataPet.race);
    cout << "Peso: ";
    cin >> dataPet.weight; cin.ignore();
    cout << "Edad: ";
    cin >> dataPet.age; cin.ignore();
    addPet(dataPet);
}
//función que busca por id e imprime la información perteneciente a dicho id
void CircularList::printById(int ref){
    bool aux;
    if(!head) //si el registro está vacío
        cout << "El registro está vacío :(" << endl;
    else{
        Node *s = head, *p;
        if(s->data.id == ref){ //si es el primero
            aux = true;
        }
        else{ 
            while(s->next != head && s->next->data.id != ref)
                s = s->next;
            if(s->next == head) //si no está en el registro
                aux = false;
            else{ //si está en el registro
                p = s->next;
                s = p;
                aux = true;
            }
        }
        if(aux == true){ //imprimiento los datos del id, encontrado.
            cout << "\n\tImprimiento resultados." << endl;
            cout << "ID: " << s->data.id <<endl; 
            cout << "Propietario: " << s->data.owner << endl;
            cout << "Raza: " <<s->data.race << endl;
            cout << "Peso: " << s->data.weight << endl;
            cout << "Edad: " << s->data.age << endl; 
        }
        else{
            cout << "No se encontró en el registro :(" << endl;  
        }
    }
}
//función que elimina un elemento dado su id
bool CircularList::deleteById(int ref){
    if(!head) //si el registro está vacío.
        return false;
    else{
        Node *s = head, *p;
        if(s->data.id == ref){
            head = head->next;
            delete s;
            return true;
        }
        else{
            while(s->next != head && s->next->data.id != ref)
                s = s->next;
            if(s->next == head)
                return false;
            else{
                p = s->next;
                s->next = s->next->next;
                delete p;
                return true;
            }
        }
    }
}

int main(void){
    int opc, dataRef, dataRef2;
    CircularList veterinary;
    bool aux = true;
    cout << "\nADMINISTRACIÓN DE VETERINARIA MEDIANTE USO DE LISTAS CIRCULARES" << endl;
    do{
        cout << endl;
        cout << "\tMenú" << endl;
        cout << "1. Agregar mascota" << endl;
        cout << "2. Mostrar por ID" << endl;
        cout << "3. Eliminar por ID" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opc; cin.ignore();

        switch(opc){
            case 1:
                veterinary.addInfo();
                break;
            case 2:
                cout << "Digite el ID de la mascota que desea mostrar: ";
                cin >> dataRef; cin.ignore();
                veterinary.printById(dataRef);
                break;
            case 3:
                cout << "Digite el ID a eliminar: ";
                cin >> dataRef2; cin.ignore();
                if(veterinary.deleteById(dataRef2))
                    cout << "Elemento elimindado satisfactoriamente :)" << endl;
                else 
                    cout << "El elemento no se eliminó, verifique si el registro está vacío o intente de nuevo." << endl;
                break;
            case 4:
                aux = false;
                break;
            case 5:
                cout << "La opcion ingresada es inválida :(" << endl;
                break; 

        }
    }while(aux != false);

    return 0;
}