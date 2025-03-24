#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

double calculate_f(double x, double epsilon, int* terms) {
    double sum = 0.0;
    double term;
    int k = 0;
    do {
        term = (pow(-1, k) * pow(x, 2 * k + 1)) / factorial(2 * k);
        sum += term;
        k++;
    } while (fabs(term) >= epsilon);
    *terms = k;
    return sum;
}

void taskA() {
    double xn, xk, dx;
    printf("\n--- Задание 1: Вычисление функции через ряд Тейлора ---\n");
    printf("Введите xn (начало интервала): ");
    scanf("%lf", &xn);
    printf("Введите xk (конец интервала): ");
    scanf("%lf", &xk);
    printf("Введите dx (шаг): ");
    scanf("%lf", &dx);

    printf("\nРезультаты:\n");
    printf("------------------------------------------------------------\n");
    printf("|   x   |  f(x)  | eps1 |  f1(x)  | terms1 | eps2   |  f2(x)  | terms2 |\n");
    printf("------------------------------------------------------------\n");

    for (double x = xn; x <= xk; x += dx) {
        double exact_value = x * cos(x);
        int terms1, terms2;
        double f1 = calculate_f(x, 0.1, &terms1);
        double f2 = calculate_f(x, 0.000001, &terms2);

        printf("| %5.2f | %6.3f | 0.1  | %6.3f  | %6d | 1e-6  | %7.5f | %6d |\n",
            x, exact_value, f1, terms1, f2, terms2);
    }
    printf("------------------------------------------------------------\n");
}

void taskB() {
    double a, epsilon;
    int max_iter;
    printf("\n--- Задание 2: Вычисление кубического корня ---\n");
    printf("Введите число a: ");
    scanf("%lf", &a);
    printf("Введите точность epsilon: ");
    scanf("%lf", &epsilon);
    printf("Введите максимальное число итераций: ");
    scanf("%d", &max_iter);

    double x_prev = a / 3.0;
    double x_next;
    int iter = 0;
    double difference;

    printf("\nИтерации:\n");
    printf("------------------------------------------------\n");
    printf("| Итерация |     x_n     |     x_{n+1}     | Разница |\n");
    printf("------------------------------------------------\n");

    do {
        x_next = (2.0 / 3.0) * (x_prev + a / (2.0 * x_prev * x_prev));
        difference = fabs(x_next - x_prev);

        printf("| %8d | %11.8f | %11.8f | %7.2e |\n",
            iter, x_prev, x_next, difference);

        x_prev = x_next;
        iter++;
    } while (difference >= epsilon && iter < max_iter);

    printf("------------------------------------------------\n");
    printf("\nРезультат: \n");
    printf("Кубический корень из %.6f = %.8f\n", a, x_next);
    printf("Проверка: %.8f^3 = %.8f\n", x_next, x_next * x_next * x_next);
    printf("Итераций выполнено: %d\n", iter);
}

void taskC() {
    int n;
    printf("\n--- Задание 3: Нахождение наименьшего числа в последовательности ---\n");
    printf("Введите натуральное число n: ");
    scanf("%d", &n);

    double min_value = INFINITY;
    int min_k = 0;

    printf("\nПоследовательность чисел:\n");
    printf("-------------------------\n");
    printf("|  k  |      Значение      |\n");
    printf("-------------------------\n");

    for (int k = 1; k <= n; k++) {
        double current_value = pow(k, 3) * sin(n + (double)k / n);
        printf("| %3d | %17.8f |\n", k, current_value);

        if (current_value < min_value) {
            min_value = current_value;
            min_k = k;
        }
    }

    printf("-------------------------\n");
    printf("\nРезультат:\n");
    printf("Наименьшее значение: %.8f\n", min_value);
    printf("Достигается при k = %d\n", min_k);
}

void taskD() {
    int n;
    printf("\n--- Задание 4: Вычисление суммы произведений последовательностей ---\n");
    printf("Введите натуральное число n: ");
    scanf("%d", &n);

    double* a = (double*)malloc(n * sizeof(double));
    double* b = (double*)malloc(n * sizeof(double));

    if (a == NULL || b == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    a[0] = b[0] = 1.0;
    double sum = a[0] * b[0];

    for (int k = 1; k < n; k++) {
        a[k] = 0.5 * (sqrt(b[k - 1]) + 0.5 * a[k - 1]);
        b[k] = 2 * pow(a[k - 1], 2) + b[k - 1];
        sum += a[k] * b[k];
    }

    printf("\nРезультат:\n");
    printf("Сумма произведений a_i*b_i: %.8f\n", sum);

    free(a);
    free(b);
}

void taskE() {
    double epsilon;
    printf("\n--- Задание 5: Проверка замечательных пределов ---\n");
    printf("Введите точность e: ");
    scanf("%lf", &epsilon);

    printf("\nа) Первый замечательный предел:\n");
    printf("lim(x->0) sin(x)/x = 1\n");
    double x = 1.0;
    int count_a = 0;
    while (fabs(sin(x) / x - 1.0) >= epsilon) {
        printf("x = %.15f, значение = %.15f\n", x, sin(x) / x);
        x /= 2.0;
        count_a++;
    }
    printf("Достигнута точность %.15f при x = %.15f\n", fabs(sin(x) / x - 1.0), x);
    printf("Количество итераций: %d\n", count_a);

    printf("\nб) Второй замечательный предел:\n");
    printf("lim(n -> *бесконечность*) (1 + 1/n)^n = e\n");
    int n = 1;
    int count_b = 0;
    double e = exp(1.0);
    while (fabs(pow(1.0 + 1.0 / n, n) - e) >= epsilon) {
        printf("n = %d, значение = %.15f\n", n, pow(1.0 + 1.0 / n, n));
        n++;
        count_b++;
    }
    printf("Достигнута точность %.15f при n = %d\n", fabs(pow(1.0 + 1.0 / n, n) - e), n);
    printf("Количество итераций: %d\n", count_b);
}

int main() {
    setlocale(LC_ALL, "rus");
    int choice;
    do {
        printf("\n=== Меню ===\n");
        printf("1. Задание 1: Ряд Тейлора для x*cos(x)\n");
        printf("2. Задание 2: Вычисление кубического корня\n");
        printf("3. Задание 3: Наименьшее число в последовательности\n");
        printf("4. Задание 4: Сумма произведений последовательностей\n");
        printf("5. Задание 5: Проверка замечательных пределов\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: taskA(); break;
        case 2: taskB(); break;
        case 3: taskC(); break;
        case 4: taskD(); break;
        case 5: taskE(); break;
        case 0: printf("Выход...\n"); break;
        default: printf("Ошибка: такого пункта нет.\n");
        }
    } while (choice != 0);

    return 0;
}