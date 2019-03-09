#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int * array,int N);
void rearrange(int bas,int son,int* KEY,int* LOCK,int N); 
int sirala(int bas,int son,int * KEY,int * LOCK,int lockNumber); // KEY ve LOCK dizilerini siralar
void printArray(int N,int * array,char * arrayName);
void swap(int *array1,int i,int j);


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int i; // for dongusu icin sayac
	int N;     // LOCK ve KEY dizilerinin boyutu
	int * LOCK; // Kilit buyukluklerinin sayisal degerlerinin dizisi
	int * KEY;  // Anahtar buyukluklerinin sayisal degerlerinin dizisi
	printf("Dizinin boyutunu giriniz:");
	scanf("%d",&N);

	LOCK = (int *) malloc(N*sizeof(int));
	KEY = (int *) malloc(N*sizeof(int));

	// LOCK dizisini giriniz
	printf("\nLOCK dizisini(kapi numaralari) giriniz:\n");
	for (i = 0; i < N; ++i)
	{
		printf("%d.eleman:",i);
		scanf("%d",&LOCK[i]);	
	}

	// KEY dizisini giriniz
	printf("\nKEY dizisini(kapi numaralari) giriniz:\n");
	for (i = 0; i < N; ++i)
	{
		printf("%d.eleman:",i);
		scanf("%d",&KEY[i]);	
	}

	printArray(N,LOCK,"LOCK");
	printArray(N,KEY,"KEY");
	printf("\nLOCK ve KEY dizileri karisitiriliyor(shuffle).\n");
	shuffle(LOCK,N);
	shuffle(KEY,N);
	printf("Shuffle isleminden sonra diziler:\n");
	printArray(N,LOCK,"LOCK");
	printArray(N,KEY,"KEY");

	printf("\nSiralama islemi basliyor...\n");
	rearrange(0,N-1,KEY,LOCK,N);
	printArray(N,LOCK,"LOCK");
	printArray(N,KEY,"KEY");
	return 0;
}

void shuffle(int * array,int N)
{
	int i;
	for (i = N-1; i > 0; i--) 
    { 
        // sifir ve i intervalindan random bir sayi secip sonuncudan itibaren sirayla degisiyor
        int j = rand() % (i+1); 
  
        // sayiyi array[i] ile degistir
        int tmp=array[i];
        array[i]=array[j];
        array[j]=tmp;
    } 
}

void rearrange(int bas,int son,int* KEY,int* LOCK,int N)
{
	if(bas<son)
	{
		int lockNumber = LOCK[sirala(bas,son,KEY,LOCK,'\0')]; // LOCK dizisini sirala 
		printArray(N,LOCK,"LOCK");
		printArray(N,KEY,"KEY");
		int keyNumber = sirala(bas,son,KEY,LOCK,lockNumber);  // KEY dizisini sirala
		printArray(N,LOCK,"LOCK");
		printArray(N,KEY,"KEY");
		rearrange(bas,keyNumber-1,KEY,LOCK,N);
		rearrange(keyNumber+1,son,KEY,LOCK,N);
	}
}

int sirala(int bas,int son,int * KEY,int * LOCK,int lockNumber)
{
	int i=bas; // dizisinin verilen araliktaki en soldaki elemaninin indisi
	int j=son; // dizisinin verilen araliktaki en sagdaki elemaninin indisi
	int pivot; // pivot degeri
	int *array=NULL;
	int index;

	if(!lockNumber) 
	{
		// Lock dizisini random key'e nazaran sirala
		index = rand()%(son-bas+1) + bas; // KEY dizisindeki random elemanin indisi
		pivot = KEY[index];
		printf("\nKey dizisinde rasgele secilen indis:%d\n",index);
		printf("\nLOCK dizisi [%d,%d] araligi KEY[%d]=%d degerine nazaran siralanacaktir.\n",bas,son,index,pivot );
		array=LOCK;
		/*LOCK sort*/
	}	
	else
	{
		// Key dizisini lockNumber'a nazaran sirala
		pivot = lockNumber;
		array=KEY;
		printf("\nKEY dizisi [%d,%d] araliginda pivot=%d degerine nazaran siralanacaktir\n",bas,son,pivot);
		/*KEY sort*/
	}
	index=bas;
	i=bas+1;
	while(array[index]!=pivot){ index++; }
	swap(array,index,bas);
	while(i<=j)
	{
		while(i<=j && array[i]<=pivot) { i++; }
		while(j>=i && array[j]>pivot) { j--; }
		if(i<j){ swap(array,i,j); }
	}
	swap(array,bas,j);


	return j;

}

void printArray(int N,int * array,char * arrayName)
{
	int i;
	printf("\n%s dizisi:\n",arrayName);
	for (i = 0; i < N; ++i)
	{
		printf("%4d",array[i]);
	}
	printf("\n");
}

void swap(int *array1,int i,int j)
{
	int tmp=array1[i];
	array1[i]=array1[j];
	array1[j]=tmp;
}
