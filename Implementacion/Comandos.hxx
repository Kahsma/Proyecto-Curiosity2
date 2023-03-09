#include "Comandos.h"

// constructor
Comandos::Comandos() {
    tipo_comando = '\0';
    nombre_del_comando = "";
}

Comandos::Comandos(char comando_comando, std::string nombre_comando) {
    tipo_comando = comando_comando;
    nombre_del_comando = nombre_comando;
}

// destructor
Comandos::~Comandos() {}

// Funciones del TAD Comandos (en el mismo orden que en el documento)
char Comandos::get_tipo() 
{
    return tipo_comando;
}

void Comandos::set_tipo(char tipo_comando) 
{
    this->tipo_comando = tipo_comando;
}

std::string Comandos::get_nombre_del_comando() 
{
    return nombre_del_comando;
}

void Comandos::set_nombre_del_comando(std::string nombre_del_comando) {
    this->nombre_del_comando = nombre_del_comando;
}

std::vector<std::string> Comandos::get_parametros() {
    return parametros;
}

void Comandos::set_parametros(std::vector<std::string> parametros) 
{
    this->parametros = parametros;
}
