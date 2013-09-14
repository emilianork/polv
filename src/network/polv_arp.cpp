#include "network/polv_arp.h"

#include "tools/polv_tools.h"

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
	const u_char* htype;
	htype = polv_oct(HTYPE,HTYPE_LEN,packet);
	
	return htype;
}

const u_char* polv_arp_ptype(const u_char* packet)
{
    const u_char* ptype;
	ptype = polv_oct(PTYPE,PTYPE_LEN,packet);

	return ptype;
}
const u_char* polv_arp_hlen(const u_char* packet)
{
	const u_char* hlen;
	hlen = polv_oct(HLEN, HLEN_LEN,packet);

	return hlen;
	
}
const u_char* polv_arp_plen(const u_char* packet)
{
	const u_char* plen;
	plen = polv_oct(PLEN, PLEN_LEN,packet);

	return plen;
}
const u_char* polv_arp_oper(const u_char* packet)
{
	const u_char* oper;
	oper = polv_oct(OPER,OPER_LEN,packet);
	
	return oper;
}
const u_char* polv_arp_sha(const u_char* packet)
{
	const u_char* sha;
	sha = polv_oct(SHA,SHA_LEN,packet);

	return sha;
}
const u_char* polv_arp_spa(const u_char* packet)
{
	const u_char* spa;
	spa = polv_oct(SPA,SPA_LEN,packet);

	return spa;
}
const u_char* polv_arp_tha(const u_char* packet)
{
	const u_char* tha;
	tha = polv_oct(THA,THA_LEN,packet);
	
	return tha;
}
const u_char* polv_arp_tpa(const u_char* packet)
{
	const u_char* tpa;
	tpa = polv_oct(TPA,TPA_LEN,packet);

	return tpa;
}
