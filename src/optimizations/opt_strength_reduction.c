/*****************************************************************************
 *
 * Module: strength_reduction
 *
 * Prefix: SR (ast)
 *
 * Description:
 *
 * This module implements a traversal of the abstract syntax tree that 
 * replaces multiplications by 2 with equivalent additions.
 *
 *****************************************************************************/


#include "opt_strength_reduction.h"

#include "types.h" /* in der Datei -  #include "mytypes.h" --> defs von binops und monops, u.a. BO_mul */
#include "tree_basic.h"
#include "traverse.h" 
#include "dbug.h"  

#include "memory.h"
#include "free.h"
#include "str.h"
#include "copy_node.h"

/*
 * Traversal function
 */

node *SRbinop (node *arg_node, info *arg_info)
{
    DBUG_ENTER("SRbinop");


    BINOP_LEFT(arg_node) = TRAVdo (BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVdo (BINOP_RIGHT(arg_node), arg_info);

    if (BINOP_OP(arg_node) == BO_mul) {
      if ((NODE_TYPE(BINOP_LEFT(arg_node)) == N_var) && 
      NODE_TYPE(BINOP_RIGHT(arg_node)) == N_num &&
      NUM_VALUE(BINOP_RIGHT(arg_node)) == 2) {
        


      // Освобождаем старый правый узел
      BINOP_RIGHT(arg_node) = FREEdoFreeTree(BINOP_RIGHT(arg_node));
      // Создаём новый правый узел
      BINOP_RIGHT(arg_node) = TBmakeVar(STRcpy(VAR_NAME(BINOP_LEFT(arg_node))));


// Создаём новый правый узел, копируя имя из левого узла
        BINOP_OP(arg_node) = BO_add;
      }
      if ((NODE_TYPE(BINOP_RIGHT(arg_node)) == N_var) && 
      NODE_TYPE(BINOP_LEFT(arg_node)) == N_num &&
      NUM_VALUE(BINOP_LEFT(arg_node)) == 2) {


         BINOP_LEFT(arg_node) = FREEdoFreeTree(BINOP_RIGHT(arg_node));
        BINOP_LEFT(arg_node) = TBmakeVar(STRcpy(VAR_NAME(BINOP_RIGHT(arg_node))));
         BINOP_OP(arg_node) = BO_add;
      }


  }

  DBUG_RETURN(arg_node);
}

/*
 * Traversal start function old SRdoStrengthReduction
 */

node *SRdoOptSR( node *syntaxtree)
{
  DBUG_ENTER("SRdoOptSR");

  TRAVpush( TR_sr);
  syntaxtree = TRAVdo( syntaxtree, NULL);
  TRAVpop();

  DBUG_RETURN( syntaxtree);
}

