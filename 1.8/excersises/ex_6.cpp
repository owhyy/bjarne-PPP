#include "std_lib_facilites.h"
void ex_6() {
  vector<string> names;
  vector<int> ages;
  string name;
  uint age;
  cout << "Please enter a name:\n";
  while (cin >> name) {
    names.push_back(name);
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    cout << "Please enter the age of " << name << '\n';
    cin >> age;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    ages.push_back(age);
    cout << "Please enter a name:\n";
  }
  cout<<"Unsorted names:\n";
  for (int i = 0; i != names.size(); ++i)
    cout << names[i] << ' ' << ages[i] << '\n';
  cout<<'\n';
  vector<string> namecp(names.begin(), names.end());
  vector<int> agecp;
  sort(names.begin(), names.end());
  for (string nm : names) {
    for (int i = 0; i != namecp.size(); ++i)
      if (nm == namecp[i])
        agecp.push_back(ages[i]);
  }
  cout<<"Sorted names:\n";
  for (int i = 0; i != names.size(); ++i)
    cout << names[i] << ' ' << agecp[i] << '\n';
}
