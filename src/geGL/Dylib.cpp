
//  Dylib.cpp
//  GPUEngine
//  Created by Marcel Kiss on 26/09/2018.

#include <geGL/Dylib.h>

void* dl_symbol(void *lib, char const *sym_name) {
    void* sym = dlsym(lib, sym_name);
#if DYLIB_ERROR_MESSAGES
    if (sym == NULL)
        fprintf(stderr, "%s\n", dlerror());
#endif
    return sym;
}

void* dl_open_lib(char const *lib_name) {
    void* lib = dlopen(lib_name, RTLD_LAZY);
#if DYLIB_ERROR_MESSAGES
    if (lib == NULL)
        fprintf(stderr, "%s\n", dlerror());
#endif
    return lib;
}

int dl_close_lib(void *lib) {
    int code = dlclose(lib);
#if DYLIB_ERROR_MESSAGES
    if (code)
        fprintf(stderr, "%s\n", dlerror());
#endif
    return code;
}

#if defined(__APPLE__)
    
#include <string.h>
void* dl_open_framework(const char *fw_name) {
    if (fw_name == NULL)
        return dl_open_lib(NULL);
    const size_t fs = strlen(fw_name);
    if (fs <= 0)
        return dl_open_lib("");
    const char *e = ".framework/";
    const size_t es = strlen(e);
    char *s = (char *)malloc(fs * 2 + es);
    s = strncat(s, fw_name, fs);
    s = strncat(s, e, es);
    s = strncat(s, fw_name, fs);
    void* lib = dl_open_lib(s);
    if (s) free(s);
    return lib;
}
    
#endif
