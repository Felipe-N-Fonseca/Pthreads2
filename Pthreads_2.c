void* Thread_sum(void* rank){
    long my_rank = (long) rank;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;
    
    if (my_first_i % 2 == 0){
        factor = 1.0;
    } else {
        factor = -1.0;
    }

    for (i = my_first_i; i < my_last_i; i++, factor = -factor){
        sum += factor/(2*i+1);
    }

    return NULL;
}