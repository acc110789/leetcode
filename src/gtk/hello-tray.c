/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>

#include "na-tray-manager.h"

#define TRAY_ICON_SIZE 22

static NaTrayManager *na_tray_manager = NULL;
static GtkWidget *flowbox = NULL;

static void window_destroy(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit(); 
}

/*
 * Thank Florian Müllner`s patch
 * https://bugzilla.gnome.org/show_bug.cgi?id=751485
 *
 */
static gboolean na_tray_draw_icon (GtkWidget *socket,
                                   gpointer   data)
{
    cairo_t *cr = data;
    GtkAllocation allocation;

    if (!NA_IS_TRAY_CHILD (socket))
        return FALSE;

    if (!na_tray_child_has_alpha (NA_TRAY_CHILD (socket)))
        return FALSE;

    gtk_widget_get_allocation (socket, &allocation);

    cairo_save (cr);
#if DEBUG
    g_message ("%s, line %d: (%d, %d) %dx%d\n", 
               __func__, __LINE__, allocation.x, allocation.y, 
               allocation.width, allocation.height);
#endif
    gdk_cairo_set_source_window (cr,
                                 gtk_widget_get_window (socket),
                                 allocation.x,
                                 allocation.y);
    cairo_rectangle (cr,
                     allocation.x, allocation.y,
                     allocation.width, allocation.height);
    cairo_clip (cr);
    cairo_paint (cr);
    cairo_restore (cr);

    return FALSE;
}

static void na_tray_icon_added(NaTrayManager *na_manager, 
                               GtkWidget *socket, 
                               gpointer data)
{
    gtk_box_pack_start(GTK_BOX(flowbox), socket, FALSE, FALSE, 0);

    gtk_widget_show(socket);
}

static void na_tray_icon_removed(NaTrayManager *na_manager, 
                                 GtkWidget *socket, 
                                 gpointer data)
{
    gtk_container_remove(GTK_CONTAINER(flowbox), socket);
}

static gboolean flowbox_draw(GtkWidget *flowbox, cairo_t *cr) 
{
    gtk_container_foreach(GTK_CONTAINER(flowbox), na_tray_draw_icon, cr);
}

int main(int argc, char *argv[]) 
{
    GtkWidget *window = NULL;
    GdkScreen *screen = NULL;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DOCK);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
    gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
    gtk_window_set_accept_focus(GTK_WINDOW(window), FALSE);
    gtk_window_stick(GTK_WINDOW(window));
    /*
     * TODO: Windows 7 style systray popup window
     * 
     * 1. "draw" all tray-children to popup window 
     * 2. when XDamageNotify reorder the child to the first 
     *
     * gtk_window_set_title(GTK_WINDOW(window), "Win7 style systray popup window");
     */
    gtk_window_resize(GTK_WINDOW(window), 100, 40);
    gtk_window_move(GTK_WINDOW(window), gdk_screen_width() - 100, 
        gdk_screen_height() - 40);
    g_signal_connect(window, "destroy", G_CALLBACK(window_destroy), NULL);

    screen = gtk_window_get_screen(GTK_WINDOW(window));

    na_tray_manager = na_tray_manager_new();
    na_tray_manager_manage_screen(na_tray_manager, screen);
    if (!na_tray_manager_check_running(screen))
        g_warning("There might be another systray implemented yet!\n");

    g_object_connect(G_OBJECT(na_tray_manager), 
        "signal::tray_icon_added", G_CALLBACK(na_tray_icon_added), NULL,
        "signal::tray_icon_removed", G_CALLBACK(na_tray_icon_removed), NULL,
        NULL);

    flowbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    g_object_connect(G_OBJECT(flowbox), 
        "signal::draw", G_CALLBACK(flowbox_draw), NULL, 
        NULL);

    gtk_container_add(GTK_CONTAINER(window), flowbox);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
