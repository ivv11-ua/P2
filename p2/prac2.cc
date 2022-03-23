// Programación 2 - Práctica 2
// DNI: 20525805-F
// Nombre: Iván Valor Verdú
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

const int KMAXSTRING = 50;

enum Error{
  ERR_OPTION,
  ERR_BOOK_TITLE,
  ERR_BOOK_AUTHORS,
  ERR_BOOK_DATE,
  ERR_BOOK_PRICE,
  ERR_ID,
  ERR_FILE,
  ERR_ARGS
};

struct Book{
  unsigned int id;
  string title;
  string authors;
  int year;
  string slug;
  float price;
};

struct BinBook{
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
};

struct BookStore{
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBookStore{
  char name[KMAXSTRING];
  unsigned int nextId;
};

void error(Error e){
  switch (e) {
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_BOOK_TITLE:
      cout << "ERROR: wrong book title" << endl;
      break;
    case ERR_BOOK_AUTHORS:
      cout << "ERROR: wrong author(s)" << endl;
      break;
    case ERR_BOOK_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_BOOK_PRICE:
      cout << "ERROR: wrong price" << endl;
      break;
    case ERR_ID:
      cout << "ERROR: wrong book id" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
      break;
  }
}

void showMainMenu(){
  cout << "[Options]" << endl
       << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl
       << "3- Add book" << endl
       << "4- Delete book" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void showCatalog(const BookStore &bookStore){
	for(unsigned int i = 0; i < bookStore.books.size(); i++){
		cout << bookStore.books[i].id << ". ";
		cout << bookStore.books[i].title;
		cout << " (" << bookStore.books[i].year << "), ";
		cout << bookStore.books[i].price << endl;
	}
}

void showExtendedCatalog(const BookStore &bookStore){
	char n='"';
	for(unsigned int i=0; i < bookStore.books.size(); i++){
		cout << n << bookStore.books[i].title << n << "," << n << bookStore.books[i].authors;
		cout << n << "," << bookStore.books[i].year << "," << n;
		cout << bookStore.books[i].slug << n << "," << bookStore.books[i].price << endl;
	}
}

bool comprobarTitulo(string cad){
	bool okTitulo;
	int tamanyo;  //almacenar el tamaño del string 
	okTitulo=true; //Saber si el titulo cumple los requisitos, primero es true y si esta mal pasa a false

	tamanyo=cad.length();
	if(tamanyo==0){
		okTitulo=false;
	}
	else{
		for(int i= 0; i < tamanyo && okTitulo; i++){
			if(isalnum(cad[i])==0 && cad[i] != ' ' && cad[i] != ':' && cad[i] != ',' && cad[i] != '-'){
				okTitulo=false;
      			}
	  	}
	}
	return okTitulo;
}

bool comprobarAnyo(string a,int &anyo){
	bool okAnyo;
	int tamanyo; //saber el tamaño del string a
	
	
	okAnyo=true;
	tamanyo=a.length();

	if(tamanyo==0){
		okAnyo=false;
	}
	else{
		for(int i=0; i < tamanyo; i++){
			if(isdigit(a[i])==0){
				okAnyo=false;
			}
		}
		if(okAnyo!=false){   //entramos si aún no es false
			anyo=stoi(a);
			if(anyo<=1440 || anyo>=2022){
				okAnyo=false;
			}
		}
 	}
	return okAnyo;
}

bool comprobarPrecio(string p,float &precio){
	bool okPrecio;
	int tamanyo; //saber el tamaño del string p
	
	
	okPrecio=true;
	tamanyo=p.length();

	if(tamanyo==0){
		okPrecio=false;
	}
	else{
		for(int i=0; i < tamanyo; i++){
			if(isdigit(p[i]) ==0 && p[i] != '.'){
				okPrecio=false;
			}
		}
		if(okPrecio!=false){   //entramos si aún no es false
			precio=stof(p);
			if(precio <= 0){
				okPrecio=false;
			}
		}
 	}
	return okPrecio;
}
string funcionSlug(string slug, int tam){
	string resultado;
	//Cambiar mayusculas por minusculas
	for(int i=0; i < tam; i++){
		slug[i]=tolower(slug[i]);
	}
	//Cambiar caracteres que no sean nums y letras, tambien espacios a -
	for(int i=0; i < tam; i++){
		if(isalnum(slug[i]) == 0 || slug[i]==' '){
			slug[i]='-';
		}
	}
	//Eliminar guiones principio y final del slug
	int i,j,k;
	i=0;
	while(i < tam && slug[i]=='-'){
		i++;
	}
	j=tam-1;
	while(j >=0 && slug[j]=='-'){
		j--;
	}
	for(k=i; k<= j; k++){
		resultado=resultado+slug[k];
	}
	slug=resultado;

	resultado="";
	tam=slug.length();
	//Eliminar guiones repetidos del medio
	for(int i=0; i < tam; i++){
		if(i==tam-1){
			resultado=resultado+slug[i];
		}
		else{
			if(slug[i] == '-'){
				if(slug[i] != slug[i+1]){
					resultado=resultado+slug[i];
				}
			}
			else{
				resultado= resultado + slug[i];
			}
			
		}
	}
	slug=resultado;
	return slug;
}

void addBook(BookStore &bookStore){
	Book newBook;
	bool okCadena;		//variable para almacenar lo que devuelve la función comprobarTitulo
   	bool okAnyo; 		//variable para almacenar lo que devuelve la funcion comporbarAnyo
	bool okPrecio;		//variable para almacenar lo que devuelve la funcion comporbarPrecio
	
	int tam;
	int year; 		//almacenar el valor que convertimos con el stoi a int
	float price;		//almacenar el valor que convertimos con el stof a float
	string anyo; 		//almacenar el anyo en string
	string precio;		//almacenar el precio en string
	string slug;
	string resultado="";    //cadena donde guardo la modificacion del slug

   	newBook.id=bookStore.nextId;
    	bookStore.nextId++;
    
    
    	do{
        
        cout << "Enter book title: ";
        getline(cin,newBook.title);

        okCadena=comprobarTitulo(newBook.title);
		if(!okCadena){
			error(ERR_BOOK_TITLE);
    		}
    	}while(okCadena == false);
	
	do{
		cout << "Enter author(s): ";
		getline(cin, newBook.authors);
		
		okCadena=comprobarTitulo(newBook.authors); //usamos el mismo módulo que antes
		if(!okCadena){
			error(ERR_BOOK_AUTHORS);
    		}
	}while(okCadena==false);
	
	do{
		cout << "Enter publication year: ";
 		getline(cin, anyo);
	
		okAnyo=comprobarAnyo(anyo, year);
		if(!okAnyo){
			error(ERR_BOOK_DATE);
    		}
	}while(okAnyo==false);
	newBook.year=year;//guardamos el año como int
	
	do{
		cout << "Enter price: ";
		getline(cin, precio);
		okPrecio=comprobarPrecio(precio, price);
		if(!okPrecio){
			error(ERR_BOOK_PRICE);
    		}
	}while(okPrecio==false);
	newBook.price=price;
	
	slug=newBook.title;
	tam=slug.length();
	
	resultado=funcionSlug(slug,tam);

	newBook.slug=resultado;
	bookStore.books.push_back(newBook);
}

int buscarIdLibro(const vector<Book> &books,unsigned int id){
	int position;
	int tam=books.size();

	position=-1; //consideramos el -1, y si encontramos el libro cambiar el valor de position
	for(int i= 0; i < tam && position==-1; i++){
		if(books[i].id == id){
			position=i;
		}	
	}
	return position;
}


void deleteBook(BookStore &bookStore){
	string book;
	int tamanyo, position, id;

	cout << "Enter book id: ";
	getline(cin, book);
	tamanyo=book.length();
	if(tamanyo==0){
		error(ERR_ID);
	}
	else{
		id=stoi(book); //pasar el string a int, lo cogemos como string para comprobar cadena vacia
		position=buscarIdLibro(bookStore.books, id); //encontrar en que posicion esta el libro
		if(position != -1){
			bookStore.books.erase(bookStore.books.begin()+position);
		}
		else{
			error(ERR_ID);
		}
	}
}


void importFromCsv(BookStore &bookStore){
	Book newBook;
	ifstream fichero;
	string nombreFich;
	

	bool okTitle,okAuthor,okYear,okPrice; //variables para hacer la comprobación de los distintos campos
	string anyo, precio; //lo guardo como string para saber si el campo es cadena vacia o no
	
	int year; 	//guardo el año despues de hacer la comprobacion
	float price;	//guardo el price después de hacer la comprobación
	
	cout << "Enter filename: "; //nombre del fichero que quieres buscar donde están almacenados los libros
	getline(cin,nombreFich);
	
	fichero.open(nombreFich.c_str());
	if(fichero.is_open()){
		fichero.get();
		while(!fichero.eof()){  
			getline(fichero, newBook.title, '"');
			fichero.get(); fichero.get();
			getline(fichero, newBook.authors, '"');
			fichero.get();

			getline(fichero,anyo,',');
			fichero.get();

			getline(fichero, newBook.slug, '"');
			fichero.get();
			
			getline(fichero,precio); //me quita el primer salto de linea
			fichero.get();
			
					
			okTitle=comprobarTitulo(newBook.title);
			okAuthor=comprobarTitulo(newBook.authors);
			okYear=comprobarAnyo(anyo,year);
			okPrice=comprobarPrecio(precio, price);
				
			newBook.year=year;
			newBook.price=price;
			if(okTitle && okAuthor && okYear && okPrice){
				newBook.id = bookStore.nextId;
				bookStore.nextId++;
				bookStore.books.push_back(newBook);
			}
			else{
				if(!okTitle){
					error(ERR_BOOK_TITLE);
				}
				else{
					if(!okAuthor){
						error(ERR_BOOK_AUTHORS);
					}
					else{
						if(!okYear){
							error(ERR_BOOK_DATE);
						}
						else{			
							error(ERR_BOOK_PRICE);
						}	
					}
				}
			}
					
		}
		fichero.close();
	}
	else{
		error(ERR_FILE);
	}
}

void exportToCsv(const BookStore &bookStore){
	int tamanyo;
	ofstream fichero;
	string nombreFich;
	char n='"';
	
	tamanyo=bookStore.books.size();
	cout << "Enter filename: ";
	getline(cin,nombreFich);
	
	fichero.open(nombreFich.c_str()); //pasarlo a vector de caracteres	
	if(fichero.is_open()){
		for(int i=0; i < tamanyo; i++){
			fichero << n << bookStore.books[i].title << n << ","
			 	<< n << bookStore.books[i].authors <<  n << ","
				<< bookStore.books[i].year << ","
				<< n << bookStore.books[i].slug << n << ","
				<< bookStore.books[i].price << endl;	
		}
		fichero.close();
	}
	else{
		error(ERR_FILE);
	} 
}

void loadData(BookStore &bookStore){
	ifstream fichero;
	string nombreFich;
	BinBookStore bbs;  
	BinBook bb;  
	Book leido;
      	char op;

	do{		
		cout << "All data will be erased, do you want to continue (Y/N)?:";
		cin >> op;
		cin.get();
	}while(op !='N' && op != 'n' && op != 'Y' && op != 'y');
	
	if(op == 'Y' || op== 'y'){
		cout << "Enter filename: ";
		getline(cin,nombreFich);

		fichero.open(nombreFich.c_str(),ios::binary);
		if(fichero.is_open()){
			bookStore.books.clear();
			
			fichero.read((char *)&bbs, sizeof(bbs));
			bookStore.name=bbs.name;
			bookStore.nextId=bbs.nextId;

			fichero.read((char *)&bb, sizeof(bb));
			while(!fichero.eof()){
				leido.id=bb.id;
				leido.title=bb.title;
				leido.authors=bb.authors;
				leido.year=bb.year;
				leido.slug=bb.slug;
				leido.price=bb.price;
				bookStore.books.push_back(leido);
				fichero.read((char *)&bb, sizeof(bb));
			}
			fichero.close();
		}
		else{
			error(ERR_FILE);
		} 
		
	}
}
void bookAbinBook(const Book &b, BinBook &bb){
	bb.id=b.id;
	strncpy(bb.title,b.title.c_str(),KMAXSTRING);
	bb.title[KMAXSTRING-1]='\0';

	strncpy(bb.authors,b.authors.c_str(),KMAXSTRING);
	bb.authors[KMAXSTRING-1]='\0';

	bb.year=b.year;
			
	strncpy(bb.slug,b.slug.c_str(),KMAXSTRING);
	bb.slug[KMAXSTRING-1]='\0';
			
	bb.price=b.price;
}
void saveData(const BookStore &bookStore){ //guardar datos en un fichero binario
	ofstream fichero;
	string nombreFich;

	BinBookStore bbs;   //para pasar la librería al fichero binario
	BinBook bb;         //para pasar el libro al fichero binario

	cout << "Enter filename: ";
	getline(cin, nombreFich);

	fichero.open(nombreFich.c_str(),ios::binary);
	if(fichero.is_open()){
		bbs.nextId=bookStore.nextId;
		strncpy(bbs.name,bookStore.name.c_str(), KMAXSTRING);
		bbs.name[KMAXSTRING-1]='\0';
		
		fichero.write((const char*)&bbs, sizeof(bbs));

		for(unsigned int i=0; i < bookStore.books.size(); i++){
			bookAbinBook(bookStore.books[i], bb);
			fichero.write((const char*) &bb, sizeof(bb));
		};
		fichero.close();
	}
	else{
		error(ERR_FILE);
	} 
}

void showMenuExterior(){
	cout << "[Import/export options]" << endl;
	cout << "1- Import from CSV" << endl;
	cout << "2- Export to CSV" << endl;
	cout << "3- Load data" << endl;
	cout << "4- Save data" << endl;
	cout << "b- Back to main menu" << endl;
	cout << "Option: ";
}	

void importExportMenu(BookStore &bookStore){
	char option;
	do{
		showMenuExterior();
		cin >> option;
		cin.get();
	
		switch(option){
			case '1':
				importFromCsv(bookStore);
			break;
			case '2':
				exportToCsv(bookStore);
			break;
			case '3':
				loadData(bookStore);
			break;
			case '4':
				saveData(bookStore);
			break;
			case 'b':
			break;
			default:
				error(ERR_OPTION);
			break;
		}
	}while(option != 'b');
}



int main(int argc, char *argv[]){
  BookStore bookStore;               //mi libreria
  bookStore.name = "My Book Store";  //nombre de la libreria
  bookStore.nextId = 1;              //id automatico para el siguiente libro
	
  
  char option;
  do{
    showMainMenu();
    cin >> option;
    cin.get();

    switch(option){
      case '1':
        showCatalog(bookStore);
        break;
      case '2':
        showExtendedCatalog(bookStore);
        break;
      case '3':
        addBook(bookStore);
        break;
      case '4':
        deleteBook(bookStore);
        break;
      case '5':
        importExportMenu(bookStore);
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  }while(option != 'q');

  return 0;
}
