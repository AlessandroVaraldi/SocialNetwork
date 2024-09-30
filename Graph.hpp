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
public:
    //enum type{directed,undirected};
    Graph();
    ~Graph();
    void insertNode(I key, T val);
    void insertEdge(I key1, I key2, W weight);
    void deleteNode(I key);
    void deleteEdge(I key1, I key2, W first_weight_to_erase, W second_weight_to_erase);
    void modifyEdge(I key1, I key2, W weight_to_modify, W new_weight);
    void modifyNodesKey(I old_key, I new_key);
    void modifyEdgesKey(I old_key, I new_key);
    map<I,T> getNodes();
    map<I,vector<W>> getEdges(I node);
private:
    int _nodesNumber;
    int _edgesNumber;
    map<I,T> _nodesMap;
    map<I,map<I,vector<W>>> _edgesMap;
};

//Implementazioni//

template<typename T,typename I,typename W>
Graph<T,I,W>::Graph(){
    _nodesNumber=0;
    _edgesNumber=0;
}

template <typename T,typename I,typename W>
Graph<T,I,W>::~Graph(){

}

template <typename T,typename I,typename W>
map<I,T> Graph<T,I,W>::getNodes(){
    return _nodesMap;
};

template <typename T,typename I,typename W>
void Graph<T,I,W>::insertNode(I key, T val){
    _nodesMap[key]=val;
    _nodesNumber++;
}

template<typename T,typename I,typename W>
void Graph<T,I,W>::insertEdge(I key1, I key2, W weight){
    _edgesNumber++;
    if(find(_edgesMap[key1][key2].begin(),_edgesMap[key1][key2].end(),weight) == _edgesMap[key1][key2].end()) {
        _edgesMap[key1][key2].push_back(weight);
    }
}

template <typename T,typename I,typename W>
void Graph<T,I,W>::deleteNode(I key){
    if(_nodesMap.find(key)!=_nodesMap.end())
        _nodesMap.erase(key);
    for(typename map<I,map<I,vector<W>>>::iterator it = _edgesMap.begin(); it!=_edgesMap.end(); it++)
        if(it->second.find(key)!=it->second.end())
            it->second.erase(key);
    if(_edgesMap.find(key)!=_edgesMap.end())
        _edgesMap.erase(key);
    _nodesNumber--;
}

template<typename T, typename I, typename W>
void Graph<T, I, W>::deleteEdge(I key1, I key2, W first_weight_to_erase, W second_weight_to_erase) {
    if(_edgesMap.find(key1)!=_edgesMap.end()){
        if(_edgesMap[key1].find(key2)!=_edgesMap[key1].end()){
            if(_edgesMap.find(key2)!=_edgesMap.end()){
                if(_edgesMap[key2].find(key1)!=_edgesMap[key2].end()){
                    if(find(_edgesMap[key2][key1].begin(),_edgesMap[key2][key1].end(),first_weight_to_erase)!=_edgesMap[key2][key1].end()){
                        _edgesMap[key2][key1].erase(find(_edgesMap[key2][key1].begin(),_edgesMap[key2][key1].end(),first_weight_to_erase));
                    }
                }
            }
            if(find(_edgesMap[key1][key2].begin(),_edgesMap[key1][key2].end(),second_weight_to_erase)!=_edgesMap[key1][key2].end()){
                _edgesMap[key1][key2].erase(find(_edgesMap[key1][key2].begin(),_edgesMap[key1][key2].end(),second_weight_to_erase));
            }
        }
    }

    _edgesNumber--;
}

template <typename T,typename I,typename W>
void Graph<T,I,W>::modifyEdge(I key1, I key2, W weight_to_modify, W new_weight){

    if(_edgesMap.find(key1)!=_edgesMap.end()){
        if(_edgesMap[key1].find(key2)!=_edgesMap[key1].end()){
            if(_edgesMap.find(key2)!=_edgesMap.end()){
                if(_edgesMap[key1].find(key2)!=_edgesMap[key1].end()){
                    if(find(_edgesMap[key2][key1].begin(),_edgesMap[key2][key1].end(),weight_to_modify)!=_edgesMap[key2][key1].end()){
                        *(find(_edgesMap[key2][key1].begin(),_edgesMap[key2][key1].end(),weight_to_modify))=new_weight;
                    }
                }
            }
            if(_edgesMap[key1][key2].find(weight_to_modify)!=_edgesMap[key1][key2].end()){
                *(find(_edgesMap[key1][key2].begin(),_edgesMap[key1][key2].end(),weight_to_modify))=new_weight;
            }
        }
    }
}

template<typename T,typename I,typename W>
map<I, vector<W>> Graph<T, I, W>::getEdges(I node) {
    if(_edgesMap.find(node) != _edgesMap.end()) {
        return _edgesMap.find(node)->second;
    }

    return map<I,vector<W>>();
}

template<typename T, typename I, typename W>
void Graph<T, I, W>::modifyNodesKey(I old_key, I new_key) {
    T val = getNodes()[old_key];
    _nodesMap.erase(old_key);
    insertNode(new_key,val);
}

template<typename T, typename I, typename W>
void Graph<T, I, W>::modifyEdgesKey(I old_key, I new_key) {
    //modifica la first della sua mappa di relazioni
    map<I,vector<W>> old_edges = getEdges(old_key);
    _edgesMap.erase(old_key);
    _edgesMap.insert(pair<I,map<I, vector<W>>> (new_key,old_edges));

    //modifica nelle mappe di relazioni di altri
    for(map<string,map<string,vector<string>>>::iterator it = _edgesMap.begin(); it != _edgesMap.end(); it++){
        if((it->second).find(old_key) != (it->second).end()){
            vector<string> vett = (it->second)[old_key];
            (it->second).erase(old_key);
            (it->second).insert(pair<I,vector<W>>(new_key,vett));
        }
    }

}

#endif //PROGETTO_GRAPH_HPP
