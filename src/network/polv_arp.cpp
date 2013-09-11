#include "polv_arp.h"

#include "polv_tools.h"

#include <cstdlib>

struct polv_arp* pol_arp_init()
{
	struct polv_arp* arp;

	arp = (struct polv_arp*) malloc(sizeof(struct polv_arp));

	arp->htype = arp->ptype = arp->hlen = arp->plen = arp->oper = arp->sha = 
		arp->spa = arp->tha = arp->tpa = NULL;

	return arp;
}

void polv_arp_destroy(struct polv_arp* arp)
{
	free((u_char*)arp->htype);
	free((u_char*)arp->ptype);
	free((u_char*)arp->hlen);
	free((u_char*)arp->plen);
	free((u_char*)arp->oper);
	free((u_char*)arp->sha);
	free((u_char*)arp->spa);
	free((u_char*)arp->tha);
	free((u_char*)arp->tpa);
	
	free(arp);
	
	return;
}

const u_char* polv_arp_htype(const u_char* packet)
{
	return NULL;
}

const u_char* polv_arp_ptype(const u_char* packet)
{
	return NULL;
}
const u_char* polv_arp_hlen(const u_char* packet)
{
	return NULL;
}
const u_char* polv_arp_plen(const u_char* packet)
{
	return NULL;
}
const u_char* polv_arp_oper(const u_char* packet)
{
	return NULL;
}
const u_char* polv_arp_sha(const u_char* packet)
{
	return NULL;
}
const u_char* polv_arp_spa(const u_char* packet)
{
	return NULL;
}
const u_char* polv_arp_tha(const u_char* packet)
{
	return NULL;
}
const u_char* polv_arp_tpa(const u_char* packet)
{
}
