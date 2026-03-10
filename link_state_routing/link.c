#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Link state routing algorithm implementation 
int main() {
  
  // Read the number of routers which are available 
  int n ; 
  printf("Enter the number of routers: "); 
  scanf("%d", &n );
  
  // Read the cost matrix  
  int cost[n][n]; 
  printf("Enter the cost matrix values => (9999 for no link): "); 
  for(int i = 0; i < n; i++ ) {
    for(int j = 0; j< n; j++) {
      scanf("%d", &cost[i][j]); 
    }
  }
  
  // Get the source router ie. From which router the distance is to be calculated. 
  int src ; 
  printf("Enter the source router: ");
  scanf("%d", &src); 
  
  // ===> Dijkstra's algorithm 
  
  // Initialize the dist and visited to default values 
  int dist[n];
  bool s[n]; 
  for(int i = 0; i < n; i++) {
    dist[i]  = cost[src][i];
    s[i] = false; 
  }
  
  dist[src] = 0; 
  s[src] = true;
  
  for(int i = 1; i < n; i++ ){
  
  // Choose the node satisfying the conditions -> s[] should be false and dist[] should be minimum 
    int min_value = INT_MAX, node ; 
    for(int j = 0; j < n; j++ ){
      if(!s[j] && dist[j] < min_value){
        min_value = dist[j]; 
        node = j ; 
      }
    }
    
    s[node] = true; 
    
    // update the adjacent nodes dist with least cost 
    
    for(int j = 0; j < n; j++ ){
      if(!s[j] && dist[j] > dist[node] + cost[node][j]) dist[j] = dist[node] + cost[node][j]; 
    }
  }
  
  // print the final shortest distance vector
  printf("\n\nDistance from the src router %d\n", src); 
  for(int i = 0; i < n; i++) {
    printf("To router %d: %d\n" , i , dist[i]); 
  }
  
  return 0 ; 
  
}




/* 
  Output 
  
Enter the number of routers: 4
Enter the cost matrix values => (9999 for no link): 
0 2 9999 1 
2 0 1 3 
9999 1 0 9999
1 3 9999 0
Enter the source router: 0


Distance from the src router 0
To router 0: 0
To router 1: 2
To router 2: 3
To router 3: 1

*/