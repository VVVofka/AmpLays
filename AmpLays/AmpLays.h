#pragma once
#include <amp.h>
#include <iostream>
#include <cassert>

using namespace std;

typedef int vtype;
typedef concurrency::array_view<vtype, 1> av;

void dumpV(const vector<vtype> v, int szx, int szy);
void dumpv(const vtype* v, int szx, int szy);
void CppAmpMethod1();
void CppAmpMethod2();
void CppAmpMethod3();
void CppAmpMethod4();
void CppAmpMethod5();
