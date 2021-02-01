# philosophers

Subject on solving the dining philosophers dilemma in three different ways. Philosophers are sitting at a round table, and can either be eating, sleeping or thinking.

There are as many forks as philosophers and each philosopher needs two forks to eat. When a philosopher cannot eat for a certain amount of time, it will die. 

3 different solutions:

## philo_one
philosophers as threads and forks as mutexes.

## philo_two
philosophers as threads and forks as semaphores.

## philo_three
philosophers as processes and forks as semaphores.


## Usage
``make`` within each subdirectory, makes an executable with the same name as the directory.

``./philo_one [time_to_die(ms)] [time_to_eat(ms)] [time_to_sleep(ms)] [number_of_times_each_philosopher_must_eat]``

f.e. to start the program. Fifth argument is optional.
