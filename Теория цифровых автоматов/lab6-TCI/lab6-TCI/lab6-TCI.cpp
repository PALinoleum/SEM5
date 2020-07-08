#include <iostream>
#include <vector>
using namespace std;


class Term{
public:
    bool skleen = false;
    vector<int> elements;
    vector<int> func;
    void print(){
        for (int i = 0; i < elements.size(); ++i) {
            if(elements.at(i)==-1){
                printf("- ");
            }else {
                printf("%i ", elements.at(i));
            }
        }

        //printf("(");
        for (int i = 0; i < func.size(); ++i) {
            //if(func.at(i)==1) {
                //printf("%i ", i + 1);
                printf("%i ", func.at(i));
            //}
        }
        //printf(")");

        printf("%s",skleen?"+":"");
    }
};

class Level{
public:
    int id;
    vector<Term> ONEterms;
};

vector<Term> NULLterms;

bool term_compare(Term a, Term b){
    for (int i = 0; i < a.elements.size(); ++i) {
        if(!((a.elements.at(i)==b.elements.at(i))||(a.elements.at(i)==-1))){
            return false;
        }
    }
    return true;
}

bool classes_compare(Term a, Term b){
    for (int i = 0; i < a.func.size(); ++i) {
        if(a.func.at(i)==b.func.at(i)){
            return true;
        }
    }
    return false;
}

bool trueSkleika(Term a, vector<Term>* NULL_terms){
    for (int i = 0; i < NULL_terms->size(); ++i) {
        if(term_compare(a,NULL_terms->at(i)) && classes_compare(a,NULL_terms->at(i))){
            return false;
        }
    }
    return true;
}

int findTerm(Term a, vector<Term>* terms){
    int g=0;
    for (int i = 0; i < terms->size(); ++i) {
        int k=0;
        for (int j = 0; j < a.elements.size(); ++j) {
            if(a.elements.at(j)==terms->at(i).elements.at(j)){
                k++;
            }
        }
        if(k==a.elements.size()){
            g++;
        }
    }
    if(g==2){
        return true;
    }
    return false;
}

int main() {
    int m1,n1,n_f1;
    int m0,n0,n_f0;
    int a;
    vector<Level> levels;
    printf("Input ones matr:\n");
	scanf_s("%i&i%i", &m1, &n1, &n_f1);
    levels.push_back(Level());

    for (int i = 0; i < m1; ++i) {

        Term* new_term = new Term();
        for (int j = 0; j < n1; ++j) {
            scanf_s("%i", &a);
            new_term->elements.push_back(a);
        }

        for (int j = 0; j < n_f1; ++j) {
            scanf_s("%i", &a);
            new_term->func.push_back(a);
        }
        levels.at(0).ONEterms.push_back(*new_term);
    }

    printf("Input null matr:\n");
    scanf_s("%i %i %i", &m0, &n0, &n_f0);

    for (int i = 0; i < m0; ++i) {
        Term* new_term = new Term();
        for (int j = 0; j < n0; ++j) {
            scanf_s("%i",&a);
            new_term->elements.push_back(a);
        }

        for (int j = 0; j < n_f0; ++j) {
            scanf_s("%i",&a);
            new_term->func.push_back(a);
        }
        NULLterms.push_back(*new_term);
    }

    for (int i = 1; i<n0; ++i) {
        puts("\n");

        levels.push_back(Level());
        for (int j = 0; j < levels.at(i-1).ONEterms.size(); ++j) {
            for (int k = 0; k < n0; ++k) {
                if(levels.at(i-1).ONEterms.at(j).elements.at(k)!=-1) {


                    Term *new_skleika = new Term();
                    *new_skleika = levels.at(i - 1).ONEterms.at(j);
                    new_skleika->elements.at(k) = -1;
                    new_skleika->skleen=false;

                    if(trueSkleika(*new_skleika, &NULLterms)){
                        levels.at(i-1).ONEterms.at(j).skleen = true;//new_skleika->skleen = true;
                        levels.at(i).ONEterms.push_back(*new_skleika);
                        //levels.at(i-1).ONEterms.at(j).print();printf("\n");//new_skleika->print();
                    }else{
                        //new_skleika->print();puts("");

                        //levels.at(i-1).ONEterms.at(j).print();printf("   ->   ");new_skleika->print();printf("\n");//new_skleika->print();
                        //trueSkleika(*new_skleika, &NULLterms);

                        //printf("-\n");
                    }
                    levels.at(i-1).ONEterms.at(j).print();printf("   ->   ");new_skleika->print();printf("\n");//new_skleika->print();

                }
            }
        }

        if(levels.at(i).ONEterms.size()==0){
            printf("-- EMPTY LEVEL --\n");
        }else {

        }
    }

    for (int i = 0; i<n0; ++i) {
        for (int j = 0; j < levels.at(i).ONEterms.size(); ++j) {
            if (!levels.at(i).ONEterms.at(j).skleen) {
                levels.at(i).ONEterms.at(j).print();
                printf("\n");
            }
        }
    }

    return 0;
}