
/**
 * @file check_node.h
 *
 * Functions to free node structures
 *
 * THIS FILE HAS BEEN GENERATED USING
 * $Id: check_node.h.xsl 15657 2007-11-13 13:57:30Z cg $.
 * DO NOT EDIT THIS FILE AS MIGHT BE CHANGED IN A LATER VERSION.
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN!
 *
 */

#ifndef _SAC_CHECK_NODE_H_
#define _SAC_CHECK_NODE_H_

#include "types.h"

extern node    *CHKMpostfun(node * arg_node, info * arg_info);

extern node    *CHKMassign(node * arg_node, info * arg_info);
extern node    *CHKMbinop(node * arg_node, info * arg_info);
extern node    *CHKMbool(node * arg_node, info * arg_info);
extern node    *CHKMerror(node * arg_node, info * arg_info);
extern node    *CHKMfloat(node * arg_node, info * arg_info);
extern node    *CHKMnum(node * arg_node, info * arg_info);
extern node    *CHKMrootnode(node * arg_node, info * arg_info);
extern node    *CHKMstmts(node * arg_node, info * arg_info);
extern node    *CHKMsymboltableentry(node * arg_node, info * arg_info);
extern node    *CHKMvar(node * arg_node, info * arg_info);
extern node    *CHKMvarlet(node * arg_node, info * arg_info);

#endif				/* _SAC_CHECK_NODE_H_ */
