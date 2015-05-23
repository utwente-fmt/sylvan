#include<hash16.h>


uint64_t
rehash16_mul(const void *key, const uint64_t seed)
{
    const uint64_t prime = 1099511628211;
    const uint64_t *p = (const uint64_t *)key;

    uint64_t hash = seed;
    hash = hash ^ p[0];
    hash = rotl64(hash, 47);
    hash = hash * prime;
    hash = hash ^ p[1];
    hash = rotl64(hash, 31);
    hash = hash * prime;

    return hash ^ (hash >> 32);
}

uint64_t
hash16_mul(const void *key)
{
    return rehash16_mul(key, 14695981039346656037LLU);
}
