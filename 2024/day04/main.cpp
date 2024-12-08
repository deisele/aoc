#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
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

    QList<QString> lines;
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }

    QList<QPoint> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    int sizeX = lines.first().size();
    int sizeY = lines.size();

    int sumPart1 = 0;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            for (const QPoint &direction: directions) {
                const char pattern[] = "XMAS";

                QPoint pos = {x, y};
                int i = 0;
                while (pos.x() >= 0 && pos.x() < sizeX && pos.y() >= 0 && pos.y() < sizeY && lines[pos.y()][pos.x()] == pattern[i]) {
                    pos += direction;
                    i++;
                }

                if (i == sizeof(pattern) - 1) {
                    sumPart1++;
                }
            }
        }
    }

    out << "Sum part 1: " << sumPart1 << "\n";

    int sumPart2 = 0;
    for (int y = 1; y < sizeY - 1; y++) {
        for (int x = 1; x < sizeX - 1; x++) {
            if (lines[y][x] == 'A' &&
                ((lines[y - 1][x - 1] == 'M' && lines[y + 1][x + 1] == 'S') || (lines[y - 1][x - 1] == 'S' && lines[y + 1][x + 1] == 'M')) &&
                ((lines[y - 1][x + 1] == 'M' && lines[y + 1][x - 1] == 'S') || (lines[y - 1][x + 1] == 'S' && lines[y + 1][x - 1] == 'M'))) {

                sumPart2++;
            }
        }
    }

    out << "Sum part 2: " << sumPart2 << "\n";

    return 0;
}
