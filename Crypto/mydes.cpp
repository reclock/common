#include "pch.h"
#include "mydes.h"
#include <memory.h>

int mydes::getbit(unsigned char *buf,int i)
{
	return ((*(unsigned char*)((unsigned char*)buf+(i>>3))) & bitmask[i&0x07])!=0;
}

void mydes::setbit(unsigned char *buf,int i)
{
	*((unsigned char *)buf+(i>>3)) |= bitmask[i&0x07];
}

void mydes::getsubkey()
{
	int i,j,s1,s2;
	for (i=0; i<56; i++)
		CDD[i]=KEY[PC_1[i]];
	for (i=0; i<16; i++)   
	{
		s1=CDD[0]; s2=CDD[1];
		for (j=0; j<28-Shift[i]; j++)
			CDD[j]=CDD[j+Shift[i]];
		if (Shift[i]==2)	
		{
			CDD[26]=s1;
			CDD[27]=s2;
		}
		else
			CDD[27]=s1;
		s1=CDD[28]; s2=CDD[29];
		for (j=28; j<56-Shift[i]; j++)
			CDD[j]=CDD[j+Shift[i]];
		if (Shift[i]==2)        
		{
			CDD[54]=s1;
			CDD[55]=s2;
		}
		else
			CDD[55]=s1;
		for (j=0; j<48; j++)
			SUBKEY[i][j]=CDD[PC_2[j]];
	}
}

void mydes::DES_setkey(unsigned char *key)
{
	int i;
	for (i=0; i<64; i++)
		KEY[i]=getbit(key,i);
	getsubkey();
}

static unsigned char deskey[9];

mydes::mydes()
{
}

mydes::~mydes()
{
}

/*src 明文,dst 密文, op -1 解密, 1 加密  */
void mydes::DES(unsigned char *src,unsigned char *dst,unsigned char *des_key,int OP) 
{
	int i,j,k,r,op;
	unsigned char v4,v6;
	unsigned char tempkey[9];
	memset(tempkey, 0, 9);

	//for (i=0;i<8;i++) deskey[i]=des_key[i];
	//DES_setkey(deskey);
	for (i=0;i<8;i++) tempkey[i]=des_key[i];
	DES_setkey(tempkey);

	if (OP==1) {r=0;op=1;}
	else {r=15;op=-1;}

	for (i=0; i<64; i++)
		LR0[i]=getbit(src,IIP[i]);

	for (i=0; i<16; i++)    
	{
		memcpy(LR1,LR0+32,32);
		memset(LR1+32,0,32);

		for (j=0; j<48; j++)
			bit48[j]=(SUBKEY[r][j]!=LR0[E[j]]);

		for (j=0; j<8; j++)     
		{                          /* S box */
			v6=0; v4=(j<<2)+(j<<1);
			for (k=5; k>=0; k--)
				v6=(v6<<1)+bit48[v4+k];
			v4=S[j][v6];
			v6=(j<<2)+3;
			for (k=0; k<4; k++)
				bit32[v6-k]=v4&1,v4>>=1;
		}
		for (j=0; j<32; j++)
			LR1[j+32]=(LR0[j]!=bit32[P[j]]);
		memcpy(LR0,LR1,64);
		r+=op;
	}
	memcpy(LR1,LR0+32,32);
	memcpy(LR1+32,LR0,32);
	memset(dst,0,8);
	for (i=0; i<64; i++)
		if (LR1[IIP_1[i]]) setbit(dst,i);
}


//zeropadding方式加解密
void mydes::DES_E(unsigned char *msg,int msgLen, unsigned char* des,unsigned char* key,int OP)
{
	unsigned char msgTmp[8]={0};
	unsigned char block[8]={0};
	int i = 0;
	
	for (i; i < msgLen / 8; i++)
	{
		memcpy(msgTmp, msg + i * 8, 8);

		DES(msgTmp,block,key,OP);	
		memcpy(des+i*8,block,8);
	}
	if (msgLen % 8 != 0)
	{
		int tmp1 = msgLen / 8 * 8;
		int tmp2 = msgLen - tmp1;
		memset(msgTmp, 0, 8);
		memcpy(msgTmp, msg + tmp1, tmp2);

		DES(msgTmp,block,key,OP);		
		memcpy(des+i*8,block,8);
	}
}
