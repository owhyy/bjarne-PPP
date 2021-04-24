#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Date.h"
#include "Patron.h"
class Library {
public:
	Library(){}
	Library(string n);
	string library_name()const;
	vector<Book> books()const;
	vector<Patron> patrons()const;
  void add_book_to_library(const Book &b);
  void add_patron_to_library(const Patron &p);
  void check_out_book(const Book &b, const Patron &p);
  vector<Patron> people_with_fees();
  void print_available_books() const;
  void print_transactions() const;
  struct Transaction {
  Book transaction_book;
  Patron transaction_patron;
  Date transaction_date;
  Transaction(Book bb, Patron pp);
  Transaction() {}
  Book ret_book() const;
  Patron ret_patron() const;
  Date ret_date() const;
  };

private:
	string library_name_;
  vector<Book> books_;
  vector<Patron> patrons_;
  vector<Transaction> transactions_;
};

void read_books_from_file(const string &f, Library &library);
ostream &operator<<(ostream &os, const Library::Transaction &t);


#endif // LIBRARY_H
