/*!
 * @author  chenghua.wang
 * @file    src/Object/PyObject.h
 * @brief   definitions of PyObject/PyTypeObject/
 */

#ifndef _PYOBJECT_H_
#define _PYOBJECT_H_
#include "_obj_base_.h"

// TODO
// #define DEBUG

#define PyObject_head \
    int32_t ref_cnt;\
    struct _PyTypeObject_ *type

#define PyObject_var_head \
    PyObject_head;\
    int32_t ob_size;

#define PyObject_head_init(type_ptr) \
    0, type_ptr

#define PyObject_var_head_init(type_ptr, _size_) \
    0, type_ptr, _size_

// below define the basic object used in python.
typedef struct _PyObject_{
    PyObject_head;
}PyObject;
typedef struct _PyVarObject_{
    PyObject_var_head;
}PyVarObject;

// below define the function used in _PyTypeObject_ 
typedef void (*_print_)(PyObject *rhs);
typedef PyObject* (*_add_)(PyObject *left, PyObject *right);
typedef PyObject* (*_sub_)(PyObject *left, PyObject *right);
typedef PyObject* (*_mul_)(PyObject *left, PyObject *right);
typedef PyObject* (*_floor_div_)(PyObject *left, PyObject *right);
typedef int64_t (*_hash_)(PyObject *rhs);

// below define the basic object used in python.
typedef struct _PyTypeObject_{
    PyObject_head;
    char *name;
    // function below
    _print_ print;
    _add_ add;
    _sub_ sub;
    _mul_ mul;
    _floor_div_ div;
    _hash_ hash;
}PyTypeObject;

//below define the type_type function
static void PyType_print(PyObject* rhs){
    printf("type is type[type_type] in python. no value could be print\n");
}

// below define the type_type.
static PyTypeObject PyType_Type = {
    //PyObject_head_init(&PyType_Type),
    PyObject_head_init(NULL),
    "type",
    PyType_print, /*print function*/
    NULL, /*add function*/
    NULL, /*sub function*/
    NULL, /*mul function*/
    NULL, /*floor_div function*/
    NULL, /*hash function*/
};

#endif  // _PYOBJECT_H_