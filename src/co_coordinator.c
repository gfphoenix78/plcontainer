#include "postgres.h"
#include <unistd.h>
#include <utils/timeout.h>

#include "access/tupdesc.h"
#include "access/xact.h"
#include "catalog/indexing.h"
#include "catalog/namespace.h"
#include "catalog/pg_collation.h"
#include "catalog/pg_database.h"
#include "catalog/pg_extension.h"
#include "catalog/pg_type.h"
#include "cdb/cdbvars.h"
#include "commands/dbcommands.h"
#include "commands/extension.h"
#include "executor/spi.h"
#include "libpq/libpq-be.h"
#include "miscadmin.h"
#include "nodes/makefuncs.h"
#include "pgstat.h"
#include "postmaster/bgworker.h"
#include "storage/ipc.h"
#include "storage/proc.h"
#include "tcop/idle_resource_cleaner.h"
#include "tcop/utility.h"
#include "utils/acl.h"
#include "utils/builtins.h"
#include "utils/fmgroids.h"
#include "utils/formatting.h"
#include "utils/memutils.h"
#include "utils/numeric.h"
#include "utils/ps_status.h"
#include "utils/snapmgr.h"
#include "utils/syscache.h"

PG_MODULE_MAGIC;
// PROTOTYPE:
extern void _PG_init(void);
extern void plc_coordinator_main(Datum datum);

// END OF PROTOTYPES.

static shmem_startup_hook_type prev_shmem_startup_hook = NULL;
static void
plc_coordinator_shmem_startup(void)
{
    if (prev_shmem_startup_hook)
        prev_shmem_startup_hook();
    // TODO: do shared memory initialization

}
static int
calc_shmem_size(void)
{
    // TODO: to calculate real shmem size
    return 16;
}
static void
init_shmem_(void)
{
    RequestAddinShmemSpace(calc_shmem_size());
    // TODO: figure out the number of locks
    RequestAddinLWLocks(4);
    prev_shmem_startup_hook = shmem_startup_hook;
    shmem_startup_hook = plc_coordinator_shmem_startup;
}

void
plc_coordinator_main(Datum datum)
{
    // TODO: impl coordinator logic here
}
void
_PG_init(void)
{
    BackgroundWorker worker;

    init_shmem_();
    memset(&worker, 0, sizeof(BackgroundWorker));

    /* coordinator.so must be in shared_preload_libraries to init SHM. */
    if (!process_shared_preload_libraries_in_progress)
        ereport(ERROR, (errmsg("coordinator.so not in shared_preload_libraries.")));

    worker.bgw_flags = BGWORKER_SHMEM_ACCESS;
    worker.bgw_start_time = BgWorkerStart_RecoveryFinished;
    worker.bgw_restart_time = BGW_DEFAULT_RESTART_INTERVAL;
    snprintf(worker.bgw_library_name, BGW_MAXLEN, "coordinator");
    snprintf(worker.bgw_function_name, BGW_MAXLEN, "plc_coordinator_main");
    worker.bgw_notify_pid = 0;

    snprintf(worker.bgw_name, BGW_MAXLEN, "[plcontainer] - coordinator");

    RegisterBackgroundWorker(&worker);
}
