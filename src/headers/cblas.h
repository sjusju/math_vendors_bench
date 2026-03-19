#pragma once
#ifndef LOCAL_CBLAS_H_
#define LOCAL_CBLAS_H_

#ifdef BLAS_MKL
#include <mkl_cblas.h>
#else
#include <cblas.h>
#endif

#endif // #ifndef LOCAL_CBLAS_H_