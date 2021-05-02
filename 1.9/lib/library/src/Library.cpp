#include "Library.h"
// member functions

Library::Library(string n):library_name_{n} {}
string Library::library_name()const {
	return this->library_name_;
}
vector<Book> Library::books()const {
	return books_;
}
vector<Patron> Library::patrons()const {
	return patrons_;
}
void Library::add_book_to_library(const Book &b) {
	books_.push_back(b);
}
void Library::add_patron_to_library(const Patron &p) {
	patrons_.push_back(p);
}
Library::Transaction::Transaction(Book bb, Patron pp)
	: transaction_book{bb}, transaction_patron{pp}, transaction_date{
	get_current_date()} {}
void Library::check_out_book(const Book &b, const Patron &p) {
	if (find_if(books_.begin(), books_.end(),
	[b](const Book &bf) {
	return b.isbn() == bf.isbn();
	}) !=
	books_.end() &&
	find_if(patrons_.begin(), patrons_.end(), [p](const Patron &pf) {
		return p.patron_name() == pf.patron_name() &&
		       p.identity_number() == pf.identity_number();
	}) != patrons_.end()) {
		if (!p.has_fee()) {
			transactions_.push_back(Transaction{b, p});
			cout << "Book checked out!\n";
		} else {
			error("You have a unpaid fee of ", p.fee());
		}
	} else if (find_if(books_.begin(), books_.end(), [b](const Book &bf) {
	return b.isbn() == bf.isbn();
	}) == books_.end()) {
		error("Book not found. Please try again\n");
	} else if (find_if(patrons_.begin(), patrons_.end(), [p](const Patron &pf) {
	return p.patron_name() == pf.patron_name() &&
		       p.identity_number() == pf.identity_number();
	}) == patrons_.end()) {
		error("Patron not found. Please try again\n");
	}
}

Book Library::Transaction::ret_book() const {
	return this->transaction_book;
}
Patron Library::Transaction::ret_patron() const {
	return this->transaction_patron;
}
Date Library::Transaction::ret_date() const {
	return this->transaction_date;
}

vector<Patron> Library::people_with_fees() {
	vector<Patron> people;
	for (auto it = patrons_.begin(); it != patrons_.end(); ++it) {
		if (it->has_fee())
			people.push_back(*it);
	}
	return people;
}

void Library::print_available_books() const {
	Library l=*this;
	sort(l.books_.begin(), l.books_.end(), [](const Book &b1, const Book &b2) {
		return b1.title() < b2.title();
	});
	for (auto it = books_.begin(); it != books_.end(); ++it)
		cout << *it;
}

void Library::print_transactions() const {
	for (auto it = transactions_.begin(); it != transactions_.end(); ++it)
		cout << *it;
	cout << endl;
}

// helper functions
ostream &operator<<(ostream &os, const Library::Transaction &t) {
	return os << "Date of transaction: " << t.ret_date() << "\n\n"
	       << "Book: " << t.ret_book() << "\n\n"
	       << "Solicited by: " << t.ret_patron() << "\n\n";
}

void read_books_from_file(const string &f, Library &library) {
	string name = f + ".in";
	ifstream in(name);
	string i, t, a, y, m, d, g;
	while (in.good()) {
		Book b = {};
		in >> i;
		if (!in)
			break;
		in >> t >> a >> y >> m >> d >> g;
		int ye = stoi(y);
		int tmpmonth = stoi(m);
		Month mo = static_cast<Month>(tmpmonth);
		int da = stoi(d);
		Date dt = Date{ye, mo, da};
		Genre gr = convert_string_to_genre(g);
		b = Book{i, t, a, dt, gr};
		library.add_book_to_library(b);
	}
}

