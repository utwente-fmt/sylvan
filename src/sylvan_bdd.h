/*
 * Copyright 2011-2015 Formal Methods and Tools, University of Twente
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Do not include this file directly. Instead, include sylvan.h */

#include <tls.h>

#ifndef SYLVAN_BDD_H
#define SYLVAN_BDD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef SYLVAN_CACHE_STATS
#define SYLVAN_CACHE_STATS 0
#endif

#ifndef SYLVAN_OPERATION_STATS
#define SYLVAN_OPERATION_STATS 0
#endif

typedef uint64_t BDD;       // low 40 bits used for index, highest bit for complement, rest 0
// BDDSET uses the BDD node hash table. A BDDSET is an ordered BDD.
typedef uint64_t BDDSET;    // encodes a set of variables (e.g. for exists etc.)
// BDDMAP also uses the BDD node hash table. A BDDMAP is *not* an ordered BDD.
typedef uint64_t BDDMAP;    // encodes a function of variable->BDD (e.g. for substitute)
typedef uint32_t BDDVAR;    // low 24 bits only

#define sylvan_complement   ((uint64_t)0x8000000000000000)
#define sylvan_false        ((BDD)0x0000000000000000)
#define sylvan_true         (sylvan_false|sylvan_complement)
#define sylvan_true_nc      ((BDD)0x000000ffffffffff)  // sylvan_true without complement edges
#define sylvan_invalid      ((BDD)0x7fffffffffffffff)

#define sylvan_isconst(a)   ( ((a&(~sylvan_complement)) == sylvan_false) || (a == sylvan_true_nc) )
#define sylvan_isnode(a)    ( ((a&(~sylvan_complement)) != sylvan_false) && ((a&(~sylvan_complement)) < sylvan_true_nc) )

/**
 * Initialize BDD functionality.
 * 
 * Granularity (BDD only) determines usage of operation cache. Smallest value is 1: use the operation cache always.
 * Higher values mean that the cache is used less often. Variables are grouped such that
 * the cache is used when going to the next group, i.e., with granularity=3, variables [0,1,2] are in the
 * first group, [3,4,5] in the next, etc. Then no caching occur between 0->1, 1->2, 0->2. Caching occurs
 * on 0->3, 1->4, 2->3, etc.
 *
 * A reasonable default is a granularity of 4-16, strongly depending on the structure of the BDDs.
 */
void sylvan_init_bdd(int granularity);

/* Create a BDD representing just <var> or the negation of <var> */
BDD sylvan_ithvar(BDDVAR var);
static inline BDD sylvan_nithvar(BDD var) { return sylvan_ithvar(var) ^ sylvan_complement; }

/* Retrieve the <var> of the BDD node <bdd> */
BDDVAR sylvan_var(BDD bdd);

/* Follow <low> and <high> edges */
BDD sylvan_low(BDD bdd);
BDD sylvan_high(BDD bdd);

/* Add or remove external reference to BDD */
BDD sylvan_ref(BDD a); 
void sylvan_deref(BDD a);

/* For use in custom mark functions */
VOID_TASK_DECL_1(sylvan_gc_mark_rec, BDD);
#define sylvan_gc_mark_rec(mdd) CALL(sylvan_gc_mark_rec, mdd)

/* Return the number of external references */
size_t sylvan_count_refs();

/* Unary, binary and if-then-else operations */
#define sylvan_not(a) (((BDD)a)^sylvan_complement)
TASK_DECL_4(BDD, sylvan_ite, BDD, BDD, BDD, BDDVAR);
#define sylvan_ite(a,b,c) (CALL(sylvan_ite,a,b,c,0))
/* Do not use nested calls for xor/equiv parameter b! */
#define sylvan_xor(a,b) (CALL(sylvan_ite,a,sylvan_not(b),b,0))
#define sylvan_equiv(a,b) (CALL(sylvan_ite,a,b,sylvan_not(b),0))
#define sylvan_or(a,b) sylvan_ite(a, sylvan_true, b)
#define sylvan_and(a,b) sylvan_ite(a,b,sylvan_false)
#define sylvan_nand(a,b) sylvan_not(sylvan_and(a,b))
#define sylvan_nor(a,b) sylvan_not(sylvan_or(a,b))
#define sylvan_imp(a,b) sylvan_not(sylvan_and(a,sylvan_not(b)))
#define sylvan_invimp(a,b) sylvan_not(sylvan_and(sylvan_not(a),b))
#define sylvan_biimp sylvan_equiv
#define sylvan_diff(a,b) sylvan_and(a,sylvan_not(b))
#define sylvan_less(a,b) sylvan_and(sylvan_not(a),b)

/* Existential and Universal quantifiers */
TASK_DECL_3(BDD, sylvan_exists, BDD, BDD, BDDVAR);
#define sylvan_exists(a, vars) (CALL(sylvan_exists, a, vars, 0))
#define sylvan_forall(a, vars) (sylvan_not(CALL(sylvan_exists, sylvan_not(a), vars, 0)))

/**
 * Compute \exists v: A(...) \and B(...)
 * Parameter vars is the disjunction of all v variables.
 */
TASK_DECL_4(BDD, sylvan_and_exists, BDD, BDD, BDDSET, BDDVAR);
#define sylvan_and_exists(a,b,vars) CALL(sylvan_and_exists,a,b,vars,0)

/**
 * Compute R(s,t) = \exists x: A(s,x) \and B(x,t)
 *      or R(s)   = \exists x: A(s,x) \and B(x)
 * Assumes s,t are interleaved with s odd and t even.
 * Parameter vars is the disjunction of all s and/or t variables.
 * For variables in A/B that are not in vars, relprev behaves as A \and B
 * Alternatively, vars=true means all variables are in vars
 *
 * Use this function to concatenate two relations   --> -->
 * or to take the 'previous' of a set               -->  S
 */
TASK_DECL_4(BDD, sylvan_relprev, BDD, BDD, BDDSET, BDDVAR);
#define sylvan_relprev(a,b,vars) CALL(sylvan_relprev,a,b,vars,0)

/**
 * Compute R(s) = \exists x: A(x) \and B(x,s)
 * with support(result) = s, support(A) = s, support(B) = s+t
 * Assumes s,t are interleaved with s odd and t even.
 * Parameter vars is the disjunction of all s and/or t variables.
 * For variables in A/B that are not in vars, relnext behaves as A \and B
 * Alternatively, vars=true means all variables are in vars
 *
 * Use this function to take the 'next' of a set     S  -->
 */
TASK_DECL_4(BDD, sylvan_relnext, BDD, BDD, BDDSET, BDDVAR);
#define sylvan_relnext(a,b,vars) CALL(sylvan_relnext,a,b,vars,0)

/**
 * Calculate a@b (a constrain b), such that (b -> a@b) = (b -> a)
 * Special cases:
 *   - a@0 = 0
 *   - a@1 = f
 *   - 0@b = 0
 *   - 1@b = 1
 *   - a@a = 1
 *   - a@not(a) = 0
 */
TASK_DECL_3(BDD, sylvan_constrain, BDD, BDD, BDDVAR);
#define sylvan_constrain(f,c) (CALL(sylvan_constrain, (f), (c), 0))

TASK_DECL_3(BDD, sylvan_restrict, BDD, BDD, BDDVAR);
#define sylvan_restrict(f,c) (CALL(sylvan_restrict, (f), (c), 0))

TASK_DECL_3(BDD, sylvan_compose, BDD, BDDMAP, BDDVAR);
#define sylvan_compose(f,m) (CALL(sylvan_compose, (f), (m), 0))

/**
 * Calculate the support of a BDD.
 * A variable v is in the support of a Boolean function f iff f[v<-0] != f[v<-1]
 * It is also the set of all variables in the BDD nodes of the BDD.
 */
TASK_DECL_1(BDD, sylvan_support, BDD);
#define sylvan_support(bdd) (CALL(sylvan_support, bdd))

/**
 * Reset all counters (for statistics)
 */
void sylvan_reset_counters();

/**
 * Write statistic report to stdout
 */
void sylvan_report_stats();

/**
 * A BDDSET, used by BDD functions.
 * Basically this is a union of all variables in the set in their positive form.
 * Note that you need to do external referencing manually.
 * If using this during your initialization, you could disable GC temporarily.
 */
// empty bddset
#define sylvan_set_empty() sylvan_false
#define sylvan_set_isempty(set) (set == sylvan_false)
// add variables to the bddset
#define sylvan_set_add(set, var) sylvan_or(set, sylvan_ithvar(var))
#define sylvan_set_addall(set, set_to_add) sylvan_or(set, set_to_add)
// remove variables from the bddset
#define sylvan_set_remove(set, var) sylvan_constrain(set, sylvan_nithvar(var))
#define sylvan_set_removeall(set, set_to_remove) sylvan_constrain(set, sylvan_not(set_to_remove))
// iterate through all variables
#define sylvan_set_var(set) (sylvan_var(set))
#define sylvan_set_next(set) (sylvan_low(set))
int sylvan_set_in(BDDSET set, BDDVAR var);
size_t sylvan_set_count(BDDSET set);
void sylvan_set_toarray(BDDSET set, BDDVAR *arr);
TASK_DECL_2(BDDSET, sylvan_set_fromarray, BDDVAR*, size_t);
#define sylvan_set_fromarray(arr, length) ( CALL(sylvan_set_fromarray, arr, length) )
void sylvan_test_isset(BDDSET set);

/**
 * BDDMAP maps BDDVAR-->BDD, implemented using BDD nodes.
 * Based on disjunction of variables, but with high edges to BDDs instead of True terminals.
 */
// empty bddmap
static inline BDDMAP sylvan_map_empty() { return sylvan_false; }
static inline int sylvan_map_isempty(BDDMAP map) { return map == sylvan_false ? 1 : 0; }
// add key-value pairs to the bddmap
BDDMAP sylvan_map_add(BDDMAP map, BDDVAR key, BDD value);
BDDMAP sylvan_map_addall(BDDMAP map_1, BDDMAP map_2);
// remove key-value pairs from the bddmap
BDDMAP sylvan_map_remove(BDDMAP map, BDDVAR key);
BDDMAP sylvan_map_removeall(BDDMAP map, BDDMAP toremove);
// iterate through all pairs
static inline BDDVAR sylvan_map_key(BDDMAP map) { return sylvan_var(map); }
static inline BDD sylvan_map_value(BDDMAP map) { return sylvan_high(map); }
static inline BDDMAP sylvan_map_next(BDDMAP map) { return sylvan_low(map); }
// is a key in the map
int sylvan_map_in(BDDMAP map, BDDVAR key);
// count number of keys
size_t sylvan_map_count(BDDMAP map);
// convert a BDDSET (disjunction of variables) to a map, with all variables pointing on the value
BDDMAP sylvan_set_to_map(BDDSET set, BDD value);

/**
 * Node creation primitive.
 * Careful: does not check ordering!
 * Preferably only use when debugging!
 */
BDD sylvan_makenode(BDDVAR level, BDD low, BDD high);

/**
 * Write a DOT representation of a BDD
 */
void sylvan_printdot(BDD bdd);
void sylvan_fprintdot(FILE *out, BDD bdd);

void sylvan_printdot_nocomp(BDD bdd);
void sylvan_fprintdot_nocomp(FILE *out, BDD bdd);

void sylvan_print(BDD bdd);
void sylvan_fprint(FILE *f, BDD bdd);

void sylvan_printsha(BDD bdd);
void sylvan_fprintsha(FILE *f, BDD bdd);
void sylvan_getsha(BDD bdd, char *target); // target must be at least 65 bytes...

/**
 * Convert normal BDD to a BDD without complement edges
 * Also replaces sylvan_true by sylvan_true_nc
 * Function only meant for debugging purposes.
 */
BDD sylvan_bdd_to_nocomp(BDD bdd);

/**
 * Calculate number of satisfying variable assignments.
 * The set of variables must be >= the support of the BDD.
 * (i.e. all variables in the BDD must be in variables)
 * 
 * The cached version uses the operation cache, but is limited to 64-bit floating point numbers.
 */

typedef double sylvan_satcount_double_t;
// if this line below gives an error, modify the above typedef until fixed ;)
typedef char __sylvan_check_double_is_8_bytes[(sizeof(sylvan_satcount_double_t) == sizeof(uint64_t))?1:-1];

TASK_DECL_3(sylvan_satcount_double_t, sylvan_satcount_cached, BDD, BDDSET, BDDVAR);
#define sylvan_satcount_cached(bdd, variables) CALL(sylvan_satcount_cached, bdd, variables, 0)

TASK_DECL_2(long double, sylvan_satcount, BDD, BDDSET);
#define sylvan_satcount(bdd, variables) CALL(sylvan_satcount, bdd, variables)

/**
 * Create a BDD cube representing the conjunction of variables in their positive or negative
 * form depending on whether the cube[idx] equals 0 (negative), 1 (positive) or 2 (any).
 * CHANGED 2014/09/19: vars is now a BDDSET (ordered!)
 */
BDD sylvan_cube(BDDSET variables, char *cube);
TASK_DECL_3(BDD, sylvan_union_cube, BDD, BDDSET, char*);
#define sylvan_union_cube(bdd, variables, cube) CALL(sylvan_union_cube, bdd, variables, cube)

/**
 * Pick one satisfying variable assignment randomly for which <bdd> is true.
 * Note that <variables> must include all variables in the support of <bdd>,
 * and that count must equal the size of both arrays.
 *
 * The function will set the values of str, such that
 * str[index] where index is the index in the <variables> set is set to
 * 0 when the variable is negative, 1 when positive, or 2 when it could be either.
 *
 * Returns 1 when succesful, or 0 when no assignment is found (i.e. bdd==sylvan_false).
 */
int sylvan_sat_one(BDD bdd, BDDVAR *variables, size_t count, char* str);

/**
 * Pick one satisfying variable assignment randomly from the given <bdd>.
 * Functionally equivalent to performing sylvan_cube on the result of sylvan_sat_one.
 * For the result: sylvan_and(res, bdd) = res.
 */
BDD sylvan_sat_one_bdd(BDD bdd);
#define sylvan_pick_cube sylvan_sat_one_bdd

TASK_DECL_1(long double, sylvan_pathcount, BDD);
#define sylvan_pathcount(bdd) (CALL(sylvan_pathcount, bdd))

// TASK_DECL_1(size_t, sylvan_nodecount, BDD);
size_t sylvan_nodecount(BDD a);
void sylvan_nodecount_levels(BDD bdd, uint32_t *variables);

/**
 * SAVING:
 * use sylvan_serialize_add on every BDD you want to store
 * use sylvan_serialize_get to retrieve the key of every stored BDD
 * use sylvan_serialize_tofile
 *
 * LOADING:
 * use sylvan_serialize_fromfile (implies sylvan_serialize_reset)
 * use sylvan_serialize_get_reversed for every key
 *
 * MISC:
 * use sylvan_serialize_reset to free all allocated structures
 * use sylvan_serialize_totext to write a textual list of tuples of all BDDs.
 *         format: [(<key>,<level>,<key_low>,<key_high>,<complement_high>),...]
 *
 * for the old sylvan_print functions, use sylvan_serialize_totext
 */
size_t sylvan_serialize_add(BDD bdd);
size_t sylvan_serialize_get(BDD bdd);
BDD sylvan_serialize_get_reversed(size_t value);
void sylvan_serialize_reset();
void sylvan_serialize_totext(FILE *out);
void sylvan_serialize_tofile(FILE *out);
void sylvan_serialize_fromfile(FILE *in);

/* For debugging: if the bdd is not a well-formed BDD, assertions fail. */
void sylvan_test_isbdd(BDD bdd);

/* Infrastructure for internal markings */
typedef struct bdd_refs_internal
{
    size_t r_size, r_count;
    size_t s_size, s_count;
    BDD *results;
    Task **spawns;
} *bdd_refs_internal_t;

extern DECLARE_THREAD_LOCAL(bdd_refs_key, bdd_refs_internal_t);

static inline BDD
bdd_refs_push(BDD bdd)
{
    LOCALIZE_THREAD_LOCAL(bdd_refs_key, bdd_refs_internal_t);
    if (bdd_refs_key->r_count >= bdd_refs_key->r_size) {
        bdd_refs_key->r_size *= 2;
        bdd_refs_key->results = (BDD*)realloc(bdd_refs_key->results, sizeof(BDD) * bdd_refs_key->r_size);
    }
    bdd_refs_key->results[bdd_refs_key->r_count++] = bdd;
    return bdd;
}

static inline void
bdd_refs_pop(int amount)
{
    LOCALIZE_THREAD_LOCAL(bdd_refs_key, bdd_refs_internal_t);
    bdd_refs_key->r_count-=amount;
}

static inline void
bdd_refs_spawn(Task *t)
{
    LOCALIZE_THREAD_LOCAL(bdd_refs_key, bdd_refs_internal_t);
    if (bdd_refs_key->s_count >= bdd_refs_key->s_size) {
        bdd_refs_key->s_size *= 2;
        bdd_refs_key->spawns = (Task**)realloc(bdd_refs_key->spawns, sizeof(Task*) * bdd_refs_key->s_size);
    }
    bdd_refs_key->spawns[bdd_refs_key->s_count++] = t;
}

static inline BDD
bdd_refs_sync(BDD result)
{
    LOCALIZE_THREAD_LOCAL(bdd_refs_key, bdd_refs_internal_t);
    bdd_refs_key->s_count--;
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
