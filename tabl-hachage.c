#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxsize 100 
// hachage fonction 

int hashing (char * tab){
    int i,hash=0;
    for(i=0; tab[i]!='\0'; i++){
        hash+=tab[i] ;
    }
    return hash % maxsize ;
}
//pour cree un tableau de hashage il faut d'abord cree le noeud qui va constituer ces cases 

typedef struct node {
    char* password  ;
    char* login;
    struct node* next ;
} node ;
                                                                                                  
// cree tableau 

node* tab[maxsize] ;


void enregistrer (char* login,char* pas){
    node* nv = malloc (sizeof (node));
    int x=hashing(login);
    nv->login = strdup(login);
    nv->password =strdup(pas);
    // insertion au debut de la list 
    nv->next = tab[x]  ;
    tab[x]=nv ;
    printf("Utilisateur enregistre avec succes \n");
}
// conexion 
void  connexion (node*tab[maxsize] ,char* login,char*password){
    int x=hashing(login);
    node*p=tab[x];
     while (p!=NULL){
            if(strcmp(p->login, login) == 0 && strcmp(p->password, password) == 0){
                printf("connexion reussie !\n");
                return;
            }
            p=p->next;  
    }
    printf("nom d'utilisatrur ou mot de pass invalide !!");
}
//affichage 
void afficher (node* tab[maxsize]){
    int booleen=0;
    for (int i=0;i<maxsize;i++){
        node* p =tab[i];
        while(p!=NULL){
            printf("\n\tVos informations :\n");
            printf("le nom : %s\n",p->login);
            printf("le mot de pass : %s\n",p->password);
            p=p->next;
            booleen=1; 
        }
    }
if(!booleen){
    printf("pas d'utilisateur stocker" );
}

}

int main (){
    for (int i = 0; i < maxsize; i++) {
        tab[i] = NULL;
    }
    
    int n=1;
    char nom[100];
    char password[100];


while (n<=3 && n>= 1){
        printf("1: ajouter un utilisateur\n2: connexion\n3: afficher les utilisateurs\n");
        printf(" \nveuillez choisir :\n");
        scanf("%d",&n);
        switch (n){
            case 1:
                printf("donner le nom :");
                scanf("%s",nom);
                printf("donner le mot de pass:");
                scanf("%s",password);
                enregistrer(nom,password);
                break;
            case 2:
                printf("donner le nom :");
                scanf("%s",nom);
                printf("donner le mot de pass:");
                scanf("%s",password);       
                connexion(tab,nom,password);
                break;
        
            case 3:
                afficher(tab);
                break;
            default:
                printf("Option invalide.\n");
                break;
         }
        }
   
        
    return 0;

}
