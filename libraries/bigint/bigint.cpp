// This code is derived from golangs math/big package
// Copyright 2009 The Go Authors. All rights reserved.
// Arduino Port Copyright 2013 Steven Pearson
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.

#include <bigint.h>
#include <panic.h>

//#define ALIASCHECKS

bigint::bigint(WORD *data,int cap) : _abs(data,cap),neg(0) {
}

void bigint::SetBytesP(const uint8_t *data,int len){
  this->neg=0;
  this->_abs.SetBytesP(data,len);
}

void bigint::SetBytes(byte neg,const uint8_t *data,int len){
  this->neg=neg;
  this->_abs.SetBytes(data,len);
}

void bigint::Set(const struct bigint &x){
  this->neg=x.neg;
  this->_abs.Set(x._abs);
}

void bigint::Set(WORD val){
  this->neg=0;
  this->_abs.Set(val);
}

int bigint::Cmp(const struct bigint &y) const{
  if( this->neg == y.neg ){
    return this->_abs.Cmp(y._abs);
  } else if(this->neg){
    return -1;
  } else {
    return 1;
  }
}


void bigint::ModInverse(struct bigint &g,const struct bigint &p){
  struct bigint d(NULL,0);
  d.GCD(*this,g,p);
  
  if( this->neg  ){
    this->Add(*this,p);
  }
}


void bigint::GCD(struct bigint &x,const struct bigint &a,const struct bigint &b){
  if( a.neg || b.neg ){
    this->Set(0);
    x.Set(0);
    return;
  }
  
  WORD Abuf[128];
  struct bigint A(Abuf,sizeof(Abuf));
  A.Set(a); //32
  
  WORD Bbuf[128];
  struct bigint B(Bbuf,sizeof(Bbuf));
  B.Set(b); //32

  WORD Xbuf[64];
  struct bigint X(Xbuf,sizeof(Xbuf));

  WORD lastXbuf[64];
  struct bigint lastX(lastXbuf,sizeof(lastXbuf));
  lastX.Set(1); //1
  
  WORD qbuf[128];
  struct bigint q(qbuf,sizeof(qbuf));

  WORD tempbuf[64];
  struct bigint temp(tempbuf,sizeof(tempbuf));

  while( B._abs.len > 0 ){
    
    WORD rbuf[128];
    struct bigint r(rbuf,sizeof(rbuf));
    
    q.QuoRem(A,B,r,tempbuf); //32

    A.Set(B); //32
    B.Set(r); //32
    
    temp.Set(X); 
    x.Mul(X,q); //32 * 32
    x.neg = !x.neg;
    X.Add(x,lastX); //+1
    lastX.Set(temp);//
  }

  x.Set(lastX);
  
  if( this->_abs.cap>0 ){
    this->Set(A);
  } else {
    this->neg = A.neg;
  }
}

void bigint::QuoRem(const struct bigint &x,const struct bigint &y,struct bigint &r,WORD vbuf[33]){
  this->_abs.Div(x._abs,y._abs,r._abs,vbuf);
  this->neg = this->_abs.len>0 && x.neg!=y.neg;
  
  r.neg = r._abs.len>0 && x.neg;
}

void bigint::Lsh(const struct bigint &x,unsigned int n){
  this->_abs.Shl(x._abs,n);
  this->neg=x.neg;
}

void bigint::Mod(const struct bigint &x,const struct bigint &y){
  
#ifdef ALIASCHECKS
  if( this == &y ){
    PANIC(PANIC_INT_MOD_ALIAS);
    return;
  }
#endif
  
  struct bigint q(NULL,0);
  q.QuoRem(x,y,*this,NULL);
  if( this->neg ){
    if( y.neg ){
      this->Sub(*this,y);
    } else {
      this->Add(*this,y);
    }
  }
}

const struct bignat &bigint::Abs() const{
  return this->_abs;
}

int bigint::Sign() const{

  if( this->_abs.len == 0 ){
    return 0;
  } else if( this-> neg ) {
    return -1;
  } else {
    return 1;
  }
}

void bigint::String(WORD base,const char *map,char *out,int limit) const{
  if( limit<1){
    PANIC(PANIC_NAT_TOSTRING_OVERFLOW);
  }

  out[0] = this->neg ? '-':'+';
  this->_abs.String(base,map,out+1,limit-1);
}

void bigint::Mul(const struct bigint &x,const struct bigint &y){
  this->_abs.Mul(x._abs,y._abs);
  this->neg = this->_abs.len > 0 && (x.neg != y.neg);
}

void bigint::Add(const struct bigint &x,const struct bigint &y){
  byte neg = x.neg;
  if( x.neg == y.neg ){
    this->_abs.Add(x._abs,y._abs);
  } else {
    if( x._abs.Cmp(y._abs) >= 0 ){
      this->_abs.Sub(x._abs,y._abs);
    } else {
      neg = !neg;
      this->_abs.Sub(y._abs,x._abs);
    }
  }
  this->neg = (this->_abs.len>0) && neg;
}

void bigint::Sub(const struct bigint &x,const struct bigint &y){
  byte neg = x.neg;
  if( x.neg != y.neg ){
    this->_abs.Add(x._abs,y._abs);
  } else {
    if( x._abs.Cmp(y._abs) >= 0 ){
      this->_abs.Sub(x._abs,y._abs);
    } else {
      neg = !neg;
      this->_abs.Sub(y._abs,x._abs);
    }
  }
  this->neg = (this->_abs.len>0) && neg;
}
