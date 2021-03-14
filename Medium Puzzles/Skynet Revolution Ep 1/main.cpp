#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();

    vector<vector<int>> graph;
    vector<int> gateway;
    graph.resize(N);

    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        graph[N2].push_back(N1);
        graph[N1].push_back(N2);
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        gateway.push_back(EI);
    }

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();

        bool *visited = new bool[N]; 
        for(int i = 0; i < N; i++) 
            visited[i] = false; 
    
        vector<int> queue; 
        bool begin = true;
        visited[SI] = true; 
        queue.push_back(SI); 

        while(!queue.empty()) 
        { 
            int s = queue.front(); 
            cerr << s << " "; 
            reverse(queue.begin(), queue.end());
            queue.pop_back(); 
            reverse(queue.begin(), queue.end());

            vector <int> :: iterator i; 
            for (i = graph[s].begin(); i != graph[s].end(); ++i) 
            { 
                if (!visited[*i]) 
                { 
                    visited[*i] = true; 
                    queue.push_back(*i); 
                } 
                for(int node : gateway){
                    if(node == *i){
                        cout << s << " " << node << endl;
                        graph[s].erase(i);
                        begin = false;
                        break;
                    } 

                }
                if(begin != true) break;
            } 
            if(begin != true) break;
        } 
    }
}
