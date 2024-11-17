#include "count_ops.h"
#include "traverse.h"
#include "tree_basic.h"
#include "memory.h"
#include "dbug.h"
#include "traverse_helper.h"

// Lokale Definition der INFO-Struktur für die Phase COUNTOPS
struct INFO {
    int count_plus;
    int count_minus;
    int count_mult;
    int count_div;
    int count_mod;
    node *root_node;
};

// Initialisiert die INFO-Struktur
static info *MakeInfo() {
    info *new_info = MEMmalloc(sizeof(info));
    new_info->count_plus = 0;
    new_info->count_minus = 0;
    new_info->count_mult = 0;
    new_info->count_div = 0;
    new_info->count_mod = 0;
    new_info->root_node = NULL;
    return new_info;
}

// Gibt die INFO-Struktur frei
static void FreeInfo(info *arg_info) {
    MEMfree(arg_info);
}

// Handler für RootNode
node *COUNTOPSrootnode(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSrootnode");

    // Initialisiere die Zähler
    ROOTNODE_COUNTPLUS(arg_node) = 0;
    ROOTNODE_COUNTMINUS(arg_node) = 0;
    ROOTNODE_COUNTMULT(arg_node) = 0;
    ROOTNODE_COUNTDIV(arg_node) = 0;
    ROOTNODE_COUNTMOD(arg_node) = 0;

    // Speichere den RootNode in der INFO-Struktur
    arg_info->root_node = arg_node;

    // Fahre mit dem Traversieren fort
    TRAVsons(arg_node, arg_info);

    DBUG_RETURN(arg_node);
}

// Handler für BinOp
node *COUNTOPSbinop(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSbinop");

    // Aktualisiere die Zähler basierend auf dem BinOp
    switch (BINOP_OP(arg_node)) {
        case BO_add:
            ROOTNODE_COUNTPLUS(arg_info->root_node)++;
            break;
        case BO_sub:
            ROOTNODE_COUNTMINUS(arg_info->root_node)++;
            break;
        case BO_mul:
            ROOTNODE_COUNTMULT(arg_info->root_node)++;
            break;
        case BO_div:
            ROOTNODE_COUNTDIV(arg_info->root_node)++;
            break;
        case BO_mod:
            ROOTNODE_COUNTMOD(arg_info->root_node)++;
            break;
        default:
            break;
    }

    // Fahre mit dem Traversieren fort
    BINOP_LEFT(arg_node) = TRAVdo(BINOP_LEFT(arg_node), arg_info);
    BINOP_RIGHT(arg_node) = TRAVdo(BINOP_RIGHT(arg_node), arg_info);

    DBUG_RETURN(arg_node);
}

// Startfunktion für die Phase COUNTOPS
node *COUNTOPSdoCount(node *syntaxtree) {
    DBUG_ENTER("COUNTOPSdoCount");

    // Erstelle die INFO-Struktur
    info *arg_info = MakeInfo();

    // Starte die Traversierung
    TRAVpush(TR_countops);
    syntaxtree = TRAVdo(syntaxtree, arg_info);
    TRAVpop();

    // Gib die INFO-Struktur frei
    FreeInfo(arg_info);

    DBUG_RETURN(syntaxtree);
}


// Обработчик для Assign
node *COUNTOPSassign(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSassign");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для Bool
node *COUNTOPSbool(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSbool");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для Error
node *COUNTOPSerror(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSerror");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для Float
node *COUNTOPSfloat(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSfloat");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для Num
node *COUNTOPSnum(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSnum");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для Stmts
node *COUNTOPSstmts(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSstmts");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для SymbolTableEntry
node *COUNTOPSsymboltableentry(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSsymboltableentry");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для Var
node *COUNTOPSvar(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSvar");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}

// Обработчик для VarLet
node *COUNTOPSvarlet(node *arg_node, info *arg_info) {
    DBUG_ENTER("COUNTOPSvarlet");
    TRAVsons(arg_node, arg_info); // Продолжить обход дочерних узлов
    DBUG_RETURN(arg_node);
}
