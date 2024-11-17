#ifndef _COUNT_OPS_H_
#define _COUNT_OPS_H_

#include "tree_basic.h"
#include "types.h" // INFO wird global verwendet und in types.h nur vorwärtsdeklariert


// Funktionsdeklarationen
extern node *COUNTOPSrootnode(node* arg_node, info* arg_info);
extern node *COUNTOPSbinop(node* arg_node, info* arg_info);
extern node *COUNTOPSdoCount(node* syntaxtree);

extern node *COUNTOPSassign(node *arg_node, info *arg_info);
extern node *COUNTOPSbool(node *arg_node, info *arg_info);
extern node *COUNTOPSerror(node *arg_node, info *arg_info);
extern node *COUNTOPSfloat(node *arg_node, info *arg_info);
extern node *COUNTOPSnum(node *arg_node, info *arg_info);
extern node *COUNTOPSstmts(node *arg_node, info *arg_info);
extern node *COUNTOPSsymboltableentry(node *arg_node, info *arg_info);
extern node *COUNTOPSvar(node *arg_node, info *arg_info);
extern node *COUNTOPSvarlet(node *arg_node, info *arg_info);



#endif
