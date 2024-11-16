#include "opt_super_sr.h"

#include "types.h"
#include "tree_basic.h"
#include "traverse.h"
#include "dbug.h"

#include "memory.h"
#include "free.h"
#include "str.h"



/*
 * Traversal functions
 */

node *createAdditionTree(node *var_node, int n) {

/* Basisfall*/
    if (n == 1) {
        return COPYvar(var_node, NULL); 
    }

/* Rekursiver Fall: neuer Additionsknoten wird erstellt */  
    node *new_node = TBmakeBinop(BO_add, NULL, NULL);

    //Linkes Kind: variable kopieren
    BINOP_LEFT(new_node) = TBmakeVar(STRcpy(VAR_NAME(var_node)));
    //Rechtes Kind:
    BINOP_RIGHT(new_node) = createAdditionTree(var_node, n-1);

    return new_node;
}


node *SSRbinop (node *arg_node, info *arg_info)
{
    DBUG_ENTER("SSRbinop");


    BINOP_LEFT(arg_node) = TRAVdo (BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVdo (BINOP_RIGHT(arg_node), arg_info);

    if (BINOP_OP(arg_node) == BO_mul) {
      if ((NODE_TYPE(BINOP_LEFT(arg_node)) == N_var) && 
      NODE_TYPE(BINOP_RIGHT(arg_node)) == N_num) {


      // rekursiv den NUM Knoten erweitern indem:
      // VAR Knoten + NUM Value der rekursiven func uebergeben wird
      int num_value = NUM_VALUE(BINOP_RIGHT(arg_node)); // Wert sichern
      BINOP_RIGHT(arg_node) = FREEdoFreeTree(BINOP_RIGHT(arg_node)); // Speicher freigeben
      BINOP_RIGHT(arg_node) = createAdditionTree(BINOP_LEFT(arg_node), num_value); // Baum erstellen
      // * durch + ersetzen
      BINOP_OP(arg_node) = BO_add;

      }
      else if ((NODE_TYPE(BINOP_RIGHT(arg_node)) == N_var) && 
      NODE_TYPE(BINOP_LEFT(arg_node)) == N_num &&
      NUM_VALUE(BINOP_LEFT(arg_node)) == 2) {
        int num_value = NUM_VALUE(BINOP_LEFT(arg_node));
        BINOP_LEFT(arg_node) = FREEdoFreeTree(BINOP_LEFT(arg_node)); // Speicher freigeben
        BINOP_LEFT(arg_node) = createAdditionTree(BINOP_RIGHT(arg_node), num_value);
    
      // * durch + ersetzen
        BINOP_OP(arg_node) = BO_add;
      }


  }

  DBUG_RETURN(arg_node);
}

/*
 * Traversal start function
 */

node *SSRdoOptSSR( node *syntaxtree)
{
  DBUG_ENTER("SSRdoOptSSR");

  TRAVpush( TR_ssr);
  syntaxtree = TRAVdo( syntaxtree, NULL);
  TRAVpop();

  DBUG_RETURN( syntaxtree);
}
