// Nombres : Alberto Vigna , Alejandro Salamanca ,Andres Salamanca , Camilo Martinez
#include <cmath>
#include <iostream>
#include <map>
#include <stdlib.h>
#include "shell.h"
#include "Curiosity.h"
#include "Comandos.h"
#include "Elementos.h"
#include <vector>
// #include <curses.h>
// #include "conio.h"
#include <unistd.h> // for sleep()
#include <cstring>
#include <regex>
#include <fstream> // archivos

using namespace std;

Curiosity curiosity;

shell::shell()
{
  command = "";
}
shell::shell(string commandd)
{
  command = commandd;
}

// - - - - - FUNCIONES IMPLEMENTADAS - - - - -
// Funcion Help-
void shell::help()
{
  cout << "Funcion de help" << endl;
  cout << "-================================================================================================-" << endl;
  cout << "-================================== Pediste ayuda? Tranquilo :) =================================-" << endl;
  cout << "-================================================================================================-" << endl;
  cout << "" << endl;
  cout << "'cargar_comandos' es usado Para la carga en memoria los comandos de desplazamiento contenidos en  " << endl;
  cout << "el archivo identificado por 'nombre_archivo1'." << endl;
  cout << "" << endl;
  cout << "'cargar_elementos' es usado para Carga en memoria los datos de puntos de interés o elementos      " << endl;
  cout << "contenidos en el archivo identificado por nombre_archivo." << endl;
  cout << "" << endl;
  cout << "'agregar_movimiento' es usado para agrega el comando de movimiento descrito a la lista de comandos" << endl;
  cout << "del robot “Curiosity”. El movimiento puede ser de dos tipos: avanzar o girar." << endl;
  cout << "" << endl;
  cout << "'agregar_analisis' es usado para agregar el comando de análisis descrito a la lista de comandos   " << endl;
  cout << "del robot “Curiosity”. El análisis puede ser de tres tipos: fotografiar, composicion o perforar.  " << endl;
  cout << "" << endl;
  cout << "'agregar_elemento' es usado para agregar el componente o elemento descrito a la lista de puntos de" << endl;
  cout << "interés del robot “Curiosity”. El tipo de componente puede ser uno entre roca, crater, monticulo  " << endl;
  cout << "o duna." << endl;
  cout << "" << endl;
  cout << "'guardar' es usado para guardar en el archivo." << endl;
  cout << "" << endl;
  cout << "'simular_comandos' es usado para Permite simular el resultado de los comandos de movimiento que se" << endl;
  cout << "enviarán al robot “Curiosity” desde la Tierra." << endl;
  cout << "'salir' termina de ejecutar la aplicacion (como obvio no? jajaj)" << endl;
  cout << "-================================================================================================-" << endl;
}

// función para saber que coamndo pasaron
void shell::verificarComandos(char comm[])
{
  string partido[6];
  char *ptr; // declare a ptr pointer
  ptr = strtok(comm, " ");
  int i = 0;
  partido[i] = ptr;
  while (ptr != NULL)
  {
    i++;
    ptr = strtok(NULL, " ");
    // if(!partido[6].empty()){
    //   //cout<<"demasiados argumentos"<<endl;
    //   break;
    // }
    if (ptr != NULL)
    {
      partido[i] = ptr;
    }
  }
  cout << "el comando fue : " << partido[0] << endl;
  if (partido[0].compare("help") == 0)
  {
    help();
  }
  else if (partido[0].compare("cargar_comandos") == 0)
  {

    cargarComandos(partido[1]);
  }
  else if (partido[0].compare("cargar_elementos") == 0)
  {
    cargarElementos(partido[1]);
  }
  else if (partido[0].compare("agregar_movimientos") == 0)
  {
    if (partido[1].empty() || partido[2].empty() || partido[3].empty())
    {
      cout << "ingrese todos los parametrod" << endl;
    }
    else
    {
      try
      {

        agregarMovimiento(partido[1], partido[2], partido[3]);
      }
      catch (exception &err)
      {
        cout << "Conversion failure" << endl;
      }
    }
  }
  else if (partido[0].compare("agregar_analisis") == 0)
  {
    if (partido[1].empty() || partido[2].empty())
    {
      cout << "Falta especificar un valor de tipo analisis o nombre objeto " << endl;
    }
    else
    {
      agregarAnalisis(partido[1], partido[2], partido[3]);
    }
  }
  else if (partido[0].compare("agregar_elementos") == 0)
  {
    if (partido[1].empty() || partido[2].empty() || partido[3].empty() || partido[4].empty() || partido[5].empty())
    {
      cout << "Ingrese todos los argumentos" << endl;
    }
    else
    {
      try
      {
        int tam = stoi(partido[2]);
        int cordx = stoi(partido[4]);
        int cordy = stoi(partido[5]);
        agregarElemento(partido[1], partido[2], partido[3], partido[4], partido[5]);
      }
      catch (exception &err)
      {
        cout << "Conversion failure" << endl;
      }
    }
  }
  else if (partido[0].compare("guardar") == 0)
  {

    bool parar = false, parar2 = false;

    queue<string> cola;

    int optionP;

    string elBuffer;

    string tipoA;

    cout << "Seleccione el tipo de archivo: Escriba (1) para Comandos o (2) para Elementos" << endl;

    while (!parar2)
    {
      cin >> optionP;
      switch (optionP)
      {
      case 1:

        tipoA = "Comandos";
        parar2 = true;

        break;

      case 2:

        tipoA = "Elementos";
        parar2 = true;
        break;

      default:
        cout << "Seleccione el tipo de archivo: Escriba (1) para Comandos o (2) para Elementos" << endl;

        break;
      }
    }

    regex regex("(.*?)\\.(txt|csv|CSV|doc|DOC|pdf|PDF)$");
    if (regex_match(partido[1], regex))
    {
      cout << "La información ha sido guardada en " << partido[1] << endl;
    }
    else
    {
      cout << "Error guardando en " << partido[1] << endl;
    }

    while (true)
    {

      getline(cin, elBuffer);
      if (elBuffer == "s")
      {
        break;
      }
      cola.push(elBuffer);
      cout << "Escriba el comando o elemento (o 's' para terminar): ";
    }

    cout << cola.front() << endl;
    cout << cola.back() << endl;

    guardar(cola, tipoA, partido[1]);
  }
  else if (partido[0].compare("simular_comandos") == 0)
  {
    if (partido[1].empty() || partido[2].empty())
    {
      cout << "La información requerida no está almacenada en memoria" << endl;
    }
    else
    {
      try
      {
        int cordx = stoi(partido[1]);
        int cordy = stoi(partido[2]);
        simularComandos(cordx, cordy);
      }
      catch (exception &err)
      {
        cout << "Conversion failure" << endl;
      }
    }
  }
  else if (partido[0].compare("en_cuadrante") == 0)
  {
    if (partido[4].empty())
    {
      cout << "Los elementos no han sido ubicados todavía" << endl;
    }
    else
    {
      try
      {
        int corx1 = stoi(partido[1]);
        int corx2 = stoi(partido[2]);
        int cory1 = stoi(partido[3]);
        int cory2 = stoi(partido[4]);
        enCuadrante(corx1, corx2, cory1, cory2);
      }
      catch (exception &err)
      {
        cout << "Conversion failure" << endl;
      }
    }
  }
  else if (partido[0].compare("salir") == 0)
  {
    salir();
  }
  else if (partido[0].compare("ubicar_elementos") == 0)
  {
    ubicarElementos();
  }
  else if (partido[0].compare("crear_mapa") == 0)
  {
    crearMapa();
  }
  else if (partido[0].compare("ruta_mas_larga") == 0)
  {
    rutaMasLarga();
  }
}

// Funcion de inicializacion.
void shell::iniciarShell()
{
  // Borrar consola
  // if (system ("CLS")==-1)
  //{
  //  cout<<"ERROR"<<endl;
  //}
  limpiar();
  cout << "Cargando, por favor espere..." << endl;
  cout << '-' << flush;
  for (int i = 0; i < 1; i++)
  {
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoading   " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLOading   " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoAding   " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoaDing   " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoadIng   " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoadiNg   " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoadinG   " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.  " << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.." << std::flush;
    sleep(1);
    std::cout << "\b\b\b\b\b\b\b\b\b\bLoading..." << std::flush;
    sleep(1);
  }

  // if (system ("CLS")==-1)
  //{
  //  cout<<"ERROR"<<endl;
  //}
  limpiar();
  cout << "-================================================================================================-" << endl;
  cout << "" << endl;
  cout << "      /$$$$$$  /$$   /$$ /$$$$$$$  /$$$$$$  /$$$$$$   /$$$$$$  /$$$$$$ /$$$$$$$$ /$$     /$$" << endl;
  cout << "     /$$__  $$| $$  | $$| $$__  $$|_  $$_/ /$$__  $$ /$$__  $$|_  $$_/|__  $$__/|  $$   /$$/" << endl;
  cout << "    | $$  \\__/| $$  | $$| $$  \\ $$  | $$  | $$  \\ $$| $$  \\__/  | $$     | $$    \\  $$ /$$/ " << endl;
  cout << "    | $$      | $$  | $$| $$$$$$$/  | $$  | $$  | $$|  $$$$$$   | $$     | $$     \\  $$$$/  " << endl;
  cout << "    | $$      | $$  | $$| $$__  $$  | $$  | $$  | $$ \\____  $$  | $$     | $$      \\  $$/   " << endl;
  cout << "    | $$    $$| $$  | $$| $$  \\ $$  | $$  | $$  | $$ /$$  \\ $$  | $$     | $$       | $$    " << endl;
  cout << "    |  $$$$$$/|  $$$$$$/| $$  | $$ /$$$$$$|  $$$$$$/|  $$$$$$/ /$$$$$$   | $$       | $$   " << endl;
  cout << "     \\______/  \\______/ |__/  |__/|______/ \\______/  \\______/ |______/   |__/       |__/   " << endl;
  cout << "" << endl;
  cout << "-================================================================================================-" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - " << endl;
  cout << "--- - -- - -- - -- - -- -- Bienvenido al sistema del robot CURIOSITY -- - -- - -- - -- - -- - ---" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - " << endl;
  cout << "- - - - - - - - - - - - - - - - Si necesitas ayuda utiliza 'help' - - - - - - - - - - - - - - - -" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - " << endl;
  cout << "=================================================================================================" << endl;

  string com;

  while (1)
  {
    char str[100];
    cout << "~$";
    cin.getline(str, 100);
    // cin.ignore();
    verificarComandos(str);
  }
}

// Funcion de cargar comandos.
void shell::cargarComandos(string nombre)
{
  cout << "Cargar comandos." << endl;

  string buffer;
  ifstream lectura;
  // string nombre = "instrucciones.txt";
  regex regex("(.*?)\\.(txt)$");
  if (regex_match(nombre, regex))
  {
    cout << "Archivo valido ." << endl;
  }
  else
  {
    cout << "Solo se admiten archivos txt" << endl;
  }
  lectura.open(nombre, ios::in);
  bool isEmpty = lectura.peek() == EOF;
  if (lectura.fail() == true)
  {
    cout << "No se pudo abrir el archivo " + nombre << endl;
  }
  if (isEmpty)
  {
    cout << "El archivo " + nombre + " esta vacio" << endl;
  }

  else
  {
    // Aqui van las intrucciones de lectura :)
    cout << "El archivo: " + nombre + " se abrio exitosamente" << endl;
  }

  while (getline(lectura, buffer))
  {
    string partido[6];
    char *ptr; // declare a ptr pointer

    ptr = strtok(const_cast<char *>(buffer.c_str()), " ");
    int i = 0;
    partido[i] = ptr;
    while (ptr != NULL)
    {
      // cout << *ptr<<endl;
      i++;
      ptr = strtok(NULL, " ");
      // if(!partido[6].empty()){
      //   cout<<"demasiados argumentos"<<endl;
      //   break;
      // }
      if (ptr != NULL)
      {
        partido[i] = ptr;
      }
      // cout<<partido[i];
    }
    cout << endl;

    cout << "el comando es " << endl;
    for (int j = 0; j < i; j++)
    {
      cout << j << "-->" << partido[j];
    }
    if (partido[0].compare("avanzar") == 0 || partido[0].compare("girar") == 0)
    {
      agregarMovimiento(partido[0], partido[1], partido[2]);
    }
    else if (partido[0].compare("fotografiar") == 0 || partido[0].compare("composicion") == 0 || partido[0].compare("perforar") == 0)
    {
      agregarAnalisis(partido[0], partido[1], partido[2]);
    }
  }

  lectura.close();
}

// Funcion de agregar elementos.
void shell::agregarElemento(string tipoComp, string tamanio, string unidad, string cordx, string cordy)
{
  float tam = stof(tamanio);
  if (!(tipoComp.compare("roca") == 0 || tipoComp.compare("crater") == 0 || tipoComp.compare("monticulo") == 0 || tipoComp.compare("duna") == 0))
  {
    cout << "La información del elemento no corresponde a los datos esperados (tipo,tamaño, unidad,x,y)" << endl;
    return;
  }
  if (tam < 0)
  {
    cout << "La información del elemento no corresponde a los datos esperados (tipo,tamaño, unidad,x,y)" << endl;
    return;
  }
  if (!(unidad.compare("cm") == 0 || unidad.compare("dm") == 0 || unidad.compare("m") == 0 || unidad.compare("km") == 0))
  {
    cout << "La información del elemento no corresponde a los datos esperados (tipo,tamaño, unidad,x,y)" << endl;
    return;
  }
  char tipo = 'n';
  if (tipoComp.compare("roca") == 0)
  {
    tipo = 'r';
  }
  else if (tipoComp.compare("crater") == 0)
  {
    tipo = 'c';
  }
  else if (tipoComp.compare("monticulo") == 0)
  {
    tipo = 'm';
  }
  else if (tipoComp.compare("duna") == 0)
  {
    tipo = 'd';
  }
  Elementos Ele;
  Ele.setTipoElemento(tipo);
  Ele.setTamanno(stoi(tamanio));
  Ele.setUnidadMedida(unidad);
  Ele.setCoordX(stof(cordx));
  Ele.setCoordY(stof(cordy));
  bool bien = curiosity.agregar_elemento(Ele);
  if (bien)
  {
    cout << "El elemento ha sido agregado exitosamente." << endl;
  }
}

void shell::cargarElementos(string nombre)
{

  string buffer;
  ifstream lectura;
  // nombre = "instrucciones.txt";
  regex regex("(.*?)\\.(txt)$");
  if (regex_match(nombre, regex))
  {
    cout << "archivo valido ." << endl;
  }
  else
  {
    cout << "nombre_archivo no se encuentra o no puede leerse." << endl;
  }
  lectura.open(nombre, ios::in);
  bool isEmpty = lectura.peek() == EOF;
  if (lectura.fail() == true)
  {
    cout << "No se pudo abrir el archivo " + nombre << endl;
  }
  if (isEmpty)
  {
    cout << "El archivo " + nombre + " esta vacio";
  }

  else
  {
    // Aqui van las intrucciones de lectura :)
    cout << "El archivo: " + nombre + " se abrio exitosamente" << endl;
  }
  while (getline(lectura, buffer))
  {
    string partido[6];
    char *ptr;
    ptr = strtok(const_cast<char *>(buffer.c_str()), " ");
    int i = 0;
    partido[i] = ptr;
    while (ptr != NULL)
    {
      // cout << *ptr<<endl;
      i++;
      ptr = strtok(NULL, " ");
      // if(!partido[6].empty()){
      //   cout<<"demasiados argumentos"<<endl;
      //   break;
      // }
      if (ptr != NULL)
      {
        partido[i] = ptr;
      }
      // cout<<partido[i];
    }
    cout << endl;
    // cout << "el comando es " << endl;
    for (int j = 0; j < i; j++)
    {
      cout << j << "-->" << partido[j];
    }
    if (partido[0].empty() || partido[1].empty() || partido[2].empty() || partido[3].empty() || partido[4].empty())
    {
      cout << "Ingrese todos los argumentos" << endl;
    }
    else
    {
      try
      {
        float tam = stof(partido[1]);
        float cordx = stof(partido[3]);
        float cordy = stof(partido[4]);
        // cout<< partido[0] << endl;
        agregarElemento(partido[0], partido[1], partido[2], partido[3], partido[4]);
      }
      catch (exception &err)
      {
        cout << "Conversion failure" << endl;
      }
    }
  }
  lectura.close();
}

// Funcion de agregar movimiento.
void shell::agregarMovimiento(string tipo, string magnitud, string unidad)
{
  std::vector<string> vecaux;
  // cout << "Agregar movimiento." << endl;
  // cout << tipo<< magnitud<< unidad<<endl;
  int mag;
  try
  {
    mag = stoi(magnitud);
  }
  catch (exception &err)
  {
    cout << "Conversion failure" << endl;
  }
  if (!(tipo.compare("avanzar") == 0 || tipo.compare("girar") == 0))
  {
    cout << "La información del movimiento no corresponde a los datos esperados(tipo, magnitud, unidad)" << endl;
    return;
  }
  if (mag < 0)
  {
    cout << "La información del movimiento no corresponde a los datos esperados(tipo, magnitud, unidad)" << endl;
    return;
  }
  if (tipo.compare("avanzar") == 0)
  {
    if (!(unidad.compare("cm") == 0 || unidad.compare("dm") == 0 || unidad.compare("m") == 0 || unidad.compare("km") == 0))
    {
      cout << "La información del movimiento no corresponde a los datos esperados(tipo, magnitud, unidad)" << endl;
      return;
    }
  }
  if (tipo.compare("girar") == 0)
  {
    if (!(unidad.compare("grd") == 0 || unidad.compare("rad") == 0))
    {
      cout << "La información del movimiento no corresponde a los datos esperados(tipo, magnitud, unidad)" << endl;
      return;
    }
  }
  Comandos n_coman('M', tipo);
  vecaux.push_back(magnitud);
  vecaux.push_back(unidad);
  n_coman.set_parametros(vecaux);
  bool bien = curiosity.agregar_comando(n_coman);

  cout << n_coman.get_tipo() << n_coman.get_nombre_del_comando() << endl;
  if (bien == true)
  {
    cout << "El comando de movimiento ha sido agregado exitosamente" << endl;
  }
}

// Funcion de agregar analisis.
void shell::agregarAnalisis(string tipo, string objteo, string comentario)
{
  bool agregadoExitosamente = false;
  if (!(tipo.compare("fotografiar") == 0 || tipo.compare("composicion") == 0 || tipo.compare("perforar") == 0))
  {
    cout << "La información del análisis no corresponde a los datos esperados (tipo,objeto, comentario)" << endl;
    return;
  }
  if (!(objteo.compare("roca") == 0 || objteo.compare("arena") == 0 || objteo.compare("monticulo") == 0 || objteo.compare("duna") == 0))
  {
    cout << "La información del análisis no corresponde a los datos esperados (tipo,objeto, comentario)" << endl;
    return;
  }
  Comandos comAnalisis;
  vector<string> argu;
  argu.push_back(objteo);
  argu.push_back(comentario);
  comAnalisis.set_tipo('A');
  comAnalisis.set_parametros(argu);
  agregadoExitosamente = curiosity.agregar_comando(comAnalisis);
  if (agregadoExitosamente)
  {
    cout << "El comando de análisis ha sido agregado exitosamente" << endl;
  }
  cout << tipo << objteo << comentario << endl;
}

void shell::guardar(queue<string> cInstrucciones, string tipoA, string nomArchivo)
{
  cout << "funcion guardar" << endl;
  ofstream file(nomArchivo);
  if (file.is_open())
  {
    while (!cInstrucciones.empty())
    {
      if (!file.tellp())
      {                                 // check if the file pointer is at the beginning of the file
        file << cInstrucciones.front(); // write the first line without a newline
      }
      else
      {
        file << endl
             << cInstrucciones.front(); // write subsequent lines with a newline
      }
      cInstrucciones.pop();
    }
    file.close();
  }
}

void shell::simularComandos(int coordenada_x, int coordenada_y)
{
  queue<Comandos> movimientosASimular;
  vector<string> parametroDeMovimiento;

  // Coordenadas actuales:
  cout << "Coordenadas iniciales en X: " << coordenada_x << endl;
  cout << "Coordenadas iniciales en Y: " << coordenada_y << endl;

  // Coordenadas simuladas
  double coordenadas_simuladas_x = coordenada_x;
  double coordenadas_simuladas_y = coordenada_y;
  double angulo_actual = 0;

  movimientosASimular = curiosity.get_queue_de_comandos();

  Comandos comando_a_simular;

  cout << endl;

  while (!movimientosASimular.empty())
  {
    comando_a_simular = movimientosASimular.front();
    cout << "Comando: " << comando_a_simular.get_nombre_del_comando()<< " " << "tipo de comando: " << comando_a_simular.get_tipo()<<endl;

    parametroDeMovimiento = comando_a_simular.get_parametros();
    double bufferAngulo;
    double bufferDistancia;

    if (comando_a_simular.get_tipo() == 'M')
    {
      if (comando_a_simular.get_nombre_del_comando().compare("avanzar") == 0)
      {
        cout << "Se avanza..." << endl;

        // 0 es para el numero, 1 es para la unidad de medida. 

        bufferDistancia = stod(parametroDeMovimiento[0]);
    

        coordenadas_simuladas_x += bufferDistancia * cos(angulo_actual);
        coordenadas_simuladas_y += bufferDistancia * sin(angulo_actual);

        cout << "Nueva localizacion: X " << coordenadas_simuladas_x << ", Y: " << coordenadas_simuladas_y << endl;
      }

      if (comando_a_simular.get_nombre_del_comando().compare("girar") == 0)
      {
        if (parametroDeMovimiento[1].compare("grd") == 0)
        {
          bufferAngulo = stod(parametroDeMovimiento[0]);

          bufferAngulo = bufferAngulo * 3.14159265358979323846 / 180;

          angulo_actual += bufferAngulo;

          cout << "Nuevo angulo" << angulo_actual << endl;
        }
        else if (parametroDeMovimiento[1].compare("rad") == 0)
        {
          bufferAngulo = stod(parametroDeMovimiento[0]);

          angulo_actual += bufferAngulo;

          cout << "Nuevo angulo" << angulo_actual << endl;
        }
      }
    }
    movimientosASimular.pop(); // este pop es para que el loop no sea infinito
  }

  /*
    // Actualizar (simular) coordenadas
    coordenada_actual_x += coordenada_x;
    coordenada_actual_y += coordenada_y;
  */

  // double angulo = atan(coordenada_x / coordenada_y) * 180 / M_PI ;

  // cout << "Coordenadas actualizadas, el robot estaba en las coordenadas " << coordenada_inicial_x << ", " << coordenada_inicial_y << endl;
  // cout << "..." << endl;
  // cout << "El robot quedo en las coordenadas " << coordenada_actual_x << ", " << coordenada_actual_y << endl;
  // cout << "El angulo resultante fue de: " << angulo << endl;
}

void shell::enCuadrante(int x1, int x2, int y1, int y2)
{
  cout << "enCuadrante" << endl;
  cout << "Los elementos ubicados en el cuadrante solicitado son: " << x1 << x2 << y1 << y2 << endl;
}

void shell::salir()
{

  exit(0);
}

void shell::ubicarElementos()
{
  cout << "Funcion Elementos" << endl;
}

void shell::crearMapa()
{
  cout << "Funcion crear Mapa" << endl;
}

void shell::rutaMasLarga()
{
  cout << "Funcion ruta Mas Larga" << endl;
}
void shell::limpiar()
{

#ifdef _WIN32
  printf("Windows\n");
  if (system("CLS") == -1)
  {
    cout << "ERROR" << endl;
  }
#elif __linux__
  printf("Other linux OS\n");
  if (system("clear") == -1)
  {
    cout << "ERROR" << endl;
  }
#elif __unix__
  printf("Other unix OS\n");
  if (system("clear") == -1)
  {
    cout << "ERROR" << endl;
  }
#elif __APPLE__
  printf("Other unix OS\n");
  if (system("clear") == -1)
  {
    cout << "ERROR" << endl;
  }
#else
  printf("Unidentified OS\n");
#endif
}
