#include "genetique.h"

using namespace std;
int main(){
    srand(time(0));
    deque<int> genotype;// vecteur qui a comme valeur le codage binaire d'un solution (population initiale) 
    deque<float> solution_candidate ;// vecteur des solutions ( individus )
    deque<float> fitnes; // vecteur qui contient la valeur du fitness cost de chaque individue
    deque<float> ps ;// vecteur qui contient la probabilité de silèctionner chaque individue
    deque<float> selection_parent;// vecteur qui contient les parents qui ont été selectionner par roue de loterie
    deque<float> decendant ; // vecteur qui contient les enfant des parents  selectioner pour le croisement
    float pc = 0.95 ; //probabilité de croisement
    float pm = 0.0005 ; //probabilié de mutation
    int nbits = 10 ;  // le nombre de bits pour coder une solution
    int t_max = 500 ; // nombre maximum de generation
    int t = 0 ;
    // l'ensemble de solution initiale en part avec 4 solution 
    for(int i(0);i<100;i++)
    solution_candidate.push_back((float)rand()/RAND_MAX);

   do{ 
   fitness_fonction(solution_candidate , fitnes) ; // calcul de la fitness cost de chaque individue
   probabilite_selectionnement_Naturelle(fitnes , ps ) ; // calcule de la probabilité de selectionnement de chaque individue

   ofstream f("./testGA.txt");
   for(int i = 0; i < solution_candidate.size(); i++){
     f  <<  solution_candidate[i] <<" \t "<<  fitnes[i]  <<  endl;
   }
   system("gnuplot fichier.gnu"); // tracé gnuplot dans un fichier jpeg
   system("eog ./testGA.jpeg"); // Affichage du fichier jpeg par l'utilitaire eog (Eye of Gnome)


   selection_parent.clear();
   // le selectionnement naturelle des parents par roue de loterie pour le coisement 
   selectionnement_Naturelle(solution_candidate , ps, selection_parent);
   decendant.clear();
   // parent a croiser (reproduction croisement)

   croisement(selection_parent ,pc ,decendant,nbits, pm);
   /* on va comparer le fitness_cost du parent et leurs enfants
      si la fitness_cost d'enfant est mieux que leurs parent on va travailler avec 
      la generation enfant pour le croisement   */
   mielleur_individue(solution_candidate,fitnes,decendant);
   // tracage des resultats
   
   solution_candidate.clear();
   solution_candidate= decendant ;
   fitnes.clear(); ps.clear();
   t++;
   }while(t<t_max );
      
   return 0;
}

