/*


- processus stochastique pour avoir une évaluation fiable de la stratégie
- implémenter la stratégie de las vegas


*/





#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

//1-13 carreau  
//14-26 coeur
//27-39 pique
//40-52 trefle

//2:10 chiffres 1:as 11:valet 12:dame 13:roi


//rep_user : 0:reste 1:tire 2:split 4:doublé

int heuristique1(int score_joueur) //s'arrêter après un score
{
    if(score_joueur <= 11)
        return 1;
    else
        return 0;
}

 
 
 
 

int strategie_brute (int score, int cartes[53])
{
    int aug[12]; //de 1 à 11 le 0 est inutile
    for(int i=1 ;i<=11; i++)
        aug[i]=0;
    
    if(score<11)
    {
        for(int i=1; i<=52; i++) //on parcourt les cartes 
        {
            if(cartes[i] != 0) //verifie si elle est encore la
            {
                if((i-1)%13 == 10 || (i-1)%13 == 11 || (i-1)%13 == 12)
                {
                    aug[10]+=1;
                }
                
                else if( (i-1)%13==0 )
                    aug[11] += 1;
                    
                else
                    aug[(i-1)%13+1] += 1;
            }
                
        }
    }
    
    else
    {
        for(int i=1; i<=52; i++) //on parcourt les cartes 
        {
            if(cartes[i] != 0) //verifie si elle est encore la
            {
                if((i-1)%13 == 10 || (i-1)%13 == 11 || (i-1)%13 == 12)
                {
                    aug[10]+=1;
                }
                
                else if( (i-1)%13==0 )
                    aug[1] += 1;
                    
                else
                    aug[(i-1)%13+1] += 1;
            }
                
        }
    }
    
    int max_ind = 1;
    float card_univers=0.0; //le nombre de tirages possibles (en gros le nombre de cartes restantes)
    float card_depasse = 0.0; //le nombre de tirages qui fait depasser 21
    for(int i=1; i<=11; i++)
    {
        card_univers += aug[i];
        
        if(i+score>21)
        {
            card_depasse += aug[i];
        }
    }
    
    float proba_depasse = card_depasse/card_univers;
    
    if(proba_depasse >= 0.5)
        return 0;
    
    else
        return 1;
}








int strategie_optimale(int main_croupier,int main_joueur)
{
    int i=main_joueur;

    while(main_croupier==2)
    {
        if(i>=4 && i<=12)
            return 1;
        else
            return 0;
    }

    while(main_croupier==3)
    {
        if(i>=4 && i<=12)
            return 1;
        else
            return 0;
    }

    while(main_croupier==4){

        if(i>=4 && i<=11)
            return 1;


        else
            return 0;

    }

    while(main_croupier==5){

        if(i>=4 && i<=11)
            return 1;

        else
            return 0;
    }

    while(main_croupier==6){

        if(i>=4 && i<=11)
            return 1;

        else
            return 0;
    }

    while(main_croupier==7){

        if(i>=4 && i<=16)
            return 1;

        else
            return 0;
    }
    while(main_croupier==8)
    {
        if(i>=4 && i<=16)
            return 1;
        else
            return 0;
    }

    while(main_croupier==9){

        if(i>=4 && i<=16)
            return 1;

        else
            return 0;
    }

    while(main_croupier==10)
    {
        if(i>=4 && i<=16)
            return 1;
        else
            return 0;
    }

    while(main_croupier==11){
        if(i>=4 && i<=16)
            return 1;
        else
            return 0;
    }
    return EXIT_SUCCESS;
}




int decision_aleatoire()
{
    return rand()%2;
}




void affiche_carte (int numero)
{
    int hauteur = (numero-1) % 13;
    int couleur = (numero-1)/13;
    
    if(hauteur == 10)
		printf("Valet");
	
	else if(hauteur == 11)
		printf("Dame");
	
	else if(hauteur == 12)
		printf("Roi");
	
	else if(hauteur == 0)
		printf("As");
		
	if(couleur == 0)	
		printf(" de carreau. \n");
	
	else if(couleur == 1)	
		printf(" de coeur. \n");
	
	else if(couleur == 2)	
		printf(" de pique. \n");
		
	else if(couleur == 3)	
		printf(" de trefle. \n");			
}


void tirage_carte(int* cartes, int* score, int* nb_cartes, int m[10])
{
    int tire=0; //0 -> carte tjrs pas tiré 1-> carte tiré
    
    //srand(time(NULL));
    int num_carte= ceil(rand()%52 + 1);    

    while (!tire)
    {
        
        if(cartes[num_carte] == 0)
        {
            num_carte= rand()%52 + 1;
        }
        
        else
        {
            tire=1;
            m[*nb_cartes]=num_carte;
            nb_cartes += 1 ;
            cartes[num_carte] -= 1;
        }
    }
    
    if( (num_carte-1)%13 == 0)
    {
		if (*score + 11 > 21)
		{
			*score = *score +1;
		}
		
		else
		{
			*score += 11;
		}			
	}
	
	if( (num_carte-1)%13 >= 1 && (num_carte-1)%13 <= 9  )
    {
		*score += (num_carte-1)%13 + 1;
	}
	
	else
		*score += 10;
	
}


int calcul_mise( int* gains, int* is_playing) //calcule la mise à mettre en fonction des gains
{
    if (*gains>=20)
    {
        return 10;
    }
    else if(*gains >= 1)
    {
        return 1;
    }

    else
    {
        *is_playing =0;
        return 0;
    }
}

int doublet(int* gains, int* score_joueur, int* mise) //determine si on double ou pas
{
    if(*gains >= 20 && *gains > 2* (*mise)  && (*score_joueur==10 || *score_joueur==11))
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int deck_jouable(int* nb_cartes)
{
    int nb_c=0;
    for(int i=1; i<=52;i+=1)
    {
       nb_c += 1;
    }

    if(nb_c >=20)
        return 1;
    else
        return 0;
}

int main() 
{
    srand(time(NULL));

    int *is_playing= malloc(sizeof(int));
    
    *is_playing = 1;
    
    int* gains = malloc(sizeof(int));
    *gains=100;
    int* is_split = malloc(sizeof(int));
    int* is_double = malloc(sizeof(int));
    
    int* mise = malloc(sizeof(int));
    *mise = 0;
    int main_joueur[10];
    int main_croupier[6];
    int* nb_cartes_j = malloc(sizeof(int));
    int* nb_cartes_c= malloc(sizeof(int));
    
    int* score_joueur= malloc(sizeof(int));
    int* score_croupier=malloc(sizeof(int));
    
    int rep_user;
    int partie_en_cours;
    int joueur_en_cours;
    int* cartes = malloc(52*sizeof(int));
    for(int i=1; i<=52; i+=1)
    {
        cartes[i]=8;
    }
    
    int carte_croupier;


    int c=0;
    *mise = calcul_mise(gains, is_playing);
    while ( c<30 && is_playing && deck_jouable(cartes) == 0)    
    {
        
        
        is_double=0;
        is_split=0;
		*nb_cartes_j=0;
		*nb_cartes_c=0;
		for (int i=1; i<10; i++)
        {
			main_croupier[i]=0;
			main_joueur[i]=0;
		}
		
		carte_croupier=0;
        *score_joueur=0;
        *score_croupier=0;
        
        partie_en_cours=1; // 1-> partie pas terminé 0-> partie terminé
        
        joueur_en_cours=1; //1->joueur 0->croupier

           
           tirage_carte(cartes, score_joueur, nb_cartes_j,main_joueur); //tire les deux premiere carte
           tirage_carte(cartes, score_joueur, nb_cartes_j, main_joueur); 
           
           tirage_carte(cartes, score_croupier, nb_cartes_c, main_croupier);
           
           
           while(joueur_en_cours == 1 && partie_en_cours ==1)
           {
			   rep_user = strategie_optimale(*score_croupier, *score_joueur);
			   //rep_user = decision_aleatoire();
			   //rep_user = strategie_brute(*score_joueur, cartes);
			  //rep_user = heuristique1(*score_joueur);
               //rep_user=0;
               if(doublet(gains, score_joueur, mise) == 1)
               {
                *mise = *mise * 2;
               }

               if(rep_user == 1)
			   {
				tirage_carte(cartes, score_joueur, nb_cartes_j, main_joueur);
				if((*score_joueur)>21)
                    partie_en_cours = 0;
               }
               
               else
                joueur_en_cours = 0;
           }
           
           while(*score_croupier < 17 && partie_en_cours == 1)
           {
			   
               tirage_carte(cartes, score_croupier, nb_cartes_c, main_croupier);
               if (*score_croupier > 21)
                    partie_en_cours = 0;
           }
           
           if(*score_croupier > 21 || ( *score_croupier < *score_joueur && *score_joueur <=21) )
           {
                 *gains += *mise ;
                 *mise = calcul_mise(gains, is_playing);
                  c+=1;
           }
           
           else if (*score_joueur > 21 || (*score_croupier > *score_joueur && *score_croupier <= 21) )
           {
             *gains -= *mise ;
             *mise = calcul_mise(gains, is_playing);
             c+=1;
           }
           
           else if (*score_joueur == *score_croupier)
           {
              *mise = calcul_mise(gains, is_playing);
              c+=1;
           }
    }    
    
    
    printf("Resultat d'Ilian : Gains totaux: %d", *gains);
   return EXIT_SUCCESS;
}

