/* Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include "cpu.h"

#include <glib-object.h>

struct _GtkCpuPrivate 
{
    GdkWindow *window;
    gint sel;
};

G_DEFINE_TYPE_WITH_PRIVATE(GtkCpu, gtk_cpu, GTK_TYPE_WIDGET/* parent class */)

static void gtk_cpu_class_init(GtkCpuClass *klass);
static void gtk_cpu_init(GtkCpu *cpu);
#if 0
static void gtk_cpu_size_request(GtkWidget *widget,
    GtkRequisition *requisition);
#endif
static void gtk_cpu_get_preferred_width(GtkWidget *widget, 
                                        gint *minimum, 
                                        gint *natural);
static void gtk_cpu_get_preferred_height(GtkWidget *widget, 
                                         gint *minimum, 
                                         gint *natural);
static void gtk_cpu_size_allocate(GtkWidget *widget,
    GtkAllocation *allocation);
static void gtk_cpu_realize(GtkWidget *widget);
static gboolean gtk_cpu_expose(GtkWidget *widget, cairo_t *cr);
static void gtk_cpu_paint(GtkWidget *widget, cairo_t *cr);
#if 0
static void gtk_cpu_destroy(GObject/*there is no GtkObject any more in Gtk3.x*/ *object);
#endif


/* It is useless for Gtk3.x */
#if 0
GtkType
gtk_cpu_get_type(void)
{
  static GtkType gtk_cpu_type = 0;


  if (!gtk_cpu_type) {
      static const GtkTypeInfo gtk_cpu_info = {
          "GtkCpu",
          sizeof(GtkCpu),
          sizeof(GtkCpuClass),
          (GtkClassInitFunc) gtk_cpu_class_init,
          (GtkObjectInitFunc) gtk_cpu_init,
          NULL,
          NULL,
          (GtkClassInitFunc) NULL
      };
      gtk_cpu_type = gtk_type_unique(GTK_TYPE_WIDGET, &gtk_cpu_info);
  }


  return gtk_cpu_type;
}
#endif


/*
 * It is better to call gtk_widget_queue_draw.
 */
#if 0
void
gtk_cpu_set_state(GtkCpu *cpu, gint num)
{
   cpu->sel = num;
   gtk_cpu_paint(GTK_WIDGET(cpu));
}
#endif
void gtk_cpu_set_sel(GtkCpu *cpu, gint sel) 
{
    GtkCpuPrivate *priv = cpu->priv;
    
    priv->sel = sel;

    gtk_widget_queue_draw(GTK_WIDGET(cpu));
}


#if 0
GtkWidget * gtk_cpu_new()
{
    return GTK_WIDGET(gtk_type_new(gtk_cpu_get_type()));
}
#endif
GtkCpu *gtk_cpu_new() 
{
    return g_object_new(gtk_cpu_get_type(), NULL);
}


static void gtk_cpu_map(GtkWidget *widget) 
{
    GtkCpuPrivate *priv = GTK_CPU(widget)->priv;

    GTK_WIDGET_CLASS(gtk_cpu_parent_class)->map(widget);

    gdk_window_show(priv->window);
}


/* 
 * Doubt about Gtk2.x style, is there no destructor for map, realize nor others? 
 */
static void
gtk_cpu_class_init(GtkCpuClass *klass)
{
    GtkWidgetClass *widget_class;
    GObjectClass/* there is no GtkObjectClass any more in Gtk3.x */ *object_class;

    widget_class = (GtkWidgetClass *)klass;
    object_class = (GObjectClass *)klass;

    /* There is no map override style for Gtk2.x */
    widget_class->map = gtk_cpu_map;

    widget_class->realize = gtk_cpu_realize;
    /*
     * In Gtk3.x, it has to override get_preferred_width and get_preferred_height
     */
#if 0
    widget_class->size_request = gtk_cpu_size_request;
#endif
    widget_class->get_preferred_width = gtk_cpu_get_preferred_width;
    widget_class->get_preferred_height = gtk_cpu_get_preferred_height;
    widget_class->size_allocate = gtk_cpu_size_allocate;
    widget_class->draw/* there is no expose_event any more in Gtk3.x */ = gtk_cpu_expose;

    /*
     * There is no destroy for GObjectClass, but dispose and finalize instead.
     */
#if 0
    object_class->destroy = gtk_cpu_destroy;
#endif
}


static void 
gtk_cpu_init(GtkCpu *self)
{
    GtkWidget *widget = GTK_WIDGET(self);
    GtkCpuPrivate *priv = self->priv = gtk_cpu_get_instance_private(self);

    gtk_widget_set_has_window(widget, FALSE);

    priv->window = NULL;
    priv->sel = 0;
}


#if 0
static void
gtk_cpu_size_request(GtkWidget *widget,
    GtkRequisition *requisition)
{
    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CPU(widget));
    g_return_if_fail(requisition != NULL);

    requisition->width = 80;
    requisition->height = 100;
}
#endif
static void gtk_cpu_get_preferred_width(GtkWidget *widget, 
                                        gint *minimum, 
                                        gint *natural) 
{
    if (minimum) *minimum = 80;
    if (natural) *natural = 80;
}


static void gtk_cpu_get_preferred_height(GtkWidget *widget, 
                                         gint *minimum, 
                                         gint *natural) 
{
    if (minimum) *minimum = 100;
    if (natural) *natural = 100;
}


static void
gtk_cpu_size_allocate(GtkWidget *widget,
    GtkAllocation *allocation)
{
    GtkCpuPrivate *priv = GTK_CPU(widget)->priv;
    
    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CPU(widget));
    g_return_if_fail(allocation != NULL);

#if 0
    widget->allocation = *allocation;
#endif
    gtk_widget_set_allocation(widget, allocation);

    if (gtk_widget_get_realized/* there is no GTK_WIDGET_REALIZED in Gtk3.x  */(widget)) {
        gdk_window_move_resize(
            priv->window,
            allocation->x, allocation->y,
            allocation->width, allocation->height
        );
    }
}


static void
gtk_cpu_realize(GtkWidget *widget)
{
    GtkCpuPrivate *priv = GTK_CPU(widget)->priv;
    GdkWindowAttr attributes;
    GtkAllocation allocation;
    guint attributes_mask;

    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CPU(widget));

    gtk_widget_get_allocation(widget, &allocation);

    GTK_WIDGET_CLASS(gtk_cpu_parent_class)->realize(widget);

#if 0
    GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);
#endif

    attributes.window_type = GDK_WINDOW_CHILD;
#if 0
    attributes.x = widget->allocation.x;
    attributes.y = widget->allocation.y;
#endif
    attributes.x = allocation.x;
    attributes.y = allocation.y;
    attributes.width = 80;
    attributes.height = 100;

    attributes.wclass = GDK_INPUT_OUTPUT;
    attributes.event_mask = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;

    attributes_mask = GDK_WA_X | GDK_WA_Y;

    priv->window = gdk_window_new(
            gtk_widget_get_parent_window(widget),
            &attributes, attributes_mask);

    /*
     * Gtk3.x it often use gtk_widget_register_window(widget, priv->window);
     */
    gdk_window_set_user_data(priv->window, widget);
#if 0
    widget->style = gtk_style_attach(widget->style, priv->window);
    gtk_style_set_background(widget->style, priv->window, GTK_STATE_NORMAL);
#endif
}


/*
 * There is no cairo_t* such arg in Gtk2.x
 */
static gboolean
gtk_cpu_expose(GtkWidget *widget, cairo_t *cr)
{
    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(GTK_IS_CPU(widget), FALSE);
#if 0
    g_return_val_if_fail(event != NULL, FALSE);
#endif
    gtk_cpu_paint(widget, cr);

    return FALSE;
}


static void
gtk_cpu_paint(GtkWidget *widget, cairo_t *cr)
{
    GtkCpuPrivate *priv = GTK_CPU(widget)->priv;
#if 0
    cairo_t *cr;

    cr = gdk_cairo_create(widget->window);
#endif
    cairo_translate(cr, 0, 7);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);

    gint pos = priv->sel;
    gint rect = pos / 5;

    cairo_set_source_rgb(cr, 0.2, 0.4, 0);

    gint i;
    for ( i = 1; i <= 20; i++) {
        if (i > 20 - rect)
            cairo_set_source_rgb(cr, 0.6, 1.0, 0);
        else
            cairo_set_source_rgb(cr, 0.2, 0.4, 0);

        cairo_rectangle(cr, 8, i*4, 30, 3);
        cairo_rectangle(cr, 42, i*4, 30, 3);
        cairo_fill(cr);
    }
}


#if 0
static void
gtk_cpu_destroy(GtkObject *object)
{
  GtkCpu *cpu;
  GtkCpuClass *klass;

  g_return_if_fail(object != NULL);
  g_return_if_fail(GTK_IS_CPU(object));

  cpu = GTK_CPU(object);

  klass = gtk_type_class(gtk_widget_get_type());

  if (GTK_OBJECT_CLASS(klass)->destroy) {
     (* GTK_OBJECT_CLASS(klass)->destroy) (object);
  }
}
#endif
