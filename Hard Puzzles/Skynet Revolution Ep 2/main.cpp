#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <utility>

using namespace std;

struct graphNode{
    int minDist, gatewayInd;
    vector<int> path;
    pair<int, int> lastLink;
};

bool compWeight(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b){
    return (a.first > b.first);
}


bool sameLink(graphNode a, graphNode b){
    return ((a.lastLink.first == b.lastLink.first) && (a.lastLink.second == b.lastLink.second));
}

bool compMinDist(graphNode a, graphNode b){
    return a.minDist > b.minDist;
}

bool pathExists(vector<int> graph[], int start, int end, int numNodes, int pred[], int dist[], bool gate[]){     // use BFS 
    bool visited[numNodes];
    list<int> queue;

    for(int i = 0; i < numNodes; i++){
        visited[i] = false;
        pred[i] = -1;
        dist[i] = 9999;
    }

    visited[start] = true;
    dist[start] = 0;
    queue.push_back(start);

    while(!queue.empty()){
        int temp = queue.front();
        queue.pop_front();

        for(int i = 0; i < graph[temp].size(); i++){
            int ind = graph[temp][i];
            if(visited[ind] == false){
                visited[ind] = true;
                dist[ind] = dist[temp] + 1;
                pred[ind] = temp;
                if(!gate[ind]) queue.push_back(ind);

                if(ind == end) return true;
            }
        }
    }
    return false;
}

int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();

    vector<int> graph[N];
    int gateway[E];
    bool isGate[N] = {0};
    int gateNodes[N] = {0};
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        graph[N1].push_back(N2);
        graph[N2].push_back(N1);
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        gateway[i] = EI;
        isGate[EI] = true;

        vector<int> subGraph = graph[EI];
        for(int j = 0; j < subGraph.size(); j++){
            gateNodes[subGraph[j]]++;
        }
    }

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();

        vector<graphNode> answer;
        for(int i = 0; i < E; i++){
            // if a path exists from SI to EI
            int pred[N], dist[N];

            if(pathExists(graph, SI, gateway[i], N, pred, dist, isGate)){
                //  store Link to Cut + minDist
                pair<int, int> link = make_pair(pred[gateway[i]] , gateway[i]);
                graphNode inCalc;
                vector<int> input(pred, pred + N);

                inCalc.minDist = dist[gateway[i]];
                inCalc.path = input;
                inCalc.gatewayInd = gateway[i];
                inCalc.lastLink = link;

                answer.push_back(inCalc);
            }
        }

        // Sort to find minDist and pop link
        sort(answer.begin(), answer.end(), compMinDist);

        vector<int> vectAns = (answer.back()).path;
        pair<int, int> linkAns = (answer.back()).lastLink;

        // -------- need to stall ----------------------
        int backInd = answer.size() - 1;
        int minDist = (answer.back()).minDist;
        if(minDist != 1){
            vector<pair<int, pair<int, int>>> negBack;
            pair<int, int> linkSearch = (answer.back()).lastLink;
            for(int i = 0; i < N; i++){
                if(gateNodes[i] > 1){
                    int pred[N], dist[N];

                    if(pathExists(graph, SI, i, N, pred, dist, isGate)){
                        int minDist = dist[i];
                        int backInd = i;
                        int nodeEnd = i;
                        int neg = 0;
                        for(int j = 0; j < N; j++){
                            if(backInd == SI) break;

                            if(gateNodes[backInd] > 0) neg++;
                            backInd = pred[backInd];
                        }
                        int weight = minDist + 1 - neg - gateNodes[nodeEnd];

                        vector<int> searchVec = graph[nodeEnd];
                        linkSearch.first = nodeEnd;
                        for(int j = 0; j < searchVec.size(); j++){
                            int searchInd = searchVec[j];
                            for(int k = 0; k < E; k++){
                                if(gateway[k] == searchInd) linkSearch.second = searchInd;
                            }
                        }

                        negBack.push_back(make_pair(weight, linkSearch));
                    }  
                }
            }


            sort(negBack.begin(), negBack.end(), compWeight);
            for(int checking = 0; checking < negBack.size(); checking++){
            }


            if(negBack.size() > 0){
                linkSearch = (negBack.back()).second;
            }
            linkAns = linkSearch;
        }

        // --------------- Delete Link From Graph --------------------
        int indErase = 0;
        for(int i = 0; i < graph[linkAns.first].size(); i++){
            if(graph[linkAns.first][i] == linkAns.second) indErase = i;
        }
        graph[linkAns.first].erase(graph[linkAns.first].begin() + indErase);
        gateNodes[linkAns.first]--;

        answer.clear();
        cout << linkAns.first << " " << linkAns.second << endl;
    }
}
