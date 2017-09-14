#define UINT64 unsigned long long int  
struct  RsaParam
{
    UINT64    p, q;   //������������������ܽ�������
    UINT64    f;      //f=(p-1)*(q-1)����������ܽ�������
    UINT64    n, e;   //���ף�n=p*q��gcd(e,f)=1
    UINT64    d;      //˽�ף�e*d=1 (mod f)��gcd(n,d)=1
    UINT64    s;      //�鳤������2^s<=n������s����log2(n)
} ;
//С������
const static long       g_PrimeTable[]=	{3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
const static long       g_PrimeCount=sizeof(g_PrimeTable) / sizeof(long);
/*const UINT64  multiplier=12747293821;
const UINT64  adder=1343545677842234541;
*/
struct PublicKey
{
	UINT64 nE;
	UINT64 nN;
};
//�������
class RandNumber
{
private:
    UINT64    randSeed;
public:
    RandNumber(UINT64 s=0)
    {
		if(!s)
		{
			randSeed= (UINT64)time(NULL);
		}
		else
		{
			randSeed=s;
		}
		unsigned int Rand[2];
		memcpy(Rand,&randSeed,8);
		srand(Rand[0]^Rand[1]);
	}
	UINT64    Random(UINT64 n)
	{
		unsigned int *pRand = (unsigned int *)&randSeed;
		pRand[0] = rand();
		pRand[1] = rand();
		return randSeed % n;
	}
};

class CRSASection
{
public:
	CRSASection()
	{
		m_cParament = RsaGetParam();
	}
	static UINT64 Encry(unsigned short nSorce, PublicKey &cKey)
	{
		return PowMod(nSorce, cKey.nE, cKey.nN);
	}
	unsigned short Decry(UINT64 nSorce )
	{
		UINT64 nRes = PowMod(nSorce, m_cParament.d, m_cParament.n);
		unsigned short * pRes=(unsigned short*)&(nRes);
		if(pRes[1]!=0||pRes[3]!=0||pRes[2]!=0)
		{//error
			return 0;
		}
		else
		{
			return pRes[0];
		}
	}
	PublicKey GetPublicKey()
	{
		PublicKey cTmp;
		cTmp.nE=this->m_cParament.e;
		cTmp.nN = this->m_cParament.n;
		return cTmp;
	}
private:
	RandNumber   m_cRadom;
	RsaParam    m_cParament;
	static inline UINT64 MulMod(UINT64 a, UINT64 b, UINT64 n)
	{

		return (a%n) * (b%n) % n;
	}

	static UINT64 PowMod(UINT64 base, UINT64 pow, UINT64 n)
	{
		UINT64    a=base, b=pow, c=1;
		while(b)
		{
			while(!(b & 1))
			{
				b>>=1; 
				a=MulMod(a, a, n);
			}       
			b--;
			c=MulMod(a, c, n);
		}    
		return c;
	}

	long RabinMillerKnl(UINT64 &n)
	{
		UINT64    a, q, k, v ;
		q=n - 1;
		k=0;  
		while(!(q & 1))
		{
			++k;
			q>>=1;
		}    
		a=2 + m_cRadom.Random(n - 3);   
		v=PowMod(a, q, n);    
		if(v == 1)
		{
			return 1;
		}    
		for(int j=0;j<k;j++)
		{
			unsigned int z=1;
			for(int w=0;w<j;w++)
			{
				z*=2;
			}
			if(PowMod(a, z*q, n)==n-1)
				return 1;
		}
		return 0;
	}

	long RabinMiller(UINT64 &n, long loop)
	{
		//����С����ɸѡһ�Σ����Ч��
		for(long i=0; i < g_PrimeCount; i++)
		{
			if(n % g_PrimeTable[i] == 0)
			{
				return 0;
			}
		}    //ѭ������Rabin-Miller����loop�Σ�ʹ�÷�����ͨ�����Եĸ��ʽ�Ϊ(1/4)^loop
		for(long i=0; i < loop; i++)
		{
			if(!RabinMillerKnl(n))
			{
				return 0;
			}
		}   
		return 1;
	}
	UINT64 RandomPrime(char bits)
	{
		UINT64    base;
		do
		{
			base= (unsigned long)1 << (bits - 1);   //��֤���λ��1
			base+=m_cRadom.Random(base);               //�ټ���һ�������
			base|=1;    //��֤���λ��1������֤������
		} while(!RabinMiller(base, 30));    //�������������ղ���30��
		return base;    //ȫ��ͨ����Ϊ������
	}

	UINT64 Gcd(UINT64 &p, UINT64 &q)
	{
		UINT64    a=p > q ? p : q;
		UINT64    b=p < q ? p : q;
		UINT64    t;
		if(p == q)
		{
			return p;   //������ȣ����Լ�����Ǳ���
		}
		else
		{
			while(b)    //շת�������gcd(a,b)=gcd(b,a-qb)
			{
				a=a % b;
				t=a;
				a=b;
				b=t;
			}       
			return a;
		}
	}

	UINT64 Euclid(UINT64 e, UINT64 t_n)
	{
		UINT64 Max;
		memset(&Max,0xff,sizeof(Max));
		Max-=t_n;
		UINT64 i=1;

		while(1)
		{
			if(((i*t_n)+1)%e==0)
			{
				return ((i*t_n)+1)/e;
			}
			i++;
			UINT64 Tmp=(i+1)*t_n;
			if(Tmp>Max)
			{
				return 0;
			}
		}
		return 0; 
	}


	RsaParam RsaGetParam(void)
	{
		RsaParam           Rsa={ 0 };
		UINT64    t;
		Rsa.p=RandomPrime(16);          //���������������
		Rsa.q=RandomPrime(16);
		Rsa.n=Rsa.p * Rsa.q;
		Rsa.f=(Rsa.p - 1) * (Rsa.q - 1);
		do
		{
			Rsa.e=m_cRadom.Random(65536);  
			Rsa.e|=1;                  
		} while(Gcd(Rsa.e, Rsa.f) != 1);   
		Rsa.d=Euclid(Rsa.e, Rsa.f);
		Rsa.s=0;
		t=Rsa.n >> 1;
		while(t)
		{
			Rsa.s++;                   
			t>>=1;
		}    
		return Rsa;
	}


};
