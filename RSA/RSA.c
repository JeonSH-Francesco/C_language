#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int n;  //n=p*q(단,p,q는 소수)
int Public_Key(long EulerPi);   //공개키
int Private_Key(int e, long EulerPi); //개인키

int Primecheck(int n);		//소수인지검사
long Random_PrimeNumber();// 랜덤 소수(2개) 생성기

int GCD(int x, int y);//최대 공약수 검사

long mod(long m, long exponent, long n); //mod연산

void main(void){
    int publickey, privatekey;
    long Eulerpi;

    Eulerpi=Random_PrimeNumber();
    //Random_PrimeNumber함수 호출

    publickey=Public_Key(Eulerpi);
    privatekey=Private_Key(publickey,Eulerpi);
    printf("\n public_key = e =%d, private_key = d =%d\n\n",publickey, privatekey);
    long long m,cipher,decipher;

    printf(" 평문 입력:");
    scanf("%d",&m);

    cipher=mod(m,publickey,n);  //암호화 mod 연산할떄 C=(m^e)mod n
    printf(" 암호화 = %ld = (m^(public key = e)) mod n", cipher);
    decipher = mod(cipher,privatekey,n); //복호화 mod 연산할때 M=(C^d)mod n
    printf("\n 복호화 = %ld = (c^(private key = d)) mod n\n", decipher);
}



long Random_PrimeNumber()// 랜덤 소수(2개) 생성기

{
    int i;
	int primearray[2];
	long Eulerpi;
	time_t t;
	srand((unsigned int) time(&t));  //난수생성
	for (i=0; i<2; i++)				// 2개의 임의의 소수 p,q 생성
	{
        do{
		primearray[i]=rand()%100; // 1~99까지의 소수인 난수 발생, 숫자범위 조정 가능
		}
		while(Primecheck(primearray[i]));	 //발생된 난수가 소수가 아니면 반복한다.

	if((primearray[0]-1==0)||(primearray[1]-1==0))
    {
    Random_PrimeNumber();
    }
	}
	n=primearray[0]*primearray[1];		// 두개의 소수 p,q를 이용해 n값 생성
	printf("\n p=%d, q=%d, n=%d\t (n은 두 소수 p,q의 곱)\n", primearray[0], primearray[1], n);
	printf("\n p-1=%d, q-1=%d, Eulerpi=%d\t (Eulerpi는 p-1,q-1의 곱)\n",primearray[0]-1,primearray[1]-1,(primearray[0]-1)*(primearray[1]-1));

	return (primearray[0]-1)*(primearray[1]-1);

}
int Public_Key(long EulerPi)
{
	long e;
	do
	{
		e=rand()%100;	//3자리로 제한했지만 숫자범위 조정 가능
		if ( (e < EulerPi) && (GCD(e, EulerPi)==1) )
            return e;	// 오일러 파이와 서로 소인 e를 리턴.
	}while(1);  //계속 실행  0은 거짓 1은 참
}

int Private_Key(int e, long Epi)
{
	int d=0;
	while (((e*d)%Epi)!=1) d++;		//개인키 생성
	return d;	//개인키를 리턴한다.
}



int Primecheck(int n)		//소수가 아닌지 검사
{
   int  i, limit;
   if (!(n%2))  return 1;		//짝수이면 소수가 아니다.
   limit = (int)sqrt(n) + 1;		//n제곱+1을 하여 소수를 찾는다.
   for (i = 3; i <= limit; i += 2) 	//3부터 홀수 단위로 나머지 연산을 한다.
      if (!(n%i))  return 1;
   return 0;
}

int GCD(int x, int y){
    int tmp;                //최대공약수 (Great Common Divisor)
        while(y!=0)         //입력한 두수 중 큰수를 작은수로 나눴을때의 나머지가  0이 될때까지 반복후
    {   tmp=x;              //GCD는 나눠지는수가 아닌(즉, y=작은수가아닌->어떻게 되었던간에 tmp통해서 작은수로 설정됨) x를 반환한다.
        x=y;
        y=tmp%y;
    }
    return x;
}

long mod(long m, long exponent, long n)	// reminder = m^exponential (mod n)을 수행한다.

{
	long i, reminder = 1;
	for(i=1; i<=exponent; i++)
	{
		reminder = reminder%n;
		reminder = reminder*m;

	} 		//mod연산의 정석!! overflow 나지 않도록!!
	return reminder%n;

}


/*
실행 결과 예시
 p=43, q=41, n=1763      (n은 두 소수 p,q의 곱)

 p-1=42, q-1=40, Eulerpi=1680    (Eulerpi는 p-1,q-1의 곱)

 public_key = e =37, private_key = d =1453

 평문 입력:17
 암호화 = 1347 = (m^(public key = e)) mod n
 복호화 = 17 = (c^(private key = d)) mod n
 */
