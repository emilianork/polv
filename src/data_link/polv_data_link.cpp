#include "data_link/polv_data_link.h"
#include "tools/polv_tools.h"

#include <cstdlib>
#include <iostream>

const u_char etherII[2] = {6,0};
const u_char len[2] = {5,220};

using namespace std;

struct polv_data_link* polv_data_link_init()
{
	struct polv_data_link* data_link;

	data_link = (struct polv_data_link*) malloc(sizeof(struct polv_data_link));

	if (data_link == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}
	
	data_link->dst = data_link->src =  data_link->ethertype = 
		data_link->dsap = data_link->ssap = data_link->control =
		data_link->org_code = NULL;

	return data_link;
}


void polv_data_link_destroy(struct polv_data_link* data_link)
{
	if (data_link->dst != NULL)
		free((u_char*)data_link->dst);
	if (data_link->src != NULL)
		free((u_char*)data_link->src);
	if (data_link->ethertype != NULL)
		free((u_char*)data_link->ethertype);
	if (data_link->dsap != NULL)
		free((u_char*)data_link->dsap);
	if (data_link->ssap != NULL)
		free((u_char*)data_link->ssap);
	if (data_link->control != NULL)
		free((u_char*)data_link->control);
	if (data_link->org_code != NULL)
		free((u_char*)data_link->org_code);
	
	free(data_link);

	return;
}

const u_char* polv_ether_dst(const u_char* packet)
{
	const u_char* dst;
	dst = polv_oct(DST,MAC_ADDRESS,packet);
	
	return dst;
}

const u_char* polv_ether_src(const u_char* packet)
{
	const u_char* src;
	src = polv_oct(SRC,MAC_ADDRESS,packet);

	return src;
}

enum polv_ethertype polv_ether_ver(const u_char* packet)
{

	const u_char* type;
	type = polv_oct(TYPE,TYPE_LEN,packet);
	if (polv_compare(type,etherII,TYPE_LEN) == 1) {
		return VII;
	} else {
		if (polv_compare(type,len,TYPE_LEN) == -1) {
			return V802;
		} else {
			/* Protocolo de capa de enlace, desconocido. */
			return UNKNOWN_LINK;
		}
	}
}

const u_char* polv_ethertype(const u_char* packet, enum polv_ethertype etherver)
{
	const u_char* ethertype;

	switch (etherver) {
	case VII:
		ethertype = polv_oct(TYPE,TYPE_LEN,packet);
		break;
	case V802:
		ethertype = polv_oct(ETHERTYPE,TYPE_LEN,packet);
		break;
	case UNKNOWN_LINK:
		ethertype = NULL;
	}

	return ethertype;
}


const u_char* polv_dsap(const u_char* packet)
{
	const u_char* dsap;
	dsap = polv_oct(DSAP,DSAP_LEN,packet);

	return dsap;
}

const u_char* polv_ssap(const u_char* packet)
{
	const u_char* ssap;
	ssap = polv_oct(SSAP,SSAP_LEN,packet);

	return ssap;	
}

const u_char* polv_control(const u_char* packet)
{
	const u_char* control;
	control = polv_oct(CONTROL,CONTROL_LEN,packet);

	return control;
}

const u_char* polv_org_code(const u_char* packet)
{
	const u_char* org_code;
	org_code = polv_oct(ORG_CODE,ORG_CODE_LEN,packet);

	return org_code;
}

struct polv_next_layer* polv_network_packet(const u_char* packet, 
								  enum polv_ethertype etherver, int len)
{
	const u_char* header;
	int next_layer_len;
	switch (etherver) {
	case VII:
	    header = polv_oct(DSAP,len - DSAP,packet);
		next_layer_len = len - DSAP;
		break;
	case V802:
		header = polv_oct(DATA,len - DATA,packet);
		next_layer_len = len - DATA;
		break;
	}

	struct polv_next_layer* next_layer;
	next_layer = polv_next_layer_init();

	next_layer->packet = header;
	next_layer->len = next_layer_len;
	
	return next_layer;
}
