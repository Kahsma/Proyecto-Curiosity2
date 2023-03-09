#include <iostream>
#include <map>
#include "shell.h"
#include "Comandos.h"
#include "Curiosity.h"
#include "Elementos.h"
#include <unistd.h> // for sleep()

//Nombres : Alberto Vigna , Alejandro Salamanca ,Andres Salamanca , Camilo Martinez
using namespace std;
int main(int argc, char *argv[]) 
{
  cout << "Entrada al main" << endl;
  shell *console = new shell();
  console->shell::iniciarShell();
  //console->help();
}