/*!
 * @author  chenghua.wang
 * @file    src/Object/PyStringObject.h
 * @brief   definitions of PyStringObject
 */

#ifndef _PYSTRINGOBJECT_H_
#define _PYSTRINGOBJECT_H_
#include "PyObject.h"

typedef struct _PyStringObject_{
    PyObject_var_head;
    int64_t ob_shash;
    int32_t ob_sstate;
    char *str;
}PyStringObject;

static PyTypeObject PyStringType = {
    PyObject_head_init(&PyType_Type),
    "string",
    NULL, /*print function*/
    NULL, /*add function*/
    NULL, /*mul function*/
    NULL, /*floor_div function*/
    NULL, /*hash function*/
}

#endif  // _PYSTRINGOBJECT_H_
