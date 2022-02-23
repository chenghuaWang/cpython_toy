/*!
 * @author  chenghua.wang
 * @file    src/test/PyIntObject_test.c
 * @brief   A test func for PyInt. Maybe TEST_UNIT from boost is better.
 */

#include "../Object/_obj_core_.h"

int main(int args, char* argv[]){
    __PyObject_GLOBAL_INIT__();

#ifdef DEBUG
    _debug_print_list_block();
    _debug_print_free_list();
#endif

    PyObject *a = PyInt_create(-1);
    PyObject *b = PyInt_create(0);
    PyObject *d = PyInt_create(1);
    PyObject *e = PyInt_create(2);
    PyObject *f = PyInt_create(3);

    PyObject *c = ((PyIntObject*)a)->type->add(a, b);
    ((PyIntObject*)a)->type->print(c);

#ifdef DEBUG
    _debug_print_list_block();
    _debug_print_free_list();
#endif
}