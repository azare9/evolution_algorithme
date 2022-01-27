#include "genetique.h"
using namespace std;
void codage_binaire(float &nombre,deque<int> &genotype , int &Nbits){
     deque<int> conteneur;
     
     int resultat(0);  
     int n = (nombre-0)*((pow(2,Nbits)-1)/(1-0)) ;
     do{
       resultat = n/2;
       conteneur.push_back(n%2);
       n = resultat;
     }while(n > 0);
     if(conteneur.size() != 1){
      for(int j=conteneur.size()-2 ; j>=0 ; j--) {
        conteneur.push_back(conteneur[j])  ; conteneur.erase(conteneur.begin()+j); 
      }
      while(conteneur.size()<Nbits){
        conteneur.push_front(0);
      }
     }
     else { while(conteneur.size()<Nbits){
     conteneur.push_front(0);
     }
     }
     // le codage binaire du n 
     genotype =  conteneur ;
}
void fitness_fonction(deque<float> &solution_candidate, deque<float> &fitness){
      for(int i(0) ; i< solution_candidate.size() ; i++){
      float tmp = (sin(solution_candidate[i] *10))*(sin(solution_candidate[i] *10))/(solution_candidate[i]+1);
      fitness.push_back(tmp);
      }    
}
void probabilite_selectionnement_Naturelle(deque<float> &fitnescost, deque<float> &probabilites){
      probabilites.resize(fitnescost.size());
      float tmp = 0 ;
      for(int i(0) ; i < fitnescost.size() ; i++){
        tmp+=fitnescost[i];
      }
      for(int j(0) ; j < fitnescost.size() ; j++){
        probabilites[j] = fitnescost[j]/tmp;
      }
}
void selectionnement_Naturelle(deque<float> & solution_candidate , deque<float> & ps, deque<float> & selection_parent){

     deque<float> tab_proba;
     float tmp(0);
     for(int i(0) ; i < ps.size() ; i++){
       tab_proba.push_back(ps[i] + tmp);
       tmp += ps[i] ;
     }    
     int i = 0 ;
     do{
       float tmp = (float)rand()/RAND_MAX;
       float tmp_1 = 0 ;
         for(int j(0) ; j < tab_proba.size() ; j++) 
           { 
             if(tmp > tmp_1 && tmp < tab_proba[j]) {   
             selection_parent.push_back(solution_candidate[j]); }
             tmp_1 = tab_proba[j] ;
         }         
     i++;
     }while(i < solution_candidate.size()); 
}
float phenotype(deque<int> &genotype,int &Nbits){
     int tmp=0,j=0;
     for(int i=genotype.size()-1;i>=0;i--){
       tmp+=genotype[j]*pow(2,i); j++;
     }
     return (0+tmp)*((1-0)/(pow(2,Nbits)-1));
}
void croisement(deque<float> &selection_parent ,float &pc , deque<float>& decendant,int &Nbits, float &pm){
     int i1,c(0);
     deque<float> pair_parent; // les parents qui ont la chance d'être selectionner pour le croisement
     for(int i(0) ; i < selection_parent.size() ; i++){
       if(pc >= (float)rand()/RAND_MAX){
         c++;
        if(c%2){   i1 = i; // un parent doit être rechercher
             pair_parent.push_back(selection_parent[i1]);   }
        else { pair_parent.push_back(selection_parent[i]); /* faire le croisement*/
           cross1p(pair_parent,Nbits,pm,decendant);
        }
       }
       else{decendant.push_back(selection_parent[i]); }
     }
    if(pair_parent.size() == 1) {decendant.push_back(pair_parent[0]); }
}
// fonction qui fait le croisement + la mutation
void cross1p(deque<float> &pair_parent,int &Nbits,float &pm,deque<float>& decendant){
     deque<int> parent_1;//premier parent 
     deque<int> parent_2 ; // desieme parent
       codage_binaire(pair_parent[0],parent_1, Nbits) ;       
       codage_binaire(pair_parent[1],parent_2, Nbits) ; 
       int p1 = 1+ rand()%Nbits;
       for(int i(p1) ; i< Nbits ; i++){ swap(parent_1[i] , parent_2[i]);}
         // mutation 
       for(int i(0) ; i < parent_1.size() ; i++){
         if(pm > (float)rand()/RAND_MAX ) {
          if(parent_1[i] == 0) parent_1[i] = 1 ;
          else parent_1[i] = 0 ;
         }
       }
       for(int i(0) ; i < parent_2.size() ; i++){
         if(pm > (float)rand()/RAND_MAX ) {
          if(parent_2[i] == 0) parent_2[i] = 1 ;
          else parent_2[i] = 0 ;
         }
       }
       // les enfants de la population selectionner pour le croisement
       decendant.push_back(phenotype(parent_1,Nbits));
       decendant.push_back(phenotype(parent_2,Nbits));   
       pair_parent.clear();
}

void mielleur_individue(deque<float> &solution_candidate,deque<float> & fitnes,deque<float>  &decendant){
     deque<float> fitnes_1;
     fitness_fonction(decendant, fitnes_1)  ;
     int indice_1 = max(fitnes.begin(),fitnes.end())-fitnes.begin();
     int indice_2 = min(fitnes_1.begin(),fitnes_1.end())-fitnes_1.begin();
     decendant[indice_2]=solution_candidate[indice_1];
     fitnes_1[indice_2] = fitnes[indice_1];
     fitness_fonction(decendant, fitnes)  ;
}


