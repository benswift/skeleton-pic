void setgbsize(int nblock);

void g_fallocate(float **g_f, int nsize, int *irc);

void g_deallocate(float **g_f);

void copyin_gmemptr(float *f, float *g_f, int nsize);

void copyout_gmemptr(float *f, float *g_f, int nsize);

void ssadd(float g_a[], float g_b[], float g_c[], int nx);
