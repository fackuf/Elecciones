#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Diputados_y_Concejales{
	
	unsigned long dni;
	char nombre[30];
	int cargo, orden;
	struct Diputados_y_Concejales *sgte;
	
};

struct Lemas{
	
	int num, exp;
	char denom[30];
	float votos;
	struct Diputados_y_Concejales *TpD;
	struct Lemas *sgte;
	
};

struct Sublemas{
	
	int num, exp, alcance, nlema;
	char denom[30];
	float votos;
	struct Diputados_y_Concejales *TpC;
	struct Sublemas *sgte;
	
};


struct Votos{
	
	int lema, sublema, nro_voto;
	struct Votos *ant;
	struct Votos *sgte;
	
};

struct Bancas{
	
	int nsubl, cantb;
	struct Bancas *sgte;
	
};

struct ArbolConcejales {
	
	struct ArbolConcejales *izq;
	
	char nombre[30];
	unsigned long dni;
	int cargo, orden;
	
	struct ArbolConcejales *der;
	
}arbol;

struct Lemas * Cargar_Lemas_Y_Dip();										//Actualiza LES de Lemas y PILAS de Diputados		LISTO
struct Sublemas * Cargar_Sublemas_Y_Con();									//Actualiza LES de Sublemas y PILAS de Concejales LISTO
void Insertar_LES_Final(struct Lemas **, struct Lemas **);	
struct Lemas * Buscar_Anterior_Final(struct Lemas *);				

void Insertar_LES_Final_Sub(struct Sublemas **, struct Sublemas **);	
struct Sublemas * Buscar_Anterior_Final_Sub(struct Sublemas *);

void Leer_Votos(struct Votos**);											//Actualiza LDE de Votos							LISTO
void InsertarLDE(struct Votos **, struct Votos **);							//L
	
void Ingresar_Lemas(); 														//Añadir un nuevo lema al archivo					FALTA TUTE
void Apilar (struct Diputados_y_Concejales **, struct Diputados_y_Concejales **);		

void Ingresar_Sublemas_Concejales();										//Añadir un nuevo sublema al archivo				

void CargarVoto(struct Votos **);											//Añadir un nuevo voto

void Imprimir_Lemas_Diputados(struct Lemas *);								//Mostrar Lemas al Votante
void Buscar_Lema(int, struct Lemas *);										//Mostrar diputados al votante

void Imprimir_Lemas(struct Lemas *);										//Mostrar Lemas existentes
void Imprimir_Diputados(struct Lemas *);
void Imprimir_Sublemas(struct Sublemas *);
void Imprimir_Concejales(struct Sublemas *);
void Buscar_Sublema(int, struct Sublemas *);
void Desapilar (struct Diputados_y_Concejales **, struct Diputados_y_Concejales **);
int Vacia (struct Diputados_y_Concejales *);

void VotosRandoms(struct Votos **);
void Imprimir_Votos(struct Votos*);											//Mostrar Votos registrados
void Generar_Voto_txt(struct Votos*);

void Resultados_Lemas(struct Votos *, struct Lemas *);

void Actualizar_Votos(struct Votos *, struct Lemas *, struct Sublemas *);

struct Bancas* Cargar_Bancas(struct Sublemas *);
void Dhont_Concejales(struct Sublemas*,struct Bancas*, struct Votos *);
void AumentoCociente(struct Bancas *, int);
int BuscarDivisor(struct Bancas *, int);
void Porcentaje_Sublemas(struct Sublemas*);

void Imprimir_Ganadores(int, int, struct Sublemas *);

void Generar_Arbol(struct Bancas *LB, struct Sublemas *Lsub, struct ArbolConcejales **r);
struct ArbolConcejales *Insertar_Arbol(struct ArbolConcejales *r, struct ArbolConcejales *n);
void RecorrerIRD (struct ArbolConcejales *);

int main(){
	
	int op;
	
	struct Lemas *L = NULL;
	struct Sublemas *L2 = NULL;
	struct Votos *LDE = NULL;
	struct Bancas*LB = NULL;
	struct ArbolConcejales *r = NULL;

	
	L = Cargar_Lemas_Y_Dip();
	L2 = Cargar_Sublemas_Y_Con();
	Leer_Votos(&LDE);
	
	LB = Cargar_Bancas(L2);
	
	do{
		
		system("cls");
       
        puts("\n\n\t\t\t\tSISTEMA RECUENTO DE VOTOS");
        puts("\t\t\t-----------------------------------------");
        puts("\n\tSeleccione una opcion.\n");
        puts("FUNCIONES:");
        puts("\t1. Cargar Nuevo voto");
        puts("\t2. Consultar Lemas");
        puts("\t3. Consultar Sublemas");
        puts("\t4. Consultar Resultados de las elecciones.");
        puts("\nAUXILIARES:");
        puts("\t5. Ingresar Nuevo Lema");
        puts("\t6. Ingresar Nuevo Sublema");
        puts("\t7. Imprimir Diputados");
        puts("\t8. Imprimir Concejales");
        puts("\t9. Imprimir Votos registrados");
        puts("\t10. Generar votos aleatorios.");
        
        puts("\n\t0. SALIR\n\n");
        
        fflush(stdin);
        scanf("%d", &op);
        
        switch (op){
        	case 1:
        		CargarVoto(&LDE);
        		Actualizar_Votos(LDE, L, L2);

        		break;
        	case 2:
        		Imprimir_Lemas(L);
        		break;
        	case 3:
        		Imprimir_Sublemas(L2);
        		break;
        	case 4:
        		Resultados_Lemas(LDE, L);
        		Porcentaje_Sublemas(L2);
        		Dhont_Concejales(L2,LB, LDE);
        		LB = Cargar_Bancas(L2);
        		break;
        	case 5:
        		Ingresar_Lemas(); 
        		L = Cargar_Lemas_Y_Dip();
        		break;
        	case 6:
        		Ingresar_Sublemas_Concejales();
        		L2 = Cargar_Sublemas_Y_Con();
        		break;
        	case 7:
        		Imprimir_Diputados(L);
        		break;
        	case 8:
        		Imprimir_Concejales(L2);
        		break;
        	case 9:
        		Imprimir_Votos(LDE);
        		break;	
        	case 10:
        		VotosRandoms(&LDE);
        		Actualizar_Votos(LDE, L, L2);
				
        		break;
        	case 0:
        		puts("Saliendo del Sistema.");
        		break;
        	default:
        		puts("Opcion no valida. Intente nuevamente.");
        		system("pause");
		}
        
	}while (op != 0);
}

struct Lemas * Cargar_Lemas_Y_Dip()
{
	FILE *fp_Lemas;
	
	int i, j, tam;
	
	struct Lemas *p = NULL;
	struct Lemas *L = NULL;
	struct Diputados_y_Concejales *q = NULL;
	struct Diputados_y_Concejales *tope = NULL;

	if((fp_Lemas = fopen("Lemas y Diputados.bin", "a+b")) != NULL)
	{
		fseek(fp_Lemas,0,SEEK_END);		
		tam= ftell(fp_Lemas);
		rewind(fp_Lemas);
		
		while(ftell(fp_Lemas)<tam)
		{
			p = (struct Lemas *) malloc(sizeof(struct Lemas));
			if(p != NULL) 
			{	
				fread(&(*p), sizeof(*p), 1, fp_Lemas);
				p->sgte = NULL;
			
				for(j = 0; j < 27; j++)
				{
					q = (struct Diputados_y_Concejales *) malloc(sizeof(struct Diputados_y_Concejales));
					if(q != NULL) 
					{	
						
						fread(&(*q), sizeof(*q), 1, fp_Lemas);
						q->sgte = NULL;
						Apilar(&q, &tope);
					}
					else
					{
						printf("Error asignacion de memoria diputados\n");
						system("pause");
					}
				}
				
				p->TpD = tope;
				tope = NULL;
				
				Insertar_LES_Final(&p, &L);
			}
			else
			{
				printf("Error asignacion de memoria lemas\n");
				system("pause");
			}
		}
		
		fclose(fp_Lemas);
		return(L);
	}
	else
	{
		printf("Error al abrir el archivo\n");
		system("pause");
	}
	
}

void Insertar_LES_Final(struct Lemas **nv, struct Lemas **ini){
	
	struct Lemas *ant;
	
	ant = Buscar_Anterior_Final((*ini));
	
	if(ant!=NULL) 
	{
		ant->sgte = (*nv);
	}
	else
	{
		(*ini) = (*nv);
	}
	
	(*nv) = NULL;
}

struct Lemas *Buscar_Anterior_Final(struct Lemas *rc){
	
	struct Lemas *ant;
	
	ant = NULL;
	
	while(rc!=NULL)
	{
		ant = rc;
		rc = rc->sgte;
	}
	
	return(ant);
	
}

void Apilar (struct Diputados_y_Concejales **p, struct Diputados_y_Concejales **tp){
	
	(*p)->sgte = (*tp);
	(*tp) = (*p);
	(*p) = NULL;
	
}

struct Sublemas * Cargar_Sublemas_Y_Con()
{
	FILE *fp_Sublemas;
	
	int i, j, tam;
	
	struct Sublemas *p = NULL;
	struct Sublemas *L = NULL;
	struct Diputados_y_Concejales *q = NULL;
	struct Diputados_y_Concejales *tope = NULL;

	if((fp_Sublemas = fopen("Sublemas y Concejales.bin", "a+b")) != NULL)
	{
		fseek(fp_Sublemas,0,SEEK_END);		
		tam= ftell(fp_Sublemas);
		rewind(fp_Sublemas);
		
		while(ftell(fp_Sublemas)<tam)
		{
			p = (struct Sublemas *) malloc(sizeof(struct Sublemas));
			if(p != NULL) 
			{	
				fread(&(*p), sizeof(*p), 1, fp_Sublemas);
				p->sgte = NULL;
			
				for(j = 0; j < 14; j++)
				{
					q = (struct Diputados_y_Concejales *) malloc(sizeof(struct Diputados_y_Concejales));
					if(q != NULL) 
					{	
						fread(&(*q), sizeof(*q), 1, fp_Sublemas);
						Apilar(&q, &tope);
					}
					else
					{
						printf("Error asignacion de memoria diputados\n");
						system("pause");
					}
				}
				
				p->TpC = tope;
				tope= NULL;
				
				Insertar_LES_Final_Sub(&p, &L);
			}
			else
			{
				printf("Error asignación de memoria Sublemas\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("Error al abrir el archivo de sublemas y concejales\n");
		system("pause");
	}
	
	fclose(fp_Sublemas);
		
	return(L);
}

void Insertar_LES_Final_Sub(struct Sublemas **nv, struct Sublemas **ini){
	
	struct Sublemas *ant;
	
	ant = Buscar_Anterior_Final_Sub((*ini));
	
	if(ant!=NULL) 
	{
		ant->sgte = (*nv);
	}
	else
	{
		(*ini) = (*nv);
	}
	
	(*nv) = NULL;
}

struct Sublemas *Buscar_Anterior_Final_Sub(struct Sublemas *rc){
	
	struct Sublemas *ant;
	
	ant = NULL;
	
	while(rc!=NULL)
	{
		ant = rc;
		rc = rc->sgte;
	}
	
	return(ant);
	
}

void Leer_Votos(struct Votos **L){
	
	FILE *fp_Votos;
	
	struct Votos *p;
	int i, tam;
	
		
	if((fp_Votos = fopen("Votos.bin","a+b")) != NULL){
		
		fseek(fp_Votos,0,SEEK_END);	
		tam = ftell(fp_Votos);
		rewind(fp_Votos);
	
		while(ftell(fp_Votos)<tam){
		
			p = (struct Votos *) malloc(sizeof(struct Votos));
			
			if(p != NULL){
				
				fread(&(*p), sizeof(*p), 1, fp_Votos);
				p->ant = NULL;
				p->sgte = NULL;
				
				InsertarLDE(&p,&(*L));
				
			}else{
				puts("No hay espacio en memoria.");
			}
		}
			
	}else{
		printf("error al abrir el archivo");
	}

	fclose(fp_Votos);
}	

void InsertarLDE(struct Votos **nv, struct Votos **ini)
{
	struct Votos *aux = (*ini);
	
	if((*ini) != NULL)
	{
		while(aux->sgte != NULL)
		{
			aux = aux->sgte;
		}
		aux->sgte = (*nv);
		(*nv)->ant = aux;
		(*nv)->sgte = NULL;
		
	}
	else
	{
		(*nv)->ant = NULL;
		(*nv)->sgte = NULL;
		(*ini) = (*nv);
	}
}

void Ingresar_Lemas()
{
	int j = 1;
	int i;
	FILE *fp_Lemas;
	
	struct Lemas *p = NULL;
	struct Diputados_y_Concejales *q = NULL;
	
	p = (struct Lemas *) malloc(sizeof(struct Lemas));
	q = (struct Diputados_y_Concejales *) malloc(sizeof(struct Diputados_y_Concejales));
	
	if(p != NULL)
	{
				
		if((fp_Lemas = fopen("Lemas y Diputados.bin", "a+b")) != NULL)
		{
			printf("Ingrese la denominacion del lema N %d, o 0 para salir:\n", j);
			fflush(stdin);
			gets(p->denom);
			
			while(strcmp(p->denom, "0") != 0){
				p->num = j;
				
				printf("Ingrese el numero de expediente del lema:\n");
				fflush(stdin);
				scanf("%d", &p->exp);
				
				p->votos = 0;
				p->TpD = NULL;
				p->sgte = NULL;
				
				fwrite(&(*p), sizeof(*p), 1, fp_Lemas);
				
				
				
				for(i=0;i<27;i++){
				
					printf("Ingrese el dni del diputado numero %d:\n", i+1);
					fflush(stdin);
					scanf("%u", &q->dni);
					printf("Ingrese el nombre del diputado numero %d:\n", i+1);
					fflush(stdin);
					gets(q->nombre);
					
					do{
						printf("Ingrese el cargo del diputado numero %d (0 para titular / 1 para suplente):\n", i+1);
						fflush(stdin);
						scanf("%d", &q->cargo);
						if(q->cargo != 0 && q->cargo != 1){
							printf("Valor invalido, intente nuevamente\n");
						}
						
					
					}while(q->cargo != 0 && q->cargo != 1);
					
					q->orden=27-i;
					
					q->sgte=NULL;
			
					fwrite(&(*q),sizeof(*q),1,fp_Lemas);	
				}
				
				j++;
				
				printf("Ingrese la denominacion de lema numero %d, o 0 para salir:\n", j);
				fflush(stdin);
				gets(p->denom);
			}
		}
		else
		{
			printf("Error al abrir el archivo\n");
		}
		
		fclose(fp_Lemas);
		
		printf("Ingreso de lemas finalizado, volviendo al menu...\n");
		
		system("pause");
	}
	else
	{
		printf("Error de asignacion de memoria\n");
	}
}

void Ingresar_Sublemas_Concejales()
{

	int i, tam;
	FILE *fp_Sublemas;
	
	struct Sublemas *p = NULL;
	struct Diputados_y_Concejales *q = NULL;
	
	p = (struct Sublemas *) malloc(sizeof(struct Sublemas));
	q = (struct Diputados_y_Concejales *) malloc(sizeof(struct Diputados_y_Concejales));
	
	if(p != NULL)
	{
				
		if((fp_Sublemas = fopen("Sublemas y Concejales.bin", "a+b")) != NULL)
		{
			
			fseek(fp_Sublemas,0,SEEK_END);	
			tam= ftell(fp_Sublemas);
			rewind(fp_Sublemas);
			
			
			printf("Ingrese la denominacion del nuevo Sublema, o 0 para salir:\n");
			fflush(stdin);
			gets(p->denom);
			
			while(strcmp(p->denom, "0") != 0)
			{
				
				
				printf("Ingrese el numero  del Sublema:\n");
				fflush(stdin);
				scanf("%d", &p->num);
				printf("Ingrese el numero de expediente del Sublema:\n");
				fflush(stdin);
				scanf("%d", &p->exp);
				
				
				do{
					printf("Ingrese el alcance del Sublema (0 para Municipal / 1 para Provincial):\n");
					fflush(stdin);
					scanf("%d", &p->alcance);
					if(p->alcance != 0 && p->alcance != 1) {
						printf("Valor invalido, intente nuevamente\n");
					}
				} while(p->alcance != 0 && p->alcance != 1);
				
				printf("Ingrese el numero de Lema al que corresponde el Sublema:\n");
				fflush(stdin);
				scanf("%d", &p->nlema);
				
				p->votos = 0;
				p->TpC = NULL;
				p->sgte = NULL;
				
				fwrite(&(*p), sizeof(*p), 1, fp_Sublemas);
				
				
				
				for(i=0;i<14;i++){
				
					printf("Ingrese el dni del Concejal numero %d:\n", i+1);
					fflush(stdin);
					scanf("%u", &q->dni);
					
					printf("Ingrese el nombre del Concejal numero %d:\n", i+1);
					fflush(stdin);
					
					gets(q->nombre);
					
					do{
						printf("Ingrese el cargo del Concejal numero %d (0 para titular / 1 para suplente):\n", i+1);
						fflush(stdin);
						scanf("%d", &q->cargo);
						if(q->cargo != 0 && q->cargo != 1) {
						printf("Valor invalido, intente nuevamente\n");
					}
					} while(q->cargo != 0 && q->cargo != 1);
					
					q->orden=14-i;
					
					q->sgte=NULL;
			
					fwrite(&(*q),sizeof(*q),1,fp_Sublemas);	
				}
				
				
				printf("Ingrese la denominacion del nuevo Sublema, o 0 para salir:\n");
				fflush(stdin);
			
				gets(p->denom);
			};
		}
		else
		{
			printf("Error al abrir el archivo\n");
		}
		
		fclose(fp_Sublemas);
		
		printf("Ingreso de lemas finalizado, volviendo al menu...\n");
	}
	else
	{
		printf("Error de asignacion de memoria\n");
		system("pause");
	}
}

void CargarVoto(struct Votos **LDE){
	
	struct Votos *nv=NULL;
	struct Votos *aux=NULL;
	struct Lemas *lema=NULL;
	int tam, op=1;
	
	FILE *fp_Votos;
	
	aux = (struct Votos *) malloc(sizeof(struct Votos));
	nv = (struct Votos *) malloc(sizeof(struct Votos));
	
	while(op == 1){
		
			
		nv = (struct Votos *) malloc(sizeof(struct Votos));
	
		if(nv != NULL && aux != NULL){
		
			
			puts("Ingrese el numero de Lema al que desea votar");
			fflush(stdin);
			scanf("%d", &nv->lema);
			
			puts("Ingrese el numero de Sublema al que desea votar");
			fflush(stdin);
			scanf("%d", &nv->sublema);
			
			nv->ant = NULL;
			nv->sgte = NULL;	
			
			if((fp_Votos = fopen("Votos.bin","a+b")) != NULL){
				
				fseek(fp_Votos, 0, SEEK_END);
				tam = ftell(fp_Votos);
				rewind(fp_Votos);
		
				if(ftell(fp_Votos)>=tam) {
					
					nv->nro_voto = 1;
					
				} else {
					
					
					fseek(fp_Votos,	((sizeof(struct Votos))*(-1)), SEEK_END);

					fread(&(*aux),sizeof(*aux),1,fp_Votos);

					nv->nro_voto = aux->nro_voto + 1;

						
				}
				
				fseek(fp_Votos, 0, SEEK_END);
				fwrite(&(*nv), sizeof(*nv), 1, fp_Votos);

				fclose(fp_Votos);
				
				InsertarLDE(&nv, &(*LDE));
				Generar_Voto_txt(nv);
				
				puts("Voto registrado.");
				puts("Si desea registrar un nuevo voto, ingrese 1, de lo contrario ingrese 0.");
				fflush(stdin);
				scanf("%d", &op);
				
				
			}else{
			puts("Error al abrir archivo Votos.bin.\n");
			system("pause");
			}
		
		}else{
			puts("ERROR: No hay espacio en memoria para un nuevo voto.");
		}
			
		
		
	}
		

}

void Generar_Voto_txt(struct Votos *nv){
	
	char nombre_archivo[30];
	FILE* fp_Votos;
	
	sprintf(nombre_archivo,"Voto N %d.txt",nv->nro_voto);	
	
	if((fp_Votos = fopen(nombre_archivo,"wt")) != NULL){
		
		fprintf(fp_Votos,"VOTO N %d\n",nv->nro_voto);
		fprintf(fp_Votos,"\nLEMA: %d\n",nv->lema);
		fprintf(fp_Votos,"SUBLEMA: %d",nv->sublema);
		
		fclose(fp_Votos);		
			
	} else {
		
		printf("Error al abrir archivo %s\n", nombre_archivo);
		system("pause");
		
	}
	
}

//FUNCIONES QUE IMPRIMEN


void Buscar_Lema(int dato,struct Lemas *rc){
	
	struct Diputados_y_Concejales *TopeD = NULL;
	struct Diputados_y_Concejales *p = NULL;
	struct Diputados_y_Concejales *TpAux = NULL;
	
	int i=0;
	char cargo[10];
	
	
	while(rc != NULL){
		
		if(rc->num == dato)
		{
			TopeD = rc->TpD;
			
			printf("Imprimiendo diputados del lema %s:\n\n", rc->denom);
	
			p = (struct Diputados_y_Concejales *) malloc(sizeof(struct Diputados_y_Concejales));
	
			while(!Vacia(TopeD))
			{
				
				Desapilar(&p, &TopeD);
				
				
				if(i<20){
					printf("%d. TITULAR\n", i+1);
				}else{
					printf("%d. SUPLENTE\n", i+1);
				}
				
				printf("\tNombre y apellido: %s\n", p->nombre);
				printf("\tDNI: %u\n", p->dni);
				printf("\tNumero de orden: %d\n", p->orden);
				
				i++;
				
				Apilar(&p, &TpAux);
			}
			
			while(!Vacia(TpAux))
			{
				Desapilar(&p, &TpAux);
				
				
				Apilar(&p, &TopeD);
			}
			
			rc = NULL;
		}
		else
		{
			rc = rc->sgte;
		}
	}
}

void Buscar_Sublema(int NumSublema, struct Sublemas *rc){
	
	struct Diputados_y_Concejales *TpC = NULL;
	struct Diputados_y_Concejales *p = NULL;
	struct Diputados_y_Concejales *TpAux = NULL;
	
	char cargo[10];
	int i=0;
	
	while(rc != NULL){
		
		if(rc->num == NumSublema){
			
			TpC = rc->TpC;
			
			printf("Imprimiendo concejales del Sublema %s:\n\n", rc->denom);
			
			while(!Vacia(TpC)){
			
				Desapilar(&p, &TpC);
				
				if(i<7){
					printf("%d. TITULAR\n", i+1);
				}else{
					printf("%d. SUPLENTE\n", i+1);
				}
				
				printf("\tNombre y apellido: %s\n", p->nombre);
				printf("\tDNI: %u\n", p->dni);
				printf("\tNumero de orden: %d\n", p->orden);
			
				
				Apilar(&p, &TpAux);
				
				i++;
			}
			
			while(!Vacia(TpAux))
			{
				Desapilar(&p, &TpAux);
				
				Apilar(&p, &TpC);
			}
			
			rc = NULL;
			
		}else{
			
			rc= rc->sgte;
			
		}
		
		
	}
	
	
}

void Actualizar_Votos(struct Votos *LDE, struct Lemas *L, struct Sublemas *L2) {
	//SE CORRIGIO EL FUNCIONAMIENTO DE LA FUNCION ACTUALIZAR_VOTOS:AHORA SE OPERA CON LAS LISTA DE VOTOS,LEMAS Y SUBLEMAS 
	//PARA ACTUALIZAR LOS CAMPOS DE VOTOS DE CADA UNA DE LAS LISTAS,LUEGO SE REGISTRAN LOS RESULTADOS EN LOS ARCHIVOS.
	
	
	float votos = 0;
	
	struct Votos *iniLDE;
	struct Lemas *iniL;
	struct Sublemas *iniL2;
	
	FILE *fp_Lemas, *fp_Sublemas;
	
	iniLDE = LDE;			//Se declaran auxiliares para poder guardar el inicio de las listas.
	iniL = L;
	iniL2 = L2;
	
	while(L != NULL) {
		
		LDE = iniLDE;
		
		while(LDE != NULL) {
			
			if(L->num == LDE->lema) {
				votos += 1;
			}
			LDE = LDE->sgte;
		}
		
		L->votos = votos;
		votos = 0;
		
		L = L->sgte;
	}
	
	while(L2 != NULL) {
		
		LDE = iniLDE;
		
		while(LDE != NULL) {
			
			if(L2->num == LDE->sublema) {
				votos += 1;
			}
			LDE = LDE->sgte;
		}
		
		L2->votos = votos;
		votos = 0;
		
		L2 = L2->sgte;
	}
	
	if((fp_Lemas = fopen("Lemas y Diputados.bin","r+b")) != NULL){
		
		L = iniL;
		L2 = iniL2;
		
		while(L != NULL) {
			
			fwrite(&(*L), sizeof(struct Lemas), 1, fp_Lemas);
			fseek(fp_Lemas, (sizeof(struct Diputados_y_Concejales) * 27), SEEK_CUR);
			L = L->sgte;
			
		}
		
		fclose(fp_Lemas);
		
		if((fp_Sublemas = fopen("Sublemas y Concejales.bin","r+b")) != NULL){
			
			while(L2 != NULL) {
			
				fwrite(&(*L2), sizeof(struct Sublemas), 1, fp_Sublemas);
				fseek(fp_Sublemas, (sizeof(struct Diputados_y_Concejales) * 14), SEEK_CUR);
				L2 = L2->sgte;
			
			}
			
			fclose(fp_Lemas);
			
		} else {
			
			printf("Error al abrir el archivo Sublemas y Concejales.bin\n");
			system("pause");
			
		}
		
	} else {
		
		printf("Error al abrir el archivo Lemas y Diputados.bin\n");
		system("pause");
		
	}
	
}
//AUXILIARES






void Imprimir_Lemas(struct Lemas *L)
{
	int i;
		
	while(L!=NULL)
	{
		printf("LEMA: %s\n", L->denom);
		printf("\tNumero de Lema: %d\n", L->num);
		printf("\tNumero de expediente: %d\n", L->exp);
		printf("\tCantidad de votos: %0.f\n", L->votos);		
		
		L = L->sgte;
	}	
	
	system("pause");
}

void Imprimir_Diputados(struct Lemas *L)
{
	int i, NumLema;
	
	printf("Ingresar numero de lema a consultar diputados:\n");
	scanf("%d", &NumLema);
	
	Buscar_Lema(NumLema, L);
	
	system("pause");
	
}

void Imprimir_Sublemas(struct Sublemas *L){
	int i, numLema;
	
	printf("Ingrese para que numero de lema quiere consultar los sublemas:\n");
	do{
		
		fflush(stdin);
		scanf("%d", &numLema);
		if(numLema < 0 || numLema > 6) {
			printf("Lema ingresado no valido, intente nuevamente:\n");
		}
		
	} while(numLema < 0 || numLema > 6);
		
	while(L!=NULL)
	{
		if(L->nlema == numLema){
			printf("SUBLEMA: %s\n", L->denom);
			printf("\tNumero de Sublema: %d\n", L->num);
			printf("\tNumero de Lema: %d\n", L->nlema);
			printf("\tNumero de expediente: %d\n", L->exp);
			if(L->alcance == 0){
				printf("\tAlcance de sublema: Municipal\n");
			} else{
				printf("\tAlcance de sublema: Provincial\n");
			}
			printf("\tCantidad de votos: %0.f\n\n", L->votos);		
		}
		
		L = L->sgte;
	}	
	system("pause");
}


void Imprimir_Concejales(struct Sublemas *L){
	int i, NumLema, NumSublema;
	
	printf("Ingrese el numero de sublema para el cual desea consultar los concejales:\n");
	fflush(stdin);
	scanf("%d", &NumSublema);
	
	Buscar_Sublema(NumSublema, L);
	
	system("pause");
}
	
void Desapilar (struct Diputados_y_Concejales **p, struct Diputados_y_Concejales **tp){
	
	(*p) = (*tp);
	(*tp) = (*tp)->sgte;
	(*p)->sgte = NULL;
	
}

int Vacia(struct Diputados_y_Concejales *tp){
	
	if(tp == NULL)
		return(1);
	else
		return(0);
	
}
	
void Imprimir_Votos(struct Votos *ini){
	
	int cont,i;
	cont=0;
	
	while(ini != NULL)
	{
		cont++;
		
		printf(" VOTO N %d\n\tLEMA: %d\n\tSUBLEMA: %d\n",cont, ini->lema, ini->sublema);

		ini= ini->sgte;
	}
	
	system("pause");
	
}

void VotosRandoms(struct Votos **ini) {

	struct Votos *nv;
	struct Votos *aux;
	struct Lemas *lema;
	FILE *fp_Votos;
	int a=0,i=0,l1=0,l2=0,l3=0,l4=0,l5=0,l6=0,VB=0,Votos[7], cant;
	srand (time(NULL));
	int tam;
	
	puts("Ingrese la cantidad de votos que desea generar de manera aleatoria.");
	fflush(stdin);
	scanf("%d", &cant);
	puts("Espere un momento.");
	
	for(a = 0; a < 7 ; a++) {
		Votos[a]=0;
	}
	
	nv = (struct Votos *) malloc(sizeof(struct Votos));
	aux = (struct Votos *) malloc(sizeof(struct Votos));
	
	
	if(nv != NULL) {
		
		for(i = 0; i < cant ; i++) {
			
			a = rand () % (6-0+1) +0;
			l1 = rand () % (55-1+1) +1;	
			if((l1<=9) && (l1>0)){
                l2= l1+110;
            }
            if((l1>9) && (l1<16)){
                l2= l1+1100;
            }
                if((l1>15) && (l1<25)){
                l2=l1-15;
                l2=l2+220;
            }
                if((l1>24) && (l1<33)){
                l2=l1-14;
                l2=l2+2200;
            }

                if((l1>32) && (l1<43)){
                l2=l1-32;
                l2=l2+330;
            }
                if((l1>43) && (l1<50)){
                l2=l1-33;
                l2=l2+3300;
            }
            if((l1>50) && (l1<53)){
                l2=l1-48;
                l2=l2+440;
            }
                if(l1==53){
                l2=l1-52;
                l2=l2+550;
            }
                if((l1>53) && (l1<=55)){
                l2=l1-53;
                l2=l2+660;
            }
			
			nv->lema=a;
			nv->sublema=l2;
			nv->nro_voto=i;
			
			
			if((fp_Votos = fopen("Votos.bin","a+b")) != NULL){
				
				fseek(fp_Votos, 0, SEEK_END);
				tam = ftell(fp_Votos);
				rewind(fp_Votos);
		
				if(ftell(fp_Votos)>=tam) {
					
					nv->nro_voto = 1;
					
				} else {
					
					
					fseek(fp_Votos,	((sizeof(struct Votos))*(-1)), SEEK_END);

					fread(&(*aux),sizeof(*aux),1,fp_Votos);

					nv->nro_voto = aux->nro_voto + 1;

						
				}
				
				fseek(fp_Votos, 0, SEEK_END);
				fwrite(&(*nv), sizeof(*nv), 1, fp_Votos);

				fclose(fp_Votos);
				
				InsertarLDE(&nv, &(*ini));
				Generar_Voto_txt(nv);
				
			}
			
			Votos[a]=Votos[a]+1;

				
			
			if (a==0) {
				nv->lema=0;
				nv->sublema=0;
				
				InsertarLDE(&nv,&(*ini));
				Votos[a]=Votos[a]+1;
			}
			
			
			nv = (struct Votos *) malloc(sizeof(struct Votos));
		}
	}

	
	printf("Se han generado %d votos exitosamente.\n", cant);
	system("pause");
	
}

void Porcentaje_Sublemas(struct Sublemas *L){
	
	//SE AÑADIO LA FUNCION PORCENTAJE_SUBLEMAS PARA LA CONTABILIZACION DE LOS  
	//VOTOS RECIBIDOS POR LOS LEMAS POR PARTE DE SUS CORRESPONDIENTES SUBLEMAS
	//LOS TOTALES SE MUESTRAN EN PANTALLA LUEGO DE LOS RESULTADOS DE LEMAS CON SUS RESPECTIVOS PORCENTAJES.
	
	int i;
	struct Sublemas * iniL;
	float totals[6]={},porc=0,totalv=0,porc2=0;
	

	
	iniL=L;
	
	while(iniL!=NULL){
		
		totalv=totalv+iniL->votos;
		iniL=iniL->sgte;
	}
	
	iniL=L;
	
		
	for(i=0;i<6;i++){
		
		while(iniL!=NULL){		
			
			if(iniL->nlema==(i+1)){		
				
				totals[i]= iniL->votos+totals[i];
				
				
			}
			
			iniL=iniL->sgte;
		}
		
		
		iniL=L;
	}
	
	
	
	for(i=0;i<6;i++){
		
		printf("\nLEMA %d\n",i+1);
	
		
		while(iniL!=NULL){
			
			if(iniL->nlema==(i+1)){
				
				porc=(iniL->votos/totalv)*100; //el numero /total *100
				
				
				printf("\n\nSUBLEMA: %s\nCANTIDAD DE VOTOS: %0.f\nPORCENTAJE:%2.f%%",iniL->denom,iniL->votos,porc);
				
				porc2=totals[i]/totalv*100;
				
			
				
			}
			
			iniL=iniL->sgte;
		
		}
		
		printf("\n\nTotal de votos del lema %d: %2.f",i+1,totals[i]);
		printf("\nPorcentaje de votos al Lema %d: %2.f%%\n",i+1,porc2);
		
		iniL=L;
		
	}
	
		printf("\nVotos totales a sublemas: %0.f\n",totalv);
	
	
}

void Resultados_Lemas(struct Votos *Lv, struct Lemas *L){
	/*En cuanto a la elección de diputados provinciales, informar la cantidad de votos acumulados
para cada lema y cuánto obtuvo porcentualmente cada uno */
	int vlema[6]={}, blanco=0, total=0, i;
	float porc;

	puts("RESULTADOS DIPUTADOS");
	
	while(Lv != NULL){
		
		if((Lv->lema < 1)||(Lv->lema>6)){
			blanco++;
		}else{
			
			total++;
			switch(Lv->lema){
			
				case 1:
					vlema[0]++;;
					break;
				case 2:
					vlema[1]++;
					break;
				case 3:
					vlema[2]++;
					break;
				case 4:
					vlema[3]++;
					break;
				case 5:
					vlema[4]++;
					break;
				case 6:
					vlema[5]++;
					break;
	
			}
			
		}
			
		Lv= Lv->sgte;
	}
	
	printf("TOTAL : %d Votos\n", total);
	printf("VOTOS EN BLANCO: %d\n\n", blanco);
	
	for(i=0; i<6; i++){
		
		
		porc = (float)vlema[i]/(float)total * 100;
		
		printf("\nLEMA %d: %s\nVOTOS OBTENIDOS: %d\t %.1f %% DEL TOTAL.\n", L->num, L->denom, vlema[i], porc);
		
		porc = 0;
		
		L = L->sgte;
		
			
	}
		
	
	
	
}

struct Bancas *Cargar_Bancas(struct Sublemas *L){
	
	struct Bancas *LB = NULL;
	struct Bancas *p = NULL;
	struct Bancas *aux = NULL;
	
	while(L != NULL){
		
		
		p = (struct Bancas *) malloc(sizeof(struct Bancas));
		
		if(p!=NULL){
			
			p->cantb = 0;
			p->nsubl = L->num;
			p->sgte = NULL;
			
			if(LB == NULL){
				LB = p;
				LB->sgte = NULL;
				
				
			}else{
				
				
				aux = LB;
				while(aux->sgte != NULL){
					
					aux = aux->sgte;
					
				}
				
				aux->sgte = p;
				
			}
			
			p = NULL;
			
		}else{
			puts("ERROR: No hay espacio en memoria.");
			system("pause");
		}
		
		L = L->sgte;
	}

	
	return(LB);
}

void Dhont_Concejales(struct Sublemas *L, struct Bancas *LB, struct Votos *LDE){
	
	float maximo=0, total=0, porc;	
	struct Bancas *aux;
	struct Sublemas *aux2, *aux3, *aux4;
	struct ArbolConcejales *r = NULL;
	
	int auxsublema, i, div, enc=0, blanco=0;
	
	aux = LB;
	aux2 = L;

	
	for(i=0; i<7; i++){
		
		while(L!=NULL){// 55 vueltas 1 por cada sublema
			
			div = BuscarDivisor(LB, L->num);
		
			if(maximo<((L->votos)/(float)(div+1))){
				
				auxsublema = L->num;
				
				maximo=(L->votos/(float)(div+1));
			
			}
				
			L = L->sgte;
			
			
		}
		

		AumentoCociente(LB, auxsublema);
	
		maximo=0;
		
		L = aux2;
		
	}
	
	aux3 = aux2;
	while(LDE!= NULL){//RECORRE VOTOS
		
		while(aux3 != NULL){//RECORRE SUBLEMAS
		
			if(LDE->sublema == aux3->num){//SI ESE N DE SUBLEMA EXISTE
				enc= 1;
				aux3= NULL;
			}else{
				aux3 = aux3->sgte;
			}
			
		}
		
		if(!enc){//ENCONTRADO ES FALSO
			blanco++;
		}else{//ENCONTRADO ES VERDADERO
			total++;
		}
		
		enc=0;
		aux3 = aux2;
		LDE = LDE->sgte;

	}
	
	
	puts("\n\nRESULTADOS CONCEJALES:");
	printf("TOTAL : %0.f VOTOS\n", total);
	printf("VOTOS EN BLANCO: %d\n\n", blanco);
	
	aux4= aux2;
	
	while(aux2!=NULL){
		
		porc = aux2->votos/(float)total*100;
		
		if(aux->cantb != 0){
			printf("\n\nSUBLEMA N %d: %s \nCANTIDAD DE VOTOS: %0.f \t %.2f %% DEL TOTAL\nOCUPA %d BANCAS:", aux->nsubl, aux2->denom, aux2->votos, porc,  aux->cantb);
			
			Imprimir_Ganadores(aux->nsubl, aux->cantb, aux4);
		}
	
	
		aux2=aux2->sgte;
		aux=aux->sgte;
		
	}
	
	printf("\n\n");
	Generar_Arbol(LB, L, &r);
			
	puts("Arbol:");
	RecorrerIRD(r);
	printf("\nRaiz: %s\n", r->nombre);
	
	system("Pause");
}

void AumentoCociente(struct Bancas * L, int dato){

	while(L != NULL){

		if(L->nsubl == dato){
			
			L->cantb = L->cantb+1;
			L = NULL;
			
		}else{
			L = L->sgte;
		}
		
	}
	
	
}

int BuscarDivisor(struct Bancas *LB, int dato){
	int divisor=0;
	
	while(LB != NULL){
			
		if(LB->nsubl == dato){
			
			divisor= LB->cantb;
			LB = NULL;
			
		}else{
			LB = LB->sgte;
		}
		
		
	}
	
	return(divisor);
	
}

void Imprimir_Ganadores(int nsublema, int cantbancas, struct Sublemas *Lsub){
	
	struct Diputados_y_Concejales *p=NULL;
	struct Diputados_y_Concejales *Tpaux=NULL;
	int i;
	
	while(Lsub != NULL){
		
		if(Lsub->num == nsublema){
			
			for(i=0; i<cantbancas; i++){
				
				p = (struct Diputados_y_Concejales *) malloc(sizeof(struct Diputados_y_Concejales));
				
				if (p != NULL){
				
					Desapilar(&p, &Lsub->TpC);
					printf("\n\tDNI %u CONCEJAL %s\n", p->dni, p->nombre);
					Apilar(&p, &Tpaux);					
					p = NULL;
				}
				
			}
			
			for(i=0; i<cantbancas; i++){
			
				Desapilar(&p, &Tpaux);
				Apilar(&p, &Lsub->TpC);
			
			}
		
		}
		
		Lsub = Lsub->sgte;
	}
	
}


void Generar_Arbol(struct Bancas *LB, struct Sublemas *Lsub, struct ArbolConcejales **r){
	
	float mayor=0, bancasMayor, nmayor, i;
	struct ArbolConcejales *nv = NULL;
	
	struct Diputados_y_Concejales *p = NULL;
	struct Diputados_y_Concejales *Tpaux = NULL;
	
	struct Sublemas *aux2 = Lsub;
	struct Bancas *aux = LB;
	

	
	while (Lsub != NULL){					//encuentra el sublema con más votos

		if (Lsub->votos > mayor){

			mayor = Lsub->votos;
			nmayor = Lsub->num;
			
		}
		
		Lsub = Lsub->sgte;
		
	}
	
	while (LB != NULL){					//encuentra cuántas bancas tiene el sublema ganador

		if (LB->nsubl == nmayor){

			bancasMayor = LB->cantb;
			LB = NULL;
			
		} else {
			
			LB = LB->sgte;
			
		}		
	}
	
	LB = aux;
	Lsub = aux2;
	
	nv = (struct ArbolConcejales *) malloc(sizeof(struct ArbolConcejales));		//reserva espacio para el primer concejal
	
	if(nv!= NULL){

		while(Lsub != NULL){
		
			if(Lsub->num == nmayor){
				
				i= 0;
				
				while((i<bancasMayor) && (nv != NULL)){				//Se desapilan de la lista de concejales del sublema ganador tantos concejales
																	//como bancas tenga, y se los inserta en el árbol,
					Desapilar(&p, &Lsub->TpC);						//comenzando por el que tiene más votos, para que sea la raíz.
					
					
					strcpy(nv->nombre, p->nombre);
					nv->cargo = p->cargo;
					nv->orden = p->orden;
					nv->der = NULL;
					nv->izq = NULL;
					
					printf("Insertando al arbol a: %s\n", nv->nombre);
					
					(*r) = Insertar_Arbol((*r), nv);
					
					Apilar(&p, &Tpaux);
					
					
					nv = (struct ArbolConcejales *) malloc(sizeof(struct ArbolConcejales));	
					
					
					i++;
					
				}
				
				for(i=0; i<bancasMayor; i++){

					Desapilar(&p, &Tpaux);
					Apilar(&p, &Lsub->TpC);
					
				}

				Lsub = NULL;
				
					
			}else{
				
				Lsub = Lsub->sgte;
				
				
			}
			
		}
		
		
	}

	//insertar el resto de los nodos
	
	LB = aux;
	Lsub = aux2;
	

	while(LB != NULL){					//AUX = LB
										//AUX2 = LSUB
		
	
		
		if((LB->cantb > 0)&&(LB->nsubl != nmayor)){
			
			
			
			nv = (struct ArbolConcejales *) malloc(sizeof(struct ArbolConcejales));	
			
			if(nv != NULL){
				
				
				while(Lsub != NULL){
					
					
					if(Lsub->num == LB->nsubl){
						
						for(i=0; i < LB->cantb; i++){
							
							Desapilar(&p, &Lsub->TpC);
						
							strcpy(nv->nombre, p->nombre);
							nv->cargo = p->cargo;
							nv->orden = p->orden;
							nv->der = NULL;
							nv->izq = NULL;
							
							printf("Insertando al arbol a: %s\n", nv->nombre);
							
							(*r) = Insertar_Arbol((*r), nv);
						
							Apilar(&p, &Tpaux);	
							
							nv = (struct ArbolConcejales *) malloc(sizeof(struct ArbolConcejales));	
							
						}
						
						for(i=0; i<LB->cantb;i++){
						
							Desapilar(&p, &Tpaux);
							Apilar(&p, &Lsub->TpC);
							
						}
						
						Lsub = NULL;
						
						
					}else{
						Lsub = Lsub->sgte;
						
					}
			
				}
				
				Lsub = aux2;					//SE VUELVE AL INICIO DE LA LISTA DE SUBLEMAS
				
			}
			
		}
			LB = LB->sgte;			
	}
	
}

struct ArbolConcejales *Insertar_Arbol(struct ArbolConcejales *r, struct ArbolConcejales *n){
	
	if(r != NULL){

		if(!strcmp(r->nombre, n->nombre)){
			
			printf("Este concejal ya esta en el arbol\n");
			
		}else {

			if(strcmp(n->nombre, r->nombre)<0){
				printf("Avanzo abajo izquierda\n");
				r->izq = Insertar_Arbol((r->izq),n);
				
			}else {
				printf("Avanzo abajo derecha\n");
				r->der = Insertar_Arbol((r->der),n);
				
			}
		}
		
	}else{
		
		printf("Se inserta el nodo\n\n");
		r = n;

	}

	return(r);
	
}

void RecorrerIRD (struct ArbolConcejales *raiz){
    

    
	if(raiz != NULL){

    	RecorrerIRD(raiz->izq);
    	printf("%s \n", raiz->nombre);
        RecorrerIRD(raiz->der);
    }
    
}
