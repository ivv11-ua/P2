// Programación 2 - Práctica 1
// DNI: 20525805F
// Nombre: IVAN VALOR VERDú

#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <cctype>
#include<cstring>

using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado

struct Core{ //centro
  int attack;
  int defense;
  int hp;
};

enum Breed{ //raza
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
};

struct Enemy{ 
  Breed name;
  Core features;
};

struct Hero{
  char name[KNAME];
  Core features;
  bool special;
  int runaways;
  int exp;
  int kills[KENEMIES];
};

int rollDice(){
  return rand()%KDICE+1;
}

Hero createHero(){
	Hero leerHero;
	bool es; //comprobar que el nombre es todo numeros o caracteres
	es=true; //es true y si cambia se repite el bucle
	do{
		cout << "Enter hero name: ";
		cin.getline(leerHero.name, KNAME);
		if(isalpha(leerHero.name[0])==false){
			cout << "ERROR: wrong name" << endl;
		}
		else{
			for(int i=0; (unsigned int)i < strlen(leerHero.name); i++){
				if(isalnum(leerHero.name[i])== 0){
					es=false;
				}
			}
			if(es==false){
				cout << "ERROR: wrong name" << endl;
			}
		}
	}while(isalpha(leerHero.name[0])==false || es == false);
	
	do{
		cout << "Enter attack/defense: ";
		cin >> leerHero.features.attack;
		cin.get();
		cin >> leerHero.features.defense;
		if(leerHero.features.attack + leerHero.features.defense != 100 && leerHero.features.attack < 0 && leerHero.features.defense < 0){
			cout << "ERROR: wrong distribution" << endl;
		}
	}while(leerHero.features.attack + leerHero.features.defense != 100 && leerHero.features.attack < 0 && leerHero.features.defense < 0);

	return leerHero;
}

Enemy createEnemy(){
	Enemy leerEnemy;
		
	return leerEnemy;
}

void fight(Hero &hero,Enemy &enemy){
}

void report(const Hero &hero){
}

void showMenu(){
  cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

int main(int argc,char *argv[]){
	Hero myHero;
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
	myHero=createHero();
  }
}
