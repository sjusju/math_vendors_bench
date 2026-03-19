AOCC_AOCL_CXX=clang++ -O2 \
-I/opt/AMD/aocl/aocl-linux-aocc-5.2.0/aocc/include \
-lblis -lflame -lfftw3 -lfftw3f

ICPX_MKL_CXX=icpx -O2 \
-DBLAS_MKL -DLAPACK_MKL -DFFTW3_MKL \
-qmkl=sequential