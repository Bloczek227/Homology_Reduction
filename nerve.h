#ifndef NERVE_NERVE_H
#define NERVE_NERVE_H


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>

using namespace std;

void print_complex(vector<vector<int>>& complex){
    for(auto& simplex:complex) {
        for (auto v: simplex)
            cout << v << " ";
        cout<<endl;
    }
}


bool check_subset(vector<int>& v1,vector<int>& v2){
    int i=0,j=0;
    while(i<v1.size()&&j<v2.size()){
        if(v1[i]==v2[j]){
            i++;
            j++;
        }
        else if(v1[i]>v2[j])
            j++;
        else
            return false;
    }
    return i==v1.size();
}

bool check_delete(vector<vector<int>>& complex,vector<vector<int>>& dual,
                  unordered_map<int,int>& labels_reverse,unordered_map<int,int>& dual_labels_reverse, int i){
    int t=labels_reverse[dual[i][0]];
    for(auto x:complex[t]){
        int r=dual_labels_reverse[x];
        if(r==i)
            continue;
        if(check_subset(dual[i],dual[r]) && (dual[i].size()<dual[r].size() || i>r))
            return true;
    }
    return false;
}



//Przed wywołaniem funkcji:
//complex - abstrakcyjny kompleks S (z samymi topleksami)
//dual - nerw kompleksu S (niekoniecznie z samymi topleksami)
//labels_reverse[i] - indeks sympleksu o etykiecie i w wektorze complex  (labels_reverse[labels[i]]=i)
//dual_labels[i] - etykieta sympleksu dual[i]
//dual_labels_reverse[i] - indeks sympleksu o etykiecie i w wektorze dual  (dual_labels_reverse[dual_labels[i]]=i)

//Po wykonaniu funkcji:
//dual - nerw kompleksu S (z samymi topleksami)
//complex - nerw nerwu kompleksu S (niekoniecznie z samymi topleksami)
bool nerveRed(vector<vector<int>>& complex,vector<vector<int>>& dual, vector<int>& dual_labels,
              unordered_map<int,int>& labels_reverse,unordered_map<int,int>& dual_labels_reverse){
    unordered_set<int> to_delete;
    vector<int> to_delete_sorted;
    for(int i=0;i<dual.size();i++){
        if(check_delete(complex,dual,labels_reverse,dual_labels_reverse,i)) {
            to_delete.insert(i);
            to_delete_sorted.push_back(i);
        }
    }
    unordered_set<int> to_delete_labels;
    for(auto x:to_delete)
        to_delete_labels.insert(dual_labels[x]);

    for(auto x:to_delete)
        for(auto y:dual[x]){
            int d = labels_reverse[y];
            int i=0,j=0;
            while(j<complex[d].size()){
                if(to_delete_labels.find(complex[d][j])!=to_delete_labels.end()){
                    j++;
                }
                else{
                    complex[d][i]=complex[d][j];
                    i++;
                    j++;
                }
            }
            complex[d].resize(i);
        }

    int i=dual.size()-1,j=dual.size()-to_delete.size()-1,k=to_delete.size()-1;
    while(k>=0&&to_delete_sorted[k]>j)
        k--;
    while(k>=0){
        while(to_delete.find(i)!=to_delete.end())
            i--;
        dual[to_delete_sorted[k]]=dual[i];
        dual_labels_reverse[dual_labels[i]]=to_delete_sorted[k];
        dual_labels[to_delete_sorted[k]]=dual_labels[i];
        k--;
        i--;
    }
    dual.resize(j+1);
    dual_labels.resize(j+1);
    return !to_delete.empty();
}


//complex - abstrakcyjny kompleks symplicjalny - w sympleksach wierzchołki są posortowane rosnąco
void nerveRed(vector<vector<int>>& complex){
    vector<int> labels;
    unordered_map<int,int> labels_reverse;
    labels.reserve(complex.size());
    for(int i=0;i<complex.size();i++) {
        labels.push_back(i);
        labels_reverse[i]=i;
    }
    unordered_map<int,int> dual_labels_reverse;
    vector<vector<int>> dual;
    for(int i=0;i<complex.size();i++){
        for(auto v:complex[i]){
            if(dual_labels_reverse.find(v)!=dual_labels_reverse.end()){
                dual[dual_labels_reverse[v]].push_back(i);
            }
            else{
                dual_labels_reverse[v]=dual.size();
                dual.push_back({i});
            }
        }
    }
    vector<int> dual_labels(dual.size());

    for(auto& x:dual_labels_reverse)
        dual_labels[x.second]=x.first;


    bool cont=true;

    while(cont) {
        cont=nerveRed(complex, dual, dual_labels, labels_reverse, dual_labels_reverse);

        if(nerveRed(dual, complex, labels, dual_labels_reverse, labels_reverse))
            cont= true;
    }
}


#endif //NERVE_NERVE_H
