#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <compare>

struct Vec2 {
    long long x, y;

    std::strong_ordering operator<=>(const Vec2 &b) const = default;
    Vec2 operator+(const Vec2 &b) const { return {x + b.x, y + b.y}; }
    Vec2 operator*(long long s) const { return {x * s, y * s}; }
};

struct Machine {
    Vec2 a, b;

    Vec2 prize;
};

long long solve(const QList<Machine> &machines, Vec2 offset = {0, 0});

int main() {
    QTextStream out(stdout);

    QFile file("input");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "Cannot open input";
        return 1;
    }

    QTextStream in(&file);

    QList<Machine> machines;
    while (!in.atEnd()) {
        auto readVec2 = [&in] () {
            QStringList parts = in.readLine().split(": ")[1].split(", ");
            return Vec2(parts[0].sliced(2).toInt(), parts[1].sliced(2).toInt());
        };

        Machine machine;
        machine.a = readVec2();
        machine.b = readVec2();
        machine.prize = readVec2();
        in.readLine(); // empty line

        machines.append(machine);
    }

    out << "Part 1: " << solve(machines) << "\n";
    long long offset = 10'000'000'000'000;
    out << "Part 2: " << solve(machines, {offset, offset}) << "\n";

    return 0;
}

long long solve(const QList<Machine> &machines, Vec2 offset) {
    long long sum = 0;
    for (const Machine &machine: machines) {
        Vec2 offsetPrice = machine.prize + offset;
        long long aPresses = (offsetPrice.x * machine.b.y - offsetPrice.y * machine.b.x) / (machine.a.x * machine.b.y - machine.a.y * machine.b.x);
        long long bPresses = (machine.a.x * offsetPrice.y - machine.a.y * offsetPrice.x) / (machine.a.x * machine.b.y - machine.a.y * machine.b.x);

        if (machine.a * aPresses + machine.b * bPresses == offsetPrice) {
            sum += 3 * aPresses + bPresses;
        }
    }

    return sum;
}
