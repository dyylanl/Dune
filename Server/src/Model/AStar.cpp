#include "../../includes/Model/AStar.h"

AStar::AStar(Map &map) : map(map) {}

std::stack<Position> AStar::reconstructPath(const std::map<Position, Position> &best_path, const Position &start) {
    std::stack<Position> total_path;
    Position current(start);
    total_path.push(current);
    while (best_path.find(current) != best_path.end()) {
        current = best_path.at(current);
        total_path.push(current);
    }
    total_path.pop();
    return (total_path);
}

std::stack<Position> AStar::makePath(Unit &unit, const Position& end) {
    if (!map.canMove(unit, end)) {
        return {};
    }
    // Creo el camino a retornar.
    std::map<Position, Position> best_path;
    // Fin
    AStarNode n_end(end);
    // Origen
    AStarNode n_start(unit.getPosition());

    // Cargo en opelist el nodo inicial (donde esta parada la unidad).
    openList.push_back(n_start);

    while (!openList.empty()) {
        // Busco el nodo que tenga el f menor de la openlist
        auto curr_node_itr = openList.begin();
        for (auto itr = openList.begin(); itr != openList.end() ; itr++) {
            if (itr->f < curr_node_itr->f) {
                curr_node_itr = itr;
            }
        }

        // Se chequea si se encuentra en el destino
        if (*curr_node_itr == n_end) {
            return this->reconstructPath(best_path, end); // Retorno la mejor ruta encontrada.
        }

        // Se quita de la lista de abiertos y se agrega en la lista de cerrados
        closeList.emplace_back(*curr_node_itr);
        openList.erase(curr_node_itr);
        curr_node_itr = closeList.end() - 1;

        // Se buscan todos los hijos que son adyacentes al nodo actual
        std::vector<AStarNode> children = curr_node_itr->getAdjacents(this->map);

        // A partir de aca, procesa cada hijo para saber si debe ignorarlo, actualizarlo en la lista de abiertos
        // o agregarlo en la lista de abiertos. Tambien chequea si uno de los hijos es el nodo final
        for (AStarNode& child : children) {
            auto child_cl_itr = std::find(closeList.begin(), closeList.end(), child);

            // Si el hijo esta en la lista de cerrados o es una pared, se ignora
            if (child_cl_itr != closeList.end() || !map.canMove(unit, child.pos)) {
                continue;
            }

            // Se calculan los parametros del hijo
            child.g = curr_node_itr->g + 1;
            child.h = child.pos.sqrtDistance(n_end.pos);
            child.f = child.g + child.h;

            // Si el hijo esta en la lista de abiertos, no se vuelve a agregar.
            // Sin embargo, si ademas, el valor de g actual es menor, se actualiza
            auto child_ol_itr = std::find(openList.begin(), openList.end(), child);
            if (child_ol_itr == openList.end()) {
                openList.push_back(child);
            } else {
                if (child.g >= child_ol_itr->g) {
                    continue;
                }
                child_ol_itr->g = child.g;
                child_ol_itr->f = child.f;
            }
            best_path[child.pos] = curr_node_itr->pos;
        }
    }
    return {};
}

