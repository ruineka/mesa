/**************************************************************************
 * 
 * Copyright 2004 VMware, Inc.
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 **************************************************************************/

 /*
  * Authors:
  *   Keith Whitwell <keithw@vmware.com>
  */
    

#ifndef ST_DRAW_H
#define ST_DRAW_H

#include "main/glheader.h"

struct _mesa_index_buffer;
struct _mesa_prim;
struct gl_context;
struct st_context;

void st_init_draw_functions(struct pipe_screen *screen,
                            struct dd_function_table *functions);

void st_destroy_draw( struct st_context *st );

struct draw_context *st_get_draw_context(struct st_context *st);

extern void
st_feedback_draw_vbo(struct gl_context *ctx,
                     const struct _mesa_prim *prims,
                     unsigned nr_prims,
                     const struct _mesa_index_buffer *ib,
		     bool index_bounds_valid,
                     bool primitive_restart,
                     unsigned restart_index,
                     unsigned min_index,
                     unsigned max_index,
                     unsigned num_instances,
                     unsigned base_instance);

/**
 * When drawing with VBOs, the addresses specified with
 * glVertex/Color/TexCoordPointer() are really offsets into the VBO, not real
 * addresses.  At some point we need to convert those pointers to offsets.
 * This function is basically a cast wrapper to avoid warnings when building
 * in 64-bit mode.
 */
static inline unsigned
pointer_to_offset(const void *ptr)
{
   return (unsigned) (((GLsizeiptr) ptr) & 0xffffffffUL);
}


bool
st_draw_quad(struct st_context *st,
             float x0, float y0, float x1, float y1, float z,
             float s0, float t0, float s1, float t1,
             const float *color,
             unsigned num_instances);

void
st_draw_transform_feedback(struct gl_context *ctx, GLenum mode,
                           unsigned num_instances, unsigned stream,
                           struct gl_transform_feedback_object *tfb_vertcount);

void
st_indirect_draw_vbo(struct gl_context *ctx,
                     GLuint mode,
                     struct gl_buffer_object *indirect_data,
                     GLsizeiptr indirect_offset,
                     unsigned draw_count,
                     unsigned stride,
                     struct gl_buffer_object *indirect_draw_count,
                     GLsizeiptr indirect_draw_count_offset,
                     const struct _mesa_index_buffer *ib,
                     bool primitive_restart,
                     unsigned restart_index);

bool
st_draw_hw_select_prepare_common(struct gl_context *ctx);
bool
st_draw_hw_select_prepare_mode(struct gl_context *ctx, struct pipe_draw_info *info);
void
st_init_hw_select_draw_functions(struct pipe_screen *screen,
                                 struct dd_function_table *functions);

#endif
