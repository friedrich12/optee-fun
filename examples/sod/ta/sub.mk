srcs-y += sod.c
srcs-y += sodtest_ta.c
cflags-sod.c-y := -w -DSTBI_NO_STDIO -DSTBI_WRITE_NO_STDIO -D_SBK_SGX -DSOD_DISABLE_CNN
global-incdirs-y += include
subdirs-y += newlib

