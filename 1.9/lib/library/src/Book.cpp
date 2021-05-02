
#include "Book.h"
// member functions
Book::Book(const string &i, const string &t, const string &a, const Date &d,
           const Genre &g)
    : isbn_{i}, title_{t}, author_{a}, copyright_date_{d}, genre_{g} {
  if (!is_book(i))
    error("Invalid book");
}
Book::Book(const string& t){title_=t;}
string Book::isbn() const { return isbn_; }
string Book::title() const { return title_; }
string Book::author() const { return author_; }
Date Book::copyright_date() const { return copyright_date_; }
bool Book::status() const { return is_checked_out_; }
int Book::genre() const { return int(genre_); }
bool Book::operator==(const Book &rhs) { return this->isbn_ == rhs.isbn_; };
bool Book::operator!=(const Book &rhs) { return this->isbn_ != rhs.isbn_; };
void Book::set_isbn(const string &i) { this->isbn_ = i; }
void Book::set_title(const string &t) { this->title_ = t; }
void Book::set_author_name(const string &n) { this->author_ = n; }
void Book::set_genre(const Genre gg) { this->genre_ = gg; }
void Book::set_copyright_date(const Date d) { this->copyright_date_ = d; }
void Book::check_out(){is_checked_out_=true;}
// helper functions
bool is_book(const string &s) {
  auto last = s.find_last_of('-');
  string first_till_third = s.substr(0, last);
  string third_till_last = s.substr(last, 0 - last);
  uint cnt =
      count_if(s.begin(), s.end(), [](const char c) { return c == '-'; });
  first_till_third.erase(remove_if(first_till_third.begin(),
                                   first_till_third.end(),
                                   [](const char c) { return c == '-'; }),
                         first_till_third.end());
  third_till_last.erase(remove_if(third_till_last.begin(),
                                  third_till_last.end(),
                                  [](const char c) { return c == '-'; }),
                        third_till_last.end());
  if (cnt != 3)
    return 0;
  for (auto it = first_till_third.begin(); it != first_till_third.end(); ++it)
    if (!isdigit(*it)) {
      cout << *it << " not digit\n";
      return 0;
    }
  for (auto it = third_till_last.begin(); it != third_till_last.end(); ++it) {
    if (!isalpha(*it)) {
      return 0;
    }
  }
  return 1;
}

ostream &operator<<(ostream &os, const Book &b) {
  return os << b.title() << '\n'
            << b.isbn() << '\n'
            << b.author() << '\n'
            << return_genre_as_string(b.genre())<<'\n'
            << return_status_as_string(b.status())<<"\n\n";
}

string return_genre_as_string(int g) {
  string genre;
  switch (g) {
  case 0:
    genre = "Fiction";
    break;
  case 1:
    genre = "Nonfiction";
    break;
  case 2:
    genre = "Periodical";
    break;
  case 3:
    genre = "Biography";
    break;
  case 4:
    genre = "Children";
    break;
  default:
    genre = "Unknown";
    break;
  }
  return genre;
}
string return_status_as_string(bool s) {
  return s ? "Checked in" : "Not checked in";
}

Genre convert_string_to_genre(const string &s) {
  if (s == "Fiction")
    return Genre::fiction;
  else if (s == "Nonfiction")
    return Genre::nonfiction;
  else if (s == "Periodical")
    return Genre::periodical;
  else if (s == "Biography")
    return Genre::biography;
  else if (s == "Children")
    return Genre::children;
  else
    return Genre::unknown;
}
