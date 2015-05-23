#pragma once


#include<avl.h>
#include<atomics.h>
#include<barrier.h>
#include<cache.h>
#include<getrss.h>
#include<hash16.h>
#include<lace.h>
#include<llmsset.h>
#include<refs.h>
#include<sha2.h>
#include<sylvan.h>
#include<sylvan_bdd.h>
#include<sylvan_common.h>
#include<sylvan_config.h>
#include<sylvan_ldd.h>
#include<tls.h>

extern "C"
{
// manually expand macro...

// line::345@lace.c
// VOID_TASK_IMPL_0(lace_steal_random)

void lace_steal_random_WRAP(WorkerP *w, Task *__dq_head, TD_lace_steal_random *t __attribute__((unused)));

static inline __attribute__((always_inline))
void lace_steal_random_WORK(WorkerP *__lace_worker, Task *__lace_dq_head );
void lace_steal_random_CALL(WorkerP *w, Task *__dq_head );

static inline __attribute__((always_inline))
void lace_steal_random_WORK(WorkerP *__lace_worker __attribute__((unused)), Task *__lace_dq_head __attribute__((unused)) );

// line::806@lace.c
// VOID_TASK_2(lace_together_helper, Task*, t, volatile int*, finished)
// #define VOID_TASK_2(NAME, ATYPE_1, ARG_1, ATYPE_2, ARG_2) VOID_TASK_DECL_2(NAME, ATYPE_1, ATYPE_2) VOID_TASK_IMPL_2(NAME, ATYPE_1, ARG_1, ATYPE_2, ARG_2)
// #define VOID_TASK_DECL_2(NAME, ATYPE_1, ATYPE_2)                                      
                                                                                      
typedef struct _TD_lace_together_helper {                                                           
  TASK_COMMON_FIELDS(_TD_lace_together_helper);                                                      
  union {                                                                             
    struct {  Task* t; volatile int* finished; } args;                                   
                                                                                    
  } d;                                                                                
} TD_lace_together_helper;                                                                          
                                                                   
// line::61@llmset.c
// VOID_TASK_1(llmsset_init_worker, llmsset_t, dbs)
typedef struct _TD_llmsset_init_worker {                                                           
  TASK_COMMON_FIELDS(_TD_llmsset_init_worker);                                                      
  union {                                                                             
    struct {  llmsset_t dbs; } args;                                                  
                                                                                    
  } d;                                                                                
} TD_llmsset_init_worker;

// line::331@llmset.c
//VOID_TASK_3(llmsset_rehash_range, llmsset_t, dbs, size_t, first, size_t, count)
typedef struct _TD_llmsset_rehash_range {                                                           
  TASK_COMMON_FIELDS(_TD_llmsset_rehash_range);                                                      
  union {                                                                             
    struct {  llmsset_t dbs; size_t first; size_t count; } args;                    
                                                                                      
  } d;                                                                               
} TD_llmsset_rehash_range;

// line:339@llmset.c
// VOID_TASK_1(llmsset_rehash_task, llmsset_t, dbs)
typedef struct _TD_llmsset_rehash_task {                                                           
  TASK_COMMON_FIELDS(_TD_llmsset_rehash_task);                                                      
  union {                                                                             
    struct {  llmsset_t dbs; } args;                                                  
                                                                                      
  } d;                                                                                
} TD_llmsset_rehash_task;

// line:368@llmset.c
// TASK_3(size_t, llmsset_count_marked_range, llmsset_t, dbs, size_t, first, size_t, count)
typedef struct _TD_llmsset_count_marked_range {                                                           
  TASK_COMMON_FIELDS(_TD_llmsset_count_marked_range);                                                      
  union {                                                                            
    struct {  llmsset_t dbs; size_t first; size_t count; } args;                    
    size_t res;                                                                        
  } d;                                                                                
} TD_llmsset_count_marked_range;

// line:157@sylvan_bdd.c
// VOID_TASK_0(sylvan_gc_mark_external_refs)
typedef struct _TD_sylvan_gc_mark_external_refs {                                                           
  TASK_COMMON_FIELDS(_TD_sylvan_gc_mark_external_refs);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_sylvan_gc_mark_external_refs;

// line:175@sylvan_bdd.c
// VOID_TASK_0(bdd_refs_mark_task)
typedef struct _TD_bdd_refs_mark_task {                                                           
  TASK_COMMON_FIELDS(_TD_bdd_refs_mark_task);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_bdd_refs_mark_task;

// line:202@sylvan_bdd.c
// VOID_TASK_0(bdd_refs_mark)
typedef struct _TD_bdd_refs_mark {                                                           
  TASK_COMMON_FIELDS(_TD_bdd_refs_mark);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_bdd_refs_mark;

// line:207@sylvan_bdd.c
// VOID_TASK_0(bdd_refs_init_task)
typedef struct _TD_bdd_refs_init_task {                                                           
  TASK_COMMON_FIELDS(_TD_bdd_refs_init_task);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_bdd_refs_init_task;

// line:207@sylvan_common.c
// VOID_TASK_0(bdd_refs_init)
typedef struct _TD_bdd_refs_init {                                                           
  TASK_COMMON_FIELDS(_TD_bdd_refs_init);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_bdd_refs_init;

// line:124@sylvan_common.c
// VOID_TASK_0(sylvan_gc_mark_cache)
typedef struct _TD_sylvan_gc_mark_cache {                                                           
  TASK_COMMON_FIELDS(_TD_sylvan_gc_mark_cache);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_sylvan_gc_mark_cache;

// line:151@sylvan_common.c
// VOID_TASK_0(sylvan_gc_default_hook)
typedef struct _TD_sylvan_gc_default_hook {                                                           
  TASK_COMMON_FIELDS(_TD_sylvan_gc_default_hook);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_sylvan_gc_default_hook;

// line:174@sylvan_common.c
// VOID_TASK_0(sylvan_gc_call_hook)
typedef struct _TD_sylvan_gc_call_hook {                                                           
  TASK_COMMON_FIELDS(_TD_sylvan_gc_call_hook);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_sylvan_gc_call_hook;

// line:180@sylvan_common.c
// VOID_TASK_0(sylvan_gc_rehash)
typedef struct _TD_sylvan_gc_rehash {                                                           
  TASK_COMMON_FIELDS(_TD_sylvan_gc_rehash);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_sylvan_gc_rehash;

// line:186@sylvan_common.c
// VOID_TASK_0(sylvan_gc_go)
typedef struct _TD_sylvan_gc_go {                                                           
  TASK_COMMON_FIELDS(_TD_sylvan_gc_go);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_sylvan_gc_go;

// line:169@sylvan_ldd.c
// VOID_TASK_0(lddmc_gc_mark_external_refs)
typedef struct _TD_lddmc_gc_mark_external_refs {                                                           
  TASK_COMMON_FIELDS(_TD_lddmc_gc_mark_external_refs);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_lddmc_gc_mark_external_refs;

// line:169@sylvan_ldd.c
// VOID_TASK_0(lddmc_refs_mark_task)
typedef struct _TD_lddmc_refs_mark_task {                                                           
  TASK_COMMON_FIELDS(_TD_lddmc_refs_mark_task);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_lddmc_refs_mark_task;

// line:213@sylvan_ldd.c
// VOID_TASK_0(lddmc_refs_mark)
typedef struct _TD_lddmc_refs_mark {                                                           
  TASK_COMMON_FIELDS(_TD_lddmc_refs_mark);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_lddmc_refs_mark;

// line:218@sylvan_ldd.c
// VOID_TASK_0(lddmc_refs_init_task)
typedef struct _TD_lddmc_refs_init_task {                                                           
  TASK_COMMON_FIELDS(_TD_lddmc_refs_init_task);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_lddmc_refs_init_task;

// line:230@sylvan_ldd.c
// VOID_TASK_0(lddmc_refs_init)
typedef struct _TD_lddmc_refs_init {                                                           
  TASK_COMMON_FIELDS(_TD_lddmc_refs_init);                                                      
  union {                                                                             
    struct {  } args;                                                                 
                                                                                      
  } d;                                                                                
} TD_lddmc_refs_init;

// line:685@sylvan_ldd.c
// TASK_4(MDD, lddmc_relprod_help, uint32_t, val, MDD, set, MDD, rel, MDD, proj)
typedef struct _TD_lddmc_relprod_help {                                                           \
  TASK_COMMON_FIELDS(_TD_lddmc_relprod_help)                                                      \
  union {                                                                             \
    struct {  uint32_t val; MDD set; MDD rel; MDD proj; } args;     \
    MDD res;                                                                        \
  } d;                                                                                \
} TD_lddmc_relprod_help; 

// line:845@sylvan_ldd.c
// TASK_5(MDD, lddmc_relprod_union_help, uint32_t, val, MDD, set, MDD, rel, MDD, proj, MDD, un)
typedef struct _TD_lddmc_relprod_union_help {                                                           
  TASK_COMMON_FIELDS(lddmc_relprod_union_help)                                                      
  union {                                                                             
    struct {  uint32_t val; MDD set; MDD rel; MDD proj; MDD un; } args;
    MDD res;                                                                        
  } d;                                                                                
} TD_lddmc_relprod_union_help;

// line:1128@sylvan_ldd.c
// TASK_5(MDD, lddmc_relprev_help, uint32_t, val, MDD, set, MDD, rel, MDD, proj, MDD, uni)
typedef struct _TD_lddmc_relprev_help {                                                           
  TASK_COMMON_FIELDS(_TD_lddmc_relprev_help)                                                      
  union {                                                                             
    struct {  uint32_t val; MDD set; MDD rel; MDD proj; MDD uni; } args;
    MDD res;                                                                        
  } d;                                                                                
} TD_lddmc_relprev_help;

// line:1861@sylvan_ldd.c
// VOID_TASK_5(_lddmc_sat_all_nopar, MDD, mdd, lddmc_enum_cb, cb, void*, context, uint32_t*, values, size_t, count)

typedef struct _TD__lddmc_sat_all_nopar {                                                           
  TASK_COMMON_FIELDS(_TD__lddmc_sat_all_nopar);                                                      
  union {                                                                             
    struct {  MDD mdd; lddmc_enum_cb cb; void* context; uint32_t* values; size_t count; } args;
                                                                                      
  } d;                                                                                
} TD__lddmc_sat_all_nopar; 

// line:1920@sylvan_ldd.c
// VOID_TASK_3(lddmc_match_sat, struct lddmc_match_sat_info *, info, lddmc_enum_cb, cb, void*, context)
typedef struct _TD_lddmc_match_sat {                                                           
  TASK_COMMON_FIELDS(_TD_lddmc_match_sat);                                                  
  union {                                                                             
    struct { struct lddmc_match_sat_info * info; lddmc_enum_cb cb; void* context; } args;                    
                                                                                      
  } d;                                                                                
} TD_lddmc_match_sat;
}
