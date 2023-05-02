#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <map>
#include <string>

using namespace std;

class enrutador
{
private:
    string nombre;
    map<string,int> tablaEnlaces;  //nombre de los enrutadores, costo de conexion del enlace directo
    map<string,pair<string,int>> tablaEnrutamiento;  //nombre de los enrutadores, costo de conexion
public:
    enrutador(string);
    ~enrutador();
    void agregarEnlace(string enlace,int costo);
    void eliminarEnlace(string enlace);
    bool buscarEnlace(string enlace);
    int getCosto(string enlace);
    void agregarTabla(map<string,pair<string,int>>& tabla);
    void eliminarTablas();
    pair<string,int> getRuta(string enr);
    string getNombre();
};

#endif // ENRUTADOR_H
