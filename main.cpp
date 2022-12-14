#include <iostream>
#include <string>
#include<time.h>
#include<stdlib.h>
#include <sstream>

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
    bool state;
    struct Edge* nextEdge; //para enlazar todos los vertices en una lista
    Edge(int dis,string des){
        distance = dis;
        destination = des;
        nextEdge = NULL;
        state= false;

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
    string origin;
    struct Place*currentLocation;
    struct People*friendsList;
    string placeDestination;
    struct People*next = NULL;
    bool finish;
    int steps;
    int totalSteps;
    struct Place*shortRoute;
    Edge*localDestination;
    People(string n,int i,string orig,string  des,short type){
        origin = orig;
        name= n;
        id = i;
        prePlace = NULL;
        currentLocation = NULL;
        placeDestination = des;
        friendsList = NULL;
        next = NULL;
        typeAdvance = 0;
        totalTravel = 0;
        finish = false;
        typeAdvance = type;
        steps = 0;
        totalSteps = 0;
        localDestination =NULL;
        shortRoute = NULL;
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
void addPeople(string name,int id,string orig,string des,short typeAdvange,Place*graph){
    Place*origin=searchPlace(orig,graph);
    Place*dest = searchPlace(des,graph);
    if( (origin == NULL) || (dest ==NULL)) {
        cout<<"\n"<<"EL LUGAR DE ORIGEN O DESTINO NO EXISTEN"<<endl;
        return;
    }

    People*newPeople = new People(name,id,orig,des,typeAdvange);

    newPeople->currentLocation = searchPlace(newPeople->origin,graph);
    addPeopleToPlace(newPeople,origin);
    newPeople->next = peopleList;
    peopleList = newPeople;
    cout<<"La persona se agrego con exito"<<endl;

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
People*searchPeople(int id,People*pList){
    if(peopleList == NULL){
        return NULL;
    }
    People*peopleTemp = pList;
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

void modPeople(int oldId,string newName,int newId,Place*current,string des,People*pList){
    People*people = searchPeople(oldId,pList);
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
    People*people = searchPeople(oldId,pList);
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
    int num = 0;
    num = 1+(rand() % random);
    cout<<num<<endl;
    return num;

}
/**
 * Crea un grafo con 5 vertices y 10 arcos.
 */
void graph1Load(){
    int num = 0;
    int r = 15;
    graph1 = addPlace("SantaClara",graph1);//A
    graph1 = addPlace("CQ",graph1);//B
    graph1 = addPlace("Florencia",graph1);//C
    graph1 = addPlace("Muelle",graph1);//D
    graph1 = addPlace("Platanar",graph1);//E
    num = randomNum(r);
    addEdge("CQ",num,"SantaClara",graph1);
    addEdge("SantaClara",num,"CQ",graph1);
    num = randomNum(r);
    addEdge("CQ",num ,"Florencia",graph1);
    addEdge("Florencia",num,"CQ",graph1);
    num = randomNum(r);
    addEdge("Florencia",num,"Muelle",graph1);
    addEdge("Muelle",num,"Florencia",graph1);
    num = randomNum(r);
    addEdge("Muelle",num,"Platanar",graph1);
    addEdge("Platanar",num,"Muelle",graph1);
    num = randomNum(r);
    addEdge("Platanar",num,"SantaClara",graph1);
    addEdge("SantaClara",num,"Platanar",graph1);

}
/**
 * Crea un gráfico con 7 vertice y 26 arcos.
 */
void graph2Load(){
    int r = 3;
    graph2 = addPlace("SantaClara",graph2);//A
    graph2 = addPlace("CQ",graph2);//B
    graph2 = addPlace("Florencia",graph2);//C
    graph2 = addPlace("Muelle",graph2);//D
    graph2 = addPlace("Platanar",graph2);//E
    graph2 = addPlace("Tanque",graph2);//F
    graph2 = addPlace("Fortuna",graph2);//G
    int num = 0;
    num = randomNum(r);
    addEdge("SantaClara", num,"CQ",graph2);
    addEdge("CQ",num,"SantaClara",graph2);
    num = randomNum(r);
    addEdge("SantaClara",num,"Florencia",graph2);
    addEdge("Florencia",num,"SantaClara",graph2);
    num = randomNum(r);
    addEdge("SantaClara",num,"Muelle",graph2);
    addEdge("Muelle",num,"SantaClara",graph2);
    num = randomNum(r);
    addEdge("SantaClara",num,"Platanar",graph2);
    addEdge("Platanar",num,"SantaClara",graph2);
    num = randomNum(r);
    addEdge("SantaClara",num,"Tanque",graph2);
    addEdge("Tanque",num,"SantaClara",graph2);
    num = randomNum(r);
    addEdge("SantaClara",num,"Fortuna",graph2);
    addEdge("Fortuna",num,"SantaClara",graph2);

    addEdge("CQ",randomNum(r),"Florencia",graph2);
    addEdge("CQ",randomNum(r),"Fortuna",graph2);

    num = randomNum(r);
    addEdge("Florencia",num,"Muelle",graph2);
    addEdge("Muelle",num,"Florencia",graph2);

    num = randomNum(r);
    addEdge("Florencia",num,"Tanque",graph2);
    addEdge("Tanque",num,"Florencia",graph2);

    num = randomNum(r);
    addEdge("Muelle",num,"Platanar",graph2);
    addEdge("Platanar",num,"Muelle",graph2);

    num = randomNum(r);
    addEdge("Platanar",num,"Tanque",graph2);
    addEdge("Tanque",num,"Platanar",graph2);

    num = randomNum(r);
    addEdge("Tanque",num,"Fortuna",graph2);
    addEdge("Fortuna",num,"Tanque",graph2);

    num = randomNum(r);
    addEdge("Fortuna",num,"CQ",graph2);
    addEdge("Florencia",num,"CQ",graph2);
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


void finishWalk(People*p){
    if (p->currentLocation != NULL){
        if (p->currentLocation->namePlace == p->placeDestination){
            p->finish = true;
        }
    }
}
void random_walk(People*p,Place*pList){
    string name = p->name;
    string d = p->placeDestination;
    if (p->localDestination !=NULL){
        if (p->localDestination->distance > p->steps){
            p->steps++;
            return;
        }
        else{
            Place*newPlace = searchPlace(p->localDestination->destination,pList);
            p->totalTravel += p->steps;
            p->steps = 0;
            p->currentLocation = newPlace;
            if (newPlace->subListPeople !=NULL){
                People*temp = newPlace->subListPeople;
                while(temp != NULL){

                    addFriends(p,temp);
                    temp = temp->next;
                }
            }
            addPeopleToPlace(p,newPlace);
            //cout<<"\n"+p->currentLocation->namePlace<<endl;
        }

    }
    finishWalk(p);
    if (p->finish){
        return;
    }
    //cout<<"\n"+p->currentLocation->namePlace<<endl;
    int n = 0;
    int num = 0;
    n = size(p->currentLocation->subListEdge);
    if (n > 1){
         num = randomNum(n);
    }
    Edge*tempList = p->currentLocation->subListEdge;
    Edge*edge = searchIndex(num-1,tempList);


    if (p->prePlace !=NULL){
        while(p->prePlace->namePlace == edge->destination){
            num = (randomNum(size(p->currentLocation->subListEdge))-1);
            edge = searchIndex(num,tempList);
        }

    }
    p->localDestination = edge;
    p->prePlace = p->currentLocation;
    deletePeopleToPlace(p,p->currentLocation);
    p->currentLocation = NULL;
    p->steps++;
}


void advacentRoute(People* people,Place* pList) {
    finishWalk(people);

    if (!people->finish) { //Si no ha llegado a su destino

        if(people->currentLocation !=NULL){
            people->prePlace = people->currentLocation;
        }

        Place* tempP = people->prePlace;

        if (tempP->subListEdge->distance <= tempP->subListEdge->nextEdge->distance){ //se busca el camino mas corto
            people->localDestination = tempP->subListEdge;
            people->localDestination->state= true;
            if (people->steps < people->localDestination->distance) {
                people->steps++;
                people->currentLocation = NULL;
            } else {
                people->currentLocation = searchPlace(people->localDestination->destination,pList); //searchPlace(tempP->subListEdge->destination, pList);
                people->totalTravel += people->steps;
                people->steps = 0;
                deletePeopleToPlace(people, people->prePlace);
                addPeopleToPlace(people, people->currentLocation);
            }
        }
        else {
            people->localDestination = tempP->subListEdge->nextEdge;
            if (people->steps < people->localDestination->distance) {
                people->steps++;
                people->currentLocation = NULL;
            } else {
                people->currentLocation = searchPlace(people->localDestination->destination,pList);
                people->totalTravel += people->steps;
                people->steps = 0;
                deletePeopleToPlace(people, people->prePlace);
                addPeopleToPlace(people, people->currentLocation);
            }
        }

    }
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

bool getShort_route(struct Place*origin, string destino, string ruta, int dis, Place*pList){

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
        getShort_route(searchPlace(tempA->destination, pList), destino, ruta + origin->namePlace + ",",dis + tempA->distance, pList);
        tempA = tempA->nextEdge;
    }
    origin->visited =false;
}
void changeShortRoute(People*people,Place*pList){
    Place*temp = NULL;
    string place;
    if (getShort_route(searchPlace(people->origin,pList),people->placeDestination,"",0,pList)){
        stringstream route(rutaMenor);
        while(getline(route, place, ',')){
            addPlace(place,temp);
        }
    }
    people->shortRoute;
}
void shortRoute(People*people,Place*pList){




}
void dataLoad() {
    graph1Load();
    graph2Load();
    addPeople("Karina",1,"CQ","SantaClara",1,graph1);
    //addPeople("Leiner",2,"Muelle","SantaClara",2,graph1);
    //addPeople("Evelyn",3,"Florencia","Muelle",3,graph1);
    //addPeople("Enrique",4,"Platanar","CQ",4,graph1);
    //addPeople("Leidy",5,"SantaClara","Florencia",1,graph1);
    //addPeople("Tania",6,"CQ","SantaClara",2,graph1);
    //addPeople("Maria",7,"Muelle","SantaClara",3,graph1);
    //addPeople("Johan",8,"Florencia","Muelle",4,graph1);
    //addPeople("Anthony",9,"Platanar","CQ",4,graph1);
    //addPeople("Jose",10,"SantaClara","Florencia",1,graph1);

    //addPeople("Melanie",11,"CQ","SantaClara",2,graph2);
    //addPeople("Vanessa",12,"Muelle","SantaClara",3,graph2);
   // addPeople("Melissa",13,"Florencia","Muelle",4,graph2);
    //addPeople("Janka",14,"Platanar","CQ",1,graph2);
    //addPeople("Carlos",15,"SantaClara","Florencia",2,graph2);
   // addPeople("Wilber",16,"Fortuna","SantaClara",3,graph2);
    //addPeople("Manfred",17,"Tanque","SantaClara",4,graph2);
    //addPeople("Brandon",18,"Florencia","Tanque",1,graph2);
    //addPeople("Kevin",19,"Platanar","Fortuna",2,graph2);
   // addPeople("Luis",20,"Fortuna","Tanque",3,graph2);

}
/**
 * Devuelve verdadero si hay personas que no han terminado de caminar, y falso si no hay personas que no hayan terminado de
 * caminar.
 *
 * Returns:
 *   Un valor booleano.
 */
bool scanPeopleToWalk(){
    People*temp = peopleList;
    while(temp!=NULL){
        if (!temp->finish){
            return true;
        }
        temp = temp->next;
    }
    return false;
}
/**
 * Devuelve una cadena que representa el tipo de avance que ha elegido el usuario
 *
 * Args:
 *   i (int): El número de avance.
 *
 * Returns:
 *   La cadena del avance
 */
string typeAdvange(int i){
    string ad = "";
    if (i == 1){
        ad = "ALEATORIO";
    }
    else if (i == 2){
        ad = "ADYACENTE MAS CERCANO";
    }
    else if (i == 3){
        ad = "RUTA CORTA DESDE PUNTO DE PARTIDA";
    }
    else if (i == 4){
        ad = "RUTA CORTA DESDE LUGAR ESPEFICIO";
    }
    return ad;
}
/**Consulta 1
 * Imprime el estado de una persona
 *
 * Args:
 *   p (People): puntero a la persona
 */
void printStatusPeople(People*p){

    if (p->currentLocation!= NULL){
        cout<<"PERSONA: "<<p->name<<endl;
        cout<<"METODO DE AVANCE: "<<typeAdvange(p->typeAdvance)<<endl;
        cout<<"LUGAR ACTUAL: "<<p->currentLocation->namePlace;
        if (p->currentLocation->subListPeople != NULL){
            People*temp = p->currentLocation->subListPeople;
            cout<<"PERSONA EN "<<temp->name<<":"<<endl;
            while (temp != NULL){
                cout<<temp->name;
            }
        }
        else{
            cout<<"NO HAY PERSONAS EN EL LUGAR ACTUALMENTE"<<endl;
        }
    }
}
/**
 * Devuelve el número de amigos de una persona.
 *
 * Args:
 *   p (People): puntero a la persona cuya lista de amigos desea saber el tamaño de
 *
 * Returns:
 *   El número de amigos de una persona.
 */
int sizeFriendsList(People*p){
    People*friends = p->friendsList;
    int cont = 0;
    while(friends!=NULL){
        cont++;
        friends = friends->next;
    }
    return cont;
}
/**Consulta 2
 * Revisa la lista de personas y compara el tamaño de la lista de amigos de cada persona, y luego imprime el nombre de la
 * persona con la lista de amigos más grande
 */
void PeopleMoreFriends(){
    People*temp = peopleList;
    People*p = NULL;
    while(temp!= NULL){
        if (p == NULL){
            p = temp;
        }
        else{
            if (sizeFriendsList(temp) > sizeFriendsList(p)){
                p = temp;
            }
        }
        temp = temp->next;
    }
    cout<<"LA PERSONA CON MAS AMIGOS ES "<<p->name<<" con "<<sizeFriendsList(p)<< "amigos"<<endl;
}
/**Consulta 3
 * Recorre la lista de personas y encuentra la que terminó primero.
 */
void peopleFinishFirst(){
    People*temp = peopleList;
    People*p = NULL;
    while(temp!= NULL){
        if (!temp->finish){
            continue;
        }
        else if (p == NULL){
            p = temp;
        }
        else{
            if (temp->totalTravel < p->totalTravel){
                p = temp;
            }
        }
        temp = temp->next;
    }
    cout<<"LA PERSONA QUE TERMINO PRIMERO LA CAMINATA FUE "<<p->name<<endl;
}

/**Consulta 4
 * Revisa la lista de personas y encuentra la que terminó en último lugar.
 */
void lastPeopleFinish(){
    People*temp = peopleList;
    People*p = NULL;
    while(temp!= NULL){
        if (!temp->finish){
            continue;
        }
        else if (p == NULL){
            p = temp;
        }
        else{
            if (temp->totalTravel > p->totalTravel){
                p = temp;
            }
        }
        temp = temp->next;
    }
    cout<<"LA PERSONA QUE TERMINO DE ULTIMO LA CAMINATA FUE "<<p->name<<endl;
}
void walks(Place*graph){
    People*temp = peopleList;

    while (temp != NULL)
    {
        string des = temp->placeDestination;
        if (temp->finish){
            continue;
        }
        else if (temp->typeAdvance == 1){
            random_walk(temp,graph);
        }
        else if (temp->typeAdvance == 2){
            advacentRoute(temp,graph);
        }
        else if (temp->typeAdvance == 3){
            //Falta
        }
        else if (temp->typeAdvance == 4){
            getShort_route(searchPlace(temp->origin, graph), temp->placeDestination, "", 0, graph);
        }
        cout<<temp->name<<"->"<<temp->totalTravel<<endl;
        finishWalk(temp);

        if (temp->next == NULL){
            if (scanPeopleToWalk()){
                temp = peopleList;
            }
            else{
                break;
            }
        }else{
            temp = temp->next;
        }

    }

}


//Bienvenida al sistema
void welcome(){
    system("cls");
    cout << "\n\n\n";
    cout << "\t\t\t * * *   *   *****  **    *   * * *   *****  **    *  *  *****    *****  "<< endl;
    cout << "\t\t\t *   *      *       * *   *   *   *  *       * *   *     *    *  *     * "<< endl;
    cout << "\t\t\t * * *   *  ****    *  *  *   * * *  ****    *  *  *  *  *    *  *     * "<< endl;
    cout << "\t\t\t *   *   *  *       *   * *   *   *  *       *   * *  *  *    *  *     * "<< endl;
    cout << "\t\t\t * * *   *   *****  *    **   * * *   *****  *    **  *  *****    *****  "<< endl;
    cout<<endl;
    cout<<"\t\t\t=========================================================================="<<endl;
    cout<<"\t\t\t\t\t                  SISTEMA DE RECORRIDO DE GRAFOS                     "<<endl;
    cout<<"\t\t\t=========================================================================="<<endl;
    cout<<endl;
    cout<<"\t\t\t\t1. MENU PRINCIPAL\n\n";
    cout<<"\t\t\t\t2. SALIR\n\n";

}

void optionListSublis(){
    system("cls");
    cout<<"\t\t======================================================"<<endl;
    cout<<"\t\t\t        SELECCIONE UNA OPCIÓN  "<<endl;
    cout<<"\t\t======================================================"<<endl;
    cout<<endl;
    cout<<"\t\t1.LISTA DE PERSONAS\n\n";
    cout<<"\t\t2.LISTA DE VERTICE\n\n";
    cout<<"\t\t3.LISTA DE ARCOS\n\n";
    cout<<"\t\t4.AVANZAR EN EL GRAFO\n\n";
    cout<<"\t\t5.VER CONSULTAS\n\n";
    cout<<"\t\t6.VER REPORTES\n\n";
    cout<<"\t\t0.REGRESAR\n\n";
    cout<<"\t\t======================================================"<<endl;
}

int main() {
    dataLoad();
    srand(time(NULL));

    char c; //OPCION DEL MENU PREINCIPAL
    char p; //OPCION DE LAS LISTAS
    char b; //OPCION DE LISTAS EN REPORTES


    while(true){
        welcome();
        cout<<"\n\t\tELIGA UNA OPCION:";
        cin>>c;

        if(c=='1'){

        }
        else if(c=='1'){

        }
        else if(c=='1'){

        }
        else if(c=='1'){

        }
        else if(c=='1'){

        }
        else if(c=='0'){ //SALIR
            system("cls");
            cout << "\n\t\t               GRACIAS POR USAR ESTE SISTEMA"<<endl;
            cout <<endl;
            cout <<"\n\t\t         PROYECTO 2  ESTRUCTURAS DE GRAFOS \n";
            cout<<"\n\t\t\t =========================================\n";
            cout<<"\n\t\t\t MIEMBROS DEL GRUPO (DESARROLLADORES)";
            cout << "\n\n";
            cout << "\n\t\t\t NOMBRE                        CARNET\n\n";
            cout << "\n\t\t\t 1. lEINER ALVARADO           2022437759\n\n";
            cout << "\n\t\t\t 2. KARINA URBINA             2022038549\n\n";
            cout<<"\n\t\t\t =========================================\n";
            cout<<"\n\t\t\t START DATE: 8/11/2022\n";
            cout<<"\n\t\t\t END DATE: 20/11/2022 ";
            cout << "\n\n";
            break;

        }

    }




   //dataLoad();
    //walks(graph1);
    //printPeopleList();

    //printPlace(graph2);
    //People* p = new People("Leiner",1,"Muelle","SantaClara",1);
    addPeople("Leiner",5,"Muelle","SantaClara",2,graph1);
    People* p = searchPeople(5,peopleList);
    //addPeopleToPlace(p,graph1);
    getShort_route(searchPlace(p->origin, graph1), p->placeDestination, "", 0, graph1);

    cout<<"\n******************** PRUEBA DE RECORRIDO ADYACENTE ********************\n";
   // advacentRoute(p,graph1);
    while(p->currentLocation->namePlace!=p->placeDestination){
        advacentRoute(p,graph1);

        cout<<"Lugar actual: "<<p->currentLocation->namePlace<<endl;
    }

*/









    /*
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

    getShort_route(searchPlace("SantaClara",graph1), "CQ", "",0,graph1,p);
    if(existPath == true){
        cout<<"\n\nLa ruta mas corta es: "<<rutaMenor
            << "con una distancia de: "<<distanciaMenor;
    }
    else cout<<"\n\nNo existe ruta.................";

    rutaMenor = "";
    distanciaMenor= 0;
    existPath= false;
    unselect();

    */
    return 0;
}


