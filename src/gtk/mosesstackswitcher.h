/*
 * Copyright (c) 2013 Red Hat, Inc.
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __MOSES_STACK_SWITCHER_H__
#define __MOSES_STACK_SWITCHER_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MOSES_TYPE_STACK_SWITCHER            (moses_stack_switcher_get_type ())
#define MOSES_STACK_SWITCHER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MOSES_TYPE_STACK_SWITCHER, MosesStackSwitcher))
#define MOSES_STACK_SWITCHER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), MOSES_TYPE_STACK_SWITCHER, MosesStackSwitcherClass))
#define MOSES_IS_STACK_SWITCHER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MOSES_TYPE_STACK_SWITCHER))
#define MOSES_IS_STACK_SWITCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MOSES_TYPE_STACK_SWITCHER))
#define MOSES_STACK_SWITCHER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), MOSES_TYPE_STACK_SWITCHER, MosesStackSwitcherClass))

typedef struct _MosesStackSwitcher              MosesStackSwitcher;
typedef struct _MosesStackSwitcherClass         MosesStackSwitcherClass;

struct _MosesStackSwitcher
{
  GtkBox widget;
};

struct _MosesStackSwitcherClass
{
  GtkBoxClass parent_class;

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

GDK_AVAILABLE_IN_3_10
GType        moses_stack_switcher_get_type          (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_3_10
GtkWidget *  moses_stack_switcher_new               (void);
GDK_AVAILABLE_IN_3_10
void         moses_stack_switcher_set_stack         (MosesStackSwitcher *switcher,
                                                   GtkStack         *stack);
GDK_AVAILABLE_IN_3_10
GtkStack *   moses_stack_switcher_get_stack         (MosesStackSwitcher *switcher);

G_END_DECLS

#endif /* __MOSES_STACK_SWITCHER_H__ */
