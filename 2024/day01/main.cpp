#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <algorithm>
#include <cstdlib>

int main(int argc, char *argv[]) {
    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);

    QList<int> listA, listB;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.simplified().split(" ");

        listA.append(parts.at(0).toInt());
        listB.append(parts.at(1).toInt());
    }

    std::ranges::sort(listA);
    std::ranges::sort(listB);

    int sumPart1 = 0;
    for (int i = 0; i < listA.size(); i++) {
        sumPart1 += std::abs(listA[i] - listB[i]);
    }

    out << "Sum part 1: " << sumPart1 << "\n";

    int sumPart2 = 0;
    for (int i = 0; i < listA.size(); i++) {
        sumPart2 += listA[i] * listB.count(listA[i]);
    }

    out << "Sum part 2: " << sumPart2 << "\n";

    return 0;
}
