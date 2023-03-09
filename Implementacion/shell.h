#ifndef _SHELL_H_
#define _SHELL_H_
#include <string>
#include <iostream>
#include <queue>
//Nombres : Alberto Vigna , Alejandro Salamanca ,Andres Salamanca , Camilo Martinez
using namespace std;

class shell {
private:
  string command;

public:
  //Constructor
  shell();
  shell(string commandd);
  
  //Memory Wipe
  ~shell();
  
  //Functions (destructor)
  void verificarComandos(char comm[]);
  void help();
  void iniciarShell();
  void cargarComandos(string nombreDocumento);
  void cargarElementos(string nombre);
  void agregarMovimiento(string tipo,string magnitud,string unidad);
  void agregarAnalisis(string tipo,string objteo, string comentario);
  void agregarElemento(string tipoComp , string tamanio,string unidadMedida,string cordx,string cordy);
  void guardar(queue <string> lInstrucciones, string tipoA, string nomArchivo);
  void simularComandos(int x,int y);
  void enCuadrante(int x1,int x2,int y1,int y2);
  void salir();
  void ubicarElementos();
  void crearMapa();
  void rutaMasLarga();
  void limpiar();
};

#include "shell.hxx"




#endif