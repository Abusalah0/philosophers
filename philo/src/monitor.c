#include "philo.h"

int check_full(t_prog *prog)
{
    int i = 0;
    while (i < prog->input[NUM_OF_PHILO])
    {
        pthread_mutex_lock(&prog->philos[i].full);
        if (prog->philos[i].num_of_eat < prog->input[NUM_TO_EAT])
        {
            pthread_mutex_unlock(&prog->philos[i].full);
            return (0);
        }
        pthread_mutex_unlock(&prog->philos[i].full);
        i++;
    }
    return (1);
}

static int check_death(t_prog *prog)
{
    int i = 0;
    long time_since_last_eat;

    while (i < prog->input[NUM_OF_PHILO])
    {
        pthread_mutex_lock(&prog->print);
        time_since_last_eat = get_time(prog->philos[i].last_eat); // Get time since last eat

        // Check for death (starvation)
        if (prog->philos[i].alive && time_since_last_eat > prog->input[TIME_TO_DIE])
        {
            printf("%d %d died\n", get_time(prog->philos[i].start), prog->philos[i].number);
            prog->philos[i].alive = 0;
            prog->stop = 1;
            pthread_mutex_unlock(&prog->print);
            return (1);
        }

        // Check for starvation
        if (prog->philos[i].alive && time_since_last_eat > prog->input[TIME_TO_DIE])
        {
            printf("%d %d is starving!\n", get_time(prog->philos[i].start), prog->philos[i].number);
            prog->philos[i].alive = 0;
            prog->stop = 1;
            pthread_mutex_unlock(&prog->print);
            return (1);
        }

        pthread_mutex_unlock(&prog->print);
        i++;
    }
    return (0);
}

void *monitor(void *ptr)
{
    t_prog *prog = (t_prog *)ptr;

    while (1)
    {
        // Check if all philosophers are full
        if (check_full(prog))
        {
            pthread_mutex_lock(&prog->print);
            printf("All philosophers are full\n");
            pthread_mutex_unlock(&prog->print);
            prog->stop = 1;
            return (NULL);
        }
        
        // Check for philosopher death or starvation
        if (check_death(prog))
        {
            prog->stop = 1;
            return (NULL);
        }

        usleep(1000); // Sleep for 1 ms to avoid busy-waiting
    }
    return (NULL);
}
