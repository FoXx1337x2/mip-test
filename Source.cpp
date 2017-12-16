#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bazar{
	char kategoria[50];
	char znacka[50];
	char predajca[100];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
	struct bazar *next;
} BAZAR;

int cmp(char find[50], char source[50]){
	char low_source[50];
	char low_find[50];						//vlastna funkcia ktora mi hlada v stringoch zadany substring a ignoruje velke/male pismena

	strcpy((low_source),source);	
	strcpy((low_find),find);
	strlwr(low_source);						//string aj substing si zmenim na male pismena aby som ich mohol porovnat pomocou strcpy ktory hlada vyskyt substringu
	strlwr(low_find);

	if(strstr(low_source,low_find) != NULL){
		return 1;
	}											//funkcia vracia hodnotu 1 pokial tam substring je , inak vracia 0
	else
		return 0;

}


void nacitaj(FILE **fr, int *list_amount, BAZAR **head, BAZAR **current,BAZAR **tail,int *n_fun_done){
	char h,row[50],stav[200];
	int int_row=0,lines_amount=0,counter=1;

	if((*list_amount)>0){
		//pokial uz funkcia bola zavolana alebo uz bol vytvoreny zoznam ktory musim uvolnit z pamate
		(*list_amount)=0;							//taktiez sa uvolnuje ak sa v zozname este nieco nachadza kebyze user vymaze vsetky zaznamy pomozou funkcie "z" tak sa neuvolnuje pamat
		while(((*current)=(*head)) != NULL){
			(*head)=(*head)->next;
			free(*current);
		}
	}




	if(((*fr) = fopen("auta.txt", "r")) != NULL){        //otvorim subor a ak sa neotvori vypise chybovu hlasku, ak sa otvory pokracujem dalej
		while((h=getc(*fr))!=EOF){
			if (h=='$') {
				(*list_amount)++;					//ak narazim na $ znamena to ze to je zaciatok noveho stacku informacii a teda si zvacsim counter zaznamov

			}
		}

		lines_amount=(*list_amount)*7;				//kazdy clovek ma 7 riadkov v subore a tymto vypocitam celkovy amount riadkov
		rewind(*fr);									//vratim sa na zaciatok suboru

		(*head)=(BAZAR *)malloc(sizeof(BAZAR));			//alokujem si zaciatok zoznamu
		(*current)=(*head);								//pomocnu current nastavim na zaciatok zoznamu

		while(1){
			fgets(row,50,(*fr));						//len ignoracia prveho riadku kedze sa tam nachadza $
			counter++;

			fgets(row,50,(*fr));						//nacitavam postupne riadky do kategorii, kam patria
			strcpy((*current)->kategoria,row);
			counter++;

			fgets(row,50,(*fr));
			strcpy((*current)->znacka,row);
			counter++;

			fgets(row,50,(*fr));
			strcpy((*current)->predajca,row);
			counter++;

			fscanf((*fr),"%d\n",&int_row);			//cisla nacitavam ako integer pretoze s nimi chcem neskor pocitat a je to jednoduchsie
			(*current)->cena=int_row;
			counter++;

			fscanf((*fr),"%d\n",&int_row);
			(*current)->rok_vyroby=int_row;
			counter++;

			fgets(stav,200,(*fr));
			strcpy((*current)->stav_vozidla,stav);
			counter++;

			if(counter==lines_amount+1){
				(*current)->next=NULL;					//pokial som nacital uz posledny zoznam tak pointer v poslednom ukazuje na NULL
				break; }

			else{
				(*tail)=(BAZAR *)malloc(sizeof(BAZAR));	//ak to este nieje posledny zoznam alokujem si next zoznam s predpokladom ze to moze byt posledny a teda ho alokujem s pomocnou tail ktora ukazuje na koniec zoznamov
				(*current)->next=*tail;				//pointer v current nastavim na tail
				(*current)=(*tail);						//pomocnu current prepnem na tail

			}
		}

		printf("Nacitalo sa %d zaznamov\n",*list_amount);	//vypis kolko sa nacitalo zoznamov
		(*n_fun_done)=1;
		fclose(*fr);
	}
	else {
		printf("Zaznamy neboli nacitane\n");				//chybova hlaska ak sa subor nepodarilo otvorit
	}

}

void vypis(BAZAR **head,BAZAR **current, BAZAR **tail,int *n_fun_done,int *list_amount){
	int cislo_zaznamu=1;

	if((*list_amount)>0){
		//funkcia pokracuje dalej len ak uz boli vytvorene zoznamy
		(*current)=(*head);			//pomocnu current prepnem na zaciatok zoznamu

		while(cislo_zaznamu<=(*list_amount)){
			//while cyklus ktory vypisuje zoznamy

			printf("%d.\n",cislo_zaznamu);
			printf("kategoria: %s",(*current)->kategoria);
			printf("znacka: %s",(*current)->znacka);
			printf("predajca: %s",(*current)->predajca);				//asi netreba koment
			printf("cena: %d\n",(*current)->cena);
			printf("rok_vyroby: %d\n",(*current)->rok_vyroby);
			printf("stav_vozidla: %s",(*current)->stav_vozidla);
			cislo_zaznamu++;
			(*current)=(*current)->next;		//pomocnu current prepnem na next zoznam v poradi
		}

		cislo_zaznamu=1;
	}

}

void pridaj(BAZAR **head,BAZAR **current, BAZAR **tail, BAZAR **new, int *list_amount,int *n_fun_done){
	int pozicia,cislo,actual_position;

	if (((*list_amount)==0) && ((*n_fun_done)==0)){

		if((*list_amount)==0){
			(*head)=(BAZAR *)malloc(sizeof(BAZAR));
			scanf("%d\n",&pozicia);

			fgets((*head)->kategoria,50,stdin);	//fgets sa da pouzit aj takto nie len zo suboru, stdin hovori ze sa bude nacitavat z konzole

			fgets((*head)->znacka,50,stdin);

			fgets((*head)->predajca,100,stdin);

			scanf("%d\n",&cislo);				//furt to iste
			(*head)->cena=cislo;

			scanf("%d\n",&cislo);
			(*head)->rok_vyroby=cislo;

			fgets((*head)->stav_vozidla,200,stdin);
			(*tail)=(*head);
			(*tail)->next=NULL;
		}
	}



	else {
		scanf("%d\n",&pozicia);						//nacitam cislo pozicie, sem sa funkcia tiez dostane len ak uz boli zoznamy vytvorene

		if(pozicia>0){

			(*new)=(BAZAR *)malloc(sizeof(BAZAR));		//alokujem si new zoznam

			if(pozicia==1){
				//pokial chce user dat zoznam na prve miesto
				fgets((*new)->kategoria,50,stdin);	//fgets sa da pouzit aj takto nie len zo suboru, stdin hovori ze sa bude nacitavat z konzole

				fgets((*new)->znacka,50,stdin);

				fgets((*new)->predajca,100,stdin);

				scanf("%d\n",&cislo);				//furt to iste
				(*new)->cena=cislo;

				scanf("%d\n",&cislo);
				(*new)->rok_vyroby=cislo;

				fgets((*new)->stav_vozidla,200,stdin);

				(*new)->next=(*head);		//new zaciatok zoznamu ukazuje na stary head
				(*head)=(*new);			//head som dal na new zaciatok zoznamov



			}

			else if(pozicia>(*list_amount)+1){
				//ak je pozicia posledne miesto alebo ktora neexistuje tak sa uklada na koniec zoznamov
				fgets((*new)->kategoria,50,stdin);

				fgets((*new)->znacka,50,stdin);

				fgets((*new)->predajca,100,stdin);

				scanf("%d\n",&cislo);
				(*new)->cena=cislo;

				scanf("%d\n",&cislo);
				(*new)->rok_vyroby=cislo;

				fgets((*new)->stav_vozidla,200,stdin);

				(*new)->next=NULL;			//vsetko to iste len pointer noveho ukazuje na NULL a stary tail ukazuje na new
				(*tail)->next=(*new);
				(*tail)=(*new);				//new zoznam je tiez new tail lebo je koniec zoznamov
				(*tail)->next=NULL;

			}

			else{
				(*current)=(*head);						// ak je pozicia niekde uprostred zaznamov
				for(actual_position=1;actual_position<=pozicia-2;actual_position++){
					(*current)=(*current)->next;			//forovym cyklom sa dostanem na poziciu na ktoru potrebujem, mam pomocnu ktora mi pocita na akej pozicii som
				}

				fgets((*new)->kategoria,50,stdin);

				fgets((*new)->znacka,50,stdin);

				fgets((*new)->predajca,100,stdin);

				scanf("%d\n",&cislo);
				(*new)->cena=cislo;

				scanf("%d\n",&cislo);
				(*new)->rok_vyroby=cislo;

				fgets((*new)->stav_vozidla,200,stdin);

				(*new)->next=(*current)->next;		//zase to iste len pointer noveho ukazuje na zoznam na ktory ukazoval current
				(*current)->next=(*new);				//pointer currentu ukazuje na new zoznam ktory ukazuje na zoznam na ktory predtym ukazoval current

			}


		}

	}

}

void hladaj(BAZAR **head,BAZAR **current, BAZAR **tail,int *n_fun_done,int *list_amount){
	int zadana_cena,counter=1;

	if((*list_amount)>0){                  //stale to iste ide len ak uz zoznamy su

		scanf("%d",&zadana_cena);						//nacitam cenu

		(*current)=(*head);

		while((*current) != NULL){
			if((*current)->cena<=zadana_cena){
				//ak zoznam vyhovuje poziadavkam tak ho vypisem
				printf("%d.\n",counter);
				printf("kategoria: %s",(*current)->kategoria);
				printf("znacka: %s",(*current)->znacka);
				printf("predajca: %s",(*current)->predajca);
				printf("cena: %d\n",(*current)->cena);
				printf("rok_vyroby: %d\n",(*current)->rok_vyroby);
				printf("stav_vozidla: %s",(*current)->stav_vozidla);
				counter++;
				(*current)=(*current)->next;

			} else {
				(*current)=(*current)->next;			//ak nevyhovuje prepnem sa na next zoznam
			}


		}
		if(counter==1) {
			printf("V ponuke su len auta s vyssou cenou\n");	//pomocna counter ktora mi povie ci nejaky zoznam vyhovoval poziadavkam ak nie vypisem hlasku ze v ponuke su len drahsie auta
		}
		else {
			counter=1;				
		}


	}


}

void vymaz(BAZAR **head,BAZAR **current, BAZAR **tail,int *n_fun_done, int *list_amount){
	char hladam[50];
	int cislo_zaznamu=1,amount_vymazanych=0,i,vymazane=0,found;
	char low_source[50];
	char low_find[50];
	BAZAR *prev;

	scanf("%s",hladam);				//nacitam string

	if((*list_amount)>0){          //zase to iste

		(*current)=(*head);					//current je head
		prev=(*head)->next;			//pomocnu ktora ukazuje na predosli zoznam som si nastavil na druhy zoznam



		for(i=0;i<(*list_amount);i++){

			strcpy(low_source,(*current)->znacka);
			strcpy((low_find),hladam);
			strlwr(low_source);
			strlwr(low_find);

			if(strstr(low_source,low_find) != NULL){
				found = 1;
			} else { 
				found = 0;
			}


			if(found == 1){
				//ak vymazavam prvy zoznam v poradi
				if(cislo_zaznamu==1){
					(*head)=(*head)->next;						//zmenim head na zoznam po starom heade
					free(*current);										//stary head vymazem
					(*current)=(*head);									//prepnem current na new head
					cislo_zaznamu++;									//counter
				}

				else if(cislo_zaznamu==2){                        //ak to su random pozicie niekde uprostred tento if je len ak je to druhy zoznam v poradi pretoze musim prenastavit pomocnu ktora ukazuje na zoznam pred
					(*head)->next=(*current)->next;		//head ukazuje na zoznam po tom na ktorom je current a teda na 3. zoznam
					free(*current);							//vymazem current
					(*current)=(*head)->next;				//current nastavim na druhy zoznam
					prev=(*head);							//prev nastavim na head ktory je pred currentom
					vymazane=1;								//pomocna
				}


				else { 
					if(cislo_zaznamu==(*list_amount)){
						(*tail)=prev;								//ak vymazavam posledny zoznam v poradi nastavim tail na zoznam pred starym koncom
						free(*current);								//stary koniec vymazem
						prev->next=NULL;							//a nastavim ho na null
					}
					else {
						prev->next=(*current)->next;		//tato cast ide ak to nieje 2. zoznam a je to to iste len neprenastavujem prev na head, pretoze od zaciatku prev ukazuje na 2. zoznam
						free(*current);
						(*current)=prev->next;
						cislo_zaznamu++;
						vymazane=1;
					}
				} 
				amount_vymazanych++;						//counter vymazanych zoznamov
			}

			else {                                 //ak zoznam nevyhovuje poziadavkam len sa prepnem na next zoznam
				cislo_zaznamu++;
				(*current)=(*current)->next;
			}

			if((cislo_zaznamu>3) && (cislo_zaznamu<=(*list_amount)) && (vymazane==0)){
				prev=prev->next;					//ak uz sme na 4. zozname tak posuniem prev na next a teda 3. ...
			}

			vymazane=0;
		}

	}
	(*list_amount)-=amount_vymazanych;				//amount zoznamov - amount vymazanych aby som vedel kolko je aktualne zoznamov
	printf("Vymazalo sa %d zaznamov\n",amount_vymazanych);
}

void aktualizuj(BAZAR **head,BAZAR **current, BAZAR **tail,int *n_fun_done, int *list_amount){

	int cena,i=1,updated=0,j=0,found=0;
	char hladam[50];
	char low_source[50];
	char low_find[50];
	BAZAR *new;

	if((*list_amount)>0){                           //to iste

		scanf("\n");
		fgets(hladam,50,stdin);						//nacitam cenu a znacku
		scanf("%d\n",&cena);

		new=(BAZAR *)malloc(sizeof(BAZAR));		//alkoujem novu pomocnu kam user nacita data

		fgets(new->kategoria,50,stdin);
		fgets(new->znacka,50,stdin);
		fgets(new->predajca,100,stdin);
		scanf("%d\n",&(new->cena));
		scanf("%d\n",&(new->rok_vyroby));
		fgets(new->stav_vozidla,200,stdin);

		(*current)=(*head);										//current nastavim na head


		for(i=0;i<(*list_amount);i++){

			strcpy(low_source,(*current)->znacka);
			strcpy((low_find),hladam);
			strlwr(low_source);
			strlwr(low_find);

			if(strstr(low_source,low_find) != NULL){
				found = 1;
			} else { 
				found = 0;
			}





			if(found==0){            
				if(cena==(*current)->cena){    


					strcpy((*current)->kategoria,new->kategoria);
					strcpy((*current)->znacka,new->znacka);
					strcpy((*current)->predajca,new->predajca);
					(*current)->cena=new->cena;
					(*current)->rok_vyroby=new->rok_vyroby;
					strcpy((*current)->stav_vozidla,new->stav_vozidla);
					updated++;									//counter
				}
			}
			(*current)=(*current)->next;		//prepnem sa na next zoznam
		}
		printf("Aktualizovalo sa %d zaznamov\n",updated);
		free(new); //uvolnim pomocny zoznam z pamate



	}

}


void main(){
	char input;
	FILE *subor;
	int zaznam=0,amount=0,n_done=0;
	BAZAR *head,*current,*tail,*new;

	while(1){
		input=getchar();	//nekonecny cyklus ktory nacitava znaky

		switch(input){      //znaky porovnavam switchom, podla toho program vie aku funkciu ma zavolat

		case'n':  { nacitaj(&subor,&amount,&head,&current,&tail,&n_done);
			break;
				  }

		case'v':  { vypis(&head,&current,&tail,&n_done,&amount);
			break;
				  }

		case'p':  { pridaj(&head,&current,&tail,&new,&amount,&n_done);
			amount+=1; break;
				  }

		case'h':  { hladaj(&head,&current,&tail,&n_done,&amount);
			break;
				  }

		case'z':  { vymaz(&head,&current,&tail,&n_done,&amount);
			break;
				  }

		case'a':  { aktualizuj(&head,&current,&tail,&n_done,&amount);
			break;
				  } 

		case'k':  { exit(0);
				  }
		default: break;
		}


	}
}





