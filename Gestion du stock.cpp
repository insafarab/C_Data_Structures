#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Fonctions de la gestion du produit 1 à l'aide des piles
typedef struct robe
{
char couleur[10];
int size;
int prix;  
robe *next;
}robe;

typedef struct collection 
{ 
robe *tete;
}collection;

collection* initialiser()
{
	collection* nouvelle=(collection*)malloc(sizeof(collection));
	nouvelle->tete=NULL;
	return nouvelle;
}

int vide(collection *c) 
{
 	if(c->tete==NULL)
 	return 0;//La collection est vide
 	else
 	return 1;//La collection n'est pas vide
}
 
collection *ajouter(collection *c,char r[],int s,int p)
{
	robe *nvRobe= (robe*)malloc(sizeof(robe));
	if(c==NULL || nvRobe==NULL)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		strcpy(nvRobe->couleur,r);
		nvRobe->size=s;
		nvRobe->prix=p;
		nvRobe->next=c->tete;
		c->tete=nvRobe;
	}
	return c;
}

collection *supprimer(collection *c)
{
	if(c==NULL)
	{
		exit(EXIT_FAILURE);
	}
	else if(vide(c)==0)
	{
		printf("La collection est vide.");
	}
	robe *temp=c->tete;
	c->tete=temp->next;
	free(temp);
	return c;
}

int taille(collection *c)
{
	int n=0;
	if(c==NULL)
	{
		exit(EXIT_FAILURE);
	}
	robe *temp=c->tete;
	while(temp!=NULL)
	{
		n++;
		temp=temp->next;
	}
	return n;
}

void afficher(collection *c) 
{
	robe *temp;
	int i;
	if(c==NULL)
	{
		exit(EXIT_FAILURE);
	}
	printf("     Nouvelles Robes      \n");
	for(i=1,temp=c->tete;temp!=NULL;temp=temp->next,i++){
		printf("%d)  %s\t %d\t %d DH\n",i,temp->couleur,temp->size,temp->prix);	
	}
	printf("     Anciennes Robes      \n");
}
//_________________________________________________________________________//

// Fonctions de la gestion du produit 2 à l'aide des files

typedef struct bague {
	char materiel[10];
	int prix;
	bague* next;
}bague;

typedef struct plaquette {
	bague *first; 
	bague *last;
}plaquette;

bague* newBague(char m[],int p){
	bague* temp = (bague*)malloc(sizeof(bague));
	strcpy(temp->materiel,m);
	temp->prix=p;
	temp->next = NULL;
	return temp;
}

void afficher(plaquette* P){
    bague* temp= P->first;
    int i=1;
    while(temp!=NULL){
        printf("%d) %s\t %d DH\n",i, temp->materiel,temp->prix);
        temp=temp->next;
        i++;
    }
}

plaquette* createPlaquette(){
	plaquette* P = (plaquette*)malloc(sizeof(plaquette));
	P->first = P->last = NULL;
	return P;
}

void ajouter(plaquette* P,char m[],int p){
	bague* New = newBague(m ,p);
	if (P->last == NULL) {
		P->first = P->last = New;
		return;
	}
	P->last->next= New;
	P->last=New;
}

void supprimer(plaquette* P){
	if (P->first==NULL)
		return;
	bague* temp = P->first;
	P->first = P->first->next;
	if (P->first==NULL)
		P->last= NULL;
	free(temp);
}

int taille(plaquette* P)
{
	int n=0;
	if(P==NULL)
	{
		exit(EXIT_FAILURE);
	}
	bague *temp=P->first;
	do
	{
		n++;
		temp=temp->next;
	}while(temp!=NULL);
	return n;
}


main(){
char c[10];
char m[10];
int produit,k,n,t,p,r;
printf("__________Programme de la gestion des produits___________\n");
printf("Veuillez choisir le produit que vous voulez gerer: \n");
printf("Une collection des robes :Tapez 1\n");
printf("Une plaquette des bagues :Tapez 2\n");
printf("Remarque: La gestion des robes se fait avec les piles alors que la gestion des bagues se fait avec les files.\n");
scanf("%d",&produit);

if(produit==1) // Gestion des robes avec les piles
{
	collection *maCollection;
    maCollection=initialiser();
	printf("*________Gestion d'une colletion des robes________*\n");
	printf("!Veuillez choisir l'operation a effectuer sur votre collection !\n");
	printf("Remplir la collection avec les robes : Tapez 1\n");
	printf("Supprimer la robe recente : Tapez 2\n");
	printf("Afficher la collection : Tapez 3\n");
	printf("Savoir la taille de votre collection : Tapez 4\n");
	printf("Sortir du programme : Tapez 0\n");
	
	do
	{
		printf("\nVeuillez choisir une operation : ");
		scanf("%d",&k);
	if(k==1)
	{
		int i;
		printf("Combien de robes contient votre collection : ");
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			printf("          Robe numero %d :\n",i);
			printf("Entrer la couleur : ");
			scanf("%s",c);
			printf("Entrer la taille : ");
			scanf("%d",&t);
			printf("Entrer le prix : ");
			scanf("%d",&p);
			maCollection=ajouter(maCollection,c,t,p);
		}
	}
	if(k==2)
	{
		maCollection=supprimer(maCollection);
		printf("La robe la plus recente a ete bien supprimee.\n");
	}
	if(k==3)
	{
		afficher(maCollection);
	}
	if(k==4)
	{
		printf("Votre collection contient %d Robes.\n",taille(maCollection));
	}
	else if(k!=1 && k!=2 && k!=3 && k!=4 && k!=0)
	{
		printf("Entez un choix valide !!\n");
	}
	}
	while(k!=0);
	printf("//Fin de la gestion//");
}

if(produit==2) // Gestion des bagues avec les files
{
	plaquette* maPlaquette = createPlaquette();
	printf("*________Gestion d'une Plaquette des bagues________*\n");
	printf("!Veuillez choisir l'operation a effectuer sur votre Plaquette !\n");
	printf("Remplir la plaquette avec les bagues : Tapez 1\n");
	printf("Supprimer la premiere bague : Tapez 2\n");
	printf("Afficher la plaquette : Tapez 3\n");
	printf("Savoir la taille de votre plaquette : Tapez 4\n");
	printf("Sortir du programme : Tapez 0\n");
	
	do
	{
		printf("\nVeuillez choisir une operation : ");
		scanf("%d",&k);
	if(k==1)
	{
		int i;
		printf("Combien de bagues contient votre plaquette : ");
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			printf("          Bague numero %d :\n",i);
			printf("Entrer le materiel : ");
			scanf("%s",m);
			printf("Entrer le prix : ");
			scanf("%d",&r);
			ajouter(maPlaquette,m,r);
		}
	}
	if(k==2)
	{
		supprimer(maPlaquette);
		printf("La premiere bague a ete bien supprimee.\n");
	}
	if(k==3)
	{
		afficher(maPlaquette);
	}
	if(k==4)
	{
		printf("Votre plaquette contient %d Bagues.\n",taille(maPlaquette));
	}
	else if(k!=1 && k!=2 && k!=3 && k!=4 && k!=0)
	{
		printf("Entez un choix valide !!\n");
	}
	}
	while(k!=0);
	printf("//Fin de la gestion//");
}

}
