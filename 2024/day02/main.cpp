#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>

bool isSafe(const QList<int> &report);

int main(int argc, char *argv[]) {
    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);

    QList<QList<int>> reports;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");

        QList<int> report;
        for (const QString &part: parts) {
            report.append(part.toInt());
        }

        reports.append(report);
    }

    int safeReportsPart1 = 0;
    for (const QList<int> &report: reports) {
        if (isSafe(report)) {
            safeReportsPart1++;
        }
    }

    out << "Safe reports part 1: " << safeReportsPart1 << "\n";

    int safeReportsPart2 = 0;
    for (const QList<int> &report: reports) {
        // if the original report is safe, the modified report will also be safe, so we don't need to check it
        for (int i = 0; i < report.size(); i++) {
            QList<int> modifiedReport = report;
            modifiedReport.removeAt(i);

            if (isSafe(modifiedReport)) {
                safeReportsPart2++;
                break;
            }
        }
    }

    out << "Safe reports part 2: " << safeReportsPart2 << "\n";

    return 0;
}

bool isSafe(const QList<int> &report) {
    for (int i = 0; i < report.size() - 1; i++) {
        int diff = report[i + 1] - report[i];
        if (report[1] - report[0] < 0) {
            diff *= -1;
        }

        if (diff < 1 || diff > 3) {
            return false;
        }
    }

    return true;
}
