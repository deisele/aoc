#include <QFile>
#include <QString>
#include <QRegularExpression>
#include <iostream>

int main() {
    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open input";
        return 1;
    }

    QString input = file.readAll();

    QRegularExpression command(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");

    bool enabled = true;
    int sumPart1 = 0;
    int sumPart2 = 0;
    for (QRegularExpressionMatch match: command.globalMatch(input)) {
        if (match.captured().startsWith("mul")) {
            int product = match.captured(1).toInt() * match.captured(2).toInt();
            sumPart1 += product;
            if (enabled) {
                sumPart2 += product;
            }
        } else {
            enabled = (match.captured() == "do()");
        }
    }

    std::cout << "Sum part 1: " << sumPart1 << "\n";
    std::cout << "Sum part 2: " << sumPart2 << "\n";

    return 0;
}
