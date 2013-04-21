//This code is derived form https://github.com/ThePiachu/Golang-Koblitz-elliptic-curve-DSA-library/tree/master/bitelliptic
// Copyright 2010 The Go Authors. All rights reserved.
// Copyright 2011 ThePiachu. All rights reserved.
// Copyright 2013 Steven Pearson. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the GOLANG_LICENSE file.

#include <bitelliptic.h>
#include <progress.h>

int bitcurve::isOnCurve(const struct bigint &x,const struct bigint &y) const{

    WORD tbuf[97];
    struct bigint t(tbuf,sizeof(tbuf));

    WORD y2buf[65];
    struct bigint y2(y2buf,sizeof(y2buf));

    WORD x3buf[98];
    struct bigint x3(x3buf,sizeof(x3buf));

    WORD bbuf[32];
    struct bigint b(bbuf,sizeof(bbuf));
    b.SetBytesP(_B,sizeof(_B));
    
    t.Mul(y,y);//64
    y2.Mod(t,this->P);
    
    x3.Mul(x,x);//64
    t.Mul(x3,x);//96
    t.Add(t,b);//97
    x3.Mod(t,this->P);//98
    
    return x3.Cmp(y2) == 0;
}

bitcurve::bitcurve(const struct bigint &P,const struct bigint &Gx,const struct bigint &Gy) : P(P),Gx(Gx),Gy(Gy){ 
}

void bitcurve::_doubleJacobianZ(const struct bigint &y,struct bigint &z){
    WORD tbuf[98];
    struct bigint t(tbuf,sizeof(tbuf));
  
    WORD z3buf[97];    
    struct bigint z3(z3buf,sizeof(z3buf));
    z3.Mul(y,z); //96
    
    t.Set(2); //1
    z3.Mul(t,z3);//97
    
    t.Mod(z3,this->P);//32  
    
    z.Set(t);
}

void bitcurve::_doubleJacobianX(const struct bigint &f,const struct bigint &d,struct bigint &x){
    WORD tbuf[133];
    struct bigint t(tbuf,sizeof(tbuf));
  
    WORD x3buf[132];    
    struct bigint x3(x3buf,sizeof(x3buf));
    t.Set(2);//1
    x3.Mul(t,d);//132
    
    x3.Sub(f,x3);//130

    t.Mod(x3,this->P);//32
    
    x.Set(t);
}

void bitcurve::_doubleJacobianY(const struct bigint &d,const struct bigint &e,const struct bigint &c,const struct bigint &x,struct bigint &y){
    WORD tbuf[1];
    struct bigint t(tbuf,sizeof(tbuf));
    WORD t2buf[197];
    struct bigint t2(t2buf,sizeof(t2buf));
  
    WORD y3buf[196];
    struct bigint y3(y3buf,sizeof(y3buf));
    t2.Sub(d,x);//131
    y3.Mul(e,t2);//196
    t.Set(8);//1
    t2.Mul(t,c);//65
    y3.Sub(y3,t2);//196
    t2.Mod(y3,this->P);//32
    y.Set(t2);
}

void bitcurve::_doubleJacobianE(const struct bigint &x,struct bigint &e){
  WORD tbuf[1];
  struct bigint t(tbuf,sizeof(tbuf));
  
  WORD abuf[64];
  struct bigint a(abuf,sizeof(abuf));
  a.Mul(x,x); //64

  t.Set(3);//1
  e.Mul(t,a);//65
  
}

void bitcurve::_doubleJacobianCD(const struct bigint &x,const struct bigint &y,struct bigint &c,struct bigint &dout){

  //TODO:I have recalcutaled A here. I'm not sure I can afford the 64 bytes of stack.
  //I could try to re-combine Jacobian CD and JacobianE
  WORD abuf[64];
  struct bigint a(abuf,sizeof(abuf));
  a.Mul(x,x); //64

  WORD bbuf[130];
  struct bigint b(bbuf,sizeof(bbuf));
  b.Mul(y,y); //64

  c.Mul(b,b); //128

  WORD tbuf[1];
  struct bigint t(tbuf,sizeof(tbuf));

  dout.Add(x,b);//65
  
  b.Mul(dout,dout);//130
  
  b.Sub(b,a);//130
  
  b.Sub(b,c);//130
  
  t.Set(2);//1
  dout.Mul(b,t);//131 
}

void bitcurve::doubleJacobian(struct bigint &x,struct bigint &y,struct bigint &z){
  WORD cbuf[128];
  struct bigint c(cbuf,sizeof(cbuf));

  WORD dbuf[131];
  struct bigint d(dbuf,sizeof(dbuf));

  WORD ebuf[131];
  struct bigint e(ebuf,sizeof(ebuf));

  WORD fbuf[130];
  struct bigint f(fbuf,sizeof(fbuf));
  
  _doubleJacobianE(x,e);

  f.Mul(e,e);//130

  _doubleJacobianCD(x,y,c,d);

  _doubleJacobianZ(y,z);
  _doubleJacobianX(f,d,x); 
  _doubleJacobianY(d,e,c,x,y);
}

void bitcurve::addJacobian(const struct bigint &x1,const struct bigint &y1,const struct bigint &z1,struct bigint &x2,struct bigint &y2,struct bigint &z2){
  WORD z1z1buf[32];
  struct bigint z1z1(z1z1buf,sizeof(z1z1buf));
  WORD z2z2buf[32];
  struct bigint z2z2(z2z2buf,sizeof(z2z2buf));
  
  _addJacobianZ12(z1,z2,z1z1,z2z2);

  WORD u1buf[32];
  struct bigint u1(u1buf,sizeof(u1buf));
  WORD hbuf[65];
  struct bigint h(hbuf,sizeof(hbuf));

  _addJacobianHU1(x1,x2,z1z1,z2z2,u1,h);
  
  WORD jbuf[192];
  struct bigint j(jbuf,sizeof(jbuf));
  //This is a horrible hack I need 230 bytes of scratch space in addJacobianY v and r are last used in y and the scratch space is needed after their last use.
  WORD vrbuf[230];
  struct bigint vrstomp(vrbuf,sizeof(vrbuf));
  struct bigint v(vrbuf,196);

  _addJacobianJV(h,u1,j,v);
  
  WORD s1buf[32];
  struct bigint s1(s1buf,sizeof(s1buf));
  struct bigint r(vrbuf+196,230-196);
  
  this->_addJacobianS1R(y1,z2,z2z2,y2,z1,z1z1,h,s1,r);
  
  this->_addJacobianX(r,v,j,x2);
  this->_addJacobianY(r,v,s1,x2,j,y2,vrstomp);
  this->_addJacobianZ(z1,z1z1,z2z2,h,z2);
}

void bitcurve::_addJacobianZ12(const struct bigint &z1,const struct bigint &z2,struct bigint &z1z1,struct bigint &z2z2){

  WORD tbuf[64];
  struct bigint t(tbuf,sizeof(tbuf));
  WORD t2buf[65];
  struct bigint t2(t2buf,sizeof(t2buf));
  
  t.Mul(z1,z1); //64
  t2.Mod(t,this->P);//32
  z1z1.Set(t2);
  
  t.Mul(z2,z2); //64
  t2.Mod(t,this->P);//32
  z2z2.Set(t2);  
}

void bitcurve::_addJacobianHU1(const struct bigint &x1,const struct bigint &x2,const struct bigint &z1z1,const struct bigint &z2z2,struct bigint &u1out,struct bigint &h){

  WORD u1buf[65];
  struct bigint u1(u1buf,sizeof(u1buf));
  h.Mul(x1,z2z2); //64
  u1.Mod(h,this->P); //32
  u1out.Set(u1);
  
  WORD u2buf[65];
  struct bigint u2(u2buf,sizeof(u2buf));
  u1.Mul(x2,z1z1); //64
  u2.Mod(u1,this->P); //32

  h.Sub(u2,u1out);//64
  if( h.neg ){
    h.Add(h,this->P);//64
  }
}

void bitcurve::_addJacobianJV(const struct bigint &h,const struct bigint &u1,struct bigint &j,struct bigint &v){
  
  WORD ibuf[130];
  struct bigint i(ibuf,sizeof(ibuf));
  j.Lsh(h,1);//65
  i.Mul(j,j);//130
  
  j.Mul(h,i);//192
  v.Mul(u1,i);//162
}

void bitcurve::_addJacobianS1R(const struct bigint &y1,const struct bigint &z2,const struct bigint &z2z2,const struct bigint &y2,const struct bigint &z1,const struct bigint &z1z1,const struct bigint &h,struct bigint &s1out,struct bigint &r){

  WORD s1buf[97];
  struct bigint s1(s1buf,sizeof(s1buf));
  WORD s2buf[97];
  struct bigint s2(s2buf,sizeof(s2buf));
  
  s1.Mul(y1,z2);//64
  s2.Mul(s1,z2z2);//96
  s1.Mod(s2,this->P);//32  
  s1out.Set(s1);

  s2.Mul(y2,z1);//33
  s1.Mul(s2,z1z1);//65
  s2.Mod(s1,this->P);//32  
  
  r.Sub(s2,s1out);//33 (s1 and s2 are only 32 at the moment)
  if( r.neg ){
    r.Add(r,this->P);//33
  }
  r.Lsh(r,1);//34
}

void bitcurve::_addJacobianX(const struct bigint &r,const struct bigint &v,const struct bigint &j,struct bigint &x2){
  
  WORD tbuf[196];
  struct bigint t(tbuf,sizeof(tbuf));
  
  WORD x3buf[195];
  struct bigint x3(x3buf,sizeof(x3buf));
  t.Set(r);//33
  x3.Mul(t,t);//66
  x3.Sub(x3,j);//193
  x3.Sub(x3,v);//194
  x3.Sub(x3,v);//195
  t.Mod(x3,this->P);//32
  
  x2.Set(t);
}


//TODO: I don't like the modificaion s1 and the destruction of V
void bitcurve::_addJacobianY(const struct bigint &r,struct bigint &v,struct bigint &s1,const struct bigint &x3,const struct bigint &j,struct bigint &y2,struct bigint &vrstomp){

  WORD tbuf[230];
  struct bigint t(tbuf,sizeof(tbuf));

  v.Sub(v,x3);//196 v.Sub(v,x3);
  t.Mul(r,v);//230 y3.Mul(r,v);

  //v and r now free togethe they provide 230 bytes
  vrstomp.Mul(s1,j); //224
  vrstomp.Lsh(vrstomp,1); //225
  
  t.Sub(t,vrstomp); //
  vrstomp.Mod(t,this->P);
  
  y2.Set(vrstomp);
}

void bitcurve::_addJacobianZ(const struct bigint &z1,const struct bigint &z1z1,const struct bigint &z2z2,const struct bigint &h,struct bigint &z2){

  WORD tbuf[132];
  struct bigint t(tbuf,sizeof(tbuf));
  
  WORD z3buf[133];
  struct bigint z3(z3buf,sizeof(z3buf));
  t.Add(z1,z2);//33
  z3.Mul(t,t);//66
  z3.Sub(z3,z1z1);//67
  if( z3.neg ){
    z3.Add(z3,this->P);//67
  }
  z3.Sub(z3,z2z2);//68
  if( z3.neg ){
    z3.Add(z3,this->P);//68
  }  
  t.Mul(z3,h);//132
  z3.Mod(t,this->P);//32

  z2.Set(z3);
}

void bitcurve::affineFromJacobian(struct bigint &x,struct bigint &y,struct bigint &z){
  
  WORD zinvbuf[64];
  struct bigint zinv(zinvbuf,sizeof(zinvbuf));
  
  zinv.ModInverse(z,this->P);
  
  this->_affineFromJacobianXY(x,y,zinv);
}

void bitcurve::_affineFromJacobianXY(struct bigint &x,struct bigint &y,const struct bigint &zinv){
  
  WORD zinvsqbuf[192];
  struct bigint zinvsq(zinvsqbuf,sizeof(zinvsqbuf));

  zinvsq.Mul(zinv,zinv);

  WORD tbuf[161];
  struct bigint t(tbuf,sizeof(tbuf));

  WORD outbuf[224];
  struct bigint out(outbuf,sizeof(outbuf));
  t.Mul(x,zinvsq);
  
  out.Mod(t,this->P);
  
  x.Set(out);

  t.Set(zinvsq);
  zinvsq.Mul(t,zinv);

  t.Mul(y,zinvsq);

  out.Mod(t,this->P);

  y.Set(out);
}


void bitcurve::ScalarMult(const struct bigint &Bx,const struct bigint &By,const uint8_t *k,int klen,struct bigint &x,struct bigint &y){

  WORD bzbuf[1];
  struct bigint Bz(bzbuf,sizeof(bzbuf));
  Bz.Set(1);
  
  WORD zbuf[32];
  struct bigint z(zbuf,sizeof(zbuf));
  z.Set(Bz);

  x.Set(Bx);
  y.Set(By);
  
  byte seenFirstTrue = 0;
  for( int i = 0 ; i < klen ; i++ ){
    PROGRESS( (float)i / (float) klen );

    byte b = k[i];
    for( int bitNum = 0 ; bitNum<8;bitNum++){
      if( seenFirstTrue ){
        this->doubleJacobian(x,y,z);
      }
      if( ((byte)((byte)b & (byte)0x80)) == (byte)0x80 ) {
        if( !seenFirstTrue ){
          seenFirstTrue=1;
        } else {
          this->addJacobian(Bx,By,Bz,x,y,z);
        }
      }
      b<<=1;
    }
  }
  
  if(!seenFirstTrue){
    x._abs.make(0);
    y._abs.make(0);
    return;
  }
  
  this->affineFromJacobian(x,y,z);  
}


void bitcurve::ScalarBaseMult(const uint8_t *k,int klen,struct bigint &x,struct bigint &y){
  this->ScalarMult(this->Gx,this->Gy,k,klen,x,y);
}
