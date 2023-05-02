#include "enrutador.h"

enrutador::enrutador(string _nombre){
    nombre = _nombre;
    tablaEnlaces[nombre] = 0;
}

enrutador::~enrutador(){
}

void enrutador::agregarEnlace(string ruta,int costo){     //agrega una nueva ruta a la tabla
    tablaEnlaces.insert(make_pair(ruta, costo));
}

void enrutador::eliminarEnlace(string enlace){      //elimina una ruta de la tabla
    tablaEnlaces.erase(enlace);
}

bool enrutador::buscarEnlace(string enlace){
    if(tablaEnlaces.count(enlace)==1){
        return true;
    }
    else{
        return false;
    }
}

int enrutador::getCosto(string enlace){
    int costo = 0;
    costo = tablaEnlaces[enlace];
    return costo;
}

void enrutador::agregarTabla(map<string,pair<string,int>>& tabla){
    tablaEnrutamiento = tabla;
}
void enrutador::eliminarTablas(){
    tablaEnrutamiento.clear();
}
pair<string,int> enrutador::getRuta(string enr){
    pair<string,int> ruta = tablaEnrutamiento[enr];
    return ruta;
}

string enrutador::getNombre(){      //devuelve el nombre del enrutador
    return nombre;
}
