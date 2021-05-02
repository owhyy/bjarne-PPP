#include "Interface.h"
Book found_book;
Library lib{"b.p. ion creanga"};
void main_menu() {
  static bool initialized;
  if (!initialized) {
    initialized = true;
    Book b1{"1-1-1-x", "to kill a mockingbird", "lee harper",
            Date(1970, Month::apr, 23), Genre::nonfiction};
    Book b2{"1-1-1-x", "the magic mountain", "thomas mann",
            Date(1989, Month::apr, 23), Genre::nonfiction};
    Book b3{"1-1-1-x", "aba", "thomas mann", Date(1989, Month::apr, 23),
            Genre::nonfiction};
    Patron p{"ion", 69};
    lib.add_patron_to_library(p);
    lib.add_book_to_library(b1);
    lib.add_book_to_library(b2);
    lib.add_book_to_library(b3);
  }
  system("clear");
  int choice;
  cout << "\n" << get_current_date() << "  ";
  cout << " welcome to the " << lib.library_name() << "\n\n";
  cout << "1. view available books\n";
  cout << "2. user information\n";
  cout << "3. exit\n\n\n";
  cout << "enter the number corresponding to the desired operation\n";
  cout << "> ";
  cin >> choice;
  cin.ignore(1000, '\n');
  if (choice == 3)
    return;
  if (choice == 1) {
    return search_screen();
  }
  //	if(choice==2){
  //		user_information();
  //	}
}
void search_screen() {
  system("clear");
  int choice = 0;
  cout << "\n";
  cout << "1. list available books\n";
  cout << "2. search for book by name\n";
  cout << "3. search for author\n";
  cout << "4. search for isbn\n";
  cout << "5. go back to main menu\n\n\n";
  cout << "> ";
  cin >> choice;
  cin.ignore(1000, '\n');
  if (choice == 1) {
    int choice_print_books = 0;
    system("clear");
    cout << "\n";
    lib.print_available_books();
    cout << "\n1. go back\n\n\n";
    cout << "> ";
    cin >> choice_print_books;
    cin.ignore(1000, '\n');
    if (choice_print_books == 1)
      return search_screen();
  }
  if (choice == 2) {
    return search_for_title();
  }
  /* if (choice == 3) { */
  /*   return search_for_author(); */
  /* } */
  /* if (choice == 4) { */
  /*   return search_for_isbn(); */
  /* } */
  if (choice == 5)
    return main_menu();
}

void search_for_title() { // prompts and returns book
  system("clear");
  vector<Book> books = lib.books();
  string title;
  cout << "\nplease enter the title of the book\n\n\n";
  cout << "> ";
  getline(cin, title);
  system("clear");
  found_book = sought_title(title, books);
  /* bool found_title = title_was_found(title, books); */
  if (found_book.title() != "empty_book") {
    cout << "\nbook was found\n";
    return prompt_check_out();
  } else {
    system("clear");
    int try_again;
    cout << "Book not found\n";
    cout << "try again?\n";
    cout << "1. Yes\n";
    cout << "2. No\n\n\n";
    cout << "> ";
    cin >> try_again;
    cin.ignore(1000, '\n');
    if (try_again == 1)
      return search_for_title();
    else
      return search_screen();
  }
}

void prompt_check_out() {
  cout << "do you want to check it out?\n";
  cout << "1. Yes\n";
  cout << "2. No\n\n\n";
  cout << "> ";
  int will_check_out;
  cin >> will_check_out;
  cin.ignore(1000, '\n');
  if (will_check_out == 1) {   // if will check out
    if (found_book.status()) { // if book is checked out already
      cout << "\nBook is already checked out\n";
      cout << "do you want to search another book?\n";
      cout << "1. Yes\n";
      cout << "2. No\n\n\n";
      cout << "> ";
      int search_again;
      cin >> search_again;
      cin.ignore(1000, '\n');
      if (search_again == 1) {
        return search_for_title();
      } else
        return search_screen();
    } else { // if not checked out
      return prompt_patron();
    }
  } else { // if won't check out;
    cout << "\nsearch for another book?\n";
    cout << "1. Yes\n";
    cout << "2. No\n\n\n";
    int search_again;
    cin >> search_again;
    cin.ignore(1000, '\n');
    if (search_again == 1) { // if will search for title
      return search_for_title();
    } else {
      return search_screen();
    }
  }
}

void prompt_patron() { // checks prompts for account
  system("clear");
  cout << "\nDo you have an account?\n";
  cout << "1. Yes\n";
  cout << "2. No\n";
  cout << "3. Go back\n\n\n";
  cout << "> ";
  int is_patron;
  cin >> is_patron;
  cin.ignore(1000, '\n');
  if (is_patron == 1)
    return search_patron();
  if (is_patron == 2)
    return make_patron(); // make patron
  if (is_patron == 3)
    return search_screen();
}
void search_patron() {
  // finds patron
  system("clear");
  cout << "\nPlease enter your name and identity number\n\n\n";
  cout << "Name\n";
  cout << "> ";
  string patron_name;
  int id_number;
  getline(cin, patron_name);
  cout << "\nIdentity number\n";
  cout << "> ";
  cin >> id_number;
  cin.ignore(1000, '\n');
  vector<Patron> patrons = lib.patrons();
  Patron sought = found_patron(patron_name, id_number, patrons);
  if (sought.patron_name() == "empty_patron") { // if not found
    cout << "\nname or id not found. try again?\n";
    cout << "1. Yes\n";
    cout << "2. No\n\n\n";
    cout << "> ";
    int try_again_name;
    cin >> try_again_name;
    cin.ignore(1000, '\n');
    if (try_again_name == 1) { // search again for the name
      return search_patron();
    } else
      return prompt_patron();
  }
  if (!sought.has_fee() &&
      sought.patron_name() != "empty_patron") { // if doesn't have fee
    system("clear");
    found_book.check_out();
    cout << "\nBook checked out!\n";
  }
}

Patron found_patron(const string &patron_name, const int patron_id,
                    const vector<Patron> &patrons) {
  auto sought_patron = find_if(patrons.begin(), patrons.end(),
                               [patron_name, patron_id](const Patron &p) {
                                 return p.patron_name() == patron_name &&
                                        p.identity_number() == patron_id;
                               });
  if (sought_patron != patrons.end())
    return *sought_patron;
  return Patron{"empty_patron", 0};
}

Book sought_title(const string &title, const vector<Book> &books) {
  auto sought_book =
      find_if(books.begin(), books.end(),
              [title](const Book &b) { return b.title() == title; });
  if (sought_book != books.end())
    return *sought_book;
  return Book("empty_book");
}
void make_patron() {
  system("clear");
  cout<<"\nCreating an account\n";
  string n;
  cout << "\nPlease enter your name\n\n\n";
  cout << "> ";
  getline(cin, n);
  Patron p{n};
  lib.add_patron_to_library(p);
  cout << "\n\nYour identity number will be " << p.identity_number()<<"\n";
  return main_menu();
}
///* void search_for_author() { */
///*   system("clear"); */
///*   cin.clear(); */
///*   cin.ignore(1000, '\n'); */
///*   string author; */
///*   vector<book> books = lib.books(); */
///*   cout << "\n\nplease enter the name of the author\n\n\n"; */
///*   cout << "> "; */
///*   getline(cin, author); */
///*   bool found_author = author_was_found(author, books); */
///*   if (found_author) { */
///*     cout << "author was found\n"; */
///*     // calls screen in which chooses to check out */
///*   } else { */
///*     int try_again; */
///*     cout << "author not found\n"; */
///*     cout << "try again?\n"; */
///*     cout << "1. Yes\n"; */
///*     cout << "2. no\n\n\n"; */
///*     cout << "> "; */
///*     cin >> try_again; */
///*     if (try_again == 1) */
///*       return search_for_author(); */
///*     else */
///*       return search_screen(); */
///*   } */
///* } */
//
///* void search_for_isbn() { */
///*   system("clear"); */
///*   cin.clear(); */
///*   cin.igNore(1000, '\n'); */
///*   string isbn; */
///*   vector<book> books = lib.books(); */
///*   cout << "\n\nplease enter the isbn of the book\n\n\n"; */
///*   cout << "> "; */
///*   getline(cin, isbn); */
///*   bool found_isbn = isbn_was_found(isbn, books); */
///*   if (found_isbn) { */
///*     cout << "isbn was found\n"; */
///*     // calls screen in which chooses to check out */
///*   } else { */
///*     int try_again; */
///*     cout << "isbn not found\n"; */
///*     cout << "try again?\n"; */
///*     cout << "1. Yes\n"; */
///*     cout << "2. No\n\n\n"; */
///*     cout << "> "; */
///*     cin >> try_again; */
///*     if (try_again == 1) */
///*       return search_for_isbn(); */
///*     else */
///*       return search_screen(); */
///*   } */
///* } */
//
///* bool title_was_found(const string &t, const vector<book> &bv) { */
///*   auto found = find_if(bv.begin(), bv.end(), */
///*                        [t](const book &b) { return b.title() == t; }); */
///*   if (found != bv.end()) */
///*     return true; */
///*   else */
///*     return false; */
///* } */
///* bool author_was_found(const string &a, const vector<book> &bv) { */
///*   auto found = find_if(bv.begin(), bv.end(), */
///*                        [a](const book &b) { return b.author() == a; }); */
///*   if (found != bv.end()) */
///*     return true; */
///*   else */
///*     return false; */
///* } */
///* bool isbn_was_found(const string &i, const vector<book> &bv) { */
///*   auto found = find_if(bv.begin(), bv.end(), */
///*                        [i](const book &b) { return b.isbn() == i; }); */
///*   if (found != bv.end()) */
///*     return true; */
///*   else */
///*     return false; */
///* } */
