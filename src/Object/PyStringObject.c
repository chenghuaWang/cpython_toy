/*!
 * @author  chenghua.wang
 * @file    src/Object/PyStringObject.c
 * @brief   implement of PyStringObject
 */

#include "PyStringObject.h"

PyObject* PyString_FromString(const char rhs[]){
#if STRING_ENABLE_MEM_OPTIMIZE == True
    PyStringObject *ans = (PyStringObject*)malloc(sizeof(PyStringObject));
    ans->ob_size = (int32_t)strlen(rhs);
    ans->ref_cnt = 1;
    ans->type = &PyStringType;
    ans->ob_sval = (char*)malloc((size_t)(ans->type->element_size) * strlen(rhs));
    strcpy(ans->ob_sval, rhs);
    ans->ob_shash = _string_hash_(ans);
#else

#endif
    return (PyObject*)ans;
}

PyObject* PyString_FromStringAndSize(const char rhs[], uint32_t ss){
#if STRING_ENABLE_MEM_OPTIMIZE == True
    PyStringObject *ans = (PyStringObject*)malloc(sizeof(PyStringObject));
    ans->ob_size = ss;
    ans->ref_cnt = 1;
    ans->type = &PyStringType;

    if (ss == 0){
        ans->ob_sval = NULL;
        ans->ob_shash = STRING_DEFAULT_HASH;
    }else{
        ans->ob_sval = (char*)malloc((size_t)(ss+1) * strlen(rhs));
        if (!ans->ob_sval){
            ans->ob_sval = NULL;
            ans->ob_shash = STRING_DEFAULT_HASH;
            printf("Warn: malloc string %s, size %d err. Set NULL by default\n", rhs, ss);
        }else{
            memcpy(ans->ob_sval, rhs, (size_t)(ss));
            ans->ob_sval[ss] = '\0';
            ans->ob_shash = _string_hash_(ans);
        }
    }
#else

#endif
    return (PyObject*)ans;
}
