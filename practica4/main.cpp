#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <enrutador.h>
#include <red.h>

using namespace std;

int select(int no){                     //pide un numero al usuario para navegar a travez de menus (numero de opciones)
    int selUser = 0;
    while(selUser < 1 || selUser > no){
        cin>>selUser;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return selUser;
}

int main()
{
    red mired("internet");
    int eleccion = 0;        //eleccion del usuario en el menú
    int c = 0;  //codigo retornado por las funciones

    while(true){
        int cantEnrutadores = mired.getCantEnrutadores();

        cout<<"1. Agregar un enrutador"<<endl<<"2. Eliminar un enrutador"<<endl<<"3. Costo de envio entre dos enrutadores"<<endl<<"4. Camino mas eficiente entre dos enrutadores"<<endl<<"5. Salir"<<endl;
        eleccion = select(5);

        if(eleccion==1){
            string nEnrutador;  //nombre enrutador

            cout<<"Ingrese el nombre del enrutador"<<endl;
            getline(cin,nEnrutador);

            c = mired.agregarEnrutador(nEnrutador);

            if(cantEnrutadores!=0 && c == 0){
                int enlaces = 0;
                string eEnrutador; //enrutador a enlazar
                int costo = 0;

                cout<<"A cuantos enrutadores desea enlazar el nuevo enrutador?"<<endl;
                enlaces = select(cantEnrutadores);

                for(int i=1;i<=enlaces;i++){
                    while(true){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"Nombre del enrutador "<<i<<" a enlazar "<<endl;
                        getline(cin,eEnrutador);

                        cout<<"Costo de enlace"<<endl;
                        cin>>costo;

                        c = mired.agregarRutaDirecta(eEnrutador,nEnrutador,costo);
                        if(c==0){
                            cout<<"Enlace agregado"<<endl;
                            break;
                        }
                        else if(c==1){
                            cout<<"El enrutador no existe"<<endl;
                        }
                    }
                }
                mired.agregarRutaNoDirecta(nEnrutador);
                cout<<"Enrutador agregado"<<endl;
                mired.calcularRutas();
            }
            else if(c==1){
                cout<<"El enrutador ya esta registrado"<<endl;
            }
        }
        else if(eleccion==2){
            string nEnrutador;  //nombre enrutador

            cout<<"Ingrese el nombre del enrutador"<<endl;
            getline(cin,nEnrutador);

            c = mired.eliminarEnrutador(nEnrutador);
            if(c==0){
                cout<<"Enrutador eliminado"<<endl;
                break;
            }
            else if(c==1){
                cout<<"El enrutador no existe"<<endl;
            }

        }
        else if(eleccion==3){
            string nEnrutador1;
            string nEnrutador2;

            cout<<"Ingrese el nombre del primer enrutador"<<endl;
            getline(cin,nEnrutador1);

            cout<<"Ingrese el nombre del segundo enrutador"<<endl;
            getline(cin,nEnrutador2);

            cout<<"El costo de conexion entre los enrutadores "<<nEnrutador1<<" y "<<nEnrutador2<<" es de "<<mired.mostrarCosto(nEnrutador1,nEnrutador2)<<endl;
        }
        else if(eleccion==4){
            string nEnrutador1;
            string nEnrutador2;

            cout<<"Ingrese el nombre del primer enrutador"<<endl;
            getline(cin,nEnrutador1);

            cout<<"Ingrese el nombre del segundo enrutador"<<endl;
            getline(cin,nEnrutador2);

            cout<<"La ruta mas eficiente entre los enrutadores "<<nEnrutador1<<" y "<<nEnrutador2<<" es "<<mired.mostrarRuta(nEnrutador1,nEnrutador2)<<endl;
        }
        else if(eleccion==5){
            break;
        }
    }
    return 0;
}
