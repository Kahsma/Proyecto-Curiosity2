#include "Elementos.h"

Elementos::Elementos() {
  tipoElemento = ' ';
  tamanno = 0;
  coordX = 0.0;
  coordY = 0.0;
}

Elementos::Elementos(char tipo, unsigned long tam, float x, float y) {
  tipoElemento = tipo;
  tamanno = tam;
  coordX = x;
  coordY = y;
}

char Elementos::getTipoElemento() const {
  return tipoElemento;
}

void Elementos::setTipoElemento(char tipo) {
  tipoElemento = tipo;
}

unsigned long Elementos::getTamanno() const {
  return tamanno;
}

void Elementos::setTamanno(unsigned long tam) {
  tamanno = tam;
}

string Elementos::getUnidadMedida(){
  return UnidadMedida;
}
void Elementos::setUnidadMedida(string unidad){
  UnidadMedida=unidad;
}

float Elementos::getCoordX() const {
  return coordX;
}

void Elementos::setCoordX(float x) {
  coordX = x;
}

float Elementos::getCoordY() const {
  return coordY;
}

void Elementos::setCoordY(float y) {
  coordY = y;
}

Elementos::~Elementos() {
  
}

