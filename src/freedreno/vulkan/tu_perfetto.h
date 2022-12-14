/*
 * Copyright © 2021 Google, Inc.
 * SPDX-License-Identifier: MIT
 */

#ifndef TU_PERFETTO_H_
#define TU_PERFETTO_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_PERFETTO

/**
 * Render-stage id's
 */
enum tu_stage_id {
   SURFACE_STAGE_ID, /* Surface is a sort of meta-stage for render-target info */
   BINNING_STAGE_ID,
   GMEM_STAGE_ID,
   BYPASS_STAGE_ID,
   BLIT_STAGE_ID,
   COMPUTE_STAGE_ID,
   CLEAR_SYSMEM_STAGE_ID,
   CLEAR_GMEM_STAGE_ID,
   GMEM_LOAD_STAGE_ID,
   GMEM_STORE_STAGE_ID,
   SYSMEM_RESOLVE_STAGE_ID,
   // TODO add the rest

   NUM_STAGES
};

static const struct {
   const char *name;
   const char *desc;
} stages[] = {
   [SURFACE_STAGE_ID] = {"Surface"},
   [BINNING_STAGE_ID] = {"Binning", "Perform Visibility pass and determine target bins"},
   [GMEM_STAGE_ID]    = {"Render", "Rendering to GMEM"},
   [BYPASS_STAGE_ID]  = {"Render", "Rendering to system memory"},
   [BLIT_STAGE_ID]    = {"Blit", "Performing a Blit operation"},
   [COMPUTE_STAGE_ID] = {"Compute", "Compute job"},
   [CLEAR_SYSMEM_STAGE_ID] = {"Clear Sysmem", ""},
   [CLEAR_GMEM_STAGE_ID] = {"Clear GMEM", "Per-tile (GMEM) clear"},
   [GMEM_LOAD_STAGE_ID] = {"GMEM Load", "Per tile system memory to GMEM load"},
   [GMEM_STORE_STAGE_ID] = {"GMEM Store", "Per tile GMEM to system memory store"},
   [SYSMEM_RESOLVE_STAGE_ID] = {"SysMem Resolve", "System memory MSAA resolve"},
   // TODO add the rest
};

/**
 * Queue-id's
 */
enum {
   DEFAULT_HW_QUEUE_ID,
};

static const struct {
   const char *name;
   const char *desc;
} queues[] = {
   [DEFAULT_HW_QUEUE_ID] = {"GPU Queue 0", "Default Adreno Hardware Queue"},
};

struct tu_perfetto_state {
   uint64_t start_ts[NUM_STAGES];
};

void tu_perfetto_init(void);

struct tu_device;
void tu_perfetto_submit(struct tu_device *dev, uint32_t submission_id);

/* Helpers */

struct tu_perfetto_state *
tu_device_get_perfetto_state(struct tu_device *dev);

int
tu_device_get_gpu_timestamp(struct tu_device *dev,
                            uint64_t *ts);

int
tu_device_get_suspend_count(struct tu_device *dev,
                            uint64_t *suspend_count);

uint64_t
tu_device_ticks_to_ns(struct tu_device *dev, uint64_t ts);

struct tu_u_trace_submission_data;
uint32_t
tu_u_trace_submission_data_get_submit_id(const struct tu_u_trace_submission_data *data);

#endif

#ifdef __cplusplus
}
#endif

#endif /* TU_PERFETTO_H_ */
