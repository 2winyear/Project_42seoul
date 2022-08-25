#ifndef FT_HOSTCMP_H
#define FT_HOSTCMP_H

#define FT_COMPARE(A, B) ((A) == (B))

#if defined(FT_USE_32_BIT)
  #define FT_HOST_CMP_IMPL(A, B) ( \
    FT_COMPARE(((A) & (0xff << 0)) >> 0, (((B) & (0xff << 24)) >> 24)) \
    && FT_COMPARE(((A) & (0xff << 8)) >> 8, (((B) & (0xff << 16)) >> 16)) \
    && FT_COMPARE(((A) & (0xff << 16)) >> 16, (((B) & (0xff << 8)) >> 8)) \
    && FT_COMPARE(((A) & (0xff << 24)) >> 24, ((B) & 0xff)) \
  )
#else
  #define FT_HOST_CMP_IMPL(A, B) (FT_COMPARE((A) & 0xffUL, ((B) & (0xffUL << 56)) >> 56) && FT_COMPARE(((A) & (0xffUL << 8)) >> 8, ((B) & (0xffUL << 48)) >> 48) \
        && FT_COMPARE(((A) & (0xffUL << 16)) >> 16, ((B) & (0xffUL << 40)) >> 40) && FT_COMPARE(((A) & (0xffUL << 24)) >> 24, ((B) & (0xffUL << 32)) >> 32) \
        && FT_COMPARE(((A) & (0xffUL << 32)) >> 32, ((B) & (0xffUL << 24)) >> 24) && FT_COMPARE(((A) & (0xffUL << 40)) >> 40, ((B) & (0xffUL << 16)) >> 16) \
        && FT_COMPARE(((A) & (0xffUL << 48)) >> 48, ((B) & (0xffUL << 8)) >> 8) && FT_COMPARE(((A) & (0xffUL << 56)) >> 56, (B) & 0xffUL))
#endif

#if defined(FT_USE_LITTLE_ENDIAN)
    #define FT_HOSTCMP(A, B) (!(FT_HOST_CMP_IMPL((A), (B))))
#else
    #define FT_HOSTCMP(A, B) ((A) != (B))
#endif

#endif