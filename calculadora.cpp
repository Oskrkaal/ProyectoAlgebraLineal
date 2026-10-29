// ==========================================
// Archivo: calculadora.cpp
// Propósito: Implementación del Módulo A (Operaciones Matemáticas y Sistemas)
// ==========================================

#include "algebra.h"

// ------------------------------------------
// OPERACIONES BÁSICAS (Suma y Resta)
// ------------------------------------------

Matriz sumarMatrices(const Matriz &A, const Matriz &B) {
  if (A.empty() || B.empty() || A.size() != B.size() ||
      A[0].size() != B[0].size()) {
    std::cout << "Error: Las dimensiones de las matrices no son idénticas para "
                 "la suma.\n";
    return Matriz();
  }
  int filas = A.size();
  int columnas = A[0].size();
  Matriz C(filas, std::vector<double>(columnas, 0.0));
  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  return C;
}

Matriz restarMatrices(const Matriz &A, const Matriz &B) {
  if (A.empty() || B.empty() || A.size() != B.size() ||
      A[0].size() != B[0].size()) {
    std::cout << "Error: Las dimensiones de las matrices no son idénticas para "
                 "la resta.\n";
    return Matriz();
  }
  int filas = A.size();
  int columnas = A[0].size();
  Matriz C(filas, std::vector<double>(columnas, 0.0));
  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
  return C;
}

// ------------------------------------------
// OPERACIONES AVANZADAS (Multiplicación)
// ------------------------------------------

Matriz multiplicarMatrices(const Matriz &A, const Matriz &B) {
  // Verificación de multiplicabilidad
  if (A.empty() || B.empty() || A[0].size() != B.size()) {
    std::cout << "Error: El numero de columnas de A debe ser igual al numero "
                 "de filas de B.\n";
    return Matriz();
  }

  int filasA = A.size();
  int columnasA = A[0].size();
  int columnasB = B[0].size();

  // Matriz resultante C tendrá dimensiones (filasA x columnasB)
  Matriz C(filasA, std::vector<double>(columnasB, 0.0));

  // Algoritmo de multiplicación
  for (int i = 0; i < filasA; ++i) {
    for (int j = 0; j < columnasB; ++j) {
      for (int k = 0; k < columnasA; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

// ------------------------------------------
// RESOLUCIÓN DE SISTEMAS Y MATRIZ INVERSA
// ------------------------------------------

// Función auxiliar para pivoteo parcial (evita división por cero)
bool pivotear(Matriz &sistema, int filaActual, int colActual) {
  int maxFila = filaActual;
  for (size_t i = filaActual + 1; i < sistema.size(); ++i) {
    if (std::abs(sistema[i][colActual]) >
        std::abs(sistema[maxFila][colActual])) {
      maxFila = i;
    }
  }
  if (std::abs(sistema[maxFila][colActual]) < 1e-9) {
    return false; // Columna de ceros, no se puede pivotear
  }
  if (maxFila != filaActual) {
    std::swap(sistema[filaActual], sistema[maxFila]);
  }
  return true;
}

void resolverGauss(Matriz sistema) {
  if (sistema.empty())
    return;
  int n = sistema.size();
  int m = sistema[0].size();

  for (int i = 0; i < n; ++i) {
    if (!pivotear(sistema, i, i))
      continue;
    for (int k = i + 1; k < n; ++k) {
      double factor = sistema[k][i] / sistema[i][i];
      for (int j = i; j < m; ++j) {
        sistema[k][j] -= factor * sistema[i][j];
      }
    }
  }

  std::cout << "\nMatriz Escalonada (Gauss):\n";
  imprimirMatriz(sistema);

  std::vector<double> soluciones(n, 0.0);
  for (int i = n - 1; i >= 0; --i) {
    if (std::abs(sistema[i][i]) < 1e-9) {
      if (std::abs(sistema[i][m - 1]) > 1e-9) {
        std::cout << "El sistema es Incompatible (No tiene solucion).\n";
        return;
      } else {
        std::cout << "El sistema es Compatible Indeterminado (Infinitas "
                     "soluciones).\n";
        return;
      }
    }
    soluciones[i] = sistema[i][m - 1];
    for (int j = i + 1; j < n; ++j)
      soluciones[i] -= sistema[i][j] * soluciones[j];
    soluciones[i] /= sistema[i][i];
  }

  std::cout << "Solucion unica (Sistema Compatible Determinado):\n";
  for (int i = 0; i < n; ++i) {
    std::cout << "X" << i + 1 << " = " << soluciones[i] << "\n";
  }
}

void resolverGaussJordan(Matriz sistema) {
  if (sistema.empty())
    return;
  int n = sistema.size();
  int m = sistema[0].size();

  for (int i = 0; i < n; ++i) {
    if (!pivotear(sistema, i, i))
      continue;
    double pivote = sistema[i][i];
    for (int j = i; j < m; ++j)
      sistema[i][j] /= pivote;
    for (int k = 0; k < n; ++k) {
      if (k != i) {
        double factor = sistema[k][i];
        for (int j = i; j < m; ++j)
          sistema[k][j] -= factor * sistema[i][j];
      }
    }
  }

  std::cout << "\nMatriz Escalonada Reducida (Gauss-Jordan):\n";
  imprimirMatriz(sistema);

  for (int i = 0; i < n; ++i) {
    bool filaCeros = true;
    for (int j = 0; j < m - 1; ++j) {
      if (std::abs(sistema[i][j]) > 1e-9)
        filaCeros = false;
    }
    if (filaCeros && std::abs(sistema[i][m - 1]) > 1e-9) {
      std::cout << "El sistema es Incompatible (No tiene solucion).\n";
      return;
    }
  }

  std::cout << "Solucion directa:\n";
  for (int i = 0; i < n; ++i)
    std::cout << "X" << i + 1 << " = " << sistema[i][m - 1] << "\n";
}

Matriz calcularInversa(Matriz A) {
  // La matriz debe ser cuadrada
  if (A.empty() || A.size() != A[0].size()) {
    std::cout
        << "Error: La matriz debe ser cuadrada para calcular su inversa.\n";
    return Matriz();
  }

  int n = A.size();
  // 1. Construir la matriz aumentada [A | I]
  Matriz aug(n, std::vector<double>(2 * n, 0.0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      aug[i][j] = A[i][j]; // Lado izquierdo (A)
    }
    aug[i][n + i] = 1.0; // Lado derecho (Identidad)
  }

  // 2. Aplicar Gauss-Jordan sobre la matriz aumentada
  for (int i = 0; i < n; ++i) {
    if (!pivotear(aug, i, i)) {
      // Si el pivote es 0 y no se puede intercambiar, el determinante es 0.
      std::cout << "Error: La matriz es singular (det = 0) o no hay pivote "
                   "valido. No tiene inversa.\n";
      return Matriz();
    }

    double pivote = aug[i][i];
    for (int j = i; j < 2 * n; ++j) {
      aug[i][j] /= pivote;
    }

    for (int k = 0; k < n; ++k) {
      if (k != i) {
        double factor = aug[k][i];
        for (int j = i; j < 2 * n; ++j) {
          aug[k][j] -= factor * aug[i][j];
        }
      }
    }
  }

  // 3. Extraer la matriz resultante del lado derecho (Inversa)
  Matriz inversa(n, std::vector<double>(n, 0.0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      inversa[i][j] = aug[i][n + j];
    }
  }

  return inversa;
}
