/*!
 * @author  chenghua.wang
 * @file    src/Object/PyIntObject.c
 * @brief   PyIntObject c implement of create-func and memory pool for int. 
 */
#include "PyIntObject.h"

PyObject* PyInt_create(int64_t rhs){
    if (rhs <= INT_NUMBER_POS_BOUND && rhs >= (-INT_NUMBER_NEG_BOUND)){
        /* should use a small number memory pool, and those number
         * object can't be deallocate by GC or other method.
         */
        return (PyObject*)(small_block_array + rhs + INT_NUMBER_NEG_BOUND);
    }else{
        // memory pool. 16 element per block. max block 1024.
        if(!free_list) free_list = get_free_list_ptr();
        PyIntObject *res = free_list->int_data;
        int_block *tmp = free_list;
        free_list = free_list->next;
        free(tmp);
        res->ref_cnt = 1;
        res->type = &PyIntType;
        res->val = rhs;
#ifdef DEBUG
        printf("debug: res->val %d\n", res->val);
#endif
        return (PyObject*)res;
    }
}

int_block* get_free_list_ptr(){
    list_block->next = (int_block*)malloc(sizeof(int_block));
    list_block = list_block->next; /*list_block is alwanys points to tail of lists*/

    list_block->next = NULL;
    list_block->int_data = (PyIntObject*)malloc(sizeof(PyIntObject)*ELEMENT_PER_BLOCK);

    int_block *tmp_head = free_list;

    /* insert int_block for free_list at head */
    for (int32_t i = 0; i < ELEMENT_PER_BLOCK; ++i){
        int_block *tmp = (int_block*)malloc(sizeof(int_block));
        tmp->int_data = list_block->int_data + i;
#ifdef DEBUG
        tmp->int_data->val = 0;
#endif
        tmp->next = tmp_head;
        tmp_head = tmp;
    }
    free_list = tmp_head;
    return tmp_head;
}

void __PyIntObject_MemPool_INIT__(){
    /* -- A simple big integer memory pool -- */
    // init list_block for 16 block.
    list_block = (int_block*)malloc(sizeof(int_block));
    list_block->next = NULL;
    list_block->int_data = (PyIntObject*)malloc(sizeof(PyIntObject)*ELEMENT_PER_BLOCK);
    list_block_st = list_block;

    int_block *tmp_head = free_list;

    /* insert int_block for free_list at head */
    for (int32_t i = 0; i < ELEMENT_PER_BLOCK; ++i){
        int_block *tmp = (int_block*)malloc(sizeof(int_block));
        tmp->int_data = list_block->int_data + i;
#ifdef DEBUG
        tmp->int_data->val = 0;
#endif
        tmp->next = tmp_head;
        tmp_head = tmp;
    }
    free_list = tmp_head;

    /* -- A simple small integer memory pool -- */
    small_block_array = (PyIntObject*)malloc(sizeof(PyIntObject)*(INT_NUMBER_NEG_BOUND+INT_NUMBER_POS_BOUND+1)); /*postive negative and zero*/
    // init negative number and zero.
    small_block_array[0].val = small_block_array[0].ref_cnt = 0;
    small_block_array[INT_NUMBER_NEG_BOUND].type = &PyIntType;
    for (int32_t i = 0; i < INT_NUMBER_NEG_BOUND; i++){
        small_block_array[i].val = -((INT_NUMBER_NEG_BOUND)-i);
        small_block_array[i].type = &PyIntType;
        small_block_array[i].ref_cnt = 0;
    }
    //init positive number
    for(int32_t i = 1; i <= INT_NUMBER_POS_BOUND; ++i){
        int32_t idx = i + INT_NUMBER_NEG_BOUND;
        small_block_array[idx].val = i;
        small_block_array[idx].type = &PyIntType;
        small_block_array[idx].ref_cnt = 0;
    }
}


#ifdef DEBUG
    void _debug_print_list_block(){
        printf("block_list\n");
        int_block* tmp = list_block_st;
        while(tmp){
            for(int32_t i = 0; i < ELEMENT_PER_BLOCK; ++i){
                printf("%d,", tmp->int_data[i].val);
            }
            tmp = tmp->next;
        }
        printf("\n");
    }

    void _debug_print_free_list(){
        printf("free_list\n");
        int_block* tmp = free_list;
        while(tmp){
            printf("%d->", (*tmp->int_data).val);
            tmp = tmp->next;
        }
        printf("\n");
    }
#endif
