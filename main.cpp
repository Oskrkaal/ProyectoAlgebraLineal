// ==========================================
// Archivo: main.cpp
// Propósito: Punto de entrada y Menú Principal.
// ==========================================

#include "algebra.h"

int main() {
  int opcion = 0;

  do {
    std::cout << "====================================================\n";
    std::cout << " CALCULADORA Y GENERADOR DE EJERCICIOS DE ALGEBRA \n";
    std::cout << "====================================================\n";
    std::cout << "1. MODULO CALCULADORA\n";
    std::cout << "   1.1. Resolver Sistema (Gauss)\n";
    std::cout << "   1.2. Resolver Sistema (Gauss-Jordan)\n";
    std::cout << "   1.3. Suma de Matrices\n";
    std::cout << "   1.4. Resta de Matrices\n";
    std::cout << "   1.5. Multiplicacion de Matrices\n";
    std::cout << "   1.6. Matriz Inversa\n";
    std::cout << "2. MODULO GENERADOR DE EJERCICIOS\n";
    std::cout << "   2.1. Practica de Sistemas\n";
    std::cout << "   2.2. Practica de Operaciones\n";
    std::cout << "3. SALIR\n";
    std::cout << "====================================================\n";

    opcion = (int)leerNumeroSeguro(
        "Ingrese una opcion numerica (Ej: 11 para 1.1, 21 para 2.1): ");

    switch (opcion) {
    case 11: {
      std::cout << "\n*** METODO DE GAUSS ***\n";
      Matriz A = leerMatriz("Matriz Aumentada");
      resolverGauss(A);
      break;
    }
    case 12: {
      std::cout << "\n*** METODO DE GAUSS-JORDAN ***\n";
      Matriz A = leerMatriz("Matriz Aumentada");
      resolverGaussJordan(A);
      break;
    }
    case 13: {
      std::cout << "\n*** SUMA DE MATRICES ***\n";
      Matriz A = leerMatriz("Matriz A");
      Matriz B = leerMatriz("Matriz B");
      Matriz C = sumarMatrices(A, B);
      if (!C.empty()) {
        std::cout << "\nResultado de A + B:";
        imprimirMatriz(C);
      }
      break;
    }
    case 14: {
      std::cout << "\n*** RESTA DE MATRICES ***\n";
      Matriz A = leerMatriz("Matriz A");
      Matriz B = leerMatriz("Matriz B");
      Matriz C = restarMatrices(A, B);
      if (!C.empty()) {
        std::cout << "\nResultado de A - B:";
        imprimirMatriz(C);
      }
      break;
    }
    case 15: {
      std::cout << "\n*** MULTIPLICACION DE MATRICES ***\n";
      Matriz A = leerMatriz("Matriz A");
      Matriz B = leerMatriz("Matriz B");
      Matriz C = multiplicarMatrices(A, B);
      if (!C.empty()) {
        std::cout << "\nResultado de A * B:";
        imprimirMatriz(C);
      }
      break;
    }
    case 16: {
      std::cout << "\n*** MATRIZ INVERSA ***\n";
      Matriz A = leerMatriz("Matriz Cuadrada A");
      Matriz inversa = calcularInversa(A);
      if (!inversa.empty()) {
        std::cout << "\nInversa de la matriz A:";
        imprimirMatriz(inversa);
      }
      break;
    }
    case 21:
      iniciarPracticaSistemas();
      break;
    case 22:
      iniciarPracticaOperaciones();
      break;
    case 3:
      std::cout << "Saliendo del sistema. !Exitos en el proyecto!\n";
      break;
    default:
      std::cout << "Opcion no valida. Verifique el formato ingresado.\n";
      break;
    }

    if (opcion != 3)
      pausarYLimpiar();

  } while (opcion != 3);

  return 0;
}
