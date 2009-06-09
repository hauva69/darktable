#ifndef DT_PIXELPIPE_CACHE_H
#define DT_PIXELPIPE_CACHE_H

#include "develop/develop.h"

/**
 * implements a simple pixel cache suitable for caching float images
 * corresponding to history items and zoom/pan settings in the develop module.
 * it is optimized for very few entries (~5), so most operations are O(N).
 */
typedef struct dt_dev_pixelpipe_cache_t
{
  int32_t  entries;
  void    **data;
  uint64_t *hash;
  int32_t  *used;
}
dt_dev_pixelpipe_cache_t;

/** constructs a new cache with given cache line count (entries) and float buffer entry size in bytes. */
void dt_dev_pixelpipe_cache_init(dt_dev_pixelpipe_cache_t *cache, int entries, int size);
void dt_dev_pixelpipe_cache_cleanup(dt_dev_pixelpipe_cache_t *cache);

/** creates a hopefully unique hash from the complete module stack up to the module-th. */
uint64_t dt_dev_pixelpipe_cache_hash(float scale, float x, float y, dt_develop_t *dev, int module);

/** returns the float data buffer for the given hash from the cache. if the hash does not match any
  * cache line, the least recently used cache line will be cleared and an empty buffer is returned
  * together with a non-zero return value. */
int dt_dev_pixelpipe_cache_get(dt_dev_pixelpipe_cache_t *cache, const uint64_t hash, void **data);

/** test availability of a cache line without destroying another, if it is not found. */
int dt_dev_pixelpipe_cache_available(dt_dev_pixelpipe_cache_t *cache, const uint64_t hash);


#endif
