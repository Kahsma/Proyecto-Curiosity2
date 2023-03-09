#ifndef _COMANDOS_H_
#define _COMANDOS_H_

#include <string>
#include <iostream>
#include <vector>
//Nombres : Alberto Vigna , Alejandro Salamanca ,Andres Salamanca , Camilo Martinez

class Comandos
{
  protected:
  char tipo_comando;
  std::string nombre_del_comando;
  std::vector<std::string> parametros;

  public:

  //constructor
  Comandos();
  Comandos(char comando_comando , std::string nombre_comando);

  // Memory Wipe
  ~Comandos();

  // Funciones del TAD Comandos (en el mismo orden que en el documento)
  char get_tipo();
  void set_tipo(char tipo_comando);

  std::string get_nombre_del_comando();
  void set_nombre_del_comando(std::string nombre_del_comando);

  std::vector<std::string> get_parametros();
  void set_parametros(std::vector<std::string> parametros);
};
#include"Comandos.hxx"

#endif