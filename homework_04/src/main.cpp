#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Використання: " << argv[0] << " <шлях_до_файлу>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Помилка: не вдалося відкрити файл " << argv[1] << std::endl;
        return 1;
    }

    // Параметри робота (як у завданні)
    const double TICKS_PER_REVOLUTION = 1024.0;
    const double WHEEL_RADIUS_M = 0.3;
    const double WHEELBASE_M = 1.0;
    const double PI = std::acos(-1.0);
    const double DIST_PER_TICK = 2.0 * PI * WHEEL_RADIUS_M / TICKS_PER_REVOLUTION;

    // Початковий стан
    long prev_timestamp = 0;
    long prev_fl_ticks = 0;
    long prev_fr_ticks = 0;
    long prev_bl_ticks = 0;
    long prev_br_ticks = 0;

    double x = 0.0;
    double y = 0.0;
    double theta = 0.0;

    // Читаємо перший рядок (стартовий стан, не виводимо)
    if (!(infile >> prev_timestamp >> prev_fl_ticks >> prev_fr_ticks >> prev_bl_ticks >> prev_br_ticks)) {
        std::cerr << "Помилка: порожній або некоректний файл" << std::endl;
        return 1;
    }

    // Обробка всіх наступних рядків
    long curr_timestamp, curr_fl, curr_fr, curr_bl, curr_br;
    while (infile >> curr_timestamp >> curr_fl >> curr_fr >> curr_bl >> curr_br) {
        // Крок 1: Delta імпульсів
        long d_fl = curr_fl - prev_fl_ticks;
        long d_fr = curr_fr - prev_fr_ticks;
        long d_bl = curr_bl - prev_bl_ticks;
        long d_br = curr_br - prev_br_ticks;

        // Крок 2: Усереднення по бортах
        double d_left_ticks = (d_fl + d_bl) / 2.0;
        double d_right_ticks = (d_fr + d_br) / 2.0;

        // Крок 3: Перетворення в метри
        double dL = d_left_ticks * DIST_PER_TICK;
        double dR = d_right_ticks * DIST_PER_TICK;

        // Крок 4: Відстань центру та поворот
        double d = (dL + dR) / 2.0;
        double dtheta = (dR - dL) / WHEELBASE_M;

        // Крок 5: Midpoint integration
        double theta_mid = theta + dtheta / 2.0;
        x += d * std::cos(theta_mid);
        y += d * std::sin(theta_mid);
        theta += dtheta;

        // Вивід у потрібному форматі
        std::cout << curr_timestamp << " " << x << " " << y << " " << theta << std::endl;

        // Оновлюємо попередні значення
        prev_timestamp = curr_timestamp;
        prev_fl_ticks = curr_fl;
        prev_fr_ticks = curr_fr;
        prev_bl_ticks = curr_bl;
        prev_br_ticks = curr_br;
    }

    return 0;
}