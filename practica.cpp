// ==========================================
// Archivo: practica.cpp
// Propósito: Implementación del Módulo B (Generador de Ejercicios)
// ==========================================

#include "algebra.h"
#include <cstdlib>
#include <ctime>
#include <random> // [Dev]: Agregado para usar generadores de números modernos (C++11/17)

// Inicializador estático de la semilla aleatoria para métodos legacy
struct InicializadorRandom {
  InicializadorRandom() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
  }
} initRand;

// Genera una matriz con valores aleatorios enteros en un rango controlado
Matriz generarMatrizAleatoria(int filas, int columnas, int min, int max) {
  Matriz m(filas, std::vector<double>(columnas, 0.0));
  for (int i = 0; i < filas; ++i) {
    for (int j = 0; j < columnas; ++j) {
      m[i][j] = min + (std::rand() % (max - min + 1));
    }
  }
  return m;
}

// Evalúa precisión celda a celda usando un margen de tolerancia
bool evaluarRespuestaEstudiante(const Matriz &calculada,
                                const Matriz &estudiante) {
  if (calculada.size() != estudiante.size() ||
      calculada[0].size() != estudiante[0].size()) {
    return false;
  }

  for (size_t i = 0; i < calculada.size(); ++i) {
    for (size_t j = 0; j < calculada[0].size(); ++j) {
      // Tolerancia de 0.01 para absorber diferencias de redondeo
      if (std::abs(calculada[i][j] - estudiante[i][j]) > 0.01) {
        return false;
      }
    }
  }
  return true;
}

// [Dev]: Función auxiliar silenciosa para resolver el sistema internamente sin
// imprimir en consola. Devuelve un vector vacío si la matriz es singular (no
// tiene solución única).
std::vector<double> resolverSistemaSilencioso(Matriz A, std::vector<double> b) {
  int n = A.size();
  Matriz aug(n, std::vector<double>(n + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      aug[i][j] = A[i][j];
    aug[i][n] = b[i];
  }

  // Pivoteo y eliminación de Gauss-Jordan
  for (int i = 0; i < n; ++i) {
    int maxRow = i;
    for (int k = i + 1; k < n; ++k) {
      if (std::abs(aug[k][i]) > std::abs(aug[maxRow][i])) {
        maxRow = k;
      }
    }

    // Si el pivote máximo es cercano a 0, el sistema es singular
    if (std::abs(aug[maxRow][i]) < 1e-9)
      return {};

    std::swap(aug[i], aug[maxRow]);
    double pivote = aug[i][i];
    for (int j = i; j <= n; ++j)
      aug[i][j] /= pivote;

    for (int k = 0; k < n; ++k) {
      if (k != i) {
        double factor = aug[k][i];
        for (int j = i; j <= n; ++j)
          aug[k][j] -= factor * aug[i][j];
      }
    }
  }

  std::vector<double> solucion(n);
  for (int i = 0; i < n; ++i)
    solucion[i] = aug[i][n];
  return solucion;
}

// Implementación del Requerimiento 2.2: Práctica de Operaciones Matriciales
void iniciarPracticaOperaciones() {
  std::cout << "\n*** PRACTICA DE OPERACIONES MATRICIALES ***\n";

  int dim = 0;
  while (dim != 2 && dim != 3) {
    dim = (int)leerNumeroSeguro(
        "Ingrese la dimension para la practica (2 para 2x2, 3 para 3x3): ");
  }

  Matriz A = generarMatrizAleatoria(dim, dim, -9, 9);
  Matriz B = generarMatrizAleatoria(dim, dim, -9, 9);
  Matriz resultadoCalculado;

  int operacion = std::rand() % 2;
  std::string operadorStr;

  if (operacion == 0) {
    operadorStr = "SUMA (A + B)";
    resultadoCalculado = sumarMatrices(A, B);
  } else {
    operadorStr = "RESTA (A - B)";
    resultadoCalculado = restarMatrices(A, B);
  }

  std::cout << "\nPlanteamiento de operacion: " << operadorStr << "\n";
  std::cout << "Matriz A:";
  imprimirMatriz(A);
  std::cout << "Matriz B:";
  imprimirMatriz(B);

  std::cout << "Calcule el resultado e ingrese los valores celda por celda:\n";
  Matriz respuestaEstudiante(dim, std::vector<double>(dim, 0.0));
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      std::string mensaje = "Resultado Fila " + std::to_string(i + 1) +
                            ", Columna " + std::to_string(j + 1) + ": ";
      respuestaEstudiante[i][j] = leerNumeroSeguro(mensaje);
    }
  }

  if (evaluarRespuestaEstudiante(resultadoCalculado, respuestaEstudiante)) {
    std::cout << "\n¡Excelente! Tu respuesta es CORRECTA.\n";
  } else {
    std::cout << "\nRespuesta INCORRECTA.\n";
    std::cout << "Tu respuesta fue:";
    imprimirMatriz(respuestaEstudiante);
    std::cout << "El resultado correcto era:";
    imprimirMatriz(resultadoCalculado);
  }
}

// Implementación del Requerimiento 2.1: Práctica de Sistemas de Ecuaciones
void iniciarPracticaSistemas() {
  std::cout << "\n*** PRACTICA DE SISTEMAS DE ECUACIONES ***\n";

  int dim = 0;
  while (dim != 2 && dim != 3) {
    dim = (int)leerNumeroSeguro(
        "Ingrese la dimension del sistema (2 para 2x2, 3 para 3x3): ");
  }

  // [Dev]: Instanciamos el motor de números aleatorios moderno de C++
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-9, 9);

  Matriz A(dim, std::vector<double>(dim));
  std::vector<double> solucion_secreta(dim);
  std::vector<double> b(dim, 0.0);
  std::vector<double> solucion_interna;

  // [Dev]: Bucle while que atrapa sistemas sin solución y genera uno nuevo
  // automáticamente
  while (true) {
    // 1. Generar Matriz A y vector secreto de soluciones
    for (int i = 0; i < dim; ++i) {
      for (int j = 0; j < dim; ++j) {
        A[i][j] = dist(gen);
      }
      solucion_secreta[i] = dist(gen);
    }

    // 2. Calcular b = A * solucion_secreta
    for (int i = 0; i < dim; ++i) {
      b[i] = 0;
      for (int j = 0; j < dim; ++j) {
        b[i] += A[i][j] * solucion_secreta[j];
      }
    }

    // 3. Validar matemáticamente si el sistema es resoluble (no singular)
    solucion_interna = resolverSistemaSilencioso(A, b);
    if (!solucion_interna.empty())
      break;
  }

  // Imprimir sistema formateado
  std::cout << "\nResuelve el siguiente sistema utilizando el metodo de Gauss "
               "o Gauss-Jordan:\n";
  for (int i = 0; i < dim; ++i) {
    std::cout << "[ ";
    for (int j = 0; j < dim; ++j) {
      std::cout << std::setw(5) << A[i][j] << " ";
    }
    std::cout << "| " << std::setw(5) << b[i] << " ]\n";
  }

  // Capturar respuesta utilizando nuestra función de utilidades para asegurar
  // la validación
  std::vector<double> respuesta_estudiante(dim);
  std::cout << "\nIngresa tu solucion (se aceptan decimales):\n";
  for (int i = 0; i < dim; ++i) {
    std::string msj = "x" + std::to_string(i + 1) + " = ";
    respuesta_estudiante[i] = leerNumeroSeguro(msj);
  }

  // Verificación celda a celda con epsilon para evitar fallos de precisión
  // binaria
  bool es_correcto = true;
  for (int i = 0; i < dim; ++i) {
    if (std::abs(respuesta_estudiante[i] - solucion_interna[i]) > 0.01) {
      es_correcto = false;
      break;
    }
  }

  // Retroalimentación
  if (es_correcto) {
    std::cout << "\n¡Excelente trabajo! Tu solucion es correcta.\n";
  } else {
    std::cout << "\nHay discrepancias en tu respuesta.\n";
    std::cout << "Tu respuesta: [ ";
    for (double val : respuesta_estudiante)
      std::cout << val << " ";
    std::cout << "]\n";

    std::cout << "La solucion correcta calculada es: [ ";
    for (double val : solucion_interna)
      std::cout << val << " ";
    std::cout << "]\n";
    std::cout << "Sugerencia: Revisa las operaciones elementales por fila.\n";
  }
}
