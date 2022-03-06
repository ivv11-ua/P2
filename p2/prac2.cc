// Programación 2 - Práctica 2
// DNI: 20525805-F
// Nombre: Iván Valor Verdú
#include <iostream>
#include <vector>

using namespace std;

const int KMAXSTRING = 50;

enum Error {
  ERR_OPTION,
  ERR_BOOK_TITLE,
  ERR_BOOK_AUTHORS,
  ERR_BOOK_DATE,
  ERR_BOOK_PRICE,
  ERR_ID,
  ERR_FILE,
  ERR_ARGS
};

struct Book {
  unsigned int id;
  string title;
  string authors;
  int year;
  string slug;
  float price;
};

struct BinBook {
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
};

struct BookStore {
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBookStore {
  char name[KMAXSTRING];
  unsigned int nextId;
};

void error(Error e) {
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

void showMainMenu() {
  cout << "[Options]" << endl
       << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl
       << "3- Add book" << endl
       << "4- Delete book" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void showCatalog(const BookStore &bookStore) {
	for(int i = 0; i < bookStore.books.size(); i++){
		cout << bookStore.books[i].id << ". ";
		cout << bookStore.books[i].title << " (";
		cout << bookStore.books[i].year << "), ";
		cout << bookStore.books[i].price << endl;
	}
}

void showExtendedCatalog(const BookStore &bookStore) {
}

void addBook(BookStore &bookStore) {
	Book newBook;
	bool okTitulo;
    int tamanyo;  //almacenar el tamaño del string 
    newBook.id=bookStore.nextId;
    bookStore.nextId++;
    
    
    do{
        okTitulo=true; //Saber si el titulo cumple los requisitos, primero es true y si esta mal pasa a false
        cout << "Enter book title: ";
        getline(cin,newBook.title);
        tamanyo=newBook.title.length();
        
        for(int i= 0; i < tamanyo && okTitulo; i++){
            if(isalnum(newBook.title[i])==0 && newBook.title[i] != ' ' && newBook.title[i] != ':' && newBook.title[i] != ',' && newBook.title[i] != '-'){
                okTitulo=false;
            }
        }
        if(tamanyo==0){
            okTitulo=false;
        }
        if(!okTitulo){
            error(ERR_BOOK_TITLE);
        }
    }while(okTitulo == false);
}

void deleteBook(BookStore &bookStore) {
}

void importExportMenu(BookStore &bookStore) {
}

void importFromCsv(BookStore &bookStore){
}

void exportToCsv(const BookStore &bookStore){
}

void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}

int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;

  char option;
  do {
    showMainMenu();
    cin >> option;
    cin.get();

    switch (option) {
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
  } while (option != 'q');

  return 0;
}
