#include "polv_packet.h"

/**

   +-------------+  next      
   |   element   |------->
   +-------------+

*/
struct polv_queue_item {
	struct polv_packet* packet;
	struct polv_queue_item* next;
};


/**

  +---------+   +---------+              +--------+
  |  front  |-->|         |--> . . . --> |  back  |
  +---------+   +---------+              +--------+

*/

struct polv_queue {
	struct polv_queue_item* front;
	struct polv_queue_item* back;
};



struct polv_queue* polv_queue_init(void);
void polv_queue_destroy(struct polv_queue*);

struct polv_queue_item* polv_queue_item_init(void);
void polv_queue_item_destroy(struct polv_queue_item*);

struct polv_packet* polv_dequeue(struct polv_queue*);
void polv_enqueue(struct polv_queue*, struct polv_packet*);

int polv_empty(struct polv_queue*);
