#include <pthread.h>
#include "caltrain.h"

#include <stdio.h>
void
station_init(struct station *station)
{
    pthread_mutex_init(&station->mutex,NULL);
    pthread_cond_init(&station->trainHasArrived,NULL);
    pthread_cond_init(&station->trainReadyToGo,NULL);
    station->passengersWaiting = 0;
    station->seatsAvailable = 0;
    station->passengersReady = 0;
}

void
station_load_train(struct station *station, int count)
{
    if (count > 0 && station->passengersWaiting > 0){
        pthread_mutex_lock(&station->mutex);
        station->seatsAvailable = count;
        pthread_cond_broadcast(&station->trainHasArrived);
        pthread_cond_wait(&station->trainReadyToGo,&station->mutex);
        station->seatsAvailable=0;
        pthread_mutex_unlock(&station->mutex);
    }
}

void
station_wait_for_train(struct station *station)
{
    station->passengersWaiting++;
    pthread_mutex_lock(&station->mutex);
    while (station->seatsAvailable<1) {
        pthread_cond_wait(&station->trainHasArrived, &station->mutex);
    }
    station->seatsAvailable--;
    station->passengersWaiting--;
    station->passengersReady--;
    pthread_mutex_unlock(&station->mutex);
}

void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->mutex);
    station->passengersReady++;
    if (!(station->seatsAvailable>0 && station->passengersWaiting > 0) && station->passengersReady == 0)
        pthread_cond_signal(&station->trainReadyToGo);
    pthread_mutex_unlock(&station->mutex);
}