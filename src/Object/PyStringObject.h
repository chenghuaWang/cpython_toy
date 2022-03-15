/*!
 * @author  chenghua.wang
 * @file    src/Object/PyStringObject.h
 * @brief   definitions of PyStringObject
 */

#ifndef _PYSTRINGOBJECT_H_
#define _PYSTRINGOBJECT_H_
#include "PyObject.h"
#include "string.h"

#define STRING_ENABLE_MEM_OPTIMIZE True

/*!
 * for convinence: copied form PyObject.h
#define PyObject_head \
    int32_t ref_cnt;\
    struct _PyTypeObject_ *type

#define PyObject_var_head \
    PyObject_head;\
    int32_t ob_size;
 */

typedef struct _PyStringObject_{
    PyObject_var_head;
    int64_t ob_shash;
    int32_t ob_sstate;
    char *ob_sval;
}PyStringObject;

/*!
 * @brief: create python string object.
 * Due to this kinds of string is unchangabel,
 * we will use a hash-tree to record and locate
 * the small string.
 **/
PyObject* PyString_create(const char rhs[]);

static void PyString_print(PyObject* rhs){
    PyStringObject *tmp = (PyStringObject*)rhs;
    printf("%s\n", tmp->ob_sval);
}

/*!
 * @brief: calculate hash[long type, int64_t] for
 * inner function and other stuff.
 */
static int64_t _string_hash_(PyStringObject *a){
    register int32_t len; 
    register unsigned char *p; 
    register int64_t x; 
    if (a->ob_shash != -1) 
    return a->ob_shash; 
    len = a->ob_size; 
    p = (unsigned char *) a->ob_sval; 
    x = *p << 7; 
    while (--len >= 0) x = (1000003*x) ^ *p++; 
    x ^= a->ob_size; 
    if (x == -1) x = -2; 
    a->ob_shash = x; 
    return x;
}


/*!
 * @brief: function for PyString object.
 * wrapped from _string_hash_ function, whitch is 
 * also a static function.
 */
static int64_t PyString_hash(PyObject *rhs){
    if (!rhs) {
        printf("Err: When calculate hash for string, found string object is NULL.\n");
        exit(EXIT_FAILURE);
    }
    PyStringObject *tmp = (PyStringObject*)rhs;
    if (!tmp->ob_size){
        printf("Err: When calculate hash for string, found string is NULL.\n");
        exit(EXIT_FAILURE);
    }
    return _string_hash_(tmp);
}

static PyTypeObject PyStringType = {
    PyObject_head_init(&PyType_Type),
    "string",
    NULL, /*print function*/
    NULL, /*add function*/
    NULL, /*mul function*/
    NULL, /*floor_div function*/
    NULL, /*hash function*/
};

#endif  // _PYSTRINGOBJECT_H_
