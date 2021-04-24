#ifndef INTERFACE_H
#define INTERFACE_H

#include "Library.h"
void main_menu();
void search_screen();
void print_books_alphabetically();
	bool book_title_was_found(const string &t);
void search_for_author(const string &a);
void search_for_isbn(const string &i);
void sort_by_genre();
void user_information();


#endif // INTERFACE_H
