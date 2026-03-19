TARGETS=aocc_aocl.x icpx_mkl.x
include toolchains.mk
include benchmarks.mk

all: ${TARGETS}

aocc_aocl.x: src/main.cpp src/headers/*
	${AOCC_AOCL_CXX} $< -o $@

icpx_mkl.x: src/main.cpp src/headers/*
	${ICPX_MKL_CXX} $< -o $@

clean:
	rm ${TARGETS} *.bench *.html

bench: all ${BENCHMARKS}

.PHONY: all clean bench ${BENCHMARKS}
