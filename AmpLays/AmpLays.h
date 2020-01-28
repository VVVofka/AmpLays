#pragma once
#include <iostream>
#include "LayBase.h"

void dumpV(const std::vector<vtype> v, int szx, int szy);
void dumpv(const vtype* v, int szx, int szy);
void dumpv(const concurrency::array_view<vtype, 2>&);

void CppAmpMethod1();
void CppAmpMethod0();
