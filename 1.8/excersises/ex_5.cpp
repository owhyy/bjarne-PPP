#include "std_lib_facilites.h"
void ex_5() {
  vector<string> names;
  vector<int> ages;
  string name;
  uint age;
  for (int i = 0; i != 5; ++i) {
    cout << "Please enter a name:\n";
    cin >> name;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    names.push_back(name);
    cout << "Please enter " << name << "'s age:\n";
    cin >> age;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    ages.push_back(age);
  }
  cout << "Unsorted names:\n";
  for (int i = 0; i != 5; ++i)
    cout << names[i] << ' ' << ages[i] << '\n';
  cout << '\n';
  vector<string> namecp(names.begin(), names.end());
  vector<int> agecp;
  sort(names.begin(), names.end());
  for (string nm : names) {
    for (int i = 0; i != namecp.size(); ++i)
      if (nm == namecp[i])
        agecp.push_back(ages[i]);
  }
  cout << "Sorted names:\n";
  for (int i = 0; i != 5; ++i)
    cout << names[i] << ' ' << agecp[i] << '\n';
}
