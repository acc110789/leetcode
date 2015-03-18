/* Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

/* http://zetcode.com/tutorials/gtktutorial/customwidget/ */

#ifndef __CPU_H
#define __CPU_H

#include <gtk/gtk.h>

G_BEGIN_DECLS


#define GTK_TYPE_CPU gtk_cpu_get_type()
#if 0
#define GTK_CPU(obj) GTK_CHECK_CAST(obj, gtk_cpu_get_type(), GtkCpu)
#endif
#define GTK_CPU(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, GTK_TYPE_CPU, GtkCpu)
/*
 * Even GTK_CHECK_CLASS_CAST and GTK_CHECK_TYPE do not throw exception, it is
 * better to use Gtk3.x style.
 */
#if 0
#define GTK_CPU_CLASS(klass) GTK_CHECK_CLASS_CAST(klass, gtk_cpu_get_type(), GtkCpuClass)
#endif
#define GTK_CPU_CLASS(klass) G_TYPE_CHECK_CLASS_CAST(klass, GTK_TYPE_CPU, GtkCpuClass)
#if 0
#define GTK_IS_CPU(obj) GTK_CHECK_TYPE(obj, gtk_cpu_get_type())
#endif
#define GTK_IS_CPU(obj) G_TYPE_CHECK_INSTANCE_TYPE(obj, GTK_TYPE_CPU)
#define GTK_IS_CPU_CLASS(klass) G_TYPE_CHECK_CLASS_TYPE(klass, GTK_TYPE_CPU)
#define GTK_CPU_GET_CLASS(obj) G_TYPE_INSTANCE_GET_CLASS(obj, GTK_TYPE_CPU, GtkCpuClass)


typedef struct _GtkCpu GtkCpu;
typedef struct _GtkCpuClass GtkCpuClass;
typedef struct _GtkCpuPrivate GtkCpuPrivate;


struct _GtkCpu {
    GtkWidget widget;

    GtkCpuPrivate *priv;
};

struct _GtkCpuClass {
    GtkWidgetClass parent_class;
};

GType/* there is no GtkType any more in Gtk3.x */ gtk_cpu_get_type(void) G_GNUC_CONST;
/* G_GNUC_CONST
 *
 * https://developer.gnome.org/glib/stable/glib-Miscellaneous-Macros.html#G-GNUC-CONST:CAPS
 *
 */

void gtk_cpu_set_sel(GtkCpu *cpu, gint sel);
GtkCpu* gtk_cpu_new();


G_END_DECLS

#endif /* __CPU_H */
