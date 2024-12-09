#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>

long long checksum(const QList<int> &blocks);

int main() {
    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);
    QString diskMap = in.readLine();

    QList<int> blocks;
    int id = 0;
    bool isData = true;
    for (QChar block: diskMap) {
        blocks.append(QList<int>(block.digitValue(), (isData? id++ : -1)));
        isData = !isData;
    }

    QList<int> compactedBlocks1 = blocks;
    for (int i = 0; i < compactedBlocks1.size(); i++) {
        if (compactedBlocks1[i] == -1) {
            compactedBlocks1[i] = compactedBlocks1.takeLast();
        }

        while (compactedBlocks1.last() == -1) {
            compactedBlocks1.removeLast();
        }
    }

    out << "Sum part 1: " << checksum(compactedBlocks1) << "\n";

    QList<int> compactedBlocks2 = blocks;
    int top = compactedBlocks2.size() - 1;
    while (top > 0) {
        while (compactedBlocks2[top] == -1) {
            top--;
        }

        int dst = top;
        int id = compactedBlocks2[top];
        int size = 0;
        while (top >= 0 && compactedBlocks2[top] == id) {
            compactedBlocks2[top--] = -1;
            size++;
        }

        int freeSpace = 0;
        for (int i = 0; i <= top; i++) {
            if (compactedBlocks2[i] == -1) {
                if (++freeSpace == size) {
                    dst = i;
                    break;
                }
            } else {
                freeSpace = 0;
            }
        }

        while (size --> 0) {
            compactedBlocks2[dst--] = id;
        }
    }

    out << "Sum part 2: " << checksum(compactedBlocks2) << "\n";

    return 0;
}

long long checksum(const QList<int> &blocks) {
    long long sum = 0;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] != -1) {
            sum += i * blocks[i];
        }
    }

    return sum;
}
