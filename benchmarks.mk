SEED=42
BENCHMARKS=

BENCHMARKS += sgemm.bench
sgemm.bench.args=\
--sgemm ${SEED} 64 64 64 \
--sgemm ${SEED} 128 128 128 \
--sgemm ${SEED} 256 256 256 \
--sgemm ${SEED} 512 512 512 \
--sgemm ${SEED} 1024 1024 1024 \
--sgemm ${SEED} 2048 2048 2048 \
--sgemm ${SEED} 4096 4096 4096
sgemm.bench:
	for target in ${TARGETS}; do ./$$target ${sgemm.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += dgemm.bench
dgemm.bench.args=\
--dgemm ${SEED} 64 64 64 \
--dgemm ${SEED} 128 128 128 \
--dgemm ${SEED} 256 256 256 \
--dgemm ${SEED} 512 512 512 \
--dgemm ${SEED} 1024 1024 1024 \
--dgemm ${SEED} 2048 2048 2048 \
--dgemm ${SEED} 4096 4096 4096
dgemm.bench:
	for target in ${TARGETS}; do ./$$target ${dgemm.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += cgemm.bench
cgemm.bench.args=\
--cgemm ${SEED} 64 64 64 \
--cgemm ${SEED} 128 128 128 \
--cgemm ${SEED} 256 256 256 \
--cgemm ${SEED} 512 512 512 \
--cgemm ${SEED} 1024 1024 1024 \
--cgemm ${SEED} 2048 2048 2048 \
--cgemm ${SEED} 4096 4096 4096
cgemm.bench:
	for target in ${TARGETS}; do ./$$target ${cgemm.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += zgemm.bench
zgemm.bench.args=\
--zgemm ${SEED} 64 64 64 \
--zgemm ${SEED} 128 128 128 \
--zgemm ${SEED} 256 256 256 \
--zgemm ${SEED} 512 512 512 \
--zgemm ${SEED} 1024 1024 1024 \
--zgemm ${SEED} 2048 2048 2048 \
--zgemm ${SEED} 4096 4096 4096
zgemm.bench:
	for target in ${TARGETS}; do ./$$target ${zgemm.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += spotrf.bench
spotrf.bench.args=\
--spotrf ${SEED} 64 \
--spotrf ${SEED} 128 \
--spotrf ${SEED} 256 \
--spotrf ${SEED} 512 \
--spotrf ${SEED} 1024 \
--spotrf ${SEED} 2048 \
--spotrf ${SEED} 4096
spotrf.bench:
	for target in ${TARGETS}; do ./$$target ${spotrf.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += dpotrf.bench
dpotrf.bench.args=\
--dpotrf ${SEED} 64 \
--dpotrf ${SEED} 128 \
--dpotrf ${SEED} 256 \
--dpotrf ${SEED} 512 \
--dpotrf ${SEED} 1024 \
--dpotrf ${SEED} 2048 \
--dpotrf ${SEED} 4096
dpotrf.bench:
	for target in ${TARGETS}; do ./$$target ${dpotrf.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += cpotrf.bench
cpotrf.bench.args=\
--cpotrf ${SEED} 64 \
--cpotrf ${SEED} 128 \
--cpotrf ${SEED} 256 \
--cpotrf ${SEED} 512 \
--cpotrf ${SEED} 1024 \
--cpotrf ${SEED} 2048 \
--cpotrf ${SEED} 4096
cpotrf.bench:
	for target in ${TARGETS}; do ./$$target ${cpotrf.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += zpotrf.bench
zpotrf.bench.args=\
--zpotrf ${SEED} 64 \
--zpotrf ${SEED} 128 \
--zpotrf ${SEED} 256 \
--zpotrf ${SEED} 512 \
--zpotrf ${SEED} 1024 \
--zpotrf ${SEED} 2048 \
--zpotrf ${SEED} 4096
zpotrf.bench:
	for target in ${TARGETS}; do ./$$target ${zpotrf.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += ssyevr.bench
ssyevr.bench.args=\
--ssyevr ${SEED} 64 \
--ssyevr ${SEED} 128 \
--ssyevr ${SEED} 256 \
--ssyevr ${SEED} 512 \
--ssyevr ${SEED} 1024 \
--ssyevr ${SEED} 2048 \
--ssyevr ${SEED} 4096
ssyevr.bench:
	for target in ${TARGETS}; do ./$$target ${ssyevr.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += dsyevr.bench
dsyevr.bench.args=\
--dsyevr ${SEED} 64 \
--dsyevr ${SEED} 128 \
--dsyevr ${SEED} 256 \
--dsyevr ${SEED} 512 \
--dsyevr ${SEED} 1024 \
--dsyevr ${SEED} 2048 \
--dsyevr ${SEED} 4096
dsyevr.bench:
	for target in ${TARGETS}; do ./$$target ${dsyevr.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += cheevr.bench
cheevr.bench.args=\
--cheevr ${SEED} 64 \
--cheevr ${SEED} 128 \
--cheevr ${SEED} 256 \
--cheevr ${SEED} 512 \
--cheevr ${SEED} 1024 \
--cheevr ${SEED} 2048 \
--cheevr ${SEED} 4096
cheevr.bench:
	for target in ${TARGETS}; do ./$$target ${cheevr.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += zheevr.bench
zheevr.bench.args=\
--zheevr ${SEED} 64 \
--zheevr ${SEED} 128 \
--zheevr ${SEED} 256 \
--zheevr ${SEED} 512 \
--zheevr ${SEED} 1024 \
--zheevr ${SEED} 2048 \
--zheevr ${SEED} 4096
zheevr.bench:
	for target in ${TARGETS}; do ./$$target ${zheevr.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += fftw1dfi.bench
fftw1dfi.bench.args=\
--fftw1dfi ${SEED} 64 \
--fftw1dfi ${SEED} 128 \
--fftw1dfi ${SEED} 256 \
--fftw1dfi ${SEED} 512 \
--fftw1dfi ${SEED} 1024 \
--fftw1dfi ${SEED} 2048 \
--fftw1dfi ${SEED} 4096 \
--fftw1dfi ${SEED} 8192 \
--fftw1dfi ${SEED} 16384 \
--fftw1dfi ${SEED} 32768 \
--fftw1dfi ${SEED} 65536 \
--fftw1dfi ${SEED} 131072 \
--fftw1dfi ${SEED} 262144 \
--fftw1dfi ${SEED} 524288 \
--fftw1dfi ${SEED} 1048576 \
--fftw1dfi ${SEED} 2097152 \
--fftw1dfi ${SEED} 4194304 \
--fftw1dfi ${SEED} 8388608 \
--fftw1dfi ${SEED} 16777216 \
--fftw1dfi ${SEED} 33554432
fftw1dfi.bench:
	for target in ${TARGETS}; do ./$$target ${fftw1dfi.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += fftw1df.bench
fftw1df.bench.args=\
--fftw1df ${SEED} 64 \
--fftw1df ${SEED} 128 \
--fftw1df ${SEED} 256 \
--fftw1df ${SEED} 512 \
--fftw1df ${SEED} 1024 \
--fftw1df ${SEED} 2048 \
--fftw1df ${SEED} 4096 \
--fftw1df ${SEED} 8192 \
--fftw1df ${SEED} 16384 \
--fftw1df ${SEED} 32768 \
--fftw1df ${SEED} 65536 \
--fftw1df ${SEED} 131072 \
--fftw1df ${SEED} 262144 \
--fftw1df ${SEED} 524288 \
--fftw1df ${SEED} 1048576 \
--fftw1df ${SEED} 2097152 \
--fftw1df ${SEED} 4194304 \
--fftw1df ${SEED} 8388608 \
--fftw1df ${SEED} 16777216 \
--fftw1df ${SEED} 33554432
fftw1df.bench:
	for target in ${TARGETS}; do ./$$target ${fftw1df.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += fftw1di.bench
fftw1di.bench.args=\
--fftw1di ${SEED} 64 \
--fftw1di ${SEED} 128 \
--fftw1di ${SEED} 256 \
--fftw1di ${SEED} 512 \
--fftw1di ${SEED} 1024 \
--fftw1di ${SEED} 2048 \
--fftw1di ${SEED} 4096 \
--fftw1di ${SEED} 8192 \
--fftw1di ${SEED} 16384 \
--fftw1di ${SEED} 32768 \
--fftw1di ${SEED} 65536 \
--fftw1di ${SEED} 131072 \
--fftw1di ${SEED} 262144 \
--fftw1di ${SEED} 524288 \
--fftw1di ${SEED} 1048576 \
--fftw1di ${SEED} 2097152 \
--fftw1di ${SEED} 4194304 \
--fftw1di ${SEED} 8388608 \
--fftw1di ${SEED} 16777216 \
--fftw1di ${SEED} 33554432
fftw1di.bench:
	for target in ${TARGETS}; do ./$$target ${fftw1di.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}

BENCHMARKS += fftw1d.bench
fftw1d.bench.args=\
--fftw1d ${SEED} 64 \
--fftw1d ${SEED} 128 \
--fftw1d ${SEED} 256 \
--fftw1d ${SEED} 512 \
--fftw1d ${SEED} 1024 \
--fftw1d ${SEED} 2048 \
--fftw1d ${SEED} 4096 \
--fftw1d ${SEED} 8192 \
--fftw1d ${SEED} 16384 \
--fftw1d ${SEED} 32768 \
--fftw1d ${SEED} 65536 \
--fftw1d ${SEED} 131072 \
--fftw1d ${SEED} 262144 \
--fftw1d ${SEED} 524288 \
--fftw1d ${SEED} 1048576 \
--fftw1d ${SEED} 2097152 \
--fftw1d ${SEED} 4194304 \
--fftw1d ${SEED} 8388608 \
--fftw1d ${SEED} 16777216 \
--fftw1d ${SEED} 33554432
fftw1d.bench:
	for target in ${TARGETS}; do ./$$target ${fftw1d.bench.args} > $$target.$@; done
	./plot.sh $@.html ${TARGETS:%=%.$@}