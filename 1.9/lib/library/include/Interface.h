#ifndef INTERFACE_H
#define INTERFACE_H

#include "Library.h"

void main_menu();
void search_screen();

bool title_was_found(const string &t, const vector<Book> &bv);
bool author_was_found(const string &a, const vector<Book> &bv);
bool isbn_was_found(const string &i, const vector<Book> &bv);

//Book find_book(const string )
Book sought_title(const string& title, const vector<Book> &books);
void search_for_title();
//void search_for_author();
//void search_for_isbn();
void search_patron();
void prompt_patron();
void prompt_check_out();
void make_patron();

Patron found_patron(const string &patron_name, const int patron_id, const vector<Patron>& patrons);
//Book found_author();
//Book found_isbn();

//
//void sort_by_genre();
//void user_information();


#endif // INTERFACE_H
