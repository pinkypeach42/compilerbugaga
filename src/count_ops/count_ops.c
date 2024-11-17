#include "count_ops.h"

#include "types.h"
#include "traverse.h"
#include "tree_basic.h"
#include "memory.h"
#include "dbug.h"
#include "ctinfo.h"

#define INFO_COUNT(n)  ((n)->count)

/*
 * INFO structure + MakeInfo + FreeInfo
 */

struct INFO {
   int count;
};


// Создание структуры INFO
static info *MakeInfo(void) 
{
  info *result;

  DBUG_ENTER( "MakeInfo:");

  result = (info *)MEMmalloc(sizeof(info));

  INFO_COUNT( result) = 0;

  DBUG_RETURN( result);
}

static info *FreeInfo( info *info)
{
  DBUG_ENTER ("FreeInfo");

  info = MEMfree( info);

  DBUG_RETURN( info);
}


/*
 * Traversal functions
 */

node *COUNTOPSbinop (node *arg_node, info *arg_info)
{
  DBUG_ENTER("COUNTOPSbinop");

  INFO_COUNT( arg_info) += 1;

  if(NODE_TYPE( BINOP_LEFT(arg_node)) == N_binop) {
      BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
  }
  else if(NODE_TYPE( BINOP_RIGHT(arg_node)) == N_binop) {
      BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);
  }

  DBUG_RETURN( arg_node);
}



/*
 * Traversal start function
 */

node *COUNTOPSdoCount( node *syntaxtree)
{
  info *arg_info;

  DBUG_ENTER("COUNTOPSdoCount");

  arg_info = MakeInfo();

  TRAVpush( TR_countops);
  syntaxtree = TRAVdo( syntaxtree, arg_info);
  TRAVpop();

  printf("count %d\n ", INFO_COUNT( arg_info));
  CTInote( "count of arithmetic operations: %d", INFO_COUNT( arg_info));

  ROOTNODE_NUM(syntaxtree) = TBmakeNum(INFO_COUNT(arg_info));
  arg_info = FreeInfo( arg_info);

  DBUG_RETURN( syntaxtree);
}