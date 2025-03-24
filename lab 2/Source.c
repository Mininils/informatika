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
    printf("\n--- ������� 1: ���������� ������� ����� ��� ������� ---\n");
    printf("������� xn (������ ���������): ");
    scanf("%lf", &xn);
    printf("������� xk (����� ���������): ");
    scanf("%lf", &xk);
    printf("������� dx (���): ");
    scanf("%lf", &dx);

    printf("\n����������:\n");
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
    printf("\n--- ������� 2: ���������� ����������� ����� ---\n");
    printf("������� ����� a: ");
    scanf("%lf", &a);
    printf("������� �������� epsilon: ");
    scanf("%lf", &epsilon);
    printf("������� ������������ ����� ��������: ");
    scanf("%d", &max_iter);

    double x_prev = a / 3.0;
    double x_next;
    int iter = 0;
    double difference;

    printf("\n��������:\n");
    printf("------------------------------------------------\n");
    printf("| �������� |     x_n     |     x_{n+1}     | ������� |\n");
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
    printf("\n���������: \n");
    printf("���������� ������ �� %.6f = %.8f\n", a, x_next);
    printf("��������: %.8f^3 = %.8f\n", x_next, x_next * x_next * x_next);
    printf("�������� ���������: %d\n", iter);
}

void taskC() {
    int n;
    printf("\n--- ������� 3: ���������� ����������� ����� � ������������������ ---\n");
    printf("������� ����������� ����� n: ");
    scanf("%d", &n);

    double min_value = INFINITY;
    int min_k = 0;

    printf("\n������������������ �����:\n");
    printf("-------------------------\n");
    printf("|  k  |      ��������      |\n");
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
    printf("\n���������:\n");
    printf("���������� ��������: %.8f\n", min_value);
    printf("����������� ��� k = %d\n", min_k);
}

void taskD() {
    int n;
    printf("\n--- ������� 4: ���������� ����� ������������ ������������������� ---\n");
    printf("������� ����������� ����� n: ");
    scanf("%d", &n);

    double* a = (double*)malloc(n * sizeof(double));
    double* b = (double*)malloc(n * sizeof(double));

    if (a == NULL || b == NULL) {
        printf("������ ��������� ������\n");
        return;
    }

    a[0] = b[0] = 1.0;
    double sum = a[0] * b[0];

    for (int k = 1; k < n; k++) {
        a[k] = 0.5 * (sqrt(b[k - 1]) + 0.5 * a[k - 1]);
        b[k] = 2 * pow(a[k - 1], 2) + b[k - 1];
        sum += a[k] * b[k];
    }

    printf("\n���������:\n");
    printf("����� ������������ a_i*b_i: %.8f\n", sum);

    free(a);
    free(b);
}

void taskE() {
    double epsilon;
    printf("\n--- ������� 5: �������� ������������� �������� ---\n");
    printf("������� �������� e: ");
    scanf("%lf", &epsilon);

    printf("\n�) ������ ������������� ������:\n");
    printf("lim(x->0) sin(x)/x = 1\n");
    double x = 1.0;
    int count_a = 0;
    while (fabs(sin(x) / x - 1.0) >= epsilon) {
        printf("x = %.15f, �������� = %.15f\n", x, sin(x) / x);
        x /= 2.0;
        count_a++;
    }
    printf("���������� �������� %.15f ��� x = %.15f\n", fabs(sin(x) / x - 1.0), x);
    printf("���������� ��������: %d\n", count_a);

    printf("\n�) ������ ������������� ������:\n");
    printf("lim(n -> *�������������*) (1 + 1/n)^n = e\n");
    int n = 1;
    int count_b = 0;
    double e = exp(1.0);
    while (fabs(pow(1.0 + 1.0 / n, n) - e) >= epsilon) {
        printf("n = %d, �������� = %.15f\n", n, pow(1.0 + 1.0 / n, n));
        n++;
        count_b++;
    }
    printf("���������� �������� %.15f ��� n = %d\n", fabs(pow(1.0 + 1.0 / n, n) - e), n);
    printf("���������� ��������: %d\n", count_b);
}

int main() {
    setlocale(LC_ALL, "rus");
    int choice;
    do {
        printf("\n=== ���� ===\n");
        printf("1. ������� 1: ��� ������� ��� x*cos(x)\n");
        printf("2. ������� 2: ���������� ����������� �����\n");
        printf("3. ������� 3: ���������� ����� � ������������������\n");
        printf("4. ������� 4: ����� ������������ �������������������\n");
        printf("5. ������� 5: �������� ������������� ��������\n");
        printf("0. �����\n");
        printf("�������� �����: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: taskA(); break;
        case 2: taskB(); break;
        case 3: taskC(); break;
        case 4: taskD(); break;
        case 5: taskE(); break;
        case 0: printf("�����...\n"); break;
        default: printf("������: ������ ������ ���.\n");
        }
    } while (choice != 0);

    return 0;
}