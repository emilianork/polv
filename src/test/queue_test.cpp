#include "queue/polv_queue.h"
#include "packet/polv_packet.h"

#include "test/test.h"
#include "test/queue_test.h"

#include "tools/polv_boolean.h"

#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <string>
#include <iostream>

short results = 0;
short total = 2;

void test_dequeue_empty() 
{
	struct polv_queue* queue;

	queue = polv_queue_init();

	results += assert(polv_dequeue(queue) == NULL, "Dequeue Empty");
	
	return;
}

void test_dequeue() 
{	
	int random,random_enqueue, random_dequeue;

	random = (rand() % 100) + 1;

	int i, j;

	for(i = 0; i < random; i++) {
		
		random_enqueue = (rand() % 100) + 1;
		random_dequeue = rand() % random_enqueue;
		
		struct polv_queue* queue;
		queue = polv_queue_init();

		struct polv_queue_item* item;

		for (j = 0; j < random_enqueue; j++) {
			polv_enqueue(queue,NULL);
			if (random_dequeue == j) 
				item = queue->back;
		}
		
		for (j = 0; j < random_dequeue; j++) {
			polv_dequeue(queue);
		}
		
		if (queue->front != item) {
			results += assert(FALSE, "Dequeue Elements");
			return;
		} 
		polv_queue_destroy(queue);
	}

	results += assert(TRUE, "Dequeue Elements");

	return;
	
}

void test_queue() 
{
	srand(time(NULL));

	test_dequeue_empty();
	test_dequeue();
	
	printf("\tResultados: %d\n", results);
	printf("\tTotal: %d\n", total);
}
