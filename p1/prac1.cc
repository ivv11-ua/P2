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
			es=true;
			for(int i=0; (unsigned int)i < strlen(leerHero.name); i++){
				if(isalnum(leerHero.name[i])== 0 && leerHero.name[i] != ' '){
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
		if(leerHero.features.attack + leerHero.features.defense != 100 || leerHero.features.attack < 0 || leerHero.features.defense < 0){
			cout << "ERROR: wrong distribution" << endl;
		}
	}while(leerHero.features.attack + leerHero.features.defense != 100 || leerHero.features.attack <= 0 || leerHero.features.defense <= 0);
	
	leerHero.features.attack= 200 * leerHero.features.attack/100.0;
	leerHero.features.defense= 200 * leerHero.features.defense/100.0;
	leerHero.features.hp=leerHero.features.defense*2;

	leerHero.special=true;
	leerHero.exp=0;
	leerHero.runaways = 3;
	//Inicializar el vector de kills a 0
	for(int i=0; i < KENEMIES; i++){
		leerHero.kills[i]=0;	
	}

	return leerHero;
}

Enemy createEnemy(){
	Enemy leerEnemy;
	int dado; //variable pa guardar el lanzamiento
	
	dado=rollDice();
	
	if(dado >= 1 && dado <= 6){

		leerEnemy.name=AXOLOTL;
	}
	else{
		if(dado <= 11){
			leerEnemy.name=TROLL;
		}
		else{
			if(dado <= 15){
				leerEnemy.name=ORC;
			}
			else{
				if(dado <= 18){
					leerEnemy.name=HELLHOUND;
				}
				else{
					leerEnemy.name=DRAGON;
				}
			}
		}
	}
	switch(leerEnemy.name){
		case AXOLOTL:
			leerEnemy.features.attack=40;
			leerEnemy.features.defense=40;
		break;
		case TROLL:
			leerEnemy.features.attack=60;
			leerEnemy.features.defense=80;
		break;
		case ORC:
			leerEnemy.features.attack=80;
			leerEnemy.features.defense=120;
		break;
		case HELLHOUND:
			leerEnemy.features.attack=120;
			leerEnemy.features.defense=100;
		break;
		case DRAGON:
			leerEnemy.features.attack=160;
			leerEnemy.features.defense=140;
		break;	
	}
	leerEnemy.features.hp=leerEnemy.features.defense*2;
	return leerEnemy;
}

void imprimirEnemigo(const Enemy &e){
	
	cout << "[Enemy]" << endl;
	cout << "Breed: ";
	switch(e.name){
		case AXOLOTL:
			cout << "Axolotl";
			break;
		case TROLL:
			cout << "Troll";
			break;
		case ORC:
			cout << "Orc";
			break;
		case HELLHOUND:
			cout << "Hellhound";
			break;
		case DRAGON:
			cout << "Dragon";
			break;
	}
	cout << endl << "Attack: " << e.features.attack << endl;
	cout << "Defense: " << e.features.defense << endl;
	cout << "Health points";	
	cout << ": " << e.features.hp << endl;
}
void report(const Hero &hero){
	int suma = 0; //utilizamos suma para alacenar las kills totales
	char tiposEnemy[KENEMIES][15]={"Axolotl", "Troll", "Orc", "Hellhound", "Dragon"}; //para poder hacer el listado de enemies killed

	cout << "[Report]" << endl;
	cout << "Name: " << hero.name << endl;
	cout << "Attack: " << hero.features.attack << endl;
	cout << "Defense: " << hero.features.defense << endl;
	cout << "Health points: " << hero.features.hp << endl;
	cout << "Special: ";
	if(hero.special==true){
		cout << "yes" << endl;
	}
	else{
		cout << "no " << endl;	
	}
	cout << "Runaways: " << hero.runaways << endl;
	cout << "Exp: " << hero.exp << endl;
	cout << "Enemies killed: " << endl;
	
	for(int i=0; i < KENEMIES; i++){
		cout << "-";
		cout << tiposEnemy[i] << ": ";
		cout << hero.kills[i] << endl;
		suma+=hero.kills[i];
	}
	cout << "-Total: " << suma << endl;
}
void fight(Hero &hero,Enemy &enemy){
	int dado1, dado2, heroe_hitP, expEnemigo;
	int enemy_hitP;
	

	dado1= rollDice()*5; //para el ataque del heroe
	dado2= rollDice()*5; //para la defensa del enemigo

	heroe_hitP=(hero.features.attack + dado1) - (enemy.features.defense + dado2);
	if(heroe_hitP < 0){
		heroe_hitP=0;	
	}
	
	enemy.features.hp = enemy.features.hp - heroe_hitP;
	if(enemy.features.hp <= 0){
		enemy.features.hp=0;
	}
	cout << "[Hero -> Enemy] " << endl;
	cout << "Attack: " << hero.features.attack << " + " << dado1 << endl;
	cout << "Defense: " << enemy.features.defense << " + " << dado2 << endl;
	cout << "Hit points: " << heroe_hitP << endl;
	cout << "Enemy health points: " <<  enemy.features.hp << endl;

	if(enemy.features.hp <= 0){

		cout << "Enemy killed" << endl;
		switch(enemy.name){
			case AXOLOTL:
				expEnemigo=100;
				break;
			case TROLL:
				expEnemigo=150;
				break;
			case ORC:
				expEnemigo=200;
				break;
			case HELLHOUND:
				expEnemigo=300;
				break;
			case DRAGON:
				expEnemigo=400;
				break;
		}
		hero.exp+=expEnemigo;
		enemy=createEnemy();
		imprimirEnemigo(enemy);
	}
	else{
		dado1= rollDice()*5; //para el ataque del enemigo
		dado2= rollDice()*5; //para la defensa del heroe

		enemy_hitP=(enemy.features.attack + dado1) - (hero.features.defense + dado2);
		if(enemy_hitP < 0){
			enemy_hitP=0;	
		}
	
		hero.features.hp-=  enemy_hitP;
		if(hero.features.hp <= 0){
				hero.features.hp=0;
		}
		cout << "[Enemy -> Heroe] " << endl;
		cout << "Attack: " << enemy.features.attack << " + " << dado1 << endl;
		cout << "Defense: " << hero.features.defense << " + " << dado2 << endl;
		cout << "Hit points: " << enemy_hitP << endl;
		cout << "Hero health points: " <<  hero.features.hp << endl;
		if(hero.features.hp <= 0){
			cout << "You are dead" << endl;
			report(hero);
		}
	
	}
	
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
	Hero miHeroe;
	Enemy miEnemigo;
	char op; //opcion a elegir en el menu

	if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
		cout << "Usage: " << argv[0] << " <seed>" << endl;
	}
	else{
		srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios

		// Aquí vendrá todo tu código del "main"...
		miHeroe=createHero();	
		miEnemigo=createEnemy();
		imprimirEnemigo(miEnemigo);
		do{
				showMenu();
				cin >> op;
				switch(op){
					case '1':
						fight(miHeroe, miEnemigo);
						break;
					case '2':
						if(miHeroe.runaways == 0){
							cout << "Error: cannot run away" << endl;
						}
						else{
							cout << "You run away" << endl;
						}
						break;
					case '3':
						break;
					case '4':
						report(miHeroe);
						break;
					case'q':
						break;
					default:
						cout << "ERROR: wrong option" << endl;
						break;
				}
		}while(op != 'q' && miHeroe.features.hp > 0);
	}
	
}
