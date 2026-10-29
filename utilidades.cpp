// ==========================================
// Archivo: utilidades.cpp
// Propósito: Funciones de interfaz, impresión y validación.
// ==========================================

#include "algebra.h"

void imprimirMatriz(const Matriz &m) {
  std::cout << "\n";
  for (const auto &fila : m) {
    std::cout << "[ ";
    for (const auto &elemento : fila) {
      std::cout << std::setw(8) << std::fixed << std::setprecision(3)
                << elemento << " ";
    }
    std::cout << "]\n";
  }
  std::cout << "\n";
}

double leerNumeroSeguro(const std::string &mensaje) {
  double valor;
  while (true) {
    std::cout << mensaje;
    if (std::cin >> valor) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Error: Entrada invalida. Por favor ingrese un numero.\n";
    }
  }
  return valor;
}

void pausarYLimpiar() {
  std::cout << "\nPresione ENTER para continuar...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();

#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

Matriz leerMatriz(const std::string &nombreMatriz) {
  std::cout << "\n--- Ingresando " << nombreMatriz << " ---\n";
  int filas = (int)leerNumeroSeguro("Ingrese el numero de filas: ");
  int columnas = (int)leerNumeroSeguro("Ingrese el numero de columnas: ");

  Matriz m(filas, std::vector<double>(columnas, 0.0));

  std::cout << "Ingrese los valores celda por celda:\n";
  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      std::string mensaje = "Fila " + std::to_string(i + 1) + ", Columna " +
                            std::to_string(j + 1) + ": ";
      m[i][j] = leerNumeroSeguro(mensaje);
    }
  }
  return m;
}
