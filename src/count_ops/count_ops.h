#ifndef _COUNT_OPS_H_
#define _COUNT_OPS_H_


#include "types.h" // INFO wird global verwendet und in types.h nur vorwärtsdeklariert

// Funktionsdeklarationen
extern node *COUNTOPSbinop (node *arg_node, info *arg_info);
extern node *COUNTOPSdoCount( node *syntaxtree);


#endif
