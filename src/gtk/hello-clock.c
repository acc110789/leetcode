/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>

#include "moses-clock.h"

static void m_destroy_cb(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit(); 
}

int main(int argc, char *argv[]) 
{
    GtkWidget *window = NULL;
    GtkWidget *clock = NULL;

    gtk_init(&argc, &argv);
    
    /* TODO: window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(m_destroy_cb), NULL);

    /* TODO: clock */
    clock = moses_clock_new();

    /* TODO: add */
    gtk_container_add(GTK_CONTAINER(window), clock);

    gtk_widget_show_all(window);

    /* TODO: main loop */
    gtk_main();

    return 0;
}
