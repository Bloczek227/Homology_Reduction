#include <iostream>
#include <vector>
#include <set>
#include <random>
#include "nerve.h"

using namespace std;

vector<vector<int>>random_complex(double p, int d, int n){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0,1);

    set<vector<int>> simplexes;
    set<vector<int>> toplexes;
    for(int i=0;i<n;i++){
        simplexes.insert({i});
        toplexes.insert({i});
    }
    for(int dim=1;dim<=d+1;dim++){
        set<vector<int>> new_simplexes;
        for(auto simplex:simplexes){
            for(int last=simplex[simplex.size()-1]+1;last<n;last++){
                vector<vector<int>> vs{simplex};
                vector<int> curr=simplex;
                curr.push_back(last);
                bool possible=true;
                for (int i=0;i<dim;i++){
                    vector<int> v;
                    for(int j=0;j<dim;j++){
                        if(i!=j)
                            v.push_back(simplex[j]);
                    }
                    v.push_back(last);
                    if(simplexes.find(v)==simplexes.end()){
                        possible=false;
                        break;
                    }
                    vs.push_back(v);
                }
                if(possible && dist(gen)<=p){
                    new_simplexes.insert(curr);
                    for(auto v:vs)
                        toplexes.erase(v);
                    toplexes.insert(curr);
                }
            }

        }
        simplexes=new_simplexes;
    }
    //for(auto simp:toplexes){for(auto x:simp) cout<<x<<" ";cout<<endl;}
    vector<vector<int>> ans;
    for(auto toplex:toplexes)
        ans.push_back(toplex);
    return ans;
}


void combs(vector<int>& simp,vector<int>& curr, int n, int i, set<vector<int>>& ans){
    if(i==n) {
        if(!curr.empty())
            ans.insert(curr);
        return;
    }
    combs(simp,curr,n,i+1,ans);
    curr.push_back(simp[i]);
    combs(simp,curr,n,i+1,ans);
    curr.pop_back();
}

void combs(vector<int>& simp,set<vector<int>>& ans){
    vector<int> curr;
    combs(simp,curr,simp.size(),0,ans);

}

void check_parameters(double p, int d, int n){

    auto v = random_complex(0.02,2,100);
    //print_complex(v);
    set<vector<int>> s_pre;
    for(auto simplex:v)
        combs(simplex,s_pre);
    cout<<"p = "<<p<<", d = "<<d<<", n = "<<n<<endl;
    cout<<"number of simplices before reduction: "<< s_pre.size() <<endl;
    nerveRed(v);
    //print_complex(v);
    set<vector<int>> s_post;
    for(auto simplex:v)
        combs(simplex,s_post);
    cout<<"number of simplices after reduction: "<< s_post.size() <<endl<<endl;
}

int main() {
    check_parameters(0.02,2,100);
    return 0;
}