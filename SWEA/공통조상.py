from collections import defaultdict
T = int(input())

for t in range(T):
    v_count, e_count, v_1, v_2 = map(int, input().split())

    s_list = list(map(int, input().split()))

    graph = defaultdict(list)
    
    max_node = max(s_list)
    graph_parent = [0] * (max_node + 1)

    for i in range(0, len(s_list), 2):
        p, c = s_list[i], s_list[i+1]
        
        graph[p].append(c)   
        graph_parent[c] = p  

    graph_size = {}


    def find_parent(node):
        if node == 1:
            return []
        
        parent = graph_parent[node]

        if parent in graph:
            graph_size[parent] = len(graph[parent])

        return [parent] + find_parent(parent)

    parent_list = [v_1]
    parent_list_2 = [v_2]
    for key, value in graph.items():
        if v_1 in value:
            parent_list += find_parent(v_1)
        
        if v_2 in value:
            parent_list_2 += find_parent(v_2)

    count = 0
    def search(node):
        global count
        count += 1

        if node not in graph:
            return 

        li = graph[node]

        
        for i in li:
            search(i)


    for i in parent_list:
        if i in parent_list_2:
            search(i)
            break

    print(f"#{t + 1} {i} {count}")