/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include "moses-clock.h"
#include "hello-resources.h"

#include <time.h>
#include <glib-object.h>

#define GTK_PARAM_READWRITE G_PARAM_READWRITE|G_PARAM_STATIC_NAME|G_PARAM_STATIC_NICK|G_PARAM_STATIC_BLURB
#define DIGITAL_PADDING 10

struct _MosesClockPrivate
{
    GdkWindow   *window;
    
    GdkPixbuf   *digital_pixbuf[10];
    GdkPixbuf   *clock_pixbuf;
    GdkPixbuf   *clock_night_pixbuf;
    GdkPixbuf   *center_pixbuf;
    GdkPixbuf   *hour_pixbuf;
    GdkPixbuf   *minute_pixbuf;
    GdkPixbuf   *second_pixbuf;
    
    gboolean    digital;
};

G_DEFINE_TYPE_WITH_PRIVATE(MosesClock, moses_clock, GTK_TYPE_WIDGET)

enum {
    PROP_0, 
    PROP_DIGITAL
};

static gboolean m_timeout_cb(gpointer user_data);

static void moses_clock_get_property(GObject    *object,
                                     guint       property_id,
                                     GValue     *value,
                                     GParamSpec *pspec)
{
    MosesClock *clock = MOSES_CLOCK(object);
    MosesClockPrivate *priv = clock->priv;
    switch (property_id) {
    case PROP_DIGITAL:
        g_value_set_boolean(value, priv->digital);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

gboolean moses_clock_get_digital(MosesClock *clock) 
{ 
    return clock->priv->digital; 
}

void moses_clock_set_digital(MosesClock *clock, gboolean digital) 
{
    MosesClockPrivate *priv = clock->priv;

    if (priv->digital != digital) {
        priv->digital = digital;
        gtk_widget_queue_draw(GTK_WIDGET(clock));
        g_object_notify(G_OBJECT(clock), "digital");
    }
}

static void moses_clock_set_property(GObject      *object,
                                     guint         property_id,
                                     const GValue *value,
                                     GParamSpec   *pspec)
{
    MosesClock *clock = MOSES_CLOCK(object);
    
    switch (property_id) {
    case PROP_DIGITAL:
        moses_clock_set_digital(clock, g_value_get_boolean(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

static void moses_clock_dispose(GObject *object)
{
    MosesClockPrivate *priv = MOSES_CLOCK(object)->priv;

    if (priv->clock_pixbuf) {
        g_object_unref(priv->clock_pixbuf); 
        priv->clock_pixbuf = NULL;
    }
    
    if (priv->clock_night_pixbuf) {
        g_object_unref(priv->clock_night_pixbuf); 
        priv->clock_night_pixbuf = NULL;
    }
    
    if (priv->center_pixbuf) {
        g_object_unref(priv->center_pixbuf); 
        priv->center_pixbuf = NULL;
    }

    if (priv->hour_pixbuf) {
        g_object_unref(priv->hour_pixbuf); 
        priv->hour_pixbuf = NULL;
    }

    if (priv->minute_pixbuf) {
        g_object_unref(priv->minute_pixbuf); 
        priv->minute_pixbuf = NULL;
    }
    
    if (priv->second_pixbuf) {
        g_object_unref(priv->second_pixbuf); 
        priv->second_pixbuf = NULL;
    }
    
    /* virtual */
    G_OBJECT_CLASS(moses_clock_parent_class)->dispose(object);
}

static void moses_clock_finalize(GObject *object)
{
    G_OBJECT_CLASS(moses_clock_parent_class)->finalize(object);
}

static void moses_clock_destroy(GtkWidget *widget) 
{
    GTK_WIDGET_CLASS(moses_clock_parent_class)->destroy(widget);
}

static void moses_clock_get_preferred_width(GtkWidget *widget,
                                            gint      *minimum,
                                            gint      *natural)
{
    MosesClock *clock = MOSES_CLOCK(widget);
    MosesClockPrivate *priv = clock->priv;
    
    if (minimum) {
        if (priv->digital) 
            *minimum = 316;
        else 
            *minimum = 200;
    }
    
    if (natural) 
        *natural = 316;
}

static void moses_clock_get_preferred_height(GtkWidget *widget,
                                             gint      *minimum,
                                             gint      *natural)
{
    MosesClock *clock = MOSES_CLOCK(widget);
    MosesClockPrivate *priv = clock->priv;
    
    if (minimum) {
        if (priv->digital) 
            *minimum = 125;
        else 
            *minimum = 200;
    }

    if (natural) 
        *natural = 200;
}

static void moses_clock_size_allocate(GtkWidget     *widget,
                                      GtkAllocation *allocation)
{
    MosesClockPrivate *priv = MOSES_CLOCK(widget)->priv;
   
    gtk_widget_set_allocation(widget, allocation);

    if (gtk_widget_get_realized(widget)) {
        gdk_window_move_resize(priv->window, allocation->x, allocation->y, 
            allocation->width, allocation->height);
    }
}

static void moses_clock_realize(GtkWidget *widget)
{
    MosesClockPrivate *priv = MOSES_CLOCK(widget)->priv;
    GtkAllocation allocation;
    GdkWindowAttr attributes;

    gtk_widget_get_allocation(widget, &allocation);

    GTK_WIDGET_CLASS(moses_clock_parent_class)->realize(widget);

    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.wclass = GDK_INPUT_ONLY;
    attributes.width = allocation.width;
    attributes.height = allocation.height;
    attributes.x = allocation.x;
    attributes.y = allocation.y;
    attributes.event_mask = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;

    priv->window = gdk_window_new(gtk_widget_get_window(widget), 
                                  &attributes, GDK_WA_X | GDK_WA_Y);

    gtk_widget_register_window(widget, priv->window);
}

static void moses_clock_unrealize(GtkWidget *widget) 
{
    MosesClockPrivate *priv = MOSES_CLOCK(widget)->priv;

    if (priv->window) {
         gtk_widget_unregister_window(widget, priv->window);
         gdk_window_destroy(priv->window);
         priv->window = NULL;
    }

    GTK_WIDGET_CLASS(moses_clock_parent_class)->unrealize(widget);
}

static double m_radians(double degree) 
{ 
    return degree * G_PI / 180.0; 
}

static void m_draw_hand(cairo_t *cr, 
                        GdkPixbuf *pixbuf, 
                        int ox, 
                        int y, 
                        double value) 
{
    int width = gdk_pixbuf_get_width(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);
    int oy = y + height / 2;
    
    cairo_save(cr);
    cairo_translate(cr, ox, oy);                                                
    cairo_rotate(cr, value);                  
    cairo_translate(cr, -width / 2, -height / 2);                     
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);                          
    cairo_paint(cr);
    cairo_restore(cr);
}

static gboolean moses_clock_draw(GtkWidget *widget, cairo_t *cr)
{
    MosesClockPrivate *priv = MOSES_CLOCK(widget)->priv;
    GtkAllocation alloc;
    int width = gdk_pixbuf_get_width(priv->clock_pixbuf);
    int height = gdk_pixbuf_get_height(priv->clock_pixbuf);
    int x = 0, y = 0, ox = 0;
    time_t cur_time = time(NULL);
    struct tm *local_tm = localtime(&cur_time);
    int i;

    /* allocate */
    gtk_widget_get_allocation(widget, &alloc);
    ox = x + width / 2;
    
    /* digital clock */
    if (priv->digital) {
        int hour = local_tm->tm_hour;
        int minute = local_tm->tm_min;
        int digital_arr[4] = {hour / 10, hour - (hour / 10) * 10, 
            minute / 10, minute - (minute / 10) * 10};
        
        width = gdk_pixbuf_get_width(priv->digital_pixbuf[0]);
        int x_arr[4] = {0, width + DIGITAL_PADDING, 
            width * 2 + DIGITAL_PADDING * 3, width * 3 + DIGITAL_PADDING * 4};

        for (i = 0; i < 4; i++) {
            cairo_save(cr);
            gdk_cairo_set_source_pixbuf(cr, 
                priv->digital_pixbuf[digital_arr[i]], x_arr[i], y);
            cairo_paint(cr);
            cairo_restore(cr);
        }

        return FALSE;
    }
    
    /* paint clock */
    cairo_save(cr);
    if (local_tm->tm_hour < 18 && local_tm->tm_hour > 6)
        gdk_cairo_set_source_pixbuf(cr, priv->clock_pixbuf, x, y);
    else 
        gdk_cairo_set_source_pixbuf(cr, priv->clock_night_pixbuf, x, y);
    cairo_paint(cr);
    cairo_restore(cr);
    /* paint hour */
    m_draw_hand(cr, priv->hour_pixbuf, ox, y, 
        m_radians(360 * local_tm->tm_hour / 12 + local_tm->tm_min * 0.5));
    /* paint minute */
    m_draw_hand(cr, priv->minute_pixbuf, ox, y, 
        m_radians(360 * local_tm->tm_min / 60));
    /* paint second */
    m_draw_hand(cr, priv->second_pixbuf, ox, y, 
        m_radians(360 * local_tm->tm_sec / 60));
    /* paint center */
    cairo_save(cr);
    gdk_cairo_set_source_pixbuf(cr,                                             
                        priv->center_pixbuf,                                   
                        x + (width - gdk_pixbuf_get_width(priv->center_pixbuf)) / 2,  
                        y + (height - gdk_pixbuf_get_height(priv->center_pixbuf)) / 2); 
    cairo_paint(cr);
    cairo_restore(cr);
    
    return FALSE;
}

static void moses_clock_map(GtkWidget *widget)
{                                                                               
    MosesClock *clock = MOSES_CLOCK(widget);  
    MosesClockPrivate *priv = clock->priv;                   
                                                                                
    GTK_WIDGET_CLASS(moses_clock_parent_class)->map(widget);
    
    gdk_window_show(priv->window);
}

static void moses_clock_unmap(GtkWidget *widget) 
{
    MosesClock *clock = MOSES_CLOCK(widget);
    MosesClockPrivate *priv = clock->priv;

    gdk_window_hide(priv->window);

    GTK_WIDGET_CLASS(moses_clock_parent_class)->unmap(widget);
}

static void moses_clock_class_init(MosesClockClass *klass)
{
    GObjectClass    *gobject_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS(klass);

    /* gobject class */
    gobject_class->get_property = moses_clock_get_property;
    gobject_class->set_property = moses_clock_set_property;
    gobject_class->dispose = moses_clock_dispose;
    gobject_class->finalize = moses_clock_finalize;
    
    /* widget class */
    widget_class->destroy = moses_clock_destroy;
    widget_class->get_preferred_width = moses_clock_get_preferred_width;
    widget_class->get_preferred_height = moses_clock_get_preferred_height;
    widget_class->size_allocate = moses_clock_size_allocate;
    widget_class->map = moses_clock_map;
    widget_class->unmap = moses_clock_unmap;
    widget_class->realize = moses_clock_realize;
    widget_class->unrealize = moses_clock_unrealize;
    widget_class->draw = moses_clock_draw;
    
    /* property */
    g_object_class_install_property(gobject_class,                               
                                    PROP_DIGITAL,                                   
                                    g_param_spec_boolean("digital", 
                                                         "Digital",                
                                                         "Whether a digital clock or not", 
                                                         FALSE, 
                                                         GTK_PARAM_READWRITE));
}

static gboolean m_timeout_cb(gpointer user_data) 
{
    MosesClock *clock = MOSES_CLOCK(user_data);

    gtk_widget_queue_draw(GTK_WIDGET(clock));
    
    return TRUE;
}

static void moses_clock_init(MosesClock *self)
{
    GtkWidget *widget = GTK_WIDGET(self);
    MosesClockPrivate *priv = self->priv = moses_clock_get_instance_private(self);
    GError *err = NULL;
    char buf[32];
    
    gtk_widget_set_has_window(widget, FALSE);

    /* main window */
    priv->window = NULL;

    hello_get_resource();

    /* digital 0~9 pixbuf */
    for (int i = 0; i <= 9; i++) {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf) - 1, "/org/moses/hello/assets/%d.png", i);
        priv->digital_pixbuf[i] = gdk_pixbuf_new_from_resource(buf, NULL);
    }

    /* clock pixbuf */
    priv->clock_pixbuf = gdk_pixbuf_new_from_resource(
        "/org/moses/hello/assets/clock.png", &err);
    if (!priv->clock_pixbuf) {
        g_warning("Could not load clock image: %s", 
                  (err) ? err->message : "Unknown error");
        g_clear_error(&err);
    }

    /* clock night pixbuf */                                                                 
    priv->clock_night_pixbuf = gdk_pixbuf_new_from_resource(
        "/org/moses/hello/assets/clock-night.png", &err);         
    if (!priv->clock_night_pixbuf) {                                                         
        g_warning("Could not load clock night image: %s",                             
                  (err) ? err->message : "Unknown error");                      
        g_clear_error(&err);                                                    
    }

    /* center pixbuf */
    priv->center_pixbuf = gdk_pixbuf_new_from_resource(
        "/org/moses/hello/assets/center.png", &err);
    if (!priv->center_pixbuf) {
        g_warning("Could not load center image: %s", 
                  (err) ? err->message : "Unknown error");
        g_clear_error(&err);
    }

    /* hour pixbuf */
    priv->hour_pixbuf = gdk_pixbuf_new_from_resource(
        "/org/moses/hello/assets/hour.png", &err);
    if (!priv->hour_pixbuf) {
        g_warning("Could not load hour image: %s", 
                  (err) ? err->message : "Unknown error");
        g_clear_error(&err);
    }

    /* minute pixbuf */
    priv->minute_pixbuf = gdk_pixbuf_new_from_resource(
        "/org/moses/hello/assets/minute.png", &err);           
    if (!priv->minute_pixbuf) {                                                          
        g_warning("Could not load minute image: %s",                                 
                  (err) ? err->message : "Unknown error");                      
        g_clear_error(&err);                                                    
    }

    /* second pixbuf */
    priv->second_pixbuf = gdk_pixbuf_new_from_resource(
        "/org/moses/hello/assets/second.png", &err);           
    if (!priv->second_pixbuf) {                                                          
        g_warning("Could not load second image: %s",                                 
                  (err) ? err->message : "Unknown error");                      
        g_clear_error(&err);                                                    
    }

    /* digital */
    priv->digital = FALSE;
    
    /* timer */
    g_timeout_add(1000, (GSourceFunc)m_timeout_cb, self);
}

MosesClock *moses_clock_new() 
{ 
    return g_object_new(TYPE_MOSES_CLOCK, NULL); 
}
