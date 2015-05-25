/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#ifndef __MOSES_CLOCK_H__
#define __MOSES_CLOCK_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define TYPE_MOSES_CLOCK moses_clock_get_type()

#define MOSES_CLOCK(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  TYPE_MOSES_CLOCK, MosesClock))

#define MOSES_CLOCK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  TYPE_MOSES_CLOCK, MosesClockClass))

#define IS_MOSES_CLOCK(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  TYPE_MOSES_CLOCK))

#define IS_MOSES_CLOCK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  TYPE_MOSES_CLOCK))

#define MOSES_CLOCK_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  TYPE_MOSES_CLOCK, MosesClockClass))

typedef struct _MosesClock MosesClock;
typedef struct _MosesClockClass MosesClockClass;
typedef struct _MosesClockPrivate MosesClockPrivate;

struct _MosesClock
{
    GtkWidget parent;

    MosesClockPrivate *priv;
};

struct _MosesClockClass
{
    GtkWidgetClass parent_class;
};

GType moses_clock_get_type (void) G_GNUC_CONST;

MosesClock *moses_clock_new();

void moses_clock_set_digital(MosesClock *clock, gboolean digital);
gboolean moses_clock_get_digital(MosesClock *clock);

G_END_DECLS

#endif /* __MOSES_CLOCK_H__ */
