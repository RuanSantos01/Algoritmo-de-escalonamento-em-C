#include <stdio.h>

// Protótipos das funções
int* waiting_time(int processos[][2], int qnt_processos);
int* turn_around_time(int processos[][2], int qnt_processos);
float average_wt(int processos[][2], int qnt_processos);
float average_tat(int processos[][2], int qnt_processos);

int main() {
    // Lista de todos os processos
    int processos[100][2]; // matriz para armazenar arrival_time e burst_time de até 100 processos
    int qnt_processos;
    printf("Qnt de Processos: ");
    scanf("%d", &qnt_processos);
    for (int i = 0; i < qnt_processos; i++) {
        printf("Arrival Time: ");
        scanf("%d", &processos[i][0]);
        printf("Burst Time: ");
        scanf("%d", &processos[i][1]);
    }

    /*
    Estrutura do Processo
        [ [arrival_time, burst_time] ]
    */

    // Cabeçalho da tabela
    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n\n");

    // Cálculo dos tempos de espera (waiting time) e de resposta (turn-around time)
    int* wt = waiting_time(processos, qnt_processos);
    int* tat = turn_around_time(processos, qnt_processos);
    float avg_wt = average_wt(processos, qnt_processos);
    float avg_tat = average_tat(processos, qnt_processos);

    // Completion Time = Turn Around Time + Arrival Time
    for (int proc = 0; proc < qnt_processos; proc++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc, processos[proc][1], processos[proc][0], wt[proc], tat[proc], tat[proc] + processos[proc][0]);
    }

    printf("Average Waiting Time : %.2f\n", avg_wt);
    printf("Average Turn-Around Time: %.2f\n", avg_tat);

    return 0;
}

// Calcular Waiting Time
int* waiting_time(int processos[][2], int qnt_processos) {
    // Definindo a quantidade tempos de serviço de cada processo baseado na quantidade de processos
    static int tempo_servico[100];
    for (int i = 0; i < qnt_processos; i++) {
        tempo_servico[i] = 0;
    }
    // O tempo de serviço é a soma de todos os BurstTime dos Processos anteriores
    tempo_servico[0] = 0;

    // Definindo tamanho da waiting list
    static int wt[100];

    for (int x = 1; x < qnt_processos; x++) {
        tempo_servico[x] = (tempo_servico[x - 1] + processos[x - 1][1]);
        wt[x] = tempo_servico[x] - processos[x][0];
        if (wt[x] < 0) {
            wt[x] = 0;
        }
    }
    return wt;
}

// Definindo a função de turn around time
int* turn_around_time(int processos[][2], int n){
    int* tat = (int*) malloc(n * sizeof(int)); // Turn around time
    int* wt = waiting_time(processos, n);
    for (int x = 0; x < n; x++){
        tat[x] = processos[x][1] + wt[x];
    }
    return tat;
}

// Calcular média do waiting time
float average_wt(int processos[][2], int n){
    int qnt_proc = n;
    int* wt = waiting_time(processos, n);
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += wt[i];
    }
    return ((float)sum / qnt_proc);
}

// Calcular média do turn around time
float average_tat(int processos[][2], int n){
    int qnt_proc = n;
    int* tat = turn_around_time(processos, n);
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += tat[i];
    }
    return ((float)sum / qnt_proc);
}
