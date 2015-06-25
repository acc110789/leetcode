/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>

#include "na-tray-manager.h"

static NaTrayManager *na_tray_manager = NULL;
static GtkWidget *flowbox = NULL;

static void window_destroy(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit(); 
}

static void na_tray_icon_added(NaTrayManager *na_manager, 
                               GtkWidget *socket, 
                               gpointer data)
{
    na_tray_child_set_composited(NA_TRAY_CHILD(socket), FALSE);
    
    gtk_container_add(GTK_CONTAINER(flowbox), socket);

    gtk_widget_set_visual(flowbox, gtk_widget_get_visual(socket));

    gtk_widget_show(socket);
}

static void na_tray_icon_removed(NaTrayManager *na_manager, 
                                 GtkWidget *socket, 
                                 gpointer data)
{
    gtk_container_remove(GTK_CONTAINER(flowbox), socket);
}

int main(int argc, char *argv[]) 
{
    GtkWidget *window = NULL;
    GdkScreen *screen = NULL;
    GtkWidget *scrolled = NULL;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Win7 style systray popup window");
    gtk_window_resize(GTK_WINDOW(window), 300, 100);
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

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), 
                                   GTK_POLICY_NEVER, 
                                   GTK_POLICY_AUTOMATIC);

    flowbox = gtk_flow_box_new();
    g_object_set(G_OBJECT(flowbox),
        "margin", 10, "homogeneous", TRUE, "valign", GTK_ALIGN_START,
        "column-spacing", 10, "row-spacing", 10,
        NULL);
    gtk_container_add(GTK_CONTAINER(scrolled), flowbox);

    gtk_container_add(GTK_CONTAINER(window), scrolled);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
