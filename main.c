#include <stdio.h>

struct Proceso
{
    int pid;
    int ts;
    int tiempoRetorno;
};

void mostrarLista(struct Proceso proc[],int tamanio){

    printf("***Lista de procesos***\n");
    printf("|PID | TS| TR\n");

    for (int i = 0; i < tamanio; i++)
    {
        printf("| %d | %d | %d \n", proc[i].pid, proc[i].ts,proc[i].tiempoRetorno);
    }
}

 float tiempoRetornoPromedio(struct Proceso proc[],int tamanio){
    int suma=0;
    for (int i = 0; i < tamanio; i++)
    {
        suma += proc[i].tiempoRetorno;
    }
    return ((float)suma / tamanio);
}

float tiempoEsperaPromedio(struct Proceso proc[],struct Proceso copia[],int tamanio){
    int suma=0;
    for (int i = 0; i < tamanio; i++)
    {
        suma += proc[i].tiempoRetorno-copia[i].ts;
    }
    return ((float)suma / tamanio);
}


int main(int argc, char const *argv[])
{
    const int TAMANIO = 10;
    struct Proceso procesos [TAMANIO];
    
    //Hardcodeo de tiempo de servicio requerido de los procesos
    procesos[0].ts = 10;
    procesos[1].ts = 3;
    procesos[2].ts = 5;
    procesos[3].ts = 14;
    procesos[4].ts = 8;
    procesos[5].ts = 4;
    procesos[6].ts = 7;
    procesos[7].ts = 18;
    procesos[8].ts = 1;
    procesos[9].ts = 39;


    int quantum = 4;
    int tiempoIntercambio = quantum / 4;
    int reloj = 0;
    int nPAnt=-1;

    int sumaTiempoServicio=0;
    for (int i = 0; i < TAMANIO; i++)
    {
        sumaTiempoServicio += procesos[i].ts;
        procesos[i].pid = i;//le pongo el id
        procesos[i].tiempoRetorno=0;//por las dudas inicializo el tiempo de retono en 0
    }

    //copia de procesos
    struct Proceso copiaProcesos [TAMANIO];
    for (int i = 0; i < TAMANIO; i++) {
        copiaProcesos[i].pid = procesos[i].pid;
        copiaProcesos[i].ts = procesos[i].ts;
        copiaProcesos[i].tiempoRetorno = procesos[i].tiempoRetorno;
    }


    mostrarLista(procesos,TAMANIO);

    while (sumaTiempoServicio>0){

        for (int i = 0; i < TAMANIO; i++){

            if (procesos[i].ts>0){
                if (procesos[i].pid != nPAnt && nPAnt != -1)
                {
                    printf("{Call a Scheduler de Corto plazo para que quite el proceso}\n");
                    //reloj += tiempoIntercambio/2;
                }

                if(procesos[i].ts>quantum){
                    if(procesos[i].pid != nPAnt){
                        printf("{Call a Scheduler de Corto plazo para que inserte el proceso}\n");
                        //reloj += tiempoIntercambio/2;
                    }

                    printf("{Ejecutando proceso %d por %d unidades de tiempo}\n",procesos[i].pid,quantum);
                    procesos[i].ts -= quantum;
                    sumaTiempoServicio -= quantum;
                    reloj += quantum;
                }else{ //TS menor que el quantum
                    if(procesos[i].pid != nPAnt){
                        printf("{Call a Scheduler de Corto plazo para que inserte el proceso}\n");
                    }
                    //finaliza
                    printf("{Ejecutando proceso %d por %d unidades de tiempo}\n",procesos[i].pid,procesos[i].ts);
                    reloj += procesos[i].ts;
                    procesos[i].tiempoRetorno=reloj;
                    sumaTiempoServicio -= procesos[i].ts;
                    procesos[i].ts = 0;
                    printf("{Proceso %d finalizado}\n",procesos[i].pid);
                }
                
                nPAnt = procesos[i].pid;


            }
        }
        mostrarLista(procesos,TAMANIO);
        
    }
    
    printf("Reloj: %d \n",reloj);
    printf("Tiempo de retorno promedio: %f \n",tiempoRetornoPromedio(procesos,TAMANIO));
    printf("Tiempo de espera promedio: %f \n",tiempoEsperaPromedio(procesos,copiaProcesos,TAMANIO));
    
    return 0;
}
