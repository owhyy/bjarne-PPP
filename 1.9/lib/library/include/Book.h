#ifndef BOOK_H
#define BOOK_H

#include "Date.h"
enum class Genre {
  fiction,
  nonfiction,
  periodical,
  biography,
  children,
  unknown
};
class Book {
public:
  Book(const string &i, const string &t, const string &a, const Date &d,const Genre &gg);
  Book() {}
  string isbn() const;
  string title() const;
  string author() const;
  Date copyright_date() const;
  bool status() const;
  int genre() const;
  bool operator==(const Book &rhs);
  bool operator!=(const Book &rhs);
  void set_isbn(const string &i);
  void set_title(const string &t);
  void set_author_name(const string &n);
  void set_genre(const Genre gg);
  void set_copyright_date(const Date d);

private:
  string isbn_;
  string title_;
  string author_;
  Date copyright_date_;
  bool is_checked_out_ = 0;
  Genre genre_;
};
bool is_book(const string &i);
ostream &operator<<(ostream &os, const Book &b);
string return_genre_as_string(int g);
string return_status_as_string(int s);
Genre convert_string_to_genre(const string &s);


#endif // BOOK_H
