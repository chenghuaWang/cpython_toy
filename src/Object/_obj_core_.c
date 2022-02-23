/*!
 * @author  chenghua.wang
 * @file    src/Object/_obj_core_.c
 * @brief   compired with .h
 */

#include "_obj_core_.h"

void __PyObject_GLOBAL_INIT__(){
    __PyIntObject_MemPool_INIT__();
}
