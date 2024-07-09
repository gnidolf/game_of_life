#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HIGHT 25

#define BACKGROUND ' '
#define CELL '#'

void init_grid(int matrix1[HIGHT][WIDTH]);
void gen_next(int matrix1[HIGHT][WIDTH], int matrix2[HIGHT][WIDTH]);
int sum_neighbours(int matrix1[HIGHT][WIDTH], int i, int j);
int solution(int matrix1[HIGHT][WIDTH], int sum, int i, int j);
void print_grid(int matrix1[HIGHT][WIDTH]);
void swap_matrix(int matrix1[HIGHT][WIDTH], int matrix2[HIGHT][WIDTH]);

int main() {
    int matrix1[HIGHT][WIDTH], matrix2[HIGHT][WIDTH], flag = 0;
    int speed = 1000000;
    init_grid(matrix1);
    if (!freopen("/dev/tty", "r", stdin)) {
        printf("n/a");
        flag = 1;
    }
    initscr();
    nodelay(stdscr, true);
    while (flag != 1) {
        if (getch() == 'a') {
            if ((speed -= 500000) < 200000) {
                speed = 200000;
            }
        }
        if (getch() == 'z') {
            speed += 500000;
        }
        usleep(speed);
        clear();
        gen_next(matrix1, matrix2);
        print_grid(matrix1);

        swap_matrix(matrix1, matrix2);
        if (getch() == 'q') {
            flag = 1;
        }
    }
    endwin();
    return 0;
}

void gen_next(int matrix1[HIGHT][WIDTH], int matrix2[HIGHT][WIDTH]) {
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int sum = sum_neighbours(matrix1, i, j);
            matrix2[i][j] = solution(matrix1, sum, i, j);
        }
    }
}

void init_grid(int matrix1[HIGHT][WIDTH]) {
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }
}

int sum_neighbours(int matrix1[HIGHT][WIDTH], int i, int j) {
    int sum = 0;

    int i_minus = i - 1;
    int j_minus = j - 1;
    int i_plus = i + 1;
    int j_plus = j + 1;

    if (i_minus < 0) {
        i_minus = HIGHT - 1;
    }
    if (j_minus < 0) {
        j_minus = WIDTH - 1;
    }
    if (i_plus > HIGHT - 1) {
        i_plus = i_plus % HIGHT;
    }
    if (j_plus > WIDTH - 1) {
        j_plus = j_plus % WIDTH;
    }

    sum += matrix1[i_minus][j_minus];
    sum += matrix1[i_minus][j];
    sum += matrix1[i_minus][j_plus];
    sum += matrix1[i][j_plus];
    sum += matrix1[i_plus][j_plus];
    sum += matrix1[i_plus][j];
    sum += matrix1[i_plus][j_minus];
    sum += matrix1[i][j_minus];

    return sum;
}

int solution(int matrix1[HIGHT][WIDTH], int sum, int i, int j) {
    int sol = 0;
    if (sum == 3 && matrix1[i][j] == 0) {
        sol = 1;
    } else if ((sum == 2 || sum == 3) && matrix1[i][j] == 1) {
        sol = 1;
    } else {
        sol = 0;
    }

    return sol;
}

void print_grid(int matrix1[HIGHT][WIDTH]) {
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (matrix1[i][j] == 1) {
                printw("%c", CELL);
            } else {
                printw("%c", BACKGROUND);
            }
        }
        printw("\n");
    }
}

void swap_matrix(int matrix1[HIGHT][WIDTH], int matrix2[HIGHT][WIDTH]) {
    for (int i = 0; i < HIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix1[i][j] = matrix2[i][j];
        }
    }
}
