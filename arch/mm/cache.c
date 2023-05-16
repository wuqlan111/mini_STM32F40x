
#include  <stdint.h>
#include  <memory.h>
#include  <math.h>

#include  "arch_regs.h"
#include  "cache.h"

#define  MAX_CACHE_WRITE_BACK      (2048)
#define  CTR_CWG_BIT       (24)
#define  CTR_ERG_BIT       (20)
#define  CTR_DCACHE_MIN_BIT     (16)

typedef  struct {
    uint8_t  write_through:1;
    uint8_t  write_back:1;
    uint8_t  read_alloc:1;
    uint8_t  write_alloc:1;
    uint8_t  icache:1;
    uint8_t  dcache:1;
    uint8_t  ucache:1;
    uint8_t  set_number;
    uint8_t  cache_associativity;
    uint8_t  line_size;         // line byte size
} ATTRIBUTE_PACK cache_info_t;



uint32_t get_cache_write_back_granule(void)
{
    uint32_t val = REG32_READ(ID_CTR_REG_ADDR)>>CTR_CWG_BIT & 0xf;
    return  1<<(val + 2);
}


uint32_t get_cache_exclusive_access_granule(void)
{
    uint32_t val = REG32_READ(ID_CTR_REG_ADDR)>>CTR_ERG_BIT & 0xf;
    return  1<<(val+2);
}


uint32_t get_dcache_min_line(void)
{
    uint32_t val = REG32_READ(ID_CTR_REG_ADDR)>>CTR_DCACHE_MIN_BIT & 0xf;
    return  1<<(val+2);
}


uint32_t get_icache_min_line(void)
{
    uint32_t val = REG32_READ(ID_CTR_REG_ADDR) & 0xf;
    return  1<<(val+2);
}


int32_t  get_cache_info(uint32_t  level, cache_info_t * info)
{
    if ( (level > 7) || !info) {
        //;
        return  -1;
    }

    memset(info, 0, sizeof(cache_info_t));

    uint32_t  flag  =  0;
    uint32_t  type  =  get_cache_type(level);
    if (type  == CTYPE_DATA_CACHE) {
        info->dcache  = 1;
    } else if (type == CTYPE_INSTRUCTION_CACHE) {
        info->icache  =  1;
        flag |= 0x1;
    } else if (type == CTYPE_UNIFIED_CACHE) {
        info->ucache = 1;
    } else if (type == CTYPE_NO_CACHE) {
        return  -1;
    }
    
    flag |= (level << 1);
 
    REG32_UPDATE(ID_CSSELR_REG_ADDR, flag, 0xf);

    uint32_t  val =  REG32_READ(ID_CCSIDR_REG_ADDR);

    info->write_through  =  val & (1 << 31)? 1: 0;
    info->write_back     =  val & (1 << 30)? 1: 0;
    info->read_alloc     =  val & (1 << 29)? 1: 0;
    info->write_alloc    =  val & (1 << 28)? 1: 0;
    info->set_number     =  ((val >> 13) & 0x7fff) + 1;
    info->cache_associativity   =  ((val >> 3) & 0x3ff) + 1;
    info->line_size      =  1 << ((val & 0x7) + 2);

    return  0;
}


inline  uint32_t  get_level_of_unification(void)
{
    return  (REG32_READ(ID_CCSIDR_REG_ADDR) >> 27)  & 0x7;
}


inline  uint32_t  get_level_of_coherency(void)
{
    return  (REG32_READ(ID_CCSIDR_REG_ADDR) >> 24)  & 0x7;
}



inline  void  invalidate_all_icache_to_pou(void)
{
    REG32_WRITE(CAHCE_ICIALLU_REG_ADDR,  0);
}

inline  void  invalidate_icache_by_mva(uint32_t addr)
{
    REG32_WRITE(CAHCE_ICIMVAU_REG_ADDR,  addr);
}



inline  void  invalidate_dcache_by_mva(uint32_t addr)
{
    REG32_WRITE(CAHCE_DCIMVAC_REG_ADDR,  addr);
}

void  invalidate_dcache_by_set(uint32_t level, uint32_t set, uint32_t way)
{
    cache_info_t info = {0};    
    if((level  > 7 ) || get_cache_info(level, &info))
        return;

    uint32_t  associaty  =  log2(info.cache_associativity);
    uint32_t  line       =  log2(info.line_size);
    uint16_t  sets       =  log2(info.set_number);

    if ( (set > info.set_number) || (way > info.cache_associativity) )
        return;

    uint32_t way_flag  =  associaty? 0: (way << (32 - associaty));
    uint32_t set_flag  =  line > 4 ? (set << line):set << 4;

    uint32_t  val  =  way_flag | set_flag  | ((level -1) << 1);

    REG32_WRITE(CAHCE_DCISW_REG_ADDR, val);

}

inline  void  clean_dcache_by_mva_pou(uint32_t addr)
{
    REG32_WRITE(CAHCE_DCCMVAU_REG_ADDR,  addr);
}


inline  void  clean_dcache_by_mva_poc(uint32_t addr)
{
    REG32_WRITE(CAHCE_DCCMVAC_REG_ADDR,  addr);
}


void  clean_dcache_by_set(uint32_t level, uint32_t set, uint32_t way)
{
    cache_info_t info = {0};    
    if((level  > 7 ) || get_cache_info(level, &info))
        return;

    uint32_t  associaty  =  log2(info.cache_associativity);
    uint32_t  line       =  log2(info.line_size);
    uint16_t  sets       =  log2(info.set_number);

    if ( (set > info.set_number) || (way > info.cache_associativity) )
        return;

    uint32_t way_flag  =  associaty? 0: (way << (32 - associaty));
    uint32_t set_flag  =  line > 4 ? (set << line):set << 4;

    uint32_t  val  =  way_flag | set_flag  | ((level -1) << 1);

    REG32_WRITE(CAHCE_DCCSW_REG_ADDR, val);

}


inline  void  clean_invalidate_dcache_by_mva_poc(uint32_t addr)
{
    REG32_WRITE(CAHCE_DCCIMVAC_REG_ADDR,  addr);
}


void  clean_invalidate_dcache_by_set(uint32_t level, uint32_t set, uint32_t way)
{
    cache_info_t info = {0};    
    if((level  > 7 ) || get_cache_info(level, &info))
        return;

    uint32_t  associaty  =  log2(info.cache_associativity);
    uint32_t  line       =  log2(info.line_size);
    uint16_t  sets       =  log2(info.set_number);

    if ( (set > info.set_number) || (way > info.cache_associativity) )
        return;

    uint32_t way_flag  =  associaty? 0: (way << (32 - associaty));
    uint32_t set_flag  =  line > 4 ? (set << line):set << 4;

    uint32_t  val  =  way_flag | set_flag  | ((level -1) << 1);

    REG32_WRITE(CAHCE_DCCISW_REG_ADDR, val);

}











