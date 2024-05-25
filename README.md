## **a)** Implemente uma solução utilizando Mutex e comparece com a anterior. O que mudou? Por quê?

**Resposta:** Comparando com a versão anterior do código, a principal diferença é a adição da inicialização, bloqueio e destruição do mutex (pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy). Isso garante que apenas uma thread por vez tenha acesso à variável sum, evitando condições de corrida.

### **Código da solução:**
```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long thread_count;
long long n;
double sum = 0.0;
pthread_mutex_t mutex;
pthread_barrier_t barrier;

void *Thread_sum(void *rank) {
    long my_rank = (long)rank;
    long long i;
    long long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    double my_sum = 0.0;
    double factor;

    if (my_first_i % 2 == 0) {
        factor = 1.0;
    } else {
        factor = -1.0;
    }

    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        my_sum += factor / (2 * i + 1);
    }

    pthread_mutex_lock(&mutex);
    sum += my_sum;
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barrier);

    return NULL;
}

int main(int argc, char *argv[]) {
    long thread;
    pthread_t *thread_handles;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <numero de threads> <n>\n", argv[0]);
        exit(1);
    }

    thread_count = strtol(argv[1], NULL, 10);
    n = strtol(argv[2], NULL, 10);
    thread_handles = malloc(thread_count * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, thread_count);

    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void *)thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);
    free(thread_handles);

    printf("Quantidade de threads: %lld\n", thread_count);
    // Corrigido o uso do operador de multiplicação e formatação correta da impressão
    printf("Valor de pi calculado: %.15f\n", 4 * sum);

    return 0;
}
```
### Print do resultado do programa:

![image](https://github.com/Felipe-N-Fonseca/Pthreads2/assets/89709011/932b55e7-c100-4733-a850-12e6886f435d)


<hr>

## **b)** No final, entregue no README do repositório uma explicação resumida sobre as diferenças entre os valores atingidos. Quais foram as causas das divergências? Por que elas aconteceram?

**Resposta:** a diferença nos valores de pi atingidos entre a versão sem mutex e a versão com mutex são, a presença de condições de corrida na versão sem mutex pode resultar em valores incorretos de sum, e consequentemente de pi. Isso ocorre porque várias threads podem tentar atualizar sum simultaneamente, causando inconsistências. Com o uso do mutex, garantimos que apenas uma thread por vez atualize sum, garantindo assim um resultado correto.
