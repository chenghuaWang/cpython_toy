/*!
 * @author  chenghua.wang
 * @file    src/Object/PyStringObject.h
 * @brief   definitions of PyStringObject
 */

#ifndef _PYSTRINGOBJECT_H_
#define _PYSTRINGOBJECT_H_
#include "PyObject.h"

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
    char *str;
}PyStringObject;

/*!
 * @brief: create python string object.
 * Due to this kinds of string is unchangabel,
 * we will use a hash-tree to record and locate
 * the small string.
 **/
PyObject* PyString_create(const char rhs[]){
    
}

static void PyString_print(PyObject* rhs){
    PyStringObject *tmp = (PyStringObject*)rhs;
    printf("%s\n", tmp->str);
}

static int64_t PyString_hash(PyObject *rhs){
    PyStringObject *tmp = (PyStringObject*)rhs;
    
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
