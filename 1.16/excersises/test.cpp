#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int numar_de_linii(const string &nume_fisier) {
  ifstream in(nume_fisier);
  int nr_linii = 0;
  string tmp;
  while (!in.eof() && getline(in, tmp)) // numarul de linii
    ++nr_linii;
  in.close();
  return nr_linii;
}
int numar_elemente(const string &nume_fisier) {

  ifstream in(nume_fisier);
  int tmp;
  int elemente_pe_linie = 0;
  while (!in.eof() && in >> tmp) // numarul de elemente
    ++elemente_pe_linie;
  in.close();
  return elemente_pe_linie;
}
int **matrice_dinamica(const string &nume_fisier) {
  ifstream in(nume_fisier);
  int **matr = 0;
  int h = numar_de_linii(nume_fisier);
  int w = numar_elemente(nume_fisier) / h;
  matr = new int *[h];

  for (int i = 0; i < h; i++) {
    matr[i] = new int[w];

    for (int j = 0; j < w; j++) {
      in >> matr[i][j];
    }
  }
  in.close();
  return matr;
}
int maxim(int **matr, int n, int m) {
  int max = matr[0][0];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; ++j)
      if (matr[i][j] > m)
        max = matr[i][j];
  return max;
}
int prod(int **matr, int n, int m) { // e iterativ, nu recursiv. nu aveam timp
  int p = 1;
  for (int i = 0; i != n; ++i)
    for (int j = 0; j != m; ++j)
      if (matr[i][j] < 0)
        p *= matr[i][j];
  return p;
}

int main() {
  string nume = "matice.in";
  int **mm = matrice_dinamica(nume);
  int n = numar_de_linii(nume);
  int m = numar_elemente(nume) / n;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != m; ++j)
      cout << mm[i][j] << ' ';
    cout << '\n';
  }
  cout << maxim(mm, n, m);
  cout << prod(mm, n, m);
}
