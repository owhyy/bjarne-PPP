#include "std_lib_facilites.h"
namespace np {
class Name_pairs {
public:
  void read_names();
  void read_ages();
  vector<string> get_name() const { return name; }
  vector<double> get_age() const { return age; }
  vector<string>::size_type Size() const { return name.size(); }
  void sort();

private:
  vector<string> name;
  vector<double> age;
};

void Name_pairs::read_names() {
  string s;
  cout << "Name input. Enter end if you are done with inputing names\n";
  cout << "Please enter a name:\n";
  while (cin >> s) {
    cout << "Please enter another name:\n";
    if (s == "end")
      break;
    name.push_back(s);
  }
}
void Name_pairs::read_ages() {
  for (int i = 0; i != name.size(); ++i) {
    double a;
    cout << "Enter " << name[i] << "'s age:\n";
    cin >> a;
    if (a > 0 && a < 100)
      age.push_back(a);
  }
}
void Name_pairs::sort() {
  vector<string> sortedname(name);
  vector<double> sortedage;
  std::sort(name.begin(), name.end());
  for (string s : name) {
    for (int i = 0; i != name.size(); ++i)
      if (sortedname[i] == s)
        sortedage.push_back(age[i]);
  }
  age = sortedage;
}
void operator<<(ostream &os, const Name_pairs &np) {
  for (int i = 0; i != np.Size(); ++i)
    os << np.get_name()[i] << " is " << np.get_age()[i] << " years old\n";
}
bool operator==(const Name_pairs &a, const Name_pairs &b) {
  return a.get_name() == b.get_name() && a.get_age() == b.get_age();
}
bool operator!=(const Name_pairs &a, const Name_pairs &b) { return !(a == b); }

}; // namespace np
