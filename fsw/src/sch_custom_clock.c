/*
** Copyright (c) 2007-2014 United States Government as represented by the
** Administrator of the National Aeronautics and Space Administration.
** All Other Rights Reserved.
**
** Default Scheduler clock and transaction customization.
**
** This implementation uses only cFE and OSAL services and is suitable for
** physical flight targets. A target may replace this source at build time.
*/

#include "cfe.h"
#include "cfe_time_msg.h"

#include "sch_app.h"
#include "sch_custom.h"
#include "sch_platform_cfg.h"

int32 SCH_CustomEarlyInit(void)
{
    return OS_TimerCreate(&SCH_AppData.TimerId,
                          SCH_TIMER_NAME,
                          &SCH_AppData.ClockAccuracy,
                          SCH_MinorFrameCallback);
}

int32 SCH_CustomLateInit(void)
{
    int32 Status;

    CFE_ES_WaitForStartupSync(SCH_STARTUP_SYNC_TIMEOUT);

    Status = CFE_TIME_RegisterSynchCallback(
        (CFE_TIME_SynchCallbackPtr_t)&SCH_MajorFrameCallback);
    if (Status == CFE_SUCCESS)
    {
        Status = OS_TimerSet(SCH_AppData.TimerId, SCH_STARTUP_PERIOD, 0);
    }

    return Status;
}

int32 SCH_CustomPrepareEntry(uint32                           ScheduleEntry,
                             const CFE_MSG_Message_t          *Message,
                             SCH_CustomEntryDecision_t        *Decision)
{
    (void)ScheduleEntry;
    (void)Message;

    if (Decision == NULL)
    {
        return CFE_SB_BAD_ARGUMENT;
    }

    Decision->Transmit = true;
    Decision->ProcessCommands = false;
    return CFE_SUCCESS;
}

int32 SCH_CustomCompleteCurrentSlot(void)
{
    return CFE_SUCCESS;
}

void SCH_CustomCleanup(void)
{
    CFE_TIME_UnregisterSynchCallback(
        (CFE_TIME_SynchCallbackPtr_t)&SCH_MajorFrameCallback);
}
