#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node* filsG;
    struct node* filsD;
}node;

typedef struct node* arbreB;

typedef struct nodefile {
    arbreB data;
    struct nodefile* next;
} nodefile;

typedef struct file {
    nodefile* head;
    nodefile* tail;
} file;

// Création d'un nouvel élément de l'arbre
arbreB cree_element(int val) {
    arbreB nv = malloc(sizeof(node));
    nv->data = val;
    nv->filsG = NULL;
    nv->filsD = NULL;
    return nv;
}

// Enfiler un noeud dans la file
void enfiller(file* f, arbreB a) {
    nodefile* nv = malloc(sizeof(nodefile));
    nv->data = a;
    nv->next = NULL;

    if (f->head == NULL) {
        f->head = f->tail = nv;
    } else {
        f->tail->next = nv;
        f->tail = nv;
    }
}

// Defiler un noeud de la file
arbreB defiler(file* f) {
    if (f->head == NULL) return NULL;
    nodefile* temp = f->head;
    f->head = f->head->next;
    arbreB a= temp->data;
    free(temp);
    return a;
}

// Insertion dans un ABR
arbreB insertion_abr(arbreB a, int val) {
    if (a == NULL)
        return cree_element(val);
    else if (val <= a->data)
        a->filsG = insertion_abr(a->filsG, val);
    else
        a->filsD = insertion_abr(a->filsD, val);
    return a;
}

// Parcours en largeur
void parcour_largeur(arbreB a) {
    if (a == NULL) return;
    file f = {NULL, NULL};
    enfiller(&f, a);

    while (f.head != NULL) {
        arbreB temp = defiler(&f);
        printf("%d ", temp->data);
        if (temp->filsG != NULL)
            enfiller(&f, temp->filsG);
        if (temp->filsD != NULL)
            enfiller(&f, temp->filsD);
    }
    printf("\n");
}

// Parcours prefixe
void prefixe(arbreB a) {
    if (a != NULL) {
        printf("%d ", a->data);
        prefixe(a->filsG);
        prefixe(a->filsD);
    }
}

// Parcours infixe
void infixe(arbreB a) {
    if (a != NULL) {
        infixe(a->filsG);
        printf("%d ", a->data);
        infixe(a->filsD);
    }
}

// Parcours suffixe
void suffixe(arbreB a) {
    if (a != NULL) {
        suffixe(a->filsG);
        suffixe(a->filsD);
        printf("%d ", a->data);
    }
}



// Recherche dans un ABR
int recherche_ABR(arbreB a, int val) {
    if (a == NULL) return 0;
    if (a->data == val) return 1;
    else if (val < a->data)
        return recherche_ABR(a->filsG, val);
    else
        return recherche_ABR(a->filsD, val);
}

// Trouver le minimum dans un sous-arbre
arbreB trouver_min(arbreB a) {
    while (a->filsG != NULL)
        a = a->filsG;
    return a;
}

// Suppression dans un ABR
arbreB supprimer_ABR(arbreB a, int val) {
    if (a == NULL) return a;
    if (val < a->data)
        a->filsG = supprimer_ABR(a->filsG, val);
    else if (val > a->data)
        a->filsD = supprimer_ABR(a->filsD, val);
    else {
        if (a->filsG == NULL && a->filsD == NULL) {
            free(a);
            return NULL;
        }
        else if (a->filsG == NULL) {
            arbreB temp = a->filsD;
            free(a);
            return temp;
        }
        else if (a->filsD == NULL) {
            arbreB temp = a->filsG;
            free(a);
            return temp;
        } else {
            arbreB temp = trouver_min(a->filsD);
            a->data = temp->data;
            a->filsD = supprimer_ABR(a->filsD, temp->data);
        }
    }
    return a;
}

// Fonction main pour tester
int main() {
arbreB a=NULL;
a=cree_element(150);
a=insertion_abr(a,15);
a=insertion_abr(a,12);   
a=insertion_abr(a,50); 
a=insertion_abr(a,26); 
a=insertion_abr(a,30); 
a=insertion_abr(a,0); 
a=insertion_abr(a,100);
printf("\t les parcours :") ;
printf("\t largeur :") ;
parcour_largeur(a);

printf("\t prefixe :") ;
prefixe(a);printf("\n") ; 

printf("\t infixe  :");
infixe(a);printf("\n") ;

printf("\t suffixe :") ;
suffixe(a);printf("\n") ;
int n;printf("donner une valeur a chercher dans l'arbre et suprimer");scanf("%d",&n);
int x=recherche_ABR(a,n);
if (x){printf("la valeur %d est dan l'arbre .",n);}
else{printf("la valeur %d n'existe pas dans l'arbre.",n);}
a=supprimer_ABR(a,n);
printf("\n\taffichage apres suppression .\n");
parcour_largeur(a);
    return 0;
}