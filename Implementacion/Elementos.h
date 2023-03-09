#ifndef _ELEMENTOS_H_
#define _ELEMENTOS_H_
#include <string>
using namespace std;
class Elementos{
private:
  char tipoElemento;
  unsigned long tamanno;
  string UnidadMedida;
  float coordX,coordY;
public:
  
  Elementos();
  Elementos(char tipo, unsigned long tam, float x, float y);
  char getTipoElemento() const;
  void setTipoElemento(char tipo);
  unsigned long getTamanno() const;
  void setTamanno(unsigned long tam);
  float getCoordX() const;
  void setCoordX(float x);
  float getCoordY() const;
  void setCoordY(float y);
  string getUnidadMedida();
  void setUnidadMedida(string unidad);
  ~Elementos();
};
#include "Elementos.hxx"


#endif