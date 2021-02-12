/*
Klesti Kokona

Viti 3 

Paraleli A1

Algoritmi Round Robin
*/

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <queue> 
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Procesor{

private:
    vector <int> arrival_t;
    vector <int> burst_t;
    vector <int> burst;
    vector <int> rem_burst_t;
    vector <int> turnaround_t;
    vector <int> completion_t;
    vector <int> waiting_t;

    queue <int> radhe;
    queue <int> radhe_gati;

    float avg_tat=0;
    float avg_wt=0;

    int QUANTUM;
    
    int clock=0;
    int time=0;
    
    int n; 
    int i;      
    int c;
    int j=i+1;

public:

    Procesor(){
        cout<<"Jep nr e proceseve"<<endl;
        cin>>this->n;
        cout<<"Jep nr e QUANTUM"<<endl;
        cin>>this->QUANTUM;
        for(int i=0;i<n;i++){
            int a;
            int b;
            cout<<"Jep kohen arritjes a per procesin "<<i+1<<endl;
            cin>>a;
            cout<<"Jep kohen burstit b per procesin "<<i+1<<endl;
            cin>>b;

            arrival_t.push_back(a);
            burst_t.push_back(b);
            burst.push_back(b);
            rem_burst_t.push_back(b);
            completion_t.push_back(0);
            turnaround_t.push_back(0);
            waiting_t.push_back(0);
        }
        cout<<"____________________________________________"<<endl<<endl;
    };


    


    void popullo(int i){
        int j=i+1;
      
        if(arrival_t[i]<=time && rem_burst_t[i]!=0 && i<n){
            radhe.push(i);
            if(rem_burst_t[i]>QUANTUM){
                rem_burst_t[i] = rem_burst_t[i] - QUANTUM;
                radhe_gati.push(i);
            }else{
                rem_burst_t[i]=0;
                
            }
            time++;
            for( c=j; c<=(i+QUANTUM) && c<n; c++){
                if(arrival_t[c]<=time){
                    radhe.push(c);
                    if (rem_burst_t[c]>QUANTUM){
                        rem_burst_t[c] = rem_burst_t[c] - QUANTUM;
                        radhe_gati.push(c);
                    }else{
                        rem_burst_t[c]=0;  
                    } 
                }
                time++;
            }
            radhe.push( radhe_gati.front() );
            if( rem_burst_t[radhe_gati.front()] > QUANTUM) {
                rem_burst_t[radhe_gati.front()]=rem_burst_t[radhe_gati.front()] - QUANTUM;
                radhe_gati.push( radhe.back() );
            }else{
                rem_burst_t[radhe_gati.front()]=0;
            }
            radhe_gati.pop();
            popullo(c);
        }
        

      
        while(!radhe_gati.empty()){
            radhe.push( radhe_gati.front() );
            if(rem_burst_t[radhe_gati.front()]>QUANTUM){
                rem_burst_t[radhe_gati.front()] = rem_burst_t[radhe_gati.front()] - QUANTUM;
                radhe_gati.push(radhe_gati.front());
            }else{
                rem_burst_t[radhe_gati.front()]=0;
            }
            radhe_gati.pop();
        }
        
    }
    
    void printoGantt(){
        queue <int> radhitja;
        cout<<"SKEMA GANT"<<endl<<endl;
        while(!radhe.empty()){
            radhitja.push(radhe.front());
            cout<<radhitja.back()+1<<" || ";
            radhe.pop();
        }
        while(!radhitja.empty()){
            radhe.push(radhitja.front());
            radhitja.pop();
        }
        cout<<endl<<endl;
    }
    
    void proceso(){
        int clock=0;
            while( !radhe.empty() ){
                
                if(burst_t[radhe.front()]>QUANTUM) {
                    clock=clock+QUANTUM;
                    burst_t[radhe.front()]=burst_t[radhe.front()]-QUANTUM;
                    radhe.pop();
                }else {
                    clock=clock+burst_t[radhe.front()];
                    completion_t[radhe.front()] = clock;
                    turnaround_t[radhe.front()] = completion_t[radhe.front()] - arrival_t[radhe.front()];
                    waiting_t[radhe.front()] = turnaround_t[radhe.front()] - burst[radhe.front()];
                    cout<< "Procesi me index " << radhe.front()+1 << " perfundoi ne kohen      -> " << completion_t[radhe.front()]<<" njesi kohe" <<endl;
                    cout<< "Procesi me index " << radhe.front()+1 << " ka turnaround time      -> " << turnaround_t[radhe.front()] << " njesi kohe"<<endl;
                    cout<< "Procesi me index " << radhe.front()+1 << " ka pritur (waiting time)-> " << waiting_t[radhe.front()] << " njesi kohe"<<endl<<endl;
                    radhe.pop();
            }
        }
    }

    void printoKohetMesatare(){
        for(int i=0;i<n;i++){
            avg_tat+=turnaround_t[i];
            avg_wt+=waiting_t[i];
        }
        avg_tat=avg_tat/n;
        avg_tat=avg_tat;

        avg_wt=avg_wt/n;
        avg_wt=avg_wt;

        cout<<endl<<endl;
        cout<<"Koha mesatare e pritjes (waiting time): "<<avg_wt<<endl;
        cout<<"Koha mesatare e turnaround (turnaround time): "<<avg_tat;
    }

};  

    
    

int main(){
    Procesor i9;
    i9.popullo(0);
    i9.printoGantt();
    i9.proceso();
    i9.printoKohetMesatare();
    return 0;

}
