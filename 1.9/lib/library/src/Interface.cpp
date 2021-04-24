#include "Interface.h"
Library lib;

void main_menu() {
	Book b{"113-32332-12332-X", "The Magic Mountain", "Thomas Mann",
	       Date(1989, Month::apr, 23), Genre::nonfiction};
	lib.add_book_to_library(b);
	do {
		int choice;
		cout<<"\n\n"<<get_current_date()<<"  ";
		cout<<" Welcome to the "<<lib.library_name()<<"\n\n";
		cout<<"1. View available books\n";
		cout<<"2. User information\n";
		cout<<"3. Exit\n\n\n";
		cout<<"Enter the number corresponding to the desired operation\n";
		cout<<"> ";
		cin>>choice;
		if(choice==3)
			return;
		if(choice == 1) {
			search_screen();
			break;
		}
//	if(choice==2){
//		user_information();
//	}
	} while(true);
}
void search_screen() {
	do {
		system("clear");
		int choice=0;
		cout<<"\n\n";
		cout<<"1. List available books\n";
		cout<<"2. Search for book by name\n";
		cout<<"3. Search for author\n";
		cout<<"4. Search for ISBN\n";
		cout<<"5. Go back to main menu\n\n\n";
		cout<<"> ";
		cin.clear();
		cin>>choice;
		if(choice == 1) {
			int choice_print_books=0;
			system("clear");
			lib.print_available_books();
			cout<<"\n\nPress 1 to go back\n\n\n";
			cout<<"> ";
			cin.clear();
			cin>>choice_print_books;
			if(choice_print_books==1)
				return search_screen();
		}
		if(choice==2) {
			system("clear");
			string title;
			cout<<"\n\nPress 1 to go back\n";
			cout<<"\n\nPlease enter the title of the book\n\n\n";
			cout<<"> ";
			cin.clear();
			while(cin>>title) {
				if(title=="1")
					return search_screen();
				else{
						if(book_title_was_found(title)){
							cout<<"Book was found\n";
						}
						else{
							cout<<"Book not found\n\n\n";
						}
				}
			}
		}
		if(choice == 3) {
			system("clear");
			string author;
			cout<<"\n\nPress 1 to go back\n";
			cout<<"\n\nPlease enter the name of the author\n\n\n";
			cout<<"> ";
			cin.clear();
			while(getline(cin, author)) {
				if(author=="1")
					return search_screen();
				}
			}
			if(choice==4) {
				system("clear");
				string ISBN;
				cout<<"\n\nPress 1 to go back\n";
				cout<<"\n\nPlease enter the book ISBN\n\n\n";
				cout<<"> ";
				while(getline(cin, ISBN)) {
					if(ISBN=="1")
						return search_screen();
					return search_for_isbn(ISBN);
				}
			}
			if(choice==5)
				return main_menu();
		}
		while(true);
	}



	bool book_title_was_found(const string &t) {
		auto found=find_if(lib.books().begin(), lib.books().end(), [t](const Book& b) {
			return b.title()==t;
		});
		if(found!=lib.books().end())
			return true;
		else return false;
	}
	void search_for_author(const string &a) {
		auto found=find_if(lib.books().begin(), lib.books().end(), [a](const Book& b) {
			return b.author()==a;
		});
//	if(found!=lib.books().end())
		cout<<"Author "<<*found<<" was found!\n";
	}
	void search_for_isbn(const string &i) {
		auto found=find_if(lib.books().begin(), lib.books().end(), [i](const Book& b) {
			return b.author()==i;
		});
		if(found!=lib.books().end())
			cout<<"ISBN"<<*found<<" was found!\n";
	}
