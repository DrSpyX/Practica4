#include "red.h"

red::red(string _nombre){
    nombre = _nombre;
}

red::~red(){
}

int red::getIndice(string nombreEnrutador){     //devuelve el indice del enrutador con el nombre del argumento, si no hay ningun enrutador con ese nombre devuelve -1
    int cantEnrutadores = enrutadores.size();
    int indice = -1;
    for(int i=0;i<=cantEnrutadores-1;i++){
        if(enrutadores[i].getNombre()==nombreEnrutador){
            indice = i;
            break;
        }
    }
    return indice;
}

int red::agregarEnrutador(string nombreEnrutador){       //agrega un enrutador a la red y agrega los costos de conexion a los enrutadores
    if(getIndice(nombreEnrutador) == -1) {
        enrutador newEnrutador(nombreEnrutador);
        enrutadores.push_back(newEnrutador);    //agrega el enrutador a el vector de enrutadores
        return 0;
    }
    else{
        return 1;
    }
}

int red::agregarRutaDirecta(string enrutador1,string enrutador2,int costo){     //agrega el coste de una ruta directa a la tabla de enrutamiento
    int indice1 = 0;
    int indice2 = 0;

    indice1 = getIndice(enrutador1);
    indice2 = getIndice(enrutador2);

    if(indice1 != -1){
        if(indice2 != -1){
            enrutadores[indice1].agregarEnlace(enrutador2,costo);
            enrutadores[indice2].agregarEnlace(enrutador1,costo);
            return 0;
        }
        else{
            return 2;
        }
    }
    else{
        return 1;
    }
}

void red::agregarRutaNoDirecta(string nombreEnrutador){         //asigna -1 al coste entre dos enrutadores para indicar que no están conectados directamente
    int cantEnrutadores = enrutadores.size();
    int indice = 0;

    indice = getIndice(nombreEnrutador);

    for(int i=0;i<=cantEnrutadores-1;i++){
        if(enrutadores[i].buscarEnlace(nombreEnrutador)==false){
            enrutadores[i].agregarEnlace(nombreEnrutador,-1);
            enrutadores[indice].agregarEnlace(enrutadores[i].getNombre(),-1);
        }
    }
}

int red::eliminarEnrutador(string nombreEnrutador){       //elimina un enrutador y sus rutas de las tablas de todos los enrutadores
    int cantEnrutadores = enrutadores.size();
    int indice = 0;

    indice = getIndice(nombreEnrutador);

    if(indice != -1){
        for(int i=0;i<=cantEnrutadores-1;i++){          //elimina las rutas del enrutador de la tabla de enrutamiento
            enrutadores[i].eliminarEnlace(nombreEnrutador);
        }
        return 0;
    }
    else{
        return 1;
    }

}

int red::getCantEnrutadores(){
    int cantEnrutadores = enrutadores.size();
    return cantEnrutadores;
}

void red::calcularRutas(){
    map<string,pair<string,int>> tabla;
    int cantEnrutadores = enrutadores.size();
    int costoTemp = 0;
    int costo = 0;
    int costoMenor = 999999;
    int costoRuta = 0;
    string enrTemp;
    string enrActual;
    string ruta;

    //if(cantEnrutadores == 2){
        /*enrActual = enrutadores[0].getNombre();
        costo = enrutadores[0].getCosto(enrActual);
        ruta = enrActual;
        tabla.insert(make_pair(enrActual,make_pair(ruta,costo)));

        enrActual = enrutadores[1].getNombre();
        costo = enrutadores[0].getCosto(enrActual);
        ruta += ">";
        ruta += enrActual;
        tabla.insert(make_pair(enrActual,make_pair(ruta,costo)));

        enrutadores[0].agregarTabla(tabla);

        enrActual = enrutadores[0].getNombre();
        costo = enrutadores[1].getCosto(enrActual);
        ruta = enrActual;
        tabla.insert(make_pair(enrActual,make_pair(ruta,costo)));

        enrActual = enrutadores[1].getNombre();
        costo = enrutadores[1].getCosto(enrActual);
        ruta += ">";
        ruta += enrActual;
        tabla.insert(make_pair(enrActual,make_pair(enrActual,costo)));
        enrutadores[1].agregarTabla(tabla);*/
    //}
    for(int i=0;i<=cantEnrutadores;i++){    //recorre todas las tablas de enrutadores
        for(int j=0;j<=cantEnrutadores;j++){    //recorre todos los enrutadores dentro de la tabla
            enrActual = enrutadores[j].getNombre();
            costo = enrutadores[i].getCosto(enrActual); //costo del enrutador j en el enrutador i
            if(costo==0){
                tabla.insert(make_pair(enrActual,make_pair(enrActual,costo)));
            }
            else{
                if(costo!=-1){
                    costoMenor = costo;
                }
                ruta += enrActual;
                bool rutaCompleta = false;
                int it = 0;
                while(rutaCompleta == false){
                    for(int k=0;k<=cantEnrutadores;k++){    //recorre todas las tablas de enrutadores
                        enrTemp = enrutadores[k].getNombre();
                        costoTemp = enrutadores[it].getCosto(enrTemp);
                        if(enrutadores[it].getCosto(enrActual) != -1){
                            ruta += ">";
                            ruta += enrActual;
                            costoRuta += enrutadores[it].getCosto(enrActual);
                            tabla.insert(make_pair(enrActual,make_pair(ruta,costoRuta)));
                            rutaCompleta = true;
                            break;
                        }
                        else if(costoTemp < costoMenor && costoTemp != -1 && costoTemp != 0){
                            ruta += ">";
                            ruta += enrTemp;
                            costoRuta += costoTemp;
                        }
                    }
                    if(costoRuta == 0){
                        tabla.insert(make_pair(enrActual,make_pair(enrActual,costo)));
                        rutaCompleta = true;
                    }
                    else{
                        it = getIndice(enrTemp);
                    }
                }
            }
        }
        enrutadores[i].agregarTabla(tabla);
    }
}

string red::mostrarRuta(string enrutador1,string enrutador2){
    int indice = 0;
    pair<string,int> ruta;

    indice = getIndice(enrutador1);
    ruta = enrutadores[indice].getRuta(enrutador2);

    return ruta.first;
}

int red::mostrarCosto(string enrutador1,string enrutador2){
    int indice = 0;
    pair<string,int> ruta;

    indice = getIndice(enrutador1);
    ruta = enrutadores[indice].getRuta(enrutador2);

    return ruta.second;
}
