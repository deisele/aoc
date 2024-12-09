#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QSet>
#include <QPair>
#include <QPoint>
#include <QDebug>

int cellsVisitedUntilOutOfBounds(const QStringList &grid, QPoint start);

int main() {
    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);

    QStringList grid;
    while (!in.atEnd()) {
        grid.append(in.readLine());
    }

    QPoint start;
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == '^') {
                start = {x, y};
                goto found;
            }
        }
    }
    found:

    out << "Part 1: " << cellsVisitedUntilOutOfBounds(grid, start) << "\n";

    int sumPart2 = 0;
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == '.') {
                grid[y][x] = '#';

                if (cellsVisitedUntilOutOfBounds(grid, start) == -1) {
                    sumPart2++;
                }

                grid[y][x] = '.';
            }
        }
    }

    out << "Part 2: " << sumPart2 << "\n";

    return 0;
}

int cellsVisitedUntilOutOfBounds(const QStringList &grid, QPoint start) {
    QList<QPoint> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    QSet<QPoint> visited;
    QSet<QPair<QPoint, int>> visitedWithDirection;
    QPoint pos = start;
    int direction = 0;
    while (0 <= pos.x() && pos.x() < grid[0].size() && 0 <= pos.y() && pos.y() < grid.size()) {
        if (visitedWithDirection.contains({pos, direction})) {
            return -1;
        }

        visited.insert(pos);
        visitedWithDirection.insert({pos, direction});

        QPoint next = pos + directions[direction];
        while (0 <= next.x() && next.x() < grid[0].size() && 0 <= next.y() && next.y() < grid.size() && grid[next.y()][next.x()] == '#') {
            direction = (direction + 1) % directions.size();
            next = pos + directions[direction];
        }

        pos = next;
    }

    return visited.size();
}
