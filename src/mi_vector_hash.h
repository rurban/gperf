#include <stdint.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C"
#endif
void mi_vector_hash(const void *__restrict key, 
                    size_t keylen, uint32_t seed, uint32_t *hashes);
