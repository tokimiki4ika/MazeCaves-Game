#include "maze_solver.h"
#include <set>

using namespace s21;

bool MazeSolver::CheckWall(Location current, Location direction, const Matrix& matrix_) {
    if (direction.x == 1) {  // Вправо
        return (matrix_(current.y, current.x) == kRightWall || matrix_(current.y, current.x) == kBothWalls);
    } else if (direction.x == -1) {  // Влево
        return (current.x == 0 || matrix_(current.y, current.x - 1) == kRightWall || matrix_(current.y, current.x - 1) == kBothWalls);
    } else if (direction.y == 1) {  // Вниз
        return (matrix_(current.y, current.x) >= kBottomWall);
    } else if (direction.y == -1) {  // Вверх
        return (current.y == 0 || matrix_(current.y - 1, current.x) >= kBottomWall);
    }
    return true;
}

// Ориентированные направления для алгоритма
std::vector<Location> MazeSolver::SolveMaze(Location begin, Location end, const Maze& maze_) {
    if (begin.x >= maze_.GetColumns() || begin.y >= maze_.GetRows() ||
        end.x >= maze_.GetColumns() || end.y >= maze_.GetRows()) {
        throw std::invalid_argument("Begin or End position is invalid");
    }

    const Matrix& matrix_ = maze_.GetMatrix();
    std::vector<Location> path;
    std::set<Location> visited;
    SolveRecursive(begin, end, matrix_, path, visited, {0, 1});  // Начнем с направления вниз
    return path;
}

bool MazeSolver::SolveRecursive(Location current, Location end, const Matrix& matrix_,
                                std::vector<Location>& path, std::set<Location>& visited, Location direction) {
    if (current == end) {
        path.push_back(current);
        return true;
    }

    if (visited.find(current) != visited.end()) {
        return false;
    }

    visited.insert(current);
    path.push_back(current);

    // Порядок поворотов: влево, прямо, вправо
    std::vector<Location> turnOrder = { {-direction.y, direction.x}, direction, {direction.y, -direction.x} };
    
    for (const auto& turn : turnOrder) {
        Location next(current.x + turn.x, current.y + turn.y);
        if (!CheckWall(current, turn, matrix_) && visited.find(next) == visited.end()) {
            if (SolveRecursive(next, end, matrix_, path, visited, turn)) {
                return true;
            }
        }
    }

    // Откат пути, если тупик
    path.pop_back();
    return false;
}
