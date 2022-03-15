/*!
 * @author  chenghua.wang
 * @file    src/Object/PyStringObject.c
 * @brief   implement of PyStringObject
 */

#include "PyStringObject.h"

PyObject* PyString_create(const char rhs[]){
#if STRING_ENABLE_MEM_OPTIMIZE == True
    PyStringObject *ans = (PyStringObject*)malloc(sizeof(PyStringObject));
    ans->ob_size = (int32_t)strlen(rhs);
    ans->ref_cnt = 1;
    ans->type = &PyStringType;
    ans->ob_sval = (char*)malloc(sizeof(char) * strlen(rhs));
    strcpy(ans->ob_sval, rhs);
    ans->ob_shash = _string_hash_(ans);
#else

#endif
    return (PyObject*)ans;
}
