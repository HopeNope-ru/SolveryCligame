#include "Astar.h"

bool Node::operator== (const Node& node) {
    return coordinate == node.coordinate;
}

std::map<WCoord, Node> astar(const Node& start, const Node& goal, GameState* gameState) {
    std::map<WCoord, Node> all_nodes;
    
    std::list<Node> frontier;
    std::list<Node>::iterator itFrontier;

    all_nodes[start.coordinate] = start;
    frontier.push_back(start);

    std::set<WCoord> visited;

     while( !(frontier.empty()) ) {
        // вытаскиваем элементы по очереди
        auto min = [](Node& a, Node& b) {
            if(a.priority < b.priority) {
                return true;
            }else{
                return false;
            }
        };
        itFrontier = std::min_element(frontier.begin(), frontier.end(), min);
        Node current = *itFrontier;
        frontier.remove(*itFrontier);

        
        if( current.coordinate == goal.coordinate )
            break;

        if(visited.count(current.coordinate)) continue;

        visited.insert(current.coordinate);


        WCoord neighbors[8] {
            {current.coordinate.x - 1, current.coordinate.y},     // left
            {current.coordinate.x + 1, current.coordinate.y},     // right
            {current.coordinate.x, current.coordinate.y - 1},     // up
            {current.coordinate.x, current.coordinate.y + 1},     // down
            {current.coordinate.x + 1, current.coordinate.y + 1}, // right down
            {current.coordinate.x - 1, current.coordinate.y - 1}, // left up
            {current.coordinate.x + 1, current.coordinate.y - 1}, // right up
            {current.coordinate.x - 1, current.coordinate.y + 1}, // left down
        };



        // Добавляем координаты в frontier и в visited
        for(int i = 0; i < 8; i++) {
            float new_cost;
            if( i < 4 )
                new_cost = 1.0f + current.cost;
            else
                new_cost = 1.41f + current.cost;
            // Необходимо произвести проверку на стоимость.
            // Если стоимость есть в координате, то сравниваем ее с новой стоимость
            // и если новая стоимость меньше предшествующей, то добавляем 
            Node& node_cmp = all_nodes[neighbors[i]];

            bool flagIntersects = false;
            // проверка пересечения с большими объектами(2 и более ячеек)
            for( auto colliderWall : *(gameState->MCObjects) ) {
                if( intersects(neighbors[i], colliderWall) && (neighbors[i] != goal.coordinate)) {
                    flagIntersects = true;
                    break;
                }
            }
            if( flagIntersects ) continue;

            if( ((node_cmp.cost < 0.0001) || new_cost < node_cmp.cost)) {
                // добавляем приоритет соседним координатам
                float priority = new_cost;
                priority += std::hypot(std::abs(neighbors[i].x - goal.coordinate.x), std::abs(neighbors[i].y - goal.coordinate.y));

                Node push_node{neighbors[i], current.coordinate, new_cost, priority};

                frontier.push_back(push_node);
                all_nodes[neighbors[i]] = push_node;
                // mvprintw(neighbors[i].y, neighbors[i].x, "*");
            }
        }
    }
    // возвращаем посещенные координты, с последующем его исп. в пути
    return all_nodes;
}

// Выстраивает путь из посещенных точек
std::list<WCoord> path_fun(const Node& start,const  Node& goal, std::map<WCoord, Node>& all_nodes) {
    std::list<WCoord> path;

    Node current = all_nodes[goal.coordinate];
    path.push_front(current.coordinate);

    while(current.coordinate != start.coordinate) {
        current = all_nodes[current.came_from];
        path.push_front(current.coordinate);
    }

    return path;
}
