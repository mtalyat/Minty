#ifndef MINTY_JOB_JOBMANAGERINFO_H
#define MINTY_JOB_JOBMANAGERINFO_H

/**
 * @file JobManagerInfo.h
 * @brief Header file for the JobManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    /**
     * @brief Configuration information for creating a JobManager.
     */
    struct JobManagerInfo
    {
        /**
         * @brief The number of worker threads to use.
         * @note If set to 0, the JobManager will use the number of hardware threads available on the system.
         */
        Size threadCount = 0;
    };
}

#endif // MINTY_JOB_JOBMANAGERINFO_H