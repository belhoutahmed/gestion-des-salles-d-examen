#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//definer un local
struct local{
    int Id;
    char Nom[20];
    int Nombre_max_places;
    int etat;
};
//Lister les locaux
void Lister_Locaux(char Nom_File[20]){
     FILE *Locaux_File;
    Locaux_File = fopen(Nom_File, "r");
    char line[1000];
    if (Locaux_File == NULL) {
        printf("\033[31m"); // définir la couleur en rouge
        printf("impossible d'ouvrir le fichier.\n");
        printf("\033[0m"); // réinitialiser la couleur par défaut
    }
    else{
    char *token;
    int field;
     printf("\033[34m"); // définir la couleur en bleu
     printf("    La liste des Locaux :\n");
     printf("\033[0m"); // réinitialiser la couleur par défaut
        printf("     ------------------------------------------------------------------------\n");
        printf("     |   Id   |        Nom        |   Nombre maximal de places   |   état   |\n");
        printf("     ------------------------------------------------------------------------\n");
    while (fgets(line, 1000, Locaux_File) != NULL) { // reading the file line by line

        field=0;
        token = strtok(line, "\t");  // get the id
    while (token != NULL) {
        if(field==0)  printf("     |%*.*s",8,(int)strlen(token), token);
        if(field==1)  printf("|%*.*s",19,(int)strlen(token), token);
        if(field==2) printf("|%*.*s",30,(int)strlen(token), token);
        if(field==3) printf("|%*.*s",10,(int)strlen(token), token);
        field=field+1;
        token = strtok(NULL, "\t");  // get the next token

    }
     printf("     ------------------------------------------------------------------------\n");
    }
    }

    fclose(Locaux_File); // closing the file

}
//Ajouter un local
void Ajouter_Local(char Nom_File[20],struct local *l){
    FILE *Locaux_File;
    Locaux_File = fopen(Nom_File, "a");
    char line[1000]="";
    char str[20];
    if (Locaux_File == NULL) {
        printf("\033[31m"); // définir la couleur en rouge
        printf("impossible d'ouvrir le fichier.\n");
        printf("\033[0m"); // réinitialiser la couleur par défaut
    }
    else{
    sprintf(str, "%d", l->Id);
    strcat(line,str);
    strcat(line,"\t");
    strcat(line,l->Nom);
    strcat(line,"\t");
    sprintf(str, "%d", l->Nombre_max_places);
    strcat(line,str);
    strcat(line,"\t");
    sprintf(str, "%d", l->etat);
    strcat(line,str);
    strcat(line,"\n");
    fprintf(Locaux_File, line);
    printf("\033[32m"); // définir la couleur en vert
    printf("  Ce local a été ajouté avec succès.\n");
    printf("\033[0m"); // réinitialiser la couleur par défaut
    }
    fclose(Locaux_File);
}
//Supprimer un local
void Supprimer_Local(char Nom_File[20],int id){
    FILE *Locaux_File;
    FILE *temp;

    Locaux_File = fopen(Nom_File, "r");
    char line[1000]="";
    char l[1000]="";
    char str[20];
    if (Locaux_File == NULL) {
        printf("\033[31m"); // définir la couleur en rouge
        printf("impossible d'ouvrir le fichier.\n");
        printf("\033[0m"); // réinitialiser la couleur par défaut
    }
    else{
    char *token;
    temp = fopen("temp.txt", "w");
    bool found=false;
   while (fgets(line, 1000, Locaux_File) != NULL) { // reading the file line by line
        strcpy(l,line);
        token = strtok(line, "\t");
        if(atoi(token)!=id){
             fprintf(temp,l);
        }
        else {
        found=true;
        }
        rename("temp.txt", Nom_File);// remove the original file
// get the id




}

fclose(Locaux_File);
fclose(temp);
if(found==true){
printf("\033[32m"); // définir la couleur en vert
    printf("  Ce local a été supprimé avec succès.\n");
    printf("\033[0m"); // réinitialiser la couleur par défaut
}
else{
printf("\033[31m"); // définir la couleur en rouge
     printf("    Veuillez écrire un ID valide.\n");
     printf("\033[0m"); // réinitialiser la couleur par défaut
}
}
}
//Modifier un local
void Modifier_Local(char Nom_File[20],int id){
    FILE *Locaux_File;
    FILE *temp;
    char nom[20];
    int max_places;
    int etat;

    Locaux_File = fopen(Nom_File, "r");
    char line[1000]="";
    char l[1000]="";
    char line_to_write[1000]="";
    char str[20];
    if (Locaux_File == NULL) {
        printf("\033[31m"); // définir la couleur en rouge
        printf("impossible d'ouvrir le fichier.\n");
        printf("\033[0m"); // réinitialiser la couleur par défaut
    }
    else{
    char *token;
    temp = fopen("temp.txt", "w");
    bool found=false;
   while (fgets(line, 1000, Locaux_File) != NULL) { // reading the file line by line
        strcpy(l,line);
        token = strtok(line, "\t");
        if(atoi(token)!=id){
             fprintf(temp,l);
        }
        else {
        found=true;

          printf("  Veuillez entrer le nouveau nom du local: ");
          scanf(" %s", &nom);
          printf("  Veuillez entrer Le nouveau nombre maximal de places associées à ce local: ");
          scanf(" %d", &max_places);
          printf("  Veuillez entrer la nouvelle etat du local: ");
          scanf(" %d", &etat);
          sprintf(str, "%d", id);
    strcat(line_to_write,str);
    strcat(line_to_write,"\t");
    strcat(line_to_write,nom);
    strcat(line_to_write,"\t");
    sprintf(str, "%d", max_places);
    strcat(line_to_write,str);
    strcat(line_to_write,"\t");
    sprintf(str, "%d", etat);
    strcat(line_to_write,str);
    strcat(line_to_write,"\n");
    fprintf(temp, line_to_write);
        }
        rename("temp.txt", Nom_File);// remove the original file
// get the id




}

fclose(Locaux_File);
fclose(temp);
if(found==true){
printf("\033[32m"); // définir la couleur en vert
    printf("  Ce local a été modifié avec succès.\n");
    printf("\033[0m"); // réinitialiser la couleur par défaut
}
else{
printf("\033[31m"); // définir la couleur en rouge
     printf("    Veuillez écrire un ID valide.\n");
     printf("\033[0m"); // réinitialiser la couleur par défaut
}
}
}
bool is_id_exists(char Nom_File_locaux[20],int id){
FILE *Locaux_File;
Locaux_File = fopen(Nom_File_locaux, "r");
 bool found=false;
 char line[1000]="";
    char l[1000]="";
    if (Locaux_File == NULL) {
        printf("\033[31m"); // définir la couleur en rouge
        printf("impossible d'ouvrir le fichier.\n");
        printf("\033[0m"); // réinitialiser la couleur par défaut
    }
    else{
    char *token;
   while (fgets(line, 1000, Locaux_File) != NULL) { // reading the file line by line
        strcpy(l,line);
        token = strtok(line, "\t");
        if(atoi(token)!=id){

        }
        else {
        found=true;
        }

}
fclose(Locaux_File);
}
return found;
}


void Affecter_emaplacement(char Nom_File_locaux[20],char Nom_File_eleves[20],char Nom_File_affectations[20]){
FILE *Locaux_File;
FILE *Eleves_File;
FILE *Affectation_File;
int array_locaux[30];
    int id_local;
    int s=0;
    int pourcentage;
    Locaux_File = fopen(Nom_File_locaux, "r");
 Eleves_File = fopen("eleves.txt", "r");
    Locaux_File = fopen(Nom_File_affectations, "w");
    bool stop=false;
    printf("\033[34m"); // définir la couleur en bleu
    printf("  Veuillez choisir (sélectionner) les locaux à exploiter: \n");
     printf("\033[0m"); // réinitialiser la couleur par défaut
    while(stop==false){
     printf("  Veuillez entrer l'id du local a exploiter, sinon cliquez sur 0 : ");
          scanf(" %d", &id_local);
          if(id_local==0){
          stop=true;
          }
          else{
          if(is_id_exists("locaux.txt",id_local)==false){
          printf("\033[31m"); // définir la couleur en rouge
          printf("    Veuillez écrire un ID valide.\n");
          printf("\033[0m"); // réinitialiser la couleur par défaut
          }
          else{
          array_locaux[s]=id_local;
          s=s+1;
          }
          }

    }
     printf("\033[34m"); // définir la couleur en bleu
    printf("  Veuillez Affecter un pourcentage de remplissage des locaux de 0 a 100 : ");
    scanf("%d", &pourcentage);
     printf("\033[0m"); // réinitialiser la couleur par défaut
     char line[1000]="";
    char l[1000]="";
    char line_to_write[1000]="";
    char str[20];
    if (Eleves_File == NULL) {
        printf("\033[31m"); // définir la couleur en rouge
        printf("impossible d'ouvrir le fichier.\n");
        printf("\033[0m"); // réinitialiser la couleur par défaut
    }
    else{
    char *token;
   while (fgets(line, 1000, Eleves_File) != NULL) { // reading the file line by line
        strcpy(l,line);
        int randomNumber = rand() % s;
        strcat(l,"\t");
        strcat(l,array_locaux[randomNumber]);
        strcat(l,"id de local : ");
        strcat(l,"\t");
        strcat(l,array_locaux[randomNumber]);
        strcat(l,"\n");
        fprintf(Affectation_File, l);
        }
        }



fclose(Locaux_File);
fclose(Eleves_File);
fclose(Affectation_File);

}

int main() {
 struct local *lo;
  bool Stop=false;
  char choix,choix_L;;
  bool Stop_L;
  int id_local;
  struct local *l;
  while(Stop==false){
  printf("\033[34m"); // définir la couleur en bleu
  printf("  Veuillez appuyer sur la lettre entre crochet pour exécuter la tâche:\n");
  printf("\033[0m"); // réinitialiser la couleur par défaut
  printf("    1. Gestion des [L]ocaux\n");
  printf("    2. Affectation des [E]mplacements\n");
  printf("    3. [P]roduction des listes\n");
  printf("    4. [S]ortie\n");
  printf("  ");
  scanf(" %c", &choix);
    switch(choix) {
    case 'L':
         Stop_L=false;
         while(Stop_L==false){
         printf("\033[34m"); // définir la couleur en bleu
         printf("  Veuillez appuyer sur la lettre entre crochet pour exécuter la tâche:\n");
         printf("\033[0m"); // réinitialiser la couleur par défaut
         printf("    1. [L]ister les locaux\n");
         printf("    2. [A]jouter un local\n");
         printf("    3. [M]odifier un local\n");
         printf("    4. [S]upprimer un local\n");
         printf("    5. [R]etour au menu principal\n");
         printf("  ");
         scanf(" %c", &choix_L);
         switch(choix_L) {
         case 'L':
          Lister_Locaux("locaux.txt");
          break;
         case 'A':
          printf("  Veuillez entrer l'id du local: ");
          scanf(" %d", &l->Id);
          printf("  Veuillez entrer le nom du local: ");
          scanf(" %s", &l->Nom);
          printf("  Veuillez entrer Le nombre maximal de places associées à ce local: ");
          scanf(" %d", &l->Nombre_max_places);
          printf("  Veuillez entrer l'etat du local: ");
          scanf(" %d", &l->etat);
          Ajouter_Local("locaux.txt",l);
          break;
         case 'M':
         printf("  Veuillez entrer l'id du local: ");
          scanf(" %d",&id_local);
          Modifier_Local("locaux.txt",id_local);
          break;
         case 'S':
         printf("  Veuillez entrer l'id du local: ");
          scanf(" %d",&id_local);
          Supprimer_Local("locaux.txt",id_local);
          break;
         case 'R':
          Stop_L=true;
          break;
         default:
          printf("\033[31m"); // définir la couleur en rouge
          printf("    Veuillez écrire une lettre valide.\n");
          printf("\033[0m"); // réinitialiser la couleur par défaut
          break;
         }
         }
         break;

    case 'E':
        Affecter_emaplacement("locaux.txt","eleves.txt","affectations.txt");
        break;
    case 'P':
       printf("3\n");
        break;
    case 'S':
       printf("\033[32m"); // définir la couleur en vert
       printf("  Merci beaucoup au revoir.");
       printf("\033[0m"); // réinitialiser la couleur par défaut
       Stop=true;
        break;
    default:
     printf("\033[31m"); // définir la couleur en rouge
     printf("    Veuillez écrire une lettre valide.\n");
     printf("\033[0m"); // réinitialiser la couleur par défaut

     break;
}




  }
  return 0;
}
