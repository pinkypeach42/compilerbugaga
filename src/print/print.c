
/**
 * @file print.c
 *
 * Functions needed by print traversal.
 *
 */

/**
 * @defgroup print Print Functions.
 *
 * Functions needed by print traversal.
 *
 * @{
 */


#include "print.h"
#include "traverse.h"
#include "tree_basic.h"
#include "dbug.h"
#include "memory.h"
#include "globals.h"
#include "traverse_helper.h" // TRAVsons (wegen Assignment 2.3)


/*
 * INFO structure
 */
struct INFO {
  bool firsterror;
};

#define INFO_FIRSTERROR(n) ((n)->firsterror)

static info *MakeInfo()
{
  info *result;
  
  result = MEMmalloc(sizeof(info));

  INFO_FIRSTERROR(result) = FALSE;
  
  return result;
}


static info *FreeInfo( info *info)
{
  info = MEMfree( info);

  return info;
}



/** <!--******************************************************************-->
 *
 * @fn PRTstmts
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node BinOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTstmts (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTstmts");

  STMTS_STMT( arg_node) = TRAVdo( STMTS_STMT( arg_node), arg_info);
  
  STMTS_NEXT( arg_node) = TRAVopt( STMTS_NEXT( arg_node), arg_info);
  
  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTassign
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node BinOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTassign (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTassign");

  if (ASSIGN_LET( arg_node) != NULL) {
    ASSIGN_LET( arg_node) = TRAVdo( ASSIGN_LET( arg_node), arg_info);
    printf( " = ");
  }
  
  ASSIGN_EXPR( arg_node) = TRAVdo( ASSIGN_EXPR( arg_node), arg_info);
  
  printf( ";\n");
  
  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTbinop
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node BinOp node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTbinop (node * arg_node, info * arg_info)
{
  char *tmp;

  DBUG_ENTER ("PRTbinop");

  printf( "( ");

  BINOP_LEFT( arg_node) = TRAVdo( BINOP_LEFT( arg_node), arg_info);

  switch (BINOP_OP( arg_node)) {
    case BO_add:
      tmp = "+";
      break;
    case BO_sub:
      tmp = "-";
      break;
    case BO_mul:
      tmp = "*";
      break;
    case BO_div:
      tmp = "/";
      break;
    case BO_mod:
      tmp = "%";
      break;
    case BO_lt:
      tmp = "<";
      break;
    case BO_le:
      tmp = "<=";
      break;
    case BO_gt:
      tmp = ">";
      break;
    case BO_ge:
      tmp = ">=";
      break;
    case BO_eq:
      tmp = "==";
      break;
    case BO_ne:
      tmp = "!=";
      break;
    case BO_or:
      tmp = "||";
      break;
    case BO_and:
      tmp = "&&";
      break;
    case BO_unknown:
      DBUG_ASSERT( 0, "unknown binop detected!");
  }

  printf( " %s ", tmp);

  BINOP_RIGHT( arg_node) = TRAVdo( BINOP_RIGHT( arg_node), arg_info);

  printf( ")");

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTfloat
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Float node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTfloat (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTfloat");

  printf( "%f", FLOAT_VALUE( arg_node));

  DBUG_RETURN (arg_node);
}



/** <!--******************************************************************-->
 *
 * @fn PRTnum
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Num node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTnum (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTnum");

  printf( "%i", NUM_VALUE( arg_node));

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTboolean
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node Boolean node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTbool (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTbool");

  if (BOOL_VALUE( arg_node)) {
    printf( "true");
  }
  else {
    printf( "false");
  }
  
  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTvar
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node letrec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTvar (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTvar");

  printf( "%s", VAR_NAME( arg_node));

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTvarlet
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node letrec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTvarlet (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTvarlet");

  printf( "%s", VARLET_NAME( arg_node));

  DBUG_RETURN (arg_node);
}


/** <!--******************************************************************-->
 *
 * @fn PRTsymboltableentry
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node letrec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *PRTsymboltableentry (node * arg_node, info * arg_info)
{
  DBUG_ENTER ("PRTsymboltableentry");

  DBUG_RETURN (arg_node);
}

/** <!--******************************************************************-->
 *
 * @fn PRTerror
 *
 * @brief Prints the node and its sons/attributes
 *
 * @param arg_node letrec node to process
 * @param arg_info pointer to info structure
 *
 * @return processed node
 *
 ***************************************************************************/

node *
PRTerror (node * arg_node, info * arg_info)
{
  bool first_error;

  DBUG_ENTER ("PRTerror");

  if (NODE_ERROR (arg_node) != NULL) {
    NODE_ERROR (arg_node) = TRAVdo (NODE_ERROR (arg_node), arg_info);
  }

  first_error = INFO_FIRSTERROR( arg_info);

  if( (global.outfile != NULL)
      && (ERROR_ANYPHASE( arg_node) == global.compiler_anyphase)) {

    if ( first_error) {
      printf ( "\n/******* BEGIN TREE CORRUPTION ********\n");
      INFO_FIRSTERROR( arg_info) = FALSE;
    }

    printf ( "%s\n", ERROR_MESSAGE( arg_node));

    if (ERROR_NEXT (arg_node) != NULL) {
      TRAVopt (ERROR_NEXT (arg_node), arg_info);
    }

    if ( first_error) {
      printf ( "********  END TREE CORRUPTION  *******/\n");
      INFO_FIRSTERROR( arg_info) = TRUE;
    }
  }

  DBUG_RETURN (arg_node);
}



//Assignment 2.3


const char* getNodeTypeString(node *arg_node) {
    switch (NODE_TYPE(arg_node)) {
        case N_rootnode:
            return "RootNode";
        case N_binop:
            return "BinOp";
        case N_assign:
            return "Assign";
        case N_stmts:
            return "Statements";
        case N_num:
            return "Number";
        case N_float:
            return "Float";
        case N_bool:
            return "Boolean";
        case N_var:
            return "Variable";
        case N_varlet:
            return "Variable Let";
        // Weitere Knotentypen hinzufügen
        default:
            return "Unknown Node";
    }
}

/** <!-- ****************************************************************** -->
 * @brief Prints the given syntaxtree
 * 
 * @param syntaxtree a node structure
 * 
 * @return the unchanged nodestructure
 ******************************************************************************/

node 
*PRTdoPrint( node *syntaxtree)
{
  info *info;
  
  DBUG_ENTER("PRTdoPrint");

  DBUG_ASSERT( (syntaxtree!= NULL), "PRTdoPrint called with empty syntaxtree");

  printf( "\n\n------------------------------\n\n");
  DBUG_PRINT("DEBUG", ("Starting Pretty-Print Traversal"));
  printf("DEBUG: Wurzelknotentyp: %s\n", getNodeTypeString(syntaxtree));

  info = MakeInfo();
  
  TRAVpush(TR_prt);
  if (NODE_TYPE(syntaxtree) == N_rootnode) {
    printf("DEBUG: Wurzelknoten gefunden.\n");
  }

  syntaxtree = TRAVdo( syntaxtree, info);
  DBUG_PRINT("DEBUG", ("Traversal abgeschlossen"));

  TRAVpop();

  info = FreeInfo(info);

  printf( "\n------------------------------\n\n");

  DBUG_RETURN( syntaxtree);
}


//Assignment 2.3

node *PRINT_node(node *arg_node, info *arg_info) {
    DBUG_ENTER("PRINT_node");

    if (arg_node == NULL) {
        DBUG_RETURN(NULL);
    }

    // Print the node type
    printf("Node Type: %s\n", getNodeTypeString(arg_node));


    // Print attributes based on the node type
    switch (NODE_TYPE(arg_node)) {
        case N_rootnode:
            printf("CountPlus: %d\n", ROOTNODE_COUNTPLUS(arg_node));
            printf("CountMinus: %d\n", ROOTNODE_COUNTMINUS(arg_node));
            printf("CountMult: %d\n", ROOTNODE_COUNTMULT(arg_node));
            printf("CountDiv: %d\n", ROOTNODE_COUNTDIV(arg_node));
            printf("CountMod: %d\n", ROOTNODE_COUNTMOD(arg_node));
            break;

        case N_binop:
            PRTbinop(arg_node, arg_info);

        // Add cases for other node types as needed
        default:
            printf("Unhandled node type.\n");
            break;
    }

    // Recursively process the node's sons
    TRAVsons(arg_node, arg_info);

    DBUG_RETURN(arg_node);
}


node *PRTrootnode(node *arg_node, info *arg_info) {
    DBUG_ENTER("PRTrootnode");
    printf("DEBUG: PRTrootnode wurde aufgerufen!\n");

    // Gib die Zählerinformationen aus
    printf("Root Node Information:\n");
    printf("CountPlus: %d\n", ROOTNODE_COUNTPLUS(arg_node));
    printf("CountMinus: %d\n", ROOTNODE_COUNTMINUS(arg_node));
    printf("CountMult: %d\n", ROOTNODE_COUNTMULT(arg_node));
    printf("CountDiv: %d\n", ROOTNODE_COUNTDIV(arg_node));
    printf("CountMod: %d\n", ROOTNODE_COUNTMOD(arg_node));

    // Traversiere die Statements, die unter dem RootNode liegen
    TRAVsons(arg_node, arg_info);

    DBUG_RETURN(arg_node);
}


/**
 * @}
 */
