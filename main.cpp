#include <stdio.h>
#include <math.h>
#include <time.h>

#define NO_OF_SERVER 3
// #define DT 0.001

class system_state
{
public:
    int No_of_server = 1;
    int No_of_customer = 0;
    int total_customer = 0;
    double ave_customer = 0.0;
    double dt = 0.01;
    double sysytem_time = 0.0;
    double end_time = 1000;
};

class server_state
{
public:
    int in_servise = 0;
    double servise_time = 0;
    double servise_rate = 10;
};

class que_state
{
public:
    int que_value;
    double arrival_rate = 9;
};

int main()
{
    //変数を定義，初期設定
    system_state system;
    server_state server;
    que_state que;
    double index;

    ///////////////////実験データ記録ファイルのための準備///////////
    FILE *Qrec;
    Qrec = fopen("querec.txt", "w");
    fprintf(Qrec, "mu %f,lammda %f,c %d,dt %f\n", server.servise_rate, que.arrival_rate, system.No_of_server, system.dt);
    fprintf(Qrec, "time,custemer in system\n");

    srand(time(NULL));
    while (1)
    {
        index = (double)rand() / RAND_MAX;
        if (index <= que.arrival_rate * system.dt)
        {
            system.No_of_customer = system.No_of_customer + 1;
        }
        index = (double)rand() / RAND_MAX;
        if (index <= server.servise_rate * system.dt * system.No_of_server && system.No_of_customer > 0)
        {
            system.No_of_customer = system.No_of_customer - 1;
        }

        system.sysytem_time = system.sysytem_time + system.dt;
        system.total_customer = system.total_customer + system.No_of_customer;
        system.ave_customer = system.total_customer / system.sysytem_time;

        fprintf(Qrec, "%f,%f", system.sysytem_time, system.ave_customer);
        printf("%f,%f\n", system.sysytem_time, system.ave_customer);

        if (system.sysytem_time >= system.end_time)
        {
            break;
        }
    }

    return 0;
}
