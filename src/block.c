#include "garble/block.h"
#include "garble/aes.h"

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <openssl/rand.h>

static AES_KEY rand_aes_key;
static uint64_t current_rand_index;

block
garble_seed(block *seed)
{
    block cur_seed;
    current_rand_index = 0;
    if (seed) {
        cur_seed = *seed;
    } else {
        fprintf(stderr, "** insecure seeding of randomness!\n");
        srand(time(NULL));
        cur_seed = _mm_set_epi32(rand(), rand(), rand(), rand());
    }
    AES_set_encrypt_key(cur_seed, &rand_aes_key);
    return cur_seed;
}

inline block
garble_random_block(void)
{
    block out;
    uint64_t *val;
    int i;

    out = garble_zero_block();
    val = (uint64_t *) &out;
    val[0] = current_rand_index++;
    out = _mm_xor_si128(out, rand_aes_key.rd_key[0]);
    for (i = 1; i < 10; ++i)
        out = _mm_aesenc_si128(out, rand_aes_key.rd_key[i]);
    return _mm_aesenclast_si128(out, rand_aes_key.rd_key[i]);
}

block *
garble_allocate_blocks(size_t nblocks)
{
    int res;
    block *blks = NULL;;
    res = posix_memalign((void **) &blks, 128, sizeof(block) * nblocks);
    if (res == 0) {
        return blks;
    } else {
        perror("allocate_blocks");
        return NULL;
    }
}