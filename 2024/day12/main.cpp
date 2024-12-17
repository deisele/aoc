#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QSet>
#include <QQueue>
#include <QRect>
#include <QPoint>
#include <QDebug>

QSet<QPoint> floodFill(const QStringList &grid, QPoint start);

const QList<QPoint> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

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

    QSet<QPoint> done;
    QList<QSet<QPoint>> groups;
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            QPoint pos(x, y);
            if (!done.contains(pos)) {
                QSet<QPoint> group = floodFill(grid, pos);
                groups.append(group);
                done.unite(group);
            }
        }
    }

    int sumPart1 = 0;
    int sumPart2 = 0;
    for (const QSet<QPoint> &group: groups) {
        int perimeter = 0;
        int sides = 0;
        for (const QPoint &pos: group) {
            for (QPoint dir: directions) {
                if (!group.contains(pos + dir)) {
                    perimeter++;

                    QPoint perpendicular = QPoint(dir.y(), -dir.x());
                    if (!group.contains(pos + perpendicular) || group.contains(pos + perpendicular + dir)) {
                        sides++;
                    }
                }
            }
        }

        int area = group.size();
        sumPart1 += area * perimeter;
        sumPart2 += area * sides;
    }

    out << "Part 1: " << sumPart1 << "\n";
    out << "Part 2: " << sumPart2 << "\n";

    return 0;
}

QSet<QPoint> floodFill(const QStringList &grid, QPoint start) {
    QSet<QPoint> group;
    QQueue<QPoint> queue;
    queue.enqueue(start);

    while (!queue.isEmpty()) {
        QPoint pos = queue.dequeue();
        if (group.contains(pos)) {
            group.insert(pos);

            for (QPoint dir: directions) {
                QPoint next = pos + dir;
                if (QRect(0, 0, grid[0].size(), grid.size()).contains(next) && grid[next.y()][next.x()] == grid[pos.y()][pos.x()]) {
                    queue.enqueue(next);
                }
            }
        }
    }

    return group;
}
