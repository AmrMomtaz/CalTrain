#include <pthread.h>

struct station {
    pthread_mutex_t mutex;
    pthread_cond_t trainHasArrived;
    pthread_cond_t trainReadyToGo;
    int passengersWaiting;
    int seatsAvailable;
    int passengersReady;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);