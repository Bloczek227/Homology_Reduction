#include <iostream>
#include <vector>
#include <chrono>
#include "nerve.h"

using namespace std;

vector<bool> primes(int n)
{
    vector<bool> prime(n + 1, true);
    for (int p=2;p*p<=n;p++) {
        if (prime[p]) {
            for (int i=p*p;i<=n;i+=p)
                prime[i]=false;
        }
    }
    return prime;
}

int main() {
    vector<vector<int>> v({{1,3,7},{2,3,6},{2,4,6},{1,2},{1,5},{4,5},{2,4}});
    nerveRed(v);
    print_complex(v);
    cout<<endl<<endl;

    vector<vector<int>> v2({{1,2},{2,3},{2,4},{3,4,5},{4,5,6},{6,7},{7,8,9}});
    nerveRed(v2);
    print_complex(v2);
    cout<<endl<<endl;


    vector<vector<int>> v3;
    for(int i=1;i<8;i++){
        for(int j=1;j<=i;j++){
            v3.push_back({(i-1)*i/2+j,i*(i+1)/2+j,i*(i+1)/2+j+1});
        }
    }
    for(int i=1;i<8;i++){
        for(int j=1;j<=i;j++){
            v3.push_back({i*(i+1)/2+j,i*(i+1)/2+j+1,(i+1)*(i+2)/2+j+1});
        }
    }
    chrono::steady_clock::time_point begin3 = chrono::steady_clock::now();
    nerveRed(v3);
    chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
    print_complex(v3);
    cout <<endl<< "Time difference v3 = " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count()/1000. << "[ms]" << endl <<endl <<endl;


    vector<vector<int>> v3hole;
    for(int i=1;i<8;i++){
        for(int j=1;j<=i;j++){
            if(i==5&&j==3)
                continue;
            v3hole.push_back({(i-1)*i/2+j,i*(i+1)/2+j,i*(i+1)/2+j+1});
        }
    }
    for(int i=1;i<8;i++){
        for(int j=1;j<=i;j++){
            v3hole.push_back({i*(i+1)/2+j,i*(i+1)/2+j+1,(i+1)*(i+2)/2+j+1});
        }
    }
    chrono::steady_clock::time_point begin3hole = chrono::steady_clock::now();
    nerveRed(v3hole);
    chrono::steady_clock::time_point end3hole = chrono::steady_clock::now();
    print_complex(v3hole);
    cout <<endl<< "Time difference v3 = " << std::chrono::duration_cast<std::chrono::microseconds>(end3hole - begin3hole).count()/1000. << "[ms]" << endl <<endl <<endl;


    auto prime=primes(100000);
    vector<vector<int>> v4;
    for(int i=2;i<100000;i++)
        if(prime[i]){
            vector<int> simplex;
            for(int j=0;j<=100000;j+=i)
                simplex.push_back(j);
            v4.push_back(simplex);
        }
    chrono::steady_clock::time_point begin4 = chrono::steady_clock::now();
    nerveRed(v4);
    chrono::steady_clock::time_point end4 = chrono::steady_clock::now();
    print_complex(v4);
    cout <<endl<< "Time difference v4 = " << std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4).count()/1000. << "[ms]" << endl <<endl <<endl;




    vector<vector<int>> v5;
    for(int i=0;i<1000;i++){
        vector<int> simplex;
        for(int j=0;j<100;j++)
            simplex.push_back(5*i+2*j);
        v5.push_back(simplex);
    }
    chrono::steady_clock::time_point begin5 = chrono::steady_clock::now();
    nerveRed(v5);
    chrono::steady_clock::time_point end5 = chrono::steady_clock::now();
    print_complex(v5);
    cout <<endl<< "Time difference v5 = " << std::chrono::duration_cast<std::chrono::microseconds>(end5 - begin5).count()/1000. << "[ms]" << endl <<endl <<endl;
    return 0;
}