#include <iostream>
#include <string>
using namespace std;


//Estructura Arco
struct Edge{
    int distance;
    string destination;
    Edge* nextEdge;
    Edge(int dis,string des){
        distance = dis;
        destination = des;
    }
};

//Estructura Lugar
struct Place{
    string namePlace;
    Edge*subListEdge;
    bool visited;
    Place(string place){
        namePlace = place;
        subListEdge = NULL;
        visited = false;
    }

}*placeList;

//Estructura Persona
struct People{
    string name;
    int id;
    Place*currentLocation;
    People*friendsList;
    Place*placeDestination;
    People(string n,int i,Place*current,Place*des){
        name= n;
        id = i;
        currentLocation = current;
        placeDestination = des;
        friendsList = NULL;
    }

}*peopleList;
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
Place*addEdge(string origin,int dis,string des){

    Place* vOrigin = vOrigin->searchPlace(origin);
    Place* vDestination = vOrigin->searchPlace(des);
    if(vOrigin == NULL){
        cout<<"NO SE HA ENCONTRO EL ORIGEN";
        return NULL;
    }
    if(vDestination == NULL ) {
        cout<<"NO SE HA ENCONTRO EL DESTINO";
        return NULL;
    }
    Edge* newEdge = new Edge(dis,des);
    newEdge->nextEdge = vOrigin->subListEdge;
    vOrigin->subListEdge = newEdge;
    return vOrigin;
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

bool searchEdge(Place * graph, string des) {

    if((graph == NULL) or (graph->visited == true))
        return existPath;

    if(graph->getNamePlace() == des) {
        existPath= true;
        return existPath;
    }
    graph->visited =true;
    Edge * tempE = graph->sublistEdge;
    while(tempE != NULL){
        searchPlace(searchPlace(tempE->destination), des);
        tempE = tempE->nextEdge;
    }
}




bool printEdge(Place* graph,string des, string path){
    if((graph == NULL) or graph->visited)
        return existPath;

    if(graph->getNamePlace() == des){
        cout<<"\n\nRuta................  "<<path<<des;
        existPath= true;
        return existPath;
    }
    graph->visited =true;

    Edge * tempE = graph->sublistEdge;

    while(tempE != NULL){
        printEdge(searchPlace(tempE->destination), des,path+graph->getNamePlace());
        tempE = tempE->nextEdge;
    }
    graph->visited =false;
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
People*addPeople(string name,int id,Place*current,Place*des,People*plist){
    People*newPeople = new People(name,id,current,des);
    newPeople->next = plist;
    plist = newPeople;
    return plist;

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
    if(pList == NULL){
        return NULL;
    }
    People*peopleTemp = pList;
    while(peopleTemp != NULL){
        if(peopleTemp->getId() == id){
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
People*modPeople(int oldId,string newName,int newId,Place*current,Place*des,People*pList){
    People*people = people->searchPeople(oldId,pList);
    if(people == NULL){
        cout<<"\nLA PERSONA NO SE ENCUENTRA REGISTRADA "<<endl;
    }
    else{
        people->setName(newName);
        people->setId(newId);
        people->setCurrentLocation(current);
        people->setPlaceDestination(des);
        return pList;

    }
}



int main() {

    return 0;
}
