#include "../GUI/GUI.h"
#include "../GUI/Graph.h"
#include "../GUI/Window.h"
#include <algorithm>
using namespace Graph_lib;

void string_transformation(string &s) { // converts from string to dobule,
                                        // removing 2 all except 2 decimals
  string::iterator it = s.begin();
  int pos_dot = 0;
  for (auto i : s) {
    pos_dot++;
    if (i == '.') {
      it += pos_dot;
      s.erase(it + 2, s.end());
    }
  }
}

enum class Valuta {
  USD = 0,
  EUR,
  CHF,
  JPY,
  GBP,
  AUD

};

struct My_window : Graph_lib::Window {
  My_window(Point xy, int w, int h, const string &t, ifstream &ifs);

private:
  // buttons
  Menu give_currency_menu;
  Menu take_currency_menu;

  In_box give_currency;
  Out_box take_currency;

  // other objects
  double currencies[6][6];
  double currency_rate;
  double amount;
  Valuta give_val;
  Valuta take_val;

  // actions
  void read_file(ifstream &ifs);

  void give_usd_pressed();
  void give_eur_pressed();
  void give_chf_pressed();
  void give_jpy_pressed();
  void give_gbp_pressed();
  void give_aud_pressed();

  void take_usd_pressed();
  void take_eur_pressed();
  void take_chf_pressed();
  void take_jpy_pressed();
  void take_gbp_pressed();
  void take_aud_pressed();

  void assign_currency();
  void convert_and_put();
};

My_window::My_window(Point xy, int w, int h, const string &t, ifstream &ifs)
    : Window{xy, w, h, t},
      give_currency_menu(Point{150, 100}, 50, 30, Menu::horizontal, "From: "),
      give_currency(Point{150, 70}, 300, 30, "From: "),
      take_currency_menu(Point{150, 300}, 50, 30, Menu::horizontal, "To: "),
      take_currency(Point{150, 270}, 300, 30, "To: ") {
  give_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "USD", [](Address, Address pw) {
                   return reference_to<My_window>(pw).give_usd_pressed();
                 }});
  give_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "EUR", [](Address, Address pw) {
                   return reference_to<My_window>(pw).give_eur_pressed();
                 }});
  give_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "CHF", [](Address, Address pw) {
                   return reference_to<My_window>(pw).give_chf_pressed();
                 }});
  give_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "JPY", [](Address, Address pw) {
                   return reference_to<My_window>(pw).give_jpy_pressed();
                 }});
  give_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "GBP", [](Address, Address pw) {
                   return reference_to<My_window>(pw).give_gbp_pressed();
                 }});
  give_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "AUD", [](Address, Address pw) {
                   return reference_to<My_window>(pw).give_aud_pressed();
                 }});

  take_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "USD", [](Address, Address pw) {
                   return reference_to<My_window>(pw).take_usd_pressed();
                 }});
  take_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "EUR", [](Address, Address pw) {
                   return reference_to<My_window>(pw).take_eur_pressed();
                 }});
  take_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "CHF", [](Address, Address pw) {
                   return reference_to<My_window>(pw).take_chf_pressed();
                 }});
  take_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "JPY", [](Address, Address pw) {
                   return reference_to<My_window>(pw).take_jpy_pressed();
                 }});
  take_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "GBP", [](Address, Address pw) {
                   return reference_to<My_window>(pw).take_gbp_pressed();
                 }});
  take_currency_menu.attach(
      new Button{Point{0, 0}, 0, 0, "AUD", [](Address, Address pw) {
                   return reference_to<My_window>(pw).take_aud_pressed();
                 }});

  attach(give_currency_menu);
  attach(give_currency);
  attach(take_currency_menu);
  attach(take_currency);
  read_file(ifs);
}

void My_window::read_file(ifstream &ifs) { // reads into 2d array from file
  double n;
  for (int i = 0; i != 6; ++i)
    for (int j = 0; j != 6; ++j) {
      ifs >> n;
      currencies[i][j] = n;
    }
}

void My_window::assign_currency() { // assigns currency calling
                                    // string_transformation
  string tmp_ampt = give_currency.get_string();
  string_transformation(tmp_ampt);
  amount = stoi(tmp_ampt);
}

void My_window::convert_and_put() { // converts Valuta to int
  int give_val_int = (int)give_val;
  int take_val_int = (int)take_val;
  double tmp_amt = amount;
  amount *= currencies[give_val_int][take_val_int];

  string tmp_ampt = to_string(amount); // temp storage
  string_transformation(tmp_ampt);
  take_currency.put(tmp_ampt);
  amount = tmp_amt; // reset amount
}

// give
void My_window::give_usd_pressed() {
  give_val = Valuta::USD;
  assign_currency();
}
void My_window::give_eur_pressed() {
  give_val = Valuta::EUR;
  assign_currency();
}
void My_window::give_chf_pressed() {
  give_val = Valuta::CHF;
  assign_currency();
}
void My_window::give_jpy_pressed() {
  give_val = Valuta::JPY;
  assign_currency();
}
void My_window::give_gbp_pressed() {
  give_val = Valuta::GBP;
  assign_currency();
}
void My_window::give_aud_pressed() {
  give_val = Valuta::AUD;
  assign_currency();
}

// take
void My_window::take_usd_pressed() {
  take_val = Valuta::USD;
  convert_and_put();
}
void My_window::take_eur_pressed() {
  take_val = Valuta::EUR;
  int give_val_int = (int)give_val;
  convert_and_put();
}
void My_window::take_chf_pressed() {
  take_val = Valuta::CHF;
  int give_val_int = (int)give_val;
  convert_and_put();
}
void My_window::take_jpy_pressed() {
  take_val = Valuta::JPY;
  int give_val_int = (int)give_val;
  convert_and_put();
}
void My_window::take_gbp_pressed() {
  take_val = Valuta::GBP;
  int give_val_int = (int)give_val;
  convert_and_put();
}
void My_window::take_aud_pressed() {
  take_val = Valuta::AUD;
  int give_val_int = (int)give_val;
  convert_and_put();
}

int main() {
  ifstream file("currencies.txt");
  My_window win{Point{100, 100}, 600, 400, "My window", file};
  return gui_main();
}
