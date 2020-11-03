//uso de Estructuras Dinamicas realizando un Juego de Batallas por turno donde se enfrentan un Heroe contra una serie de Malos. 
//hacer un juego de batalla por turnos entre un heroe y varios malos, los malos se incrementar�n en 1 cuando el contador del turno de
//la batalla sea par

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
	int vida;
	int fuerza;
	int magia;
	int mana;
}heroe;

typedef struct{
	int fuerza;
	int vida;
}malo;

heroe yo;
malo *otros; //vector din�mico de malos

void valores_heroe();
void ini_malo(int *N);
void valores_malo(int N);
void batalla(int ob, int op);
void cambio(char l[]);


//********************FUNCI�N PRINCIPAL****************************
int main() 
{
	int op, i, ob, pegar, cont;
	char l[1];
	int N;
	N=0; //contador inicial de malos
	ob=0; //que malo vamos a atacar
	cont=0; //contador de turnos
	srand(time(NULL));
	
	valores_heroe();
	ini_malo(&N);
	
	do{
		do{
			printf("(1) Atacar. \n");
			printf("(2) Magia. \n");
			scanf("%i",&op);
		}while(op<1 || op>2);
		
		for(i=0; i<N;i++) //recorremos todos los malos que tenemos
		{
			if(otros[i].vida>0)
			{
				printf("El malo %i tiene una vida de %i\n",i,otros[i].vida);
			}
			else{
				printf("El malo %i esta muerto\n",i);
			}
		}
		printf("Contra quien quieres pelear?: ");
		scanf("%i", &ob);	
		
		if(otros[ob].vida>0)
		{
			batalla(ob,op);	
		}	
		else{
			printf("\nDeja a los muertos en paz\n");
		}
		
		printf("Pulsa una tecla para continuar\n");
		fflush(stdin);
		fgets(l,10,stdin);
		cambio(l);
		system("cls");
		
		
		printf("\nTurno de los malos: %i\n\n", cont);
		system("pause")	;

		for(i=0;i<N;i++)
		{
			if(otros[i].vida>0)
			{
				pegar=otros[i].fuerza * (rand() % 3);
				yo.vida=yo.vida-pegar;
				printf("el malo %i pega con fuerza %i al heroe quedandose este con una vida de %i\n",i,pegar,yo.vida);
			}
			else{
			printf("El malo %i esta muerto\n",i);
			}
			
		

		}
		
		if((cont % 2)==0) //se va a redimensionar el vector ya que cada dos turnos (cont) se aumenta 1 malo
		{
			otros = (malo*)realloc(otros,(N+1)*sizeof(malo));
			if(otros==NULL)
			{
				printf("No se ha podido reservar en memoria\n");
				exit(1);
			}
			valores_malo(N);
			N++;
		}
		
		cont++;
		
		system("pause")	;
		printf("Pulsa una tecla para continuar\n");
		fflush(stdin);
		fgets(l,1,stdin);
		cambio(l);
		system("cls");
	
		
		
	}while(yo.vida>0);
	
	
	system("pause");
	return 0;	
	
}


//********************FUNCI�N: DAR VALORES INICIALES A NUESTRO H�ROE****************************
void valores_heroe(){ 
	
	yo.fuerza=50;
	yo.magia=100;
	yo.mana=50;
	yo.vida=10000;
}


//********************FUNCI�N: DIMENSIONAR NUESTRA VARIABLE DIN�MICA DE OTROS (MALOS)****************************
void ini_malo(int *N) 
{
	otros=(malo*)malloc((*N+1)*sizeof(malo)); //ponemos N+1 ya que N es 0 y sino malloc se multiplicar�a por 0
	if(otros==NULL)
	{
		printf("No se ha podido reservar en memoria\n");
		exit(1);
	}
	
	valores_malo(*N); 
		
	(*N)++; //se tiene que poner de esta forma para que se incremente N
}


//********************FUNCI�N: DAR VALORES INICIALES A NUESTRO MALO****************************
void valores_malo(int N) 
{
	otros[N].fuerza=100;
	otros[N].vida=100;
}


//********************FUNCI�N: VARIOS ATAQUES****************************
void batalla(int ob, int op) 
{
	int pegar, i;
	
	switch(op){
		case 1:{
			printf("Heroe ataca normal %i\n", yo.fuerza);
			pegar=yo.fuerza;
			otros[ob].vida=otros[ob].vida-pegar;
			printf("el malo %i se queda con una vida de %i\n",ob,otros[ob].vida);
			break;
		}
		case 2:{
			if(yo.mana>0)
			{
				pegar=yo.magia*(rand()%3);
				otros[ob].vida=otros[ob].vida-pegar;
				yo.mana=yo.mana-25;
				printf("Heroe ataque magia %i\n", pegar);
				printf("el malo %i se queda con una vida de %i\n",ob,otros[ob].vida);
				printf("el heroe se queda con %i de mana\n",yo.mana);
			}
			else
			{
				printf("Losiento, no hay suficiente mana\n");
			}
			break;
		}
	}

}


//********************FUNCI�N: PARA CAMBIAR EL FINAL DE LA CADENA EN VEZ DE SALTO DE L�NEA****************************
void cambio(char l[])
{
	int i;
	
	for(i=0;i<1;i++)
	{
		if(l[i]=='\n')
		{
			l[i]='\0';
		}
	}
	
}
