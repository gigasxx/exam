import heapq
n = int(input("Enter number of cities: "))
cities = []
print("\nEnter city names")
for i in range(n):
    cities.append(input(f"City {i+1}: "))
distance_matrix = []
print("\nEnter distances between cities")
for i in range(n):
    row = []
    for j in range(n):
        if i == j:
            row.append(0)
        else:
            d = int(input(f"Distance from {cities[i]} to {cities[j]}: "))
            row.append(d)
    distance_matrix.append(row)
source_city = input("\nEnter source city: ")
destination_city = input("Enter destination city: ")
if source_city not in cities or destination_city not in cities:
    print("Invalid city name entered.")
    exit()
source = cities.index(source_city)
destination = cities.index(destination_city)
direct_distance = distance_matrix[source][destination]
if direct_distance == 0:
    print("\nNo direct route exists from",source_city,"to",destination_city)
else:
    print("\nDirect distance from",source_city,"to",destination_city,"is",direct_distance,"km")
dist = [float('inf')] * n
parent = [-1] * n
dist[source] = 0
pq = [(0, source)]
while pq:
    current_dist, u = heapq.heappop(pq)
    if current_dist > dist[u]:
        continue
    for v in range(n):
        weight = distance_matrix[u][v]
        if weight > 0:
            new_dist = dist[u] + weight
            if new_dist < dist[v]:
                dist[v] = new_dist
                parent[v] = u
                heapq.heappush(pq, (new_dist, v))
if dist[destination] == float('inf'):
    print("No path exists from",source_city,"to",destination_city)
else:
    path = []
    current = destination
    while current != -1:
        path.append(cities[current])
        current = parent[current]
    path.reverse()
    print("\nShortest distance from",source_city,"to",destination_city,"is",dist[destination],"km")
    print("\nShortest path:")
    print(" -> ".join(path))
