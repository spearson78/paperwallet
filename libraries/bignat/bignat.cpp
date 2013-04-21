// This code is derived from golangs math/big package
// Copyright 2009 The Go Authors. All rights reserved.
// Arduino Port Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.

#include <bignat.h>
#include <panic.h>

//#define ALIASCHECKS

const WORD _S = sizeof(WORD);
const WORD _W = _S << 3;
const WORD _B = (WORD)(1<<_W);
const WORD _M = _B-1;

const WORD _W2 = _W/2;
const WORD _B2 = 1 << _W2;
const WORD _M2 = _B2-1;

bignat::bignat(WORD *data,int cap) : data(data),cap(cap),len(0) {
}

inline void bignat::make(int n) {
  if( n<= this->cap ){
    this->len=n;
    return;
  } else {
    PANIC(PANIC_NAT_MAKE_OVERFLOW);
  }  
}

inline void bignat::norm(){
  int i = this->len;
  while( i>0 && this->data[i-1] == 0 ){
    i--;
  }
  this->len=i;
}

void bignat::Set(const struct bignat &b){
#ifdef ALIASCHECKS
  if( this!=&b ){
#endif
    this->make(b.len);
    memcpy(this->data,b.data,b.len * sizeof(WORD));
#ifdef ALIASCHECKS
  } else {
    PANIC(PANIC_NAT_SET_ALIAS);
  }
#endif
}

void bignat::Set(WORD word) {
    this->make(1);
    this->data[0]=word;
}

WORD bignat::subWW(WORD *z0,WORD x,WORD y,WORD c){
  WORD z1 = 0;
  
  WORD yc = y+c;
  *z0 = x-yc;
  if( *z0 > x || yc < y ){
    z1 = 1;
  }
  
  return z1;
}

WORD bignat::addWW(WORD *z0,WORD x,WORD y,WORD c){
  WORD z1 = 0;
  
  WORD yc = y+c;
  *z0 = x+yc;
  if( *z0 < x || yc < y ){
    z1 = 1;
  }
  
  return z1;
}

WORD bignat::addVV(WORD *z,int limit,const WORD *x,const WORD *y){
  WORD c=0;
  for( int i = 0 ; i < limit ; i++ ){
    c = bignat::addWW(z+i,x[i],y[i],c);
  }
  
  return c;
}

WORD bignat::subVV(WORD *z,int limit,const WORD *x,const WORD *y){
  WORD c=0;
  for( int i = 0 ; i < limit ; i++ ){
    c = bignat::subWW(z+i,x[i],y[i],c);
  }
  
  return c;
}


WORD bignat::addVW(WORD *z,int zlen,const WORD *x,WORD y){
  WORD c=y;
  
  for( int i = 0 ; i < zlen ; i++ ){
    c = bignat::addWW(&z[i],x[i],c,0);
  }
  
  return c;
}

WORD bignat::subVW(WORD *z,int zlen,const WORD *x,WORD y){
  WORD c=y;
  
  for( int i = 0 ; i < zlen ; i++ ){
    c = bignat::subWW(&z[i],x[i],c,0);
  }
  
  return c;
}

void bignat::Add(const struct bignat &x,const struct bignat &y){
  int m = x.len;
  int n = y.len;
  
  if( m < n ){
    this->Add(y,x);
    return;
  } else if(  m == 0 ){
    this->make(0);
    return;
  } else if( n== 0 ){
    this->Set(x);
    return;
  }

  this->make(m+1);
  WORD c = bignat::addVV(this->data,n,x.data,y.data);
 
  if( m > n ){
    c = bignat::addVW(&this->data[n],m-n,&x.data[n],c);
  }
  this->data[m]=c;
  
  this->norm();
}

void bignat::Sub(const struct bignat &x,const struct bignat &y){
  int m = x.len;
  int n = y.len;
  
  if( m < n ){
    PANIC(PANIC_NAT_SUB_UNDERFLOW);
    return;
  } else if(  m == 0 ){
    this->make(0);
    return;
  } else if( n== 0 ){
    this->Set(x);
    return;
  }

  this->make(m);
  WORD c = bignat::subVV(this->data,n,x.data,y.data);
 
  if( m > n ){
    c = bignat::subVW(&this->data[n],m-n,&x.data[n],c);
  }
  if( c!=0 ){
    PANIC(PANIC_NAT_SUB_CNONZERO);
    return;
  }
  
  this->norm();
}

void bignat::SetBytes(const uint8_t *buf,int len) {
  
  this->make((len+_S-1)/_S);
  
  int k = 0;
  WORD s = 0;
  WORD d = 0;
  
  for(int i=len;i>0;i--){
    d|= ((WORD)buf[i-1]) << s;
    s+=8;
    if( s== _S*8) {
      this->data[k]=d;
      k++;
      s=0;
      d=0;
    }
  }
  if( k < this->len ){
    this->data[k]=d;
  }
  
  this->norm();
}

void bignat::SetBytesP(const uint8_t *buf,int len) {
  
  this->make((len+_S-1)/_S);
  
  int k = 0;
  WORD s = 0;
  WORD d = 0;
  
  for(int i=len;i>0;i--){
    d|= ((WORD)pgm_read_byte(buf+i-1)) << s;
    s+=8;
    if( s== _S*8) {
      this->data[k]=d;
      k++;
      s=0;
      d=0;
    }
  }
  if( k < this->len ){
    this->data[k]=d;
  }
  
  this->norm();
}

inline WORD bignat::Word() const{
  if( this->len==0){
    return 0;
  } else if( this->len>1){
    PANIC(PANIC_NAT_TOWORD_OVERFLOW);
    return 0;
  } else {
    return this->data[0];
  }
  
}

inline WORD bignat::leadingZeros(WORD x){
  int n=0;
  //NOT needed on 8bit arduino uno need to re-enable on 32 bit systems
  //while( x >= 0x8000){
  //  x>>=16;
  //  n+=16;
  //}
  
  if( x>= 0x80 ){
    x>>=8;
    n+=8;
  }
  if( x>= 0x8 ){
    x>>=4;
    n+=4;
  }  
  if( x>= 0x2 ){
    x>>=2;
    n+=2;
  }    
  if( x>= 0x1 ){
    n++;
  }     
 
  return _W -n; 
}

inline WORD bignat::divWW(WORD u1,WORD u0,WORD v,WORD *r){
  WORD q=0;
  if( u1 >= v ){
    q = (1<<_W) -1;
    *r = (1<<_W) -1;
    return q;
  }
  
  WORD s = leadingZeros(v);
  v <<= s;
  
  WORD vn1 = v >> _W2;
  WORD vn0 = v &_M2;
  WORD un32 = u1<<s | u0>>(_W-s);
  WORD un10 = u0<<s;
  WORD un1 = un10 >> _W2;
  WORD un0 = un10 & _M2;
  WORD q1 = un32 / vn1;
  WORD rhat = un32 - q1*vn1;
  
again1:
  if( q1 >= _B2 || q1*vn0 > _B2*rhat+un1 ){
    q1--;
    rhat += vn1;
    if( rhat < _B2 ){
      goto again1;
    }
  }
  
  WORD un21 = un32*_B2+un1-q1*v;
  WORD q0 = un21/vn1;
  rhat = un21-q0*vn1;
  
again2:
  if( q0 >= _B2 || q0*vn0 > _B2*rhat+un0){
    q0--;
    rhat += vn1;
    if( rhat < _B2 ){
      goto again2;
    }
  }

  q = q1*_B2+q0;
  *r = (un21*_B2 + un0 - q0*v) >> s;
  
  return q;
}


inline void bignat::reverseInPlace(char *in,int l){
  int hl = l/2;
  
  for( int i=0;i<hl;i++){
    int j = l-i-1;
    char t = in[i];
    in[i]=in[j];
    in[j]=t;    
  }
}

void bignat::String(WORD base,const char *map,char *out,int limit) const{ 
  WORD abuf[196];
  struct bignat a(abuf,sizeof(abuf));
  a.Set(*this);
  WORD qbuf[196];
  struct bignat q(qbuf,sizeof(qbuf));

  WORD bbuf[1];
  struct bignat b(bbuf,sizeof(bbuf));
  b.make(1);
  bbuf[0]=base;

  WORD rbuf[1];
  struct bignat r(rbuf,sizeof(rbuf));

  struct bignat zero(NULL,0);
  
  int encodedLen=0;

  while( a.Cmp(zero) > 0 && encodedLen < limit){
    q.Div(a,b,r,NULL);
  
    out[encodedLen]=pgm_read_byte(map+r.Word());
    encodedLen++;
  
    a.Set(q);
  }
   
  reverseInPlace(out,encodedLen);
  
  out[encodedLen]=0;
  
  if( encodedLen == limit){
    PANIC(PANIC_NAT_TOSTRING_OVERFLOW);
  }
}

void bignat::Mul(const struct bignat &x,const struct bignat&y){
  int m = x.len;
  int n = y.len;
  
  if( m<n ){
    this->Mul(y,x);
  } else if( m== 0 || n== 0 ){
    this->make(0);
  } else if (n == 1){
    this->mulAddWW(x,y.data[0],0);
  } else {
    //m>= n > 1
   
#ifdef ALIASCHECKS
    if( &x == this || &y == this ){
      PANIC(PANIC_NAT_MUL_ALIAS);
      return;
    }
#endif

    this->basicMul(x,y);
    this->norm();
  }
}

void bignat::mulAddWW(const struct bignat &x,WORD y,WORD r){
  int m = x.len;
  if( m==0 || y==0 ){
    this->make(1);
    this->data[0]=r;
    return;
  }

  //m>0

  this->make(m+1);
  this->data[m] = bignat::mulAddVWW(this->data,m,x.data,y,r);
  this->norm();
}

void bignat::basicMul(const struct bignat &x,const struct bignat &y){
  this->make(x.len+y.len);
  memset(this->data,0,this->len);
  for( int i = 0 ; i < y.len ; i++ ){
    WORD d = y.data[i];
    if( d!=0){
      this->data[x.len+i] = bignat::addMulVVW(this->data+i,x.len,x.data,d);
    }
  }
}

WORD bignat::mulAddVWW(WORD *z,int zlen,const WORD *x,WORD y,WORD r){
  int c = r;
  for( int i=0; i<zlen ;i++){
    c = bignat::mulAddWWW(z+i,x[i],y,c);
  }
  return c;
}

WORD bignat::mulAddWWW(WORD *z0,WORD x,WORD y,WORD c){
  WORD zz0 = 0;
  WORD z1 = bignat::mulWW(&zz0,x,y);
  *z0 = zz0+c;
  if( *z0 < zz0 ){
    z1++;
  }
  return z1;
}

WORD bignat::mulWW(WORD *z0,WORD x,WORD y){

  WORD x0 = x & _M2;
  WORD x1 = x >> _W2;
  WORD y0 = y & _M2;
  WORD y1 = y >> _W2;
  WORD w0 = x0 * y0;
   
  WORD t = x1*y0 + (w0>>_W2);
  WORD w1 = t & _M2;
  WORD w2 = t >> _W2;
  w1 += x0 * y1;
  
  WORD z1 = x1*y1+w2+(w1>>_W2);
  *z0 = x*y;
  
  return z1;
}

WORD bignat::addMulVVW(WORD *z,int zlen,const WORD *x,WORD y){
  WORD c=0;
  
  for( int i=0;i<zlen;i++){
    WORD z0 = 0;
    WORD z1 = bignat::mulAddWWW(&z0,x[i],y,z[i]);
    c = bignat::addWW(z+i,z0,c,0);
    c += z1;
  }
  return c;
}

void bignat::Div(const struct bignat &u,const struct bignat &v,struct bignat &r, WORD vbuf[33]){
  if(v.len == 0){
    PANIC(PANIC_NAT_DIVZERO);
    return;
  }
  
  if( u.Cmp(v) < 0 ){
    this->make(0);
    r.Set(u);
    return;
  }
  
  if( v.len == 1 ){
    WORD rprime = this->divW(u,v.data[0]);
    if( rprime > 0 ){
      r.make(1);
      r.data[0]=rprime;
    } else {
      r.make(0);
    }
    return;
  }
  
  this->divLarge(u,v,r,vbuf);
}

int bignat::Cmp(const struct bignat &y) const{
  int m = this->len;
  int n = y.len;
  if( m!=n || m==0 ){
    if( m<n){
      return -1;
    } else if (m>n){
      return 1;
    } else {
      return 0;
    }    
  }
  
  int i = m-1;
  while( i>0 && this->data[i] == y.data[i] ){
    i--;
  }
  
  if( this->data[i] < y.data[i] ){
    return -1;
  } else if( this->data[i] > y.data[i] ){
    return 1;
  } else {
    return 0;
  }
}

WORD bignat::divW(const struct bignat &x,WORD y){
  int m = x.len;
  if ( y==1 ){
    this->Set(x);
    return 0;
  } else if(m==0){
    this->make(0);
    return 0;
  }
  
  this->make(m);
  WORD r = bignat::divWVW(this->data,m,0,x.data,y);
  this->norm();
  return r;
}

WORD bignat::divWVW(WORD *z,int zlen,WORD xn,const WORD *x,WORD y){
  WORD r =xn;
  for( int i=zlen-1;i>=0;i--){
    z[i] = bignat::divWW(r,x[i],y,&r);
  }
  return r;
}

WORD bignat::shlVU(WORD *z,int n,const WORD *x,unsigned int s){
  WORD c=0;
  if( n>0 ){
    WORD shat = _W-s;
    WORD w1 = x[n-1];
    c = w1>>shat;
    for( int i= n-1;i>0;i--){
      WORD w = w1;
      w1 = x[i-1];
      z[i] = w<<s | w1>>shat;
    }
    z[0] = w1 << s;
  } 
 
 return c; 
}

WORD bignat::shrVU(WORD *z,int lenz,const WORD *x,unsigned int s){
  WORD c=0;
  int n = lenz;
  if( n>0 ){
    WORD shat = _W-s;
    WORD w1 = x[0];
    c = w1<<shat;
    for( int i= 0;i<n-1;i++){
      WORD w = w1;
      w1 = x[i+1];
      z[i] = w>>s | w1<<shat;
    }
    z[n-1] = w1 >> s;
  } 
 
 return c; 
}

int bignat::greaterThan(WORD x1,WORD x2,WORD y1,WORD y2){
  return x1>y1 || (x1==y1 && x2>y2);
}

void bignat::divLarge(const struct bignat &uIn,const struct bignat &vIn,struct bignat &r,WORD vbuf[33]){
  int n = vIn.len;
  int m = uIn.len-n;
  
#ifdef ALIASCHECKS
  if( this == &uIn || this == &vIn || &r == &uIn){
    PANIC(PANIC_NAT_DIV_ALIAS);
    return;
  }
#endif

  if( this->cap != 0 ){
    this->make(m+1);
    memset(this->data,0,this->len);
  }

  r.make(uIn.len+1);
  memset(r.data,0,r.len);

  WORD qhatvbuf[33];
  struct bignat qhatv(qhatvbuf,sizeof(qhatvbuf));
  qhatv.make(n+1);
  
  WORD shift = bignat::leadingZeros(vIn.data[n-1]);

  //TODO: GCD needs shift support but it overflows the stack for scalarMult :(
  const struct bignat *v = &vIn;
  if( shift > 0 ) {
#ifdef ALIASCHECKS
    if( vbuf == 0 ){
      PANIC(PANIC_NAT_DIV_SHIFTOFF);
      return;
    }
#endif
    struct bignat v1(vbuf,33);
    v1.make(n);
    bignat::shlVU(v1.data,n,vIn.data,shift);
    v = &v1;
  }
 
  r.data[uIn.len] = bignat::shlVU(r.data,uIn.len,uIn.data,shift); 
  
  //D2
  for( int j = m;j>=0;j--){
    //D3
    WORD qhat = _M;
    if( r.data[j+n] != v->data[n-1] ) {
      WORD rhat = 0;
      
      qhat = divWW(r.data[j+n],r.data[j+n-1],v->data[n-1],&rhat);
      
      WORD x2=0;
      WORD x1 = mulWW(&x2,qhat,v->data[n-2]);
      
      while( bignat::greaterThan(x1,x2,rhat,r.data[j+n-2]) ) {
        qhat--;
        WORD prevRhat = rhat;
        rhat += v->data[n-1];
        if( rhat < prevRhat ){
          break;
        }
        x1 = mulWW(&x2,qhat,v->data[n-2]);
      }
    }

    //D4
    qhatv.data[n] = mulAddVWW(qhatv.data,n,v->data,qhat,0);
    
    WORD c = subVV(r.data+j,qhatv.len,r.data+j,qhatv.data);
    if( c!=0 ){
      c = bignat::addVV(r.data+j,n,r.data+j,v->data);
      r.data[j+n] += c;
      qhat--;
    }

    if( this->cap != 0 ){
      this->data[j] = qhat;
    }
  }
  
  this->norm();
  bignat::shrVU(r.data,r.len,r.data,shift);
  r.norm();
}

void bignat::Shl(const struct bignat &x,unsigned int s){
  int m = x.len;
  if(m == 0){
    this->make(0);
    return;
  }

  int n = m+(int)(s/_W);
  this->make(n+1);

  this->data[n] = bignat::shlVU(this->data+n-m,m,x.data,s%_W);
  memset(this->data,0,n-m);

  this->norm();
}

void bignat::Bytes(uint8_t *out,int limit) const{
  int j=0;
  for( int i=this->len-1;i>=0;i--){
    if(j== limit){
      PANIC(PANIC_NAT_BYTES_OVERFLOW);
    }
    out[j]=this->data[i];
    j++;
  }
}
