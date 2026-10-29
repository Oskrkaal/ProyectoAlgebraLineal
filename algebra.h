// ==========================================
// Archivo: algebra.h
// Propósito: Conectar todos los módulos del proyecto.
// ==========================================

#ifndef ALGEBRA_H // Guarda de inclusión (evita que el archivo se incluya
                  // múltiples veces)
#define ALGEBRA_H

#include <cmath>
#include <iomanip> // Para std::setw y std::setprecision (alinear matrices)
#include <iostream>
#include <limits> // Para limpiar el buffer de std::cin
#include <vector>

// Definimos un alias ('typedef' moderno) para no escribir el vector de vectores
// cada vez. Esto hace que el código sea mucho más legible, ¡una buena práctica
// en C++!
using Matriz = std::vector<std::vector<double>>;

// ==========================================
// MÓDULO C: Utilidades y Validaciones
// ==========================================
void imprimirMatriz(const Matriz &m);
double leerNumeroSeguro(const std::string &mensaje);
void pausarYLimpiar();

// ==========================================
// MÓDULO A: Calculadora de Álgebra Lineal
// (Estas funciones las iremos implementando en calculadora.cpp)
// ==========================================
Matriz sumarMatrices(const Matriz &A, const Matriz &B);
Matriz restarMatrices(const Matriz &A, const Matriz &B);
Matriz multiplicarMatrices(const Matriz &A, const Matriz &B);
void resolverGauss(Matriz sistema);
void resolverGaussJordan(Matriz sistema);
Matriz calcularInversa(Matriz A);
Matriz leerMatriz(const std::string &nombreMatriz);
// ==========================================
// MÓDULO B: Generador de Ejercicios
// (Estas funciones las implementaremos en practica.cpp)
// ==========================================
void iniciarPracticaSistemas();
void iniciarPracticaOperaciones();

#endif
