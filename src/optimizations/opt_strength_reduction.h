#ifndef _OPT_STRENGTH_REDUCTION_H_
#define _OPT_STRENGTH_REDUCTION_H_
#include "types.h"

extern node *SRbinop (node *arg_node, info *arg_info);
extern node *SRdoOptSR( node *syntaxtree);

#endif
