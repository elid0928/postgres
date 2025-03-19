/*-------------------------------------------------------------------------
 *
 * superwrite.h
 *	  Header for super_write functionality
 *
 * Portions Copyright (c) 1996-2025, PostgreSQL Global Development Group
 *
 * src/include/utils/superwrite.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef SUPERWRITE_H
#define SUPERWRITE_H

#include "executor/executor.h"

/* Check if an operation is a SUPER_WRITE operation */
extern bool IsSuperWriteOperation(ModifyTableState *mtstate);

/* Process SUPER_WRITE priority for a result relation */
extern void ProcessSuperWritePriority(EState *estate, ResultRelInfo *resultRelInfo);

#endif /* SUPERWRITE_H */ 