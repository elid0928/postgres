/*-------------------------------------------------------------------------
 *
 * superwrite.c
 *	  Implementation of SUPER_WRITE functionality for high-priority write operations
 *
 * This module provides special handling for high-priority write operations
 * marked with the SUPER_WRITE keyword in SQL.
 *
 * Portions Copyright (c) 1996-2025, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *	  src/backend/utils/superwrite.c
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "access/tableam.h"
#include "access/xact.h"
#include "executor/executor.h"
#include "storage/lmgr.h"
#include "tcop/utility.h"
#include "utils/superwrite.h"

/*
 * IsSuperWriteStatement - check if the current statement is a SUPER_WRITE
 *
 * Returns true if the current operation is a high-priority write operation
 * marked with SUPER_WRITE
 */
bool
IsSuperWriteOperation(ModifyTableState *mtstate)
{
    if (mtstate == NULL)
        return false;

    ModifyTable *node = (ModifyTable *) mtstate->ps.plan;
    return node->super_write;
}

/*
 * ProcessSuperWritePriority - adjust priorities for super_write operations
 *
 * For SUPER_WRITE operations, we immediately process any pending inserts
 * to ensure they have high priority
 */
void
ProcessSuperWritePriority(EState *estate, ResultRelInfo *resultRelInfo)
{
    /* Skip if not a SUPER_WRITE operation */
    if (!resultRelInfo->ri_super_write)
        return;

    /* Process any pending inserts immediately */
    if (estate->es_insert_pending_result_relations != NIL)
        ExecPendingInserts(estate);
} 