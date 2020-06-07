#include <unordered_map>
#include <vector>

int dfs(std::vector<std::vector<int>>& adj, std::unordered_map<int, int>& count, std::vector<bool> visited, std::vector<bool>& visited_centroids, int src) {
    count[src] = 1;
    visited[src] = 1;
    for(auto it: adj[src]) {
        if(!visited[it] && !visited_centroids[it]) {
            count[src] += dfs(adj, count, visited, visited_centroids, it);
        }
    }
    return count[src];
}

int get_centroid(std::vector<std::vector<int>>& adj, std::unordered_map<int, int>& count, std::vector<bool> visited, std::vector<bool>& visited_centroids, int src, int n) {
    visited[src] = 1;
    for(auto it: adj[src]) {
        if(!visited[it] && !visited_centroids[it] && count[it] > n / 2) {
            return get_centroid(adj, count, visited, visited_centroids, it, n);
        }
    }
    return src;
}

std::vector<std::vector<int>> create_adjacency_list(std::vector<std::vector<int>>& list) {
    std::vector<std::vector<int>> adj(2* list.size());
    for(int i = 0; i < list.size(); ++i) {
        adj[list[i][0]].push_back(list[i][1]);
        adj[list[i][1]].push_back(list[i][0]);
    }
    return adj;
}

int centroid_decomposition(std::vector<std::vector<int>>& adj, std::vector<std::vector<int>>& adj_nodes, std::vector<bool>& visited_centroids, std::vector<int>& levels, int src, int level, int size) 
{ 
    std::vector<bool> visited(size, 0);
    std::unordered_map<int, int> count{};
    int n = dfs(adj ,count, visited, visited_centroids, src); 
    int centroid = get_centroid(adj, count, visited, visited_centroids, src, n);
    visited_centroids[centroid] = 1;
    levels[centroid] = level;
    for(auto& item : adj[centroid]) 
    { 
        if (!visited_centroids[item]) 
        { 
            int sub_centroid = centroid_decomposition(adj, adj_nodes, visited_centroids, levels, item, level + 1, size); 
            adj_nodes[centroid].push_back(sub_centroid); 
            adj_nodes[sub_centroid].push_back(centroid); 
        } 
    } 
    return centroid; 
} 
