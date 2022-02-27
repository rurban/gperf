/* Written by Reini Urban and 王一 Wang Yi <godspeed_china@yeah.net>, 2022 */
/* Released into the public domain under The Unlicense (http://unlicense.org/) */
#include <stdint.h>
/* Need to include wyhash.h externally */

/* MPH needs at least 96 bit */
static inline void wyhash3(const void *key, size_t len, uint64_t seed, uint64_t *hashes){
  const uint64_t secret[4] = { _wyp[0],_wyp[1],_wyp[2],_wyp[3] };
  const uint8_t *p=(const uint8_t *)key; seed^=secret[0];
  uint64_t a, b;
  if(_likely_(len<=16)){
    if(_likely_(len>=4)){
	a=(_wyr4(p)<<32)|_wyr4(p+((len>>3)<<2));
	b=(_wyr4(p+len-4)<<32)|_wyr4(p+len-4-((len>>3)<<2));
    }
    else if(_likely_(len>0)){ a=_wyr3(p,len); b=0;}
    else a=b=0;
  }
  else{
    size_t i=len; 
    if(_unlikely_(i>48)){
      uint64_t see1=seed, see2=seed;
      do{
        seed=_wymix(_wyr8(p)^secret[1],_wyr8(p+8)^seed);
        see1=_wymix(_wyr8(p+16)^secret[2],_wyr8(p+24)^see1);
        see2=_wymix(_wyr8(p+32)^secret[3],_wyr8(p+40)^see2);
        p+=48; i-=48;
      }while(_likely_(i>48));
      seed^=see1^see2;
    }
    while(_unlikely_(i>16)){  seed=_wymix(_wyr8(p)^secret[1],_wyr8(p+8)^seed);  i-=16; p+=16;  }
    a=_wyr8(p+i-16);  b=_wyr8(p+i-8);
  }
  hashes[0] = _wymix(secret[1]^len,_wymix(a^secret[1],b^seed));
  hashes[1] = _wymix(b^secret[1],a^seed);
}
