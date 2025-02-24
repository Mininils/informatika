#include <stdio.h>
#include <math.h>
#include <locale.h>

int taskA() {
    int a, b;
    double c;

    printf("������� ���������: ");
    scanf("%d", &a);

    printf("������� �����������: ");
    scanf("%d", &b);

    printf("������� ����������� �����: ");
    scanf("%lf", &c);

    double val1 = (double)a / b;
    double val2 = sqrt(c);

    double app1 = 0.765;
    double app2 = 5.57;

    double err1 = fabs(val1 - app1);
    double err2 = fabs(val2 - app2);

    double rel1 = (err1 / val1) * 100;
    double rel2 = (err2 / val2) * 100;

    printf("\n������ ��������:\n");
    printf("1) %d/%d = %.6f\n", a, b, val1);
    printf("2) sqrt(%.6f) = %.6f\n", c, val2);

    printf("\n���������� �����������:\n");
    printf("1) %.6f\n", err1);
    printf("2) %.6f\n", err2);

    printf("\n������������� ����������� (� %%):\n");
    printf("1) %.6f\n", rel1);
    printf("2) %.6f\n", rel2);

    if (rel1 < rel2) {
        printf("\n����� ������ ���������: %d/%d = %.3f\n", a, b, val1);
    }
    else {
        printf("\n����� ������ ���������: sqrt(%.3f) = %.3f\n", c, val2);
    }

}

int taskB() {
    double num, err;

    printf("\n������� �����: ");
    scanf("%lf", &num);

    printf("������� ���������� �����������: ");
    scanf("%lf", &err);

   
    int places = 0;
    while (err < 1) {
        err *= 10;
        places++;
    }

    double rounded = round(num * pow(10, places)) / pow(10, places);

    printf("\n����������� �����: %.*f\n", places, rounded);
    printf("���������� ����������� ����������: %.6f\n", err / pow(10, places));

}

int taskC() {
    double num;

    printf("\n������� ������������ ����� (��� ����� ������): ");
    scanf("%lf", &num);

    
    double abs_err = 0.5 * pow(10, -2); 

    
    double rel_err = (abs_err / num) * 100;

    printf("\n���������� ���������� �����������: %.6f\n", abs_err);
    printf("���������� ������������� �����������: %.6f%%\n", rel_err);

}

int main() {
    setlocale(LC_ALL, "rus");

    int choice;
    printf("�������� ������� (1, 2 ��� 3): ");
    scanf("%d", &choice);

    if (choice == 1) {
        taskA();
    }
    else if (choice == 2) {
        taskB();
    }
    else if (choice == 3) {
        taskC();
    }
    else {
        printf("�������� �����.\n");
    }

}