#ifndef A1_MAZE_1_SRC_MAZE_CAVES_MAZE_MAZE_SOLVER_H_
#define A1_MAZE_1_SRC_MAZE_CAVES_MAZE_MAZE_SOLVER_H_

#include <queue>
#include <vector>
#include <set>

#include "maze.h"

namespace s21 {

/**
 * @brief Класс локации
 */
struct Location {
  int x;                      ///< Местонахождение по x
  int y;                      ///< Местонахождение по y
  Location() : x(0), y(0) {}  ///< Дефолтный конструктор
  Location(int x_value, int y_value)
      : x(x_value), y(y_value) {}  ///< Параметризированный конструктор

  bool operator==(const Location &other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Location &other) const {
    return x != other.x || y != other.y;
  }
  bool operator<(const Location &other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};

/**
 * @brief Класс для нахождения пути в лабиринте
 */
class MazeSolver {
 public:
  MazeSolver() = delete;  ///< Дефолтный конструктор недоступен
  ~MazeSolver() = delete;  ///< Дефолтный деструктор недоступен
  /**
   * @brief Решения лабиринта
   * @details Путь находится методом правой руки (придерживаясь правой стены)
   * @param begin начальная позиция
   * @param end конечная позиция
   * @param maze_ сам лабиринт
   * @return вектор локаций - точки, через которые нужно пройти, чтобы дойти из
   * точки begin в точку end
   */
  static std::vector<Location> SolveMaze(Location begin, Location end,
                                         const Maze &maze_);

 private:
  /**
   * @brief проверка стены впереди
   * @param current настоящая позиция
   * @param turn в какую сторону в данный момент направлен взгляд пути
   * @param matrix_ матрица, описывающая стены лабиринта
   * @return результат проверки (true - стена есть, false - стены нет)
   */
  static bool CheckWall(Location current, Location direction, const Matrix& matrix_);

  static bool SolveRecursive(Location current, Location end, const Matrix& matrix_,
                                std::vector<Location>& path, std::set<Location>& visited, Location direction);
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MAZE_CAVES_MAZE_MAZE_SOLVER_H_
