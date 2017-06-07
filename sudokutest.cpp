#include <iostream>
using namespace std;

typedef int Tablero[9][9];

void sudoku_print(Tablero t) {
	cout << "-------------------";
	cout << endl;
	for (int i = 0; i < 9; i++) {
		cout << "|";
		for (int j = 0; j < 9; j++) {
			if (t[i][j] == 0) {
				cout << " ";
			} else {
				cout << t[i][j];
			}
			cout << "|";
		}
		cout << endl;
		if (i == 8) {
			cout << "+-+-+-+-+-+-+-+-+-+";
		} else {
			cout << "-------------------";
		}
		cout << endl;
	}
}

bool sudoku_esCeldaVacia(Tablero t, int f, int c) {
	return t[f][c] == 0;
}

void sudoku_vaciarTablero(Tablero &t) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
			t[i][j] = 0;
		}
	}
}

int sudoku_nroDeCeldasVacias(Tablero t) {
  int total = 0;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (t[i][j] == 0) {
        total++;
      }
    }
  }
	return total;
}

int * primerCeldaVacia(Tablero t) {
  static int celda [2] = {-1,-1};
  bool primera = true;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (t[i][j] == 0 && primera == true) {
        celda[0] = i;
        celda[1] = j;
        primera = false;
      }
    }
  }
  return celda;
}

int sudoku_primerCeldaVaciaFila(Tablero t) {
	int *fila;
  fila = primerCeldaVacia(t);
  return fila[0];
}

int sudoku_primerCeldaVaciaColumna(Tablero t) {
	int *columna;
  columna = primerCeldaVacia(t);
  return columna[1];
}

int sudoku_valorEnCelda(Tablero t, int f, int c) {
	return t[f][c];
}

void sudoku_llenarCelda(Tablero& t, int f, int c, int v) {
	t[f][c] = v;
}

void sudoku_vaciarCelda(Tablero& t, int f, int c) {
	t[f][c] = 0;
}

bool sudoku_esTableroValido(Tablero t) {
  bool valido = true;
	for (int i = 0; i < 9; i++) {
	  for (int j = 0; j < 9; j++) {
	    if (t[i][j] > 9) {
	      valido = false;
	    }
	  }
	}
	return valido;
}

// start funciones auxiliares para esTableroParcialmenteResuelto

int cantidadRepetidos(int l[]){
	int result = 0;
	for (int i = 0; i < 9; i++){
		if (l[i] != 0){
			for (int j = 0; j < 9; j++){
				if (i != j && l[i] == l[j]){
					result++;
				}
			}
		}
	}
	return result;
}

bool sudoku_esFilaParcialmenteResuelto(Tablero t){
	int result = 0;
	for (int i = 0; i < 9; i++){
		result += cantidadRepetidos(t[i]);
	}
	return (result == 0);
}

bool sudoku_esColumnaParcialmenteResuelto(Tablero t){
	int result = 0;
	for (int j = 0; j < 9; j++){
		int subArray[9];
		for (int i = 0; i < 9; i++){
			subArray[i] = t[i][j];
		}
		result += cantidadRepetidos(subArray);
	}
	return (result == 0);
}

bool sudoku_sonRegionesParcialmenteResueltas(Tablero t) {
	int result = 0;
	for(int i = 0; i < 9; i = i + 3) {
		for(int j = 0; j < 9; j = j + 3) {
			int subArray[9];
			int pos = 0;
			for(int k = i; k < i + 3; k++) {
				for(int l = j; l < j + 3; l++) {
					subArray[pos] = t[k][l];
					pos++;
				}
			}
			result += cantidadRepetidos(subArray);
		}
	}
	return (result == 0);
}

bool sudoku_esTableroParcialmenteResuelto(Tablero t) {
	return (sudoku_esTableroValido(t) &&
          sudoku_esFilaParcialmenteResuelto(t) &&
          sudoku_esColumnaParcialmenteResuelto(t) &&
          sudoku_sonRegionesParcialmenteResueltas(t));
}

bool sudoku_noHayCeldasVacias(Tablero t) {
	int counter = 0;
	for(int i = 0; i < 9 && counter == 0; i++) {
		for(int j = 0; j < 9 && counter == 0; j++) {
			if(t[i][j] == 0) {
				counter++;
			}
		}
	}
	return counter == 0;
}

bool sudoku_esTableroTotalmenteResuelto(Tablero t) {
	return (sudoku_esTableroParcialmenteResuelto(t) && sudoku_noHayCeldasVacias(t));
}

bool sudoku_esSubTablero(Tablero t0, Tablero t1) {
	int esSubTablero = true;
	for(int i = 0; i < 9 && esSubTablero; i++){
		for(int j = 0; j < 9 && esSubTablero; j++){
			if(t0[i][j] != 0 && (t0[i][j] != t1[i][j])){
				esSubTablero = false;
			}
		}
	}
	return esSubTablero;
}

void copiarTablero(Tablero t, Tablero& s){
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			s[i][j] = t[i][j];
		}
	}
}

int main(int argc, char const *argv[]) {

  Tablero test1 = {{8,0,0,4,1,6,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0}};

  Tablero test =  {{8,3,5,4,1,6,9,2,7},
                  {2,9,6,8,5,7,4,3,1},
                  {4,1,7,2,9,3,6,5,8},
                  {5,6,9,1,3,4,7,8,2},
                  {1,2,3,6,7,8,5,4,9},
                  {7,4,8,5,2,9,1,6,3},
                  {6,5,2,7,8,1,3,9,4},
                  {9,8,1,3,4,5,2,7,6},
                  {3,7,4,9,6,2,8,1,5}};

  sudoku_print(test);
  cout << "hola" << endl;
  cout << sudoku_esCeldaVacia(test, 0, 0) << endl;
  cout << sudoku_esCeldaVacia(test, 8, 7) << endl;
  cout << sudoku_nroDeCeldasVacias(test) << endl;
  std::cout << "Es valido? " << sudoku_esTableroValido(test) << '\n';
  cout << "Primera celda vacia fila: " << sudoku_primerCeldaVaciaFila(test) << endl;
  cout << "Primera celda vacia columna: " << sudoku_primerCeldaVaciaColumna(test) << endl;
  std::cout << "Valor en celda " << sudoku_valorEnCelda(test,8,0) << '\n';
  std::cout << "Es Parcialmente resuelto? " << sudoku_esTableroParcialmenteResuelto(test) << '\n';
  std::cout << "Columna resuelta????" << sudoku_esColumnaParcialmenteResuelto(test) << '\n';
  std::cout << "Es totalmente resuelto?? " << sudoku_esTableroTotalmenteResuelto(test) << '\n';
  std::cout << "Es subtablero ? " << sudoku_esSubTablero(test1,test) << '\n';
  copiarTablero(test, test1);
  sudoku_vaciarTablero(test);
  sudoku_llenarCelda(test,5,3,4);
  sudoku_vaciarCelda(test1,5,3);
  sudoku_print(test);
  sudoku_print(test1);

  std::cout << "Es valido? " << sudoku_esTableroValido(test) << '\n';
  std::cout << "Es Parcialmente resuelto? " << sudoku_esTableroParcialmenteResuelto(test) << '\n';
  cout << sudoku_nroDeCeldasVacias(test) << endl;
  return 0;
}
