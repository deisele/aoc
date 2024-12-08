#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QSet>
#include <QMap>
#include <QMultiMap>
#include <QQueue>
#include <QDebug>

QList<int> topologicalSort(const QMultiMap<int, int> &edges, const QList<int> &nodes);

int main() {
    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);

    QMultiMap<int, int> edges;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) {
            break;
        }

        QStringList parts = line.split("|");
        edges.insert(parts[0].toInt(), parts[1].toInt());
    }

    int sumPart1 = 0;
    int sumPart2 = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        QList<int> row;
        for (const QString &part: parts) {
            row.append(part.toInt());
        }

        QList<int> sorted = topologicalSort(edges, row);
        if (row == sorted) {
            sumPart1 += row[row.size() / 2];
        } else {
            sumPart2 += sorted[sorted.size() / 2];
        }
    }

    out << "Sum part 1: " << sumPart1 << "\n";
    out << "Sum part 2: " << sumPart2 << "\n";

    return 0;
}

QList<int> topologicalSort(const QMultiMap<int, int> &edges, const QList<int> &nodes) {
    QSet<int> nodeSet(nodes.begin(), nodes.end());
    QMap<int, int> inDegree;
    for (int node: nodeSet) {
        for (int to: edges.values(node)) {
            if (nodeSet.contains(to)) {
                inDegree[to]++;
            }
        }
    }

    QQueue<int> next;
    for (int node: nodeSet) {
        if (inDegree[node] == 0) {
            next.enqueue(node);
        }
    }

    QList<int> sorted;
    while (!next.empty()) {
        int node = next.dequeue();
        sorted.append(node);

        int enqueued = 0;
        for (int to: edges.values(node)) {
            inDegree[to]--;
            if (inDegree[to] == 0) {
                if (enqueued++ > 0) {
                    // for the puzzle input, the sorting seems to be unique, so this should not happen
                    qFatal() << "Multiple nodes with in-degree 0";
                }
                next.enqueue(to);
            }
        }
    }

    return sorted;
}
