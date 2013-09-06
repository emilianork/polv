#include "polv_queue.h"
#include "polv_boolean.h"

#include <cstdlib>
#include <iostream>

using namespace std;

struct polv_queue* polv_queue_init()
{
	struct polv_queue* queue;

	queue = (struct polv_queue*) malloc(sizeof(struct polv_queue));

	if (queue == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}
	queue->front = queue->back = NULL;
	
	return queue;
}

void polv_queue_destroy(struct polv_queue* queue)
{
	while (!polv_empty(queue)) {
		struct polv_packet* packet;
		
		packet = polv_dequeue(queue);
		polv_packet_destroy(packet);
	}
	
	return;
}

struct polv_queue_item* polv_queue_item_init()
{
	struct polv_queue_item* item;
	item = (struct polv_queue_item*) malloc(sizeof(struct polv_queue_item));
	
	if (item == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}

	item->packet = NULL;
	item->next = NULL;

	return item;
}

void polv_queue_item_destroy(struct polv_queue_item* item)
{
	free(item);
	return;
}

void polv_enqueue(struct polv_queue* queue, struct polv_packet* packet)
{
	struct polv_queue_item *item;
	
	item = polv_queue_item_init();

	item->packet = packet;
	item->next = NULL;

	if (polv_empty(queue)) {
		queue->front = item;
		queue->back = item;
	} else {
		queue->back->next = item;
		queue->back = item;
	}

	return;
}

struct polv_packet* polv_dequeue(struct polv_queue* queue)
{
	if (polv_empty(queue)) 
		return NULL;

	struct polv_packet *packet;
	struct polv_queue_item *tmp;

	packet = queue->front->packet;

	if (queue->front == queue->back) {
		tmp = queue->front;
		queue->front = queue->back = NULL;
		polv_queue_item_destroy(tmp);
	} else {
		
		tmp = queue->front;
		queue->front = tmp->next;
		
		polv_queue_item_destroy(tmp);
	}
	
	return packet;
}



int polv_empty(struct polv_queue* queue)
{
	return ((queue->front == NULL) && (queue->back == NULL));
}
