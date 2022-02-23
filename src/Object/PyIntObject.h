/*!
 * @author  chenghua.wang
 * @file    src/Object/PyIntObject.h
 * @brief   definitions of PyIntObject
 */

#ifndef _PYINTOBJECT_H_
#define _PYINTOBJECT_H_
#include "PyObject.h"

// definition of macro for big integer pool
#define INT_NUMBER_POS_BOUND 257
#define INT_NUMBER_NEG_BOUND 5
#define ELEMENT_PER_BLOCK 8
#define BLOCK_LIST_MAX 1024

// definition of PyIntObject.
typedef struct _PyIntObject_{
    PyObject_head;
    int64_t val;
}PyIntObject;

// definition of macro for ref_cnt
#define INT_REF_INC(x) ((((PyIntObject*)x)->ref_cnt)++)
#define INT_REF_DEC(x) ((((PyIntObject*)x)->ref_cnt)--) // TODO for GC. and inner free func.


// big integer block and linked list (free_list ptr for empty block.).
struct _int_block_{
    struct _int_block_ *next;
    PyIntObject *int_data;
};
typedef struct _int_block_ int_block;
static int_block* list_block_st = NULL; /* list_block_str point to head of list*/
static int_block* list_block = NULL; /* list_block point to the tail of list*/
static int_block* free_list = NULL; /* free_list point to the head of list */

// small integer block memory pool
static PyIntObject* small_block_array = NULL; /* A small integer array for speed consider*/

// function for PyIntObject class.
PyObject* PyInt_create(int64_t rhs);

static void PyInt_print(PyObject* rhs){
    PyIntObject *tmp = (PyIntObject*)rhs;
    printf("%ld\n", tmp->val);
}

static PyObject* PyInt_add(PyObject* left, PyObject* right){
    PyIntObject *res = (PyIntObject*)PyInt_create(0);
    if (res == NULL) {
        printf("Err: allocate memory for int class failed.\n");
        exit(1);
    }
    PyIntObject *left_int = (PyIntObject*)left;
    PyIntObject *right_int = (PyIntObject*)right;
    res->val = left_int->val + right_int->val;
    return (PyObject*)res;
}

static PyObject* PyInt_sub(PyObject* left, PyObject* right){
    PyIntObject *res = (PyIntObject*)PyInt_create(0);
    if (res == NULL) {
        printf("Err: allocate memory for int class failed.\n");
        exit(1);
    }
    PyIntObject *left_int = (PyIntObject*)left;
    PyIntObject *right_int = (PyIntObject*)right;
    res->val = left_int->val - right_int->val;
    return (PyObject*)res;
}

static PyObject* PyInt_mul(PyObject* left, PyObject* right){
    PyIntObject *res = (PyIntObject*)PyInt_create(0);
    if (res == NULL) {
        printf("Err: allocate memory for int class failed.\n");
        exit(1);
    }
    PyIntObject *left_int = (PyIntObject*)left;
    PyIntObject *right_int = (PyIntObject*)right;
    res->val = left_int->val * right_int->val;
    return (PyObject*)res;
}

static PyObject* PyInt_floor_div(PyObject* left, PyObject* right){
    PyIntObject *res = (PyIntObject*)PyInt_create(0);
    if (res == NULL) {
        printf("Err: allocate memory for int class failed.\n");
        exit(1);
    }
    PyIntObject *left_int = (PyIntObject*)left;
    PyIntObject *right_int = (PyIntObject*)right;
    res->val = left_int->val / right_int->val;
    return (PyObject*)res;
}

static int64_t PyInt_hash(PyObject* rhs){
    return ((PyIntObject*)rhs)->val;
}


// class for PyIntType.
static PyTypeObject PyIntType = {
    PyObject_head_init(&PyType_Type),
    "int",
    PyInt_print, /*print function*/
    PyInt_add, /*add function*/
    PyInt_sub, /*sub function*/
    PyInt_mul, /*mul function*/
    PyInt_floor_div, /*floor_div function*/
    PyInt_hash, /*hash function*/
};

// function for big integer memory pool
/*
    struct _int_block_{
        struct _int_block_ *next;
        PyIntObject *int_data;
    };
*/
int_block* get_free_list_ptr();

void __PyIntObject_MemPool_INIT__();

#ifdef DEBUG
    void _debug_print_list_block();
    void _debug_print_free_list();
#endif

#endif  // _PYINTOBJECT_H_