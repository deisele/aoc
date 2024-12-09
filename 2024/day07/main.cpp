#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>

bool checkRow(long long target, const QList<int> &numbers, int numOperators);
int powi(int base, int exp);

int main() {
    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);

    long long sumPart1 = 0;
    long long sumPart2 = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(": ");

        long long target = parts[0].toLongLong();
        QList<int> numbers;
        for (const QString &part: parts[1].split(" ")) {
            numbers.append(part.toInt());
        }

        sumPart1 += checkRow(target, numbers, 2) * target;
        sumPart2 += checkRow(target, numbers, 3) * target;
    }

    out << "Sum part 1: " << sumPart1 << "\n";
    out << "Sum part 2: " << sumPart2 << "\n";

    return 0;
}

bool checkRow(long long target, const QList<int> &numbers, int numOperators) {
    for (int i = 0; i < powi(numOperators, numbers.size() - 1); i++) {
        int operators = i;
        long long result = numbers[0];

        for (int j = 1; j < numbers.size(); j++) {
            switch (operators % numOperators) {
                case 0:
                    result += numbers[j];
                    break;

                case 1:
                    result *= numbers[j];
                    break;

                case 2:
                    result = (QString::number(result) + QString::number(numbers[j])).toLongLong();
                    break;
            }

            operators /= numOperators;
        }

        if (result == target) {
            return true;
        }
    }

    return false;
}

int powi(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }

    return result;
}
