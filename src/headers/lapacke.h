#pragma once
#ifndef LOCAL_LAPACKE_H_
#define LOCAL_LAPACKE_H_

#ifdef LAPACK_MKL
#include <mkl_lapacke.h>
#else
#include <lapacke.h>
#endif

#endif // #ifndef LOCAL_LAPACKE_H_