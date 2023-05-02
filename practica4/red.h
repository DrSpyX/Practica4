#ifndef RED_H
#define RED_H
#include <vector>
#include <map>
#include <string>
#include <enrutador.h>

using namespace std;

class red
{
private:
    string nombre;
    vector<enrutador> enrutadores;
    int getIndice(string nombreEnrutador);
public:
    red(string);
    ~red();
    int agregarEnrutador(string nombreEnrutador);
    int agregarRutaDirecta(string enrutador1,string enrutador2,int costo);
    void agregarRutaNoDirecta(string nombreEnrutador);
    int eliminarEnrutador(string nombreEnrutador);
    int getCantEnrutadores();
    void calcularRutas();
    string mostrarRuta(string enrutador1,string enrutador2);
    int mostrarCosto(string enrutador1,string enrutador2);
};

#endif // RED_H
