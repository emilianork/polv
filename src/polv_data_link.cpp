#include "polv_data_link.h"
#include "polv_tools.h"

#include <cstdlib>
#include <iostream>

using namespace std;

struct polv_data_link* polv_data_link_init()
{
	struct polv_data_link* data_link;

	data_link = (struct polv_data_link*) malloc(sizeof(struct polv_data_link));

	if (data_link == NULL) {
		cout << "\nNo se encontro memoria disponible." << endl;
		exit(EXIT_FAILURE);
	}
	
	data_link->dst = data_link->src =  data_link->ethertype = NULL;
	
	return data_link;
}


void polv_data_link_destroy(struct polv_data_link* data_link)
{
	free(data_link);
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

	u_char* etherII = (u_char*) malloc(sizeof(u_char)*2);
	u_char* len = (u_char*) malloc(sizeof(u_char)*2);

	etherII[0] = 6;
	etherII[1] = 0;

	len[0] = 5;
	len[1] = 220;

	if (type > etherII) {
		return V802;
	} else {
		if (type < len) {
			return VII;
		} else {
			cout << "\nProtocolo de capa de enlace, desconocido." << endl;
			exit(EXIT_FAILURE);
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

const u_char* polv_network_header(const u_char* packet, 
								  enum polv_ethertype etherver, int len)
{
	const u_char* header;
	switch (etherver) {
	case VII:
	    header = polv_oct(DSAP,len,packet);
		break;
	case V802:
		header = polv_oct(DATA,len,packet);
		break;
	}

	return header;
}
