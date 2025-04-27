// Online C compiler to run C program online

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>


// regarder dans le cas ou on remet les cartes dans le paquet et quand on les remet pas : c'est codé tout est ok
// 1 er cas : bienaymé tcébitchev
// 2ème cas : incertitude type avec méthode de monte-carlo pour évaluer la fiabilité 

//refaire le dénombrement : pas loin 




// analyser la stratégie de seuil et son resultat : ok 



//1-13 carreau  
//14-26 coeur
//27-39 pique
//40-52 trefle

//2:10 chiffres 1:as 11:valet 12:dame 13:roi

int denombrement(int cartes[53],int* score_joueur, int* score_croupier)
{
    int* compte_score = malloc (11*sizeof(int)) ;
    float nb_cartes = 0;
    float p_depass = 0.0;
    for (int i=1; i<=11; i+=1)
    {
        compte_score[i] = 0;
    }
   

    
    if(*score_joueur <= 10)  //sur de pas dépasser
    {

    for (int i=1; i<=52; i+=1)
    {
        if(cartes[i] > 0)
        {
        nb_cartes+=1.0;
        if((i-1)%13 == 0)
            compte_score[11]+=1;

        if((i-1)%13 >= 2 && (i-1)%13 <=10)
        {
            compte_score[(i-1)%13] +=1;
        }

        if( (i-1)%13 > 10 )
        {
            compte_score[10] +=1 ;
        }
        }
    
    return 1;
        
    }


    }

     if(*score_joueur > 10) //peut dépasser
    {

    for (int i=1; i<=52; i+=1)
    {
        if(cartes[i] > 0)
        {
        nb_cartes +=1.0;
        if((i-1)%13 == 0)
            compte_score[1]+=1;

        if((i-1)%13 >= 2 && (i-1)%13 <=10)
        {
            compte_score[(i-1)%13] +=1;
        }

        if( (i-1)%13 > 10 )
        {
            compte_score[10] +=1 ;
        }
        }
    }
    for(int i=21; i <= 11  ; i += 1)
    {
        p_depass += compte_score[i] / nb_cartes ;
    }

    if(p_depass >= 0.3 ) 
        return 0;
    }

   else
    {
        return 1;
    }

   

}





int heuristique1(int score_joueur) //s'arrêter après un score
{
    if(score_joueur <= 21)
        return 1;
    else
        return 0;
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
    
    if(hauteur <= 9 && hauteur >= 1)
		printf("%d ", hauteur+1);
    
    else if(hauteur == 10)
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


void tirage_carte(int cartes[53], int* score)
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
            
            cartes[num_carte] = 0;
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

int est_vide (int cartes[53])
{
    for(int i=0; i<53; i+=1)
    {
        if(cartes[i]==1)
        {
            return 0;
        }
    }

    return 1;
}


void tirage_carte_aux(int cartes[53], int* score) //tirage carte pour le cas ou on remet pas les cartes dans le paquet
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





int main() 
{
    
    srand(time(NULL));

    int cartes [53];
    int* score_joueur= malloc(sizeof(int));
    int* score_croupier=malloc(sizeof(int));
    int rep_user;
    int partie_en_cours;
    int joueur_en_cours;
    
    int nb_d=0;
    int nb_v=0;
    int nb_n=0;
    float nb_parties = 500000.0;
    int nb_dd=0; //défaiteses par dépassement
    int nb_ds=0; //défaites par score
    int nb_vd=0; //victoires par dépassement
    int nb_vs=0; //victoires par score

    for(int c=0; c<nb_parties; c++)    //inéalité de bienaymé tchébytchev pour trouver le bon nombre de tentatives/ cas ou on remet les cartes dans le paquet
    {
        *score_joueur=0;
        *score_croupier=0;
        cartes[0]=0;
        for (int i=1; i<53; i++)
        {
            cartes[i]=i;
        }
        
        partie_en_cours=1; // 1-> partie pas terminé 0-> partie terminé
        
        joueur_en_cours=1;

           
           tirage_carte(cartes, score_joueur); //tire les deux premiere carte
           tirage_carte(cartes, score_joueur); 
           
           tirage_carte(cartes, score_croupier); 
           
        

           while(joueur_en_cours == 1 && partie_en_cours ==1)
           {
			   //rep_user = strategie_optimale(*score_croupier, *score_joueur);
			   //rep_user = decision_aleatoire();
			   //rep_user = heuristique1(*score_joueur);
               rep_user = denombrement(cartes, score_joueur, score_croupier);
               if(rep_user == 1)
			   {
				tirage_carte(cartes, score_joueur);
				if((*score_joueur)>21)
                    partie_en_cours = 0;
               }
               
               else
                joueur_en_cours = 0;
           }
           
          
           while(*score_croupier < 17 && partie_en_cours == 1)
           {
               tirage_carte(cartes, score_croupier);
              
               if (*score_croupier > 21)
                    partie_en_cours = 0;
           }
           
           if(*score_croupier > 21 || ( *score_croupier < *score_joueur && *score_joueur <=21) )
           {
             nb_v+=1;
           }
           
           else if (*score_joueur > 21 || (*score_croupier > *score_joueur && *score_croupier <= 21) )
           {
             nb_d +=1;
           }
           
           else if (*score_joueur == *score_croupier)
           {
              nb_n +=1;
           }
    }    
    
    
    /*
    for (int i=1; i<53; i++)
        {
            cartes[i]=10000;
        }

    for(int c=0; c<nb_parties; c++)    //utiliser la méthode de monte-carlo pour calculer la bonne valeur 
    {
        *score_joueur=0;
        *score_croupier=0;
        
        partie_en_cours=1; // 1-> partie pas terminé 0-> partie terminé
        
        joueur_en_cours=1;

       
           tirage_carte_aux(cartes, score_joueur); //tire les deux premiere carte
           tirage_carte_aux(cartes, score_joueur); 
           
           tirage_carte_aux(cartes, score_croupier); 
           
        

           while(joueur_en_cours == 1 && partie_en_cours ==1)
           {
			   //rep_user = strategie_optimale(*score_croupier, *score_joueur);
			   //rep_user = decision_aleatoire();
			   rep_user = heuristique1(*score_joueur);
               //rep_user = denombrement(cartes, score_joueur, score_croupier);
               if(rep_user == 1)
			   {
				tirage_carte_aux(cartes, score_joueur);
				if((*score_joueur)>21)
                    partie_en_cours = 0;
               }
               
               else
                joueur_en_cours = 0;
           }
           
           
           
           while(*score_croupier < 17 && partie_en_cours == 1)
           {
               tirage_carte_aux(cartes, score_croupier);
              
               if (*score_croupier > 21)
                    partie_en_cours = 0;
           }
           
           

           if(*score_croupier > 21)
           {
             nb_v+=1;
             nb_vd +=1;
           }

           if(*score_croupier < *score_joueur && *score_joueur <=21)
           {
            nb_v += 1;
            nb_vs += 1;
           }
           
           else if (*score_joueur > 21 )
           {
             nb_d +=1;
             nb_dd += 1;
           }
           
           else if(*score_croupier > *score_joueur && *score_croupier <= 21)
           {
            nb_d +=1;
            nb_ds += 1;
           }

           else if (*score_joueur == *score_croupier)
           {
              nb_n +=1;
           }
    }

    */
    
   printf("Victoires : %f%, Nuls   : %f%, Défaites :%f% \n", nb_v/nb_parties*100, nb_n/nb_parties*100, nb_d/nb_parties*100);
   /*
   printf("Défaites par dépassement : %.2f%%, Défaites par score : %.2f%%\n", nb_dd * 100.0 / nb_d, nb_ds * 100.0 / nb_d);
   printf("Victoires par dépassement : %.2f%%, Victoires par score : %.2f%%\n", nb_vd * 100.0 / nb_v, nb_vs * 100.0 / nb_v); */
   return EXIT_SUCCESS;
}
