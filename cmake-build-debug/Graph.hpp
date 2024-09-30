//
// Created by Alessio on 02/06/2018.
//

#ifndef PROGETTO_GRAPH_HPP
#define PROGETTO_GRAPH_HPP
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


template <typename T,typename I,typename W>
class Graph {

/*Dichiarazione Enum */

public:
    enum Directed{SI,NO};

public:
    Graph();
    ~Graph();
    T findNode(I key);
    void InsertNode(I key, T val);
    void InsertEdge(I key1, I key2, W weight, Directed isdirected);
    void DeleteNode(I key);
    void DeleteEdge(I key1, I key2, W weight_to_erase);
    void ModifyEdge(I key1, I key2, W weight_to_modify, W new_weight);
    void Display();
    map<I,T> GetNodes();
    map<I,vector<W>> GetEdges(I node);


private:

    int V;

    int E;

    map<I,T> tab;

    map<I,map<I,vector<W>>> adj;

};

//Implementazioni//

template <typename T,typename I,typename W>
Graph<T,I,W>::Graph(){
    V=0;
    E=0;
}

template <typename T,typename I,typename W>
Graph<T,I,W>::~Graph(){

}

template <typename T, typename I, typename W>
map<I,T> Graph<T,I,W>::GetNodes(){
    return tab;
};

template <typename T,typename I,typename W>
void Graph<T,I,W>::InsertNode(I key, T val){
    tab[key]=val;
    V++;
}

template <typename T,typename I,typename W>
T Graph<T,I,W>::findNode(I key){
    T pointer = nullptr;
    for(typename map<I,map<I,vector<W>>>::iterator it = adj.begin(); it!=adj.end(); it++){
        if(it->second.find(key)!=it->second.end()){
        pointer = it->second;
        }
    }
    return pointer;
}

template<typename T, typename I, typename W>
void Graph<T,I,W>::InsertEdge(I key1, I key2, W weight, Directed isdirected){
    E++;
    adj[key1][key2].push_back(weight);

    if(isdirected==Graph<T,I,W>::NO){
        adj[key2][key1].push_back(weight);
    }
}

template <typename T, typename I, typename W>
void Graph<T,I,W>::DeleteNode(I key){
    if(tab.find(key)!=tab.end())
        tab.erase(key);
    for(typename map<I,map<I,vector<W>>>::iterator it = adj.begin(); it!=adj.end(); it++)
        if(it->second.find(key)!=it->second.end())
            it->second.erase(key);
    if(adj.find(key)!=adj.end())
        adj.erase(key);
    V--;
}

template<typename T, typename I, typename W>
void Graph<T,I,W>::DeleteEdge(I key1, I key2, W weight_to_erase){

    if(adj.find(key1)!=adj.end()){
        if(adj[key1].find(key2)!=adj[key1].end()){
            if(adj.find(key2)!=adj.end()){
                if(adj[key2].find(key1)!=adj[key2].end()){
                    if(find(adj[key2][key1].begin(),adj[key2][key1].end(),weight_to_erase)!=adj[key2][key1].end()){
                        adj[key2][key1].erase(adj[key2][key1].find(weight_to_erase));
                    }
                }
            }
            if(find(adj[key1][key2].begin(),adj[key1][key2].end(),weight_to_erase)!=adj[key2][key1].end()){
                adj[key1][key2].erase(adj[key1][key2].find(weight_to_erase));
            }
        }
    }

    E--;
}

template <typename T, typename I, typename W>
void Graph<T,I,W>::ModifyEdge(I key1, I key2, W weight_to_modify, W new_weight){

    if(adj.find(key1)!=adj.end()){
        if(adj[key1].find(key2)!=adj[key1].end()){
            if(adj.find(key2)!=adj.end()){
                if(adj[key1].find(key2)!=adj[key1].end()){
                    if(find(adj[key2][key1].begin(),adj[key2][key1].end(),weight_to_modify)!=adj[key2][key1].end()){
                        *(find(adj[key2][key1].begin(),adj[key2][key1].end(),weight_to_modify))=new_weight;
                    }
                }
            }
            if(adj[key1][key2].find(weight_to_modify)!=adj[key1][key2].end()){
                *(find(adj[key1][key2].begin(),adj[key1][key2].end(),weight_to_modify))=new_weight;
            }
        }

    }


}

template <typename T, typename I, typename W>
void Graph<T,I,W>::Display(){
    for(typename map<I,map<I,W>>::iterator it=adj.begin(); it!=adj.end(); it++){
        cout << "Node with id " << it->first << ":" << endl;
        for(typename map<I,vector<W>>::iterator it2=it->second.begin(); it2!=it->second.end();it2++){
            for(typename vector<W>::iterator it3 = it2->second.begin(); it3!=it2->second.end(); it3++)
                cout << "\tIs connected to node with id " << it2->first << " and has weight = " << *it3 << endl;
        }
    }

}

template<typename T, typename I, typename W>
map<I, vector<W>> Graph<T, I, W>::GetEdges(I node) {

    return adj.find(node)->second;
}

#endif //PROGETTO_GRAPH_HPP
