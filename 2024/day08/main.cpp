#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QSet>
#include <QMap>
#include <QPoint>
#include <QDebug>

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

    QMap<QChar, QList<QPoint>> antennas;
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] != '.') {
                antennas[grid[y][x]].append({x, y});
            }
        }
    }

    QSet<QPoint> antinodesPart1;
    QSet<QPoint> antinodesPart2;
    for (const QList<QPoint> &points: antennas) {
        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
                if (i == j) {
                    continue;
                }

                QPoint diff = points[i] - points[j];

                QPoint antinode = points[i] + diff;
                if (0 <= antinode.x() && antinode.x() < grid[0].size() && 0 <= antinode.y() && antinode.y() < grid.size()) {
                    antinodesPart1.insert(antinode);
                }

                antinode = points[i];
                while (0 <= antinode.x() && antinode.x() < grid[0].size() && 0 <= antinode.y() && antinode.y() < grid.size()) {
                    antinodesPart2.insert(antinode);
                    antinode += diff;
                }
            }
        }
    }

    out << "Part 1: " << antinodesPart1.size() << "\n";
    out << "Part 2: " << antinodesPart2.size() << "\n";

    return 0;
}
