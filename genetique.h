#ifndef GENTIQUE_CONST
#define GENTIQUE_CONST
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <cmath>
void codage_binaire(float &,std::deque<int> & , int &);
void fitness_fonction(std::deque<float> &, std::deque<float> &);
void probabilite_selectionnement_Naturelle(std::deque<float> & , std::deque<float> &);
void selectionnement_Naturelle(std::deque<float> & ,std::deque<float> & , std::deque<float> &);
float phenotype(std::deque<int> &genotype,int &Nbits);
void croisement(std::deque<float> &selection_parent ,float &pc , std::deque<float>& decendant,int &Nbits, float &pm);
void cross1p(std::deque<float> &pair_parent,int &Nbits,float &pm,std::deque<float>& decendant);
std::deque<float> plus_grandf(std::deque<float> & , std::deque<float> & );
void mielleur_individue(std::deque<float> &solution_candidate,std::deque<float> & fitnes,std::deque<float>  &decendant);
bool homogenite(std::deque<float>  );

#endif


