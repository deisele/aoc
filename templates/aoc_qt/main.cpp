#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <csignal>

void handler(int signal) {
    Q_UNUSED(signal);
    Q_ASSERT(0);
}

int main() {
    signal(SIGABRT, &handler);

    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
    }

    return 0;
}
