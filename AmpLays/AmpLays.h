#pragma once
#include <amp.h>
#include <iostream>
#include <cassert>


typedef int vtype;
//typedef concurrency::array_view<vtype, 1> av;

void dumpV(const std::vector<vtype> v, int szx, int szy);
void dumpv(const vtype* v, int szx, int szy);
void CppAmpMethod1();
