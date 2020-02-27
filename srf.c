/*
 * contrib/citext/citext.c
 */
#include "postgres.h"
#include "funcapi.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(srf_c);

typedef struct SrfCounterContext {
    int32 current;
    int32 end;
} SrfCounterContext;

/**
create or replace function srf_c(start int, "end" int) returns setof int language c as 'MODULE_PATHNAME', 'srf_c';
//create or replace function srf_c(start int, "end" int) returns TABLE (v int, v_x_9 int) language c as 'MODULE_PATHNAME', 'srf_c';
 */
Datum
srf_c(PG_FUNCTION_ARGS)
{
    FuncCallContext *funcctx;
    SrfCounterContext *counterContext;

    if (SRF_IS_FIRSTCALL()) {
        int32 start = PG_GETARG_INT32(0);
        int32 end = PG_GETARG_INT32(1);
        MemoryContext oldContext;

        funcctx = SRF_FIRSTCALL_INIT();

        oldContext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        counterContext = palloc(sizeof(SrfCounterContext));
        counterContext->current = start;
        counterContext->end = end;
        funcctx->user_fctx = counterContext;

        MemoryContextSwitchTo(oldContext);
    }

    /* stuff done on every call of the function */
    funcctx = SRF_PERCALL_SETUP();
    counterContext = (SrfCounterContext *) funcctx->user_fctx;

    if (counterContext->current <= counterContext->end) {
        int32 result = counterContext->current;

        counterContext->current++;

        /* do when there is more left to send */
        SRF_RETURN_NEXT(funcctx, Int32GetDatum(result));
    } else {
        /* do when there is no more left */
        SRF_RETURN_DONE(funcctx);
    }

    // never get here
    PG_RETURN_VOID();
}

