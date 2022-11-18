#include <iostream>
#include <string>
#include<time.h>
using namespace std;


bool existPath = false;

//Estructura Lugar
struct Place{

    string namePlace;
    struct Place* nextPlace; //para enlazar todos los vertices en una lista
    struct Edge* subListEdge; //representa los arcos que salen de ese vertice
    struct People* subListPeople;
    bool visited;
    Place(string place){
        subListPeople = NULL;
        namePlace = place;
        nextPlace = NULL;
        subListEdge = NULL;
        visited = false;
    }
};

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
    short typeAdvance;
    int totalTravel; // el total de distancia recorrida
    struct Place*prePlace;
    struct Place*origin;
    struct Place*currentLocation;
    struct People*friendsList;
    string placeDestination;
    struct People*next;
    People(string n,int i,Place* orig,Place*current,string  des){
        origin = orig;
        name= n;
        id = i;
        prePlace = NULL;
        currentLocation = current;
        placeDestination = des;
        friendsList = NULL;
        next = NULL;
        typeAdvance = 0;
        totalTravel = 0;
    }

}*peopleList;
//*****************************************PLACE******************************


/**
 * Esta función busca un lugar en la lista de lugares
 *
 * Args:
 *   origin (string): el nombre del lugar que desea buscar
 *   pList (Place): la lista de lugares
 *
 * Returns:
 *   un puntero a un lugar.
 */
struct Place* searchPlace(string origin,Place*pList) {
    struct Place* tempP = pList;
    while(tempP != NULL){
        if(tempP->namePlace == origin)
            return tempP;
        tempP = tempP->nextPlace;
    }
    return NULL;
}
/**
 * Esta función crea un nuevo objeto Lugar y lo agrega al frente de la lista vinculada de Lugares
 *
 * Args:
 *   namePlace (string): El nombre del lugar que desea agregar.
 *   pList (Place): la lista de lugares
 *
 * Returns:
 *   Un puntero al nuevo lugar.
 */
Place*addPlace(string namePlace,Place*pList){
    struct Place* newPlace= new Place(namePlace);
    newPlace->nextPlace= pList;
    pList = newPlace;
    return pList;

}
void addPeopleToPlace(People*newPeople,Place*pList){

    newPeople->next= pList->subListPeople;
    pList->subListPeople = newPeople;

}
void deletePeopleToPlace(People*people,Place*pList){

    if (people == NULL){
        cout<<"\nLA PERSONA NO EXISTE";
    }
    else{
        if (pList->subListPeople->id == people->id){
            pList->subListPeople = pList->subListPeople->next;
        }
        else{
            Place*temp = pList;
            People*ant = NULL;
            while((temp!=NULL)&&(temp->subListPeople->id!=people->id)){
                ant = temp->subListPeople;
                temp->subListPeople = temp->subListPeople;
            }
            if(temp ==NULL){
                cout<<"\nLA PERSONA NO EXISTE";

            }else{
                ant->next = temp->subListPeople->next;
            }
        }
    }
}
void printPlace(Place*pList){
    Place*temp = pList;
    while(temp != NULL){
        while(temp->subListEdge != NULL){
            cout<<temp->namePlace<<"->"<<temp->subListEdge->destination+": "<<temp->subListEdge->distance<<endl;
            temp->subListEdge = temp->subListEdge->nextEdge;

        }



        temp = temp->nextPlace;
    }

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
bool searchEdge(struct  Place* origin, string des,Place*pList) {

    if((origin == NULL) or (origin->visited == true))
        return existPath;

    if(origin->namePlace == des) {
        existPath= true;
        return existPath;
    }
    origin->visited =true;
    struct Edge * tempE = origin->subListEdge;
    while(tempE != NULL){
        searchEdge(searchPlace(tempE->destination,pList),des,pList);
        tempE = tempE->nextEdge;
    }
}

/**
 * Es una función recursiva que imprime la ruta desde el origen hasta el destino.
 *
 * Args:
 *   origin: El lugar donde comienza la búsqueda.
 *   des (string): destino
 *   path (string): es la ruta que se está imprimiendo
 *   pList (Place): es la lista de lugares
 *
 * Returns:
 *   un valor booleano que indica si hay un camino entre dos lugares.
 */
bool printEdge(struct Place* origin,string des, string path,Place*pList){
    if((origin == NULL) or origin->visited)
        return existPath;
    if(origin->namePlace == des){
        cout<<"\n\nRuta................  "<<path<<des;
        existPath= true;
        return existPath;
    }
    origin->visited = true;
    struct Edge * tempE = origin->subListEdge;

    while(tempE != NULL){
        printEdge(searchPlace(tempE->destination,pList), des,path+pList->namePlace,pList);
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
void addPeople(string name,int id,Place*current,string des){
    Place*origin=current;
    People*newPeople = new People(name,id,current,current,des);
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

void modPeople(int oldId,string newName,int newId,Place*current,string des){
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
            cout<<temp->placeDestination<<endl;
            temp = temp->next;
        }
    }
}

void addFriends(People*p,People*newFriend){

    newFriend->next = p->friendsList;
    p->friendsList = newFriend;
}
/*
void dataLoad() {

    addPeople("Karina", 1, searchPlace("SantaClara",placeList), searchPlace("CQ",placeList));
    addPeople("Leiner", 2, searchPlace("CQ",placeList), searchPlace("SantaClara",placeList));
    addPeople("Tania", 3, searchPlace("Florencia",placeList), searchPlace("Muelle",placeList));
    addPeople("Leidy", 4, searchPlace("Platanar",placeList), searchPlace("SantaClara",placeList));
    addPeople("Enrique", 5, searchPlace("CQ",placeList), searchPlace("Florencia",placeList));
    addPeople("Prueba", 6, searchPlace("Muelle",placeList), searchPlace("SantaClara",placeList));

}*/


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

/**
 * Imprime el nombre del lugar, el nombre del destino, la distancia entre ellos, y luego se llama a sí mismo con el destino
 * como parámetro
 *
 * Args:
 *   start: es el lugar donde comienza el algoritmo
 *
 * Returns:
 *   el número de lugares que hay en la gráfica.
 */

void depth(struct Place * start,Place* pList){

    if((start == NULL) or (start->visited == true)){
        cout<<endl;
        return;
    }
    start->visited = true;
    struct Edge*  tempE = start->subListEdge;
    while(tempE != NULL){
        cout<<start->namePlace<<tempE->destination<<tempE->distance<<",  ";

        depth(searchPlace(tempE->destination,pList),pList);

        tempE = tempE->nextEdge;
    }
}


void unselect() {

    struct Place *tempP = graph1;

    while (tempP != NULL) {

        tempP->visited = false;
        tempP = tempP->nextPlace;
    }
}
/**
 * Genera un número aleatorio entre 1 y 10
 *
 * Returns:
 *   un número aleatorio entre 1 y 10.
 */

int randomNum(int random){
    int num = 0,c;
    srand(time(NULL));


    for(c = 1; c <= random; c++)
    {
        num = 1 + rand() % (random - 1);
        return num;
    }
}
/**
 * Crea un grafo con 5 vertices y 10 arcos.
 */
void graph1Load(){
    int num = 0;
    graph1 = addPlace("SantaClara",graph1);//A
    graph1 = addPlace("CQ",graph1);//B
    graph1 = addPlace("Florencia",graph1);//C
    graph1 = addPlace("Muelle",graph1);//D
    graph1 = addPlace("Platanar",graph1);//E
    num = randomNum(100);
    addEdge("CQ",num,"SantaClara",graph1);
    addEdge("SantaClara",num,"CQ",graph1);
    num = randomNum(100);
    addEdge("CQ",num ,"Florencia",graph1);
    addEdge("Florencia",num,"CQ",graph1);
    num = randomNum(100);
    addEdge("Florencia",num,"Muelle",graph1);
    addEdge("Muelle",num,"Florencia",graph1);
    num = randomNum(100);
    addEdge("Muelle",num,"Platanar",graph1);
    addEdge("Platanar",num,"Muelle",graph1);
    num = randomNum(100);
    addEdge("Platanar",num,"SantaClara",graph1);
    addEdge("SantaClara",num,"Platanar",graph1);

}
/**
 * Crea un gráfico con 7 vertice y 26 arcos.
 */
void graph2Load(){

    graph2 = addPlace("SantaClara",graph2);//A
    graph2 = addPlace("CQ",graph2);//B
    graph2 = addPlace("Florencia",graph2);//C
    graph2 = addPlace("Muelle",graph2);//D
    graph2 = addPlace("Platanar",graph2);//E
    graph2 = addPlace("Tanque",graph2);//F
    graph2 = addPlace("Fortuna",graph2);//G

    addEdge("SantaClara",randomNum(100),"CQ",graph2);

    addEdge("CQ",randomNum(100),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(100),"Florencia",graph2);
    addEdge("Florencia",randomNum(100),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(100),"Muelle",graph2);
    addEdge("Muelle",randomNum(100),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(100),"Platanar",graph2);
    addEdge("Platanar",randomNum(100),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(100),"Tanque",graph2);
    addEdge("Tanque",randomNum(100),"SantaClara",graph2);

    addEdge("SantaClara",randomNum(100),"Fortuna",graph2);
    addEdge("Fortuna",randomNum(100),"SantaClara",graph2);

    addEdge("CQ",randomNum(100),"Florencia",graph2);
    addEdge("CQ",randomNum(100),"Fortuna",graph2);

    addEdge("Florencia",randomNum(100),"Muelle",graph2);
    addEdge("Muelle",randomNum(100),"Florencia",graph2);

    addEdge("Florencia",randomNum(100),"Tanque",graph2);
    addEdge("Tanque",randomNum(100),"Florencia",graph2);

    addEdge("Muelle",randomNum(100),"Platanar",graph2);
    addEdge("Platanar",randomNum(100),"Muelle",graph2);

    addEdge("Platanar",randomNum(100),"Tanque",graph2);
    addEdge("Tanque",randomNum(100),"Platanar",graph2);

    addEdge("Tanque",randomNum(100),"Fortuna",graph2);
    addEdge("Fortuna",randomNum(100),"Tanque",graph2);

    addEdge("Fortuna",randomNum(100),"CQ",graph2);
    addEdge("Florencia",randomNum(100),"CQ",graph2);
}
int size(Edge*list){
    int cont =0;
    Edge*temp = list;
    while(temp !=NULL){
        cont++;
        temp = temp->nextEdge;
    }
    return cont;
}
Edge*searchIndex(int index,Edge*list){
    Edge*temp = list;
    int i = 0;
    while(temp != NULL){
        if (i == index){
            return temp;
        }
        i++;
        temp  = temp->nextEdge;
    }
}

void random_walk(People*p,Place*pList){
    cout<<"\n"+p->currentLocation->namePlace<<endl;
    int n = 0;
    int num = 0;
    n = size(p->currentLocation->subListEdge);
    if (n > 1){
         num = randomNum(n);
    }
    Edge*tempList = p->currentLocation->subListEdge;
    Edge*edge = searchIndex(num,tempList);


    if (p->prePlace !=NULL){
        while(p->prePlace->namePlace == edge->destination){
            num = (randomNum(size(p->currentLocation->subListEdge))-1);
            edge = searchIndex(num,tempList);
        }

    }
    deletePeopleToPlace(p,p->currentLocation);
    Place*newPlace = searchPlace(edge->destination,pList);
    p->totalTravel += tempList->distance;
    p->prePlace = p->currentLocation;
    p->currentLocation = newPlace;

    if (newPlace->subListPeople !=NULL){
        People*temp = newPlace->subListPeople;
        while(temp != NULL){
            addFriends(p,temp);
            temp = temp->next;
        }
    }
    addPeopleToPlace(p,newPlace);
    cout<<"\n"+p->currentLocation->namePlace<<endl;

}


void advacentRoute(People* people,Place* pList){

    Place* tempP = people->currentLocation;
    Edge* tempE = tempP->subListEdge;

    while(tempP != NULL) {
        if (tempP->subListEdge->distance <= tempP->subListEdge->nextEdge->distance) {
            people->prePlace = people->currentLocation;
            Place *newPlace = searchPlace(tempP->subListEdge->destination, pList);
            people->currentLocation = newPlace;
        }
        else{
            people->prePlace = people->currentLocation;
            deletePeopleToPlace(people,people->currentLocation);
            people->totalTravel += tempE->distance;
            Place *newPlace = searchPlace(tempE->nextEdge->destination, pList);
            people->currentLocation = newPlace;
        }
        tempE=tempE->nextEdge;

    }
    Place *newPlace = searchPlace(tempE->destination, pList);
    if (newPlace->subListPeople !=NULL){
        People*temp = newPlace->subListPeople;
        while(temp != NULL){
            addFriends(people,temp);
            temp = temp->next;
        }
    }
    addPeopleToPlace(people,newPlace);

}


bool searchPath( struct Place * origin, string destination,Place* pList){

    if((origin == NULL) or (origin->visited == true))
        return existPath;

    if(origin->namePlace == destination){
        existPath= true;
        return existPath;
    }
    origin->visited =true;

    struct Edge * tempE = origin->subListEdge;
    while(tempE!= NULL){

        searchPath(searchPlace(tempE->destination,pList), destination,pList);
        tempE = tempE->nextEdge;
    }
}

/**
 * La función anterior es una función recursiva que encuentra el camino más corto entre dos lugares.
 *
 * Args:
 *   origen: El origen de la ruta.
 *   destino (string): El destino de la ruta.
 *   ruta (string): es el camino que se va construyendo
 *   dis (int): distancia
 *   pList (Place): es la lista de lugares
 *
 * Returns:
 *   un valor booleano que indica si hay una ruta entre el origen y el destino.
 */

string rutaMenor = "";
int distanciaMenor = 0;

bool short_route(struct Place*origin, string destino, string ruta, int dis, Place*pList,People*people){

    if((origin == NULL) or (origin->visited == true))
        return existPath;

    if(origin->namePlace == destino){
        if((distanciaMenor==0) || (dis < distanciaMenor)){
            distanciaMenor =dis;
            rutaMenor = ruta+destino;
        }
        existPath = true;
        return existPath;
    }
    origin->visited =true;

    struct Edge *tempA =origin->subListEdge;
    while(tempA != NULL){
        short_route(searchPlace(tempA->destination,pList), destino, ruta + origin->namePlace, dis + tempA->distance, pList,people);
        tempA = tempA->nextEdge;
    }
    origin->visited =false;
}

int main() {

    //printPeopleList();
    graph1Load();
    graph2Load();
    printPlace(graph1);
    People*p = new People("Leiner",1, searchPlace("CQ",graph1),searchPlace("CQ",graph1),"Florencia");
    addPeopleToPlace(p,searchPlace("CQ",graph1));

  /*  cout<<"\n******************** PRUEBA DE RECORRIDO ADYACENTE ********************\n";
    advacentRoute(p,graph1);*/











    //random_walk(p,graph1);
    //random_walk(p,graph1);
    if(searchEdge(searchPlace("SantaClara",graph1),"CQ",graph1)){
        cout<<"si";
    }

    cout<<"\n\n---------------Averigurar si hay ruta de CQ a Fortuna:\n";

    searchPath(searchPlace("CQ",graph1), "SantaClara",graph1);
    if(existPath == true)
        cout<<"\n Si existe ruta";
    else
        cout<<"\nNo existe ruta";

    existPath= false;
    unselect();


    cout<<"\n\n.................Rutas Cortas...................\n";

    short_route(searchPlace("SantaClara",graph1), "CQ", "",0,graph1,p);
    if(existPath == true){
        cout<<"\n\nLa ruta mas corta es: "<<rutaMenor
            << "con una distancia de: "<<distanciaMenor;
    }
    else cout<<"\n\nNo existe ruta.................";

    rutaMenor = "";
    distanciaMenor= 0;
    existPath= false;
    unselect();


    return 0;
}


