#include <iostream>
#include <string>
#include<time.h>
using namespace std;

//Estructura Lugar
struct Place{

    string namePlace;
    struct Place* nextPlace; //para enlazar todos los vertices en una lista
    struct Edge* subListEdge; //representa los arcos que salen de ese vertice
    bool visited;
    Place(string place){
        namePlace = place;
        nextPlace = NULL;
        subListEdge = NULL;
        visited = false;
    }
}*placeList;

//Estructura Arco
struct Edge{
    int distance;
    string destination;
    struct Edge* nextEdge; //para enlazar todos los vertices en una lista
    Edge(int dis,string des){
        distance = dis;
        destination = des;
        nextEdge = NULL;
    }
};

struct Place* graph1; // el apuntador inicial del grafo
struct Place* graph2; // el apuntador inicial del grafo

//Estructura Persona
struct People{
    string name;
    int id;
    struct Place*currentLocation;
    struct People*friendsList;
    struct Place*placeDestination;
    struct People*next;
    People(string n,int i,Place*current,Place*des){
        name= n;
        id = i;
        currentLocation = current;
        placeDestination = des;
        friendsList = NULL;
        next = NULL;
    }

}*peopleList;
//*****************************************PLACE******************************

struct Place* searchPlace(string origin,Place*pList) {
    struct Place* tempP = pList;
    while(tempP != NULL){
        if(tempP->namePlace == origin)
            return tempP;
        tempP = tempP->nextPlace;
    }
    return NULL;
}
Place*addPlace(string namePlace,Place*pList){
    struct Place* newPlace= new Place(namePlace);
    newPlace->nextPlace= pList;
    pList = newPlace;
    return pList;

}

//*****************************************************EDGE*****************************************************
/**
 * * Crea un nuevo arco entre el vertice origen y el vertice destino
 *
 * Args:
 *   origin (string): El nombre del lugar de origen.
 *   dis (int): distancia entre el origen y el destino
 *   des (string): destino
 *
 * Returns:
 *   un puntero al lugar donde se agregó el borde.
 */

void addEdge(string origin,int dis,string des,struct Place * pList){

    struct Place* vOrigin = searchPlace(origin,pList);
    struct Place* vDestination = searchPlace(des,pList);

    if(vOrigin == NULL){
        cout<<"NO SE HA ENCONTRO EL ORIGEN";
        return;
    }
    if(vDestination == NULL ) {
        cout<<"NO SE HA ENCONTRO EL DESTINO";
        return;
    }
    struct Edge* newEdge = new Edge(dis,des);

    //se inserto al inicio de la sublista de Arcos
    newEdge->nextEdge = vOrigin->subListEdge;
    vOrigin->subListEdge = newEdge;

}


bool existPath = false;
/**
 * Función recursiva que busca un camino entre dos lugares.
 *
 * Args:
 *   graph (Place): El gráfico a buscar.
 *   des (string): el lugar de destino
 *
 * Returns:
 *   un valor booleano.
 */
bool searchEdge(struct  Place* origin, string des) {

    if((origin == NULL) or (origin->visited == true))
        return existPath;

    if(origin->namePlace == des) {
        existPath= true;
        return existPath;
    }
    origin->visited =true;
    struct Edge * tempE = origin->subListEdge;
    while(tempE != NULL){
        searchEdge(searchPlace(tempE->destination),des);
        tempE = tempE->nextEdge;
    }
}




bool printEdge(struct Place* origin,string des, string path){
    if((origin == NULL) or origin->visited)
        return existPath;

    if(origin->namePlace == des){
        cout<<"\n\nRuta................  "<<path<<des;
        existPath= true;
        return existPath;
    }
    origin->visited =true;

    struct Edge * tempE = origin->subListEdge;

    while(tempE != NULL){
        printEdge(searchPlace(tempE->destination), des,path+graph->namePlace);
        tempE = tempE->nextEdge;
    }
    origin->visited =false;
}


//*******************************************************************************************************

//*****************************************************PEOPLE********************************************
//NO PROBADO

/**
 * Esta función crea un nuevo objeto Personas y lo agrega a la lista de personas
 *
 * Args:
 *   name (string): el nombre de la persona
 *   id (int): la identificación de la gente
 *   current (Place): el lugar actual de la gente
 *   des (Place): el destino de la gente
 *   plist (People): la lista de personas
 *
 * Returns:
 *   La lista.
 */
void addPeople(string name,int id,Place*current,Place*des){
    People*newPeople = new People(name,id,current,des);
    newPeople->next = peopleList;
    peopleList = newPeople;

}

/**
 * Busca una persona en la lista de personas.
 *
 * Args:
 *   id (int): la identificación de las personas que desea buscar
 *   pList (People): La lista de personas para buscar.
 *
 * Returns:
 *   Un puntero a un objeto Personas.
 */
People*searchPeople(int id){
    if(peopleList == NULL){
        return NULL;
    }
    People*peopleTemp = peopleList;
    while(peopleTemp != NULL){
        if(peopleTemp->id == id){
            return peopleTemp;
        }
    }
    return NULL;
}

/**
 * Modifica la información de una persona
 *
 * Args:
 *   oldId (int): El id de la persona que quieres modificar.
 *   newName (string): El nuevo nombre de la persona.
 *   newId (int): La nueva identificación de la persona.
 *   current (Place): es la ubicación actual de la persona
 *   des (Place): es el destino de la persona
 *   pList (People): es la lista de personas
 *
 * Returns:
 *   la lista de personas
 */

void modPeople(int oldId,string newName,int newId,Place*current,Place*des){
    People*people = searchPeople(oldId);
    if(people == NULL){
        cout<<"\nLA PERSONA NO SE ENCUENTRA REGISTRADA "<<endl;
    }
    else{
        people->name = newName;
        people->id = newId;
        people->currentLocation = current;
        people->placeDestination = des;

    }
}

/**
 * Busca a una persona con la identificación dada, y si la encuentra, la elimina de la lista
 *
 * Args:
 *   oldId (int): La identificación de la persona que desea eliminar.
 *   pList (People): La lista de personas.
 *
 * Returns:
 *   la lista de personas
 */
void deletePeople(int oldId,People*pList){
    People*people = searchPeople(oldId);
    if (people == NULL){
        cout<<"\nLA PERSONA NO EXISTE";
    }
    else{
        if (pList->id == oldId){
            pList = pList->next;
        }
        else{
            People*temp = pList;
            People*ant = NULL;
            while((temp!=NULL)&&(temp->id!=oldId)){
                ant = temp;
                temp = temp->next;
            }
            if(temp ==NULL){
                cout<<"\nLA PERSONA NO EXISTE";

            }else{
                ant->next = temp->next;
            }
        }
    }
}

/**
 * Esta función imprime la lista de personas
 *
 * Args:
 *   pList (People): es la lista de personas
 */
void printPeopleList(){
    if (peopleList == NULL){
        cout<<"LA LISTA DE PERSONAS ESTA VACIA";
    }
    else{
        People*temp = peopleList;
        while(temp !=NULL){
            cout<<temp->name<<endl;
            cout<<temp->id<<endl;
            cout<<temp->currentLocation->namePlace<<endl;
            cout<<temp->placeDestination->namePlace<<endl;
            temp = temp->next;
        }
    }
}

void dataLoad() {



    //addPeople("Karina", 1, searchPlace("SantaClara"), searchPlace("CQ"));
    //addPeople("Leiner", 2, searchPlace("CQ"), searchPlace("SantaClara"));

}
void amplitude(){
    struct Place *tempP = graph1;

    while(tempP != NULL){//RECORRE LA LISTA DE VERTICES
        cout<<"\nVertice:  "<<tempP->namePlace<<"\t";
        struct Edge* tempE = tempP->subListEdge;

        while(tempE!= NULL){//RECORRE LOS ARCOS DE LA LISTA DE ARCOS DEL VERTICE
            cout<<tempP->namePlace<<tempE->destination<<tempE->distance<<",  ";
            tempE = tempE->nextEdge;
        }
        tempP = tempP->nextPlace;
    }
}

void depth(struct Place * start){
    if((start == NULL) or (start->visited == true)){
        cout<<endl;
        return;
    }

    start->visited = true;

    struct Edge*  tempE = start->subListEdge;
    while(tempE != NULL){
        cout<<start->namePlace<<tempE->destination<<tempE->distance<<",  ";

        profundidad(buscarVertice(tempE->destination));

        tempA = tempA->sigA;
    }

}

void desmarcar(){
    struct Vertice *tempV = grafo;

    while(tempV != NULL){

        tempV->visitado = false;
        tempV = tempV->sigV;
    }
}
int randomNum(){
    int num, c;
    srand(time(NULL));


    for(c = 1; c <= 25; c++)
    {
        num = 1 + rand() % (11 - 1);
        return num;
    }
}
void graph1Load(){
    graph1 = addPlace("SantaClara",graph1);
    graph1 = addPlace("CQ",graph1);
    graph1 = addPlace("Florencia",graph1);
    graph1 = addPlace("Muelle",graph1);
    graph1 = addPlace("Platanar",graph1);

    addEdge("CQ",randomNum(),"Florencia",graph1);
    addEdge("Florencia",randomNum(),"CQ",graph1);
    addEdge("Florencia",randomNum(),"SantaClara",graph1);
    addEdge("SantaClara",randomNum(),"Florencia",graph1);
    addEdge("Florencia",randomNum(),"Platanar",graph1);
    addEdge("Platanar",randomNum(),"Florencia",graph1);
    addEdge("Platanar",randomNum(),"Muelle",graph1);
}
void graph2Load(){

    graph2 = addPlace("SantaClara",graph2);//A
    graph2 = addPlace("CQ",graph2);//B
    graph2 = addPlace("Florencia",graph2);//C
    graph2 = addPlace("Muelle",graph2);//D
    graph2 = addPlace("Platanar",graph2);//E
    graph2 = addPlace("Tanque",graph2);//F
    graph2 = addPlace("Fortuna",graph2);//G

    addEdge("SantaClara",randomNum(),"CQ",graph2);
    addEdge("CQ",randomNum(),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(),"Florencia",graph2);
    addEdge("Florencia",randomNum(),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(),"Muelle",graph2);
    addEdge("Muelle",randomNum(),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(),"Platanar",graph2);
    addEdge("Platanar",randomNum(),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(),"Tanque",graph2);
    addEdge("Tanque",randomNum(),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(),"Fortuna",graph2);
    addEdge("Fortuna",randomNum(),"SantaClara",graph2);

    addEdge("CQ",randomNum(),"Florencia",graph2);
    addEdge("CQ",randomNum(),"Fortuna",graph2);

    addEdge("Florencia",randomNum(),"Muelle",graph2);
    addEdge("Muelle",randomNum(),"Florencia",graph2);

    addEdge("Florencia",randomNum(),"Tanque",graph2);
    addEdge("Tanque",randomNum(),"Florencia",graph2);

    addEdge("Muelle",randomNum(),"Platanar",graph2);
    addEdge("Platanar",randomNum(),"Muelle",graph2);

    addEdge("Platanar",randomNum(),"Tanque",graph2);
    addEdge("Tanque",randomNum(),"Platanar",graph2);

    addEdge("Tanque",randomNum(),"Fortuna",graph2);
    addEdge("Fortuna",randomNum(),"Tanque",graph2);






}
int main() {
    dataLoad();
    printPeopleList();
    return 0;
}
