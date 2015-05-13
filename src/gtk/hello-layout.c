/* Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>

static GtkWidget *m_spin_hour = NULL;
static GtkWidget *m_spin_minute = NULL;

static void m_destroy_cb(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit();
}

static void m_value_changed(GtkSpinButton *spin, gpointer user_data) 
{
    /* timedate1_call_set_time org.freedesktop.timedate1 system bus */
}

static gboolean m_timeout_cb(gpointer user_data) 
{
    GDateTime *now = NULL;
    
    g_signal_handlers_block_by_func(m_spin_hour, m_value_changed, NULL);
    g_signal_handlers_block_by_func(m_spin_minute, m_value_changed, NULL);

    now = g_date_time_new_now_local();
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(m_spin_hour), g_date_time_get_hour(now));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(m_spin_minute), g_date_time_get_minute(now));

    g_signal_handlers_unblock_by_func(m_spin_minute, m_value_changed, NULL);
    g_signal_handlers_unblock_by_func(m_spin_hour, m_value_changed, NULL);

    g_date_time_unref(now);
    now = NULL;

    return TRUE;
}

int main(int argc, char *argv[]) 
{
    GtkWidget *window = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *button = NULL;
    GtkWidget *align = NULL;    /* deprecated */

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(m_destroy_cb), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    m_spin_hour = gtk_spin_button_new_with_range(.0, 23.0, 1.0);
    g_signal_connect(m_spin_hour, "value-changed", G_CALLBACK(m_value_changed), NULL);
    gtk_widget_set_margin_top(m_spin_hour, 30);
    gtk_widget_set_margin_end(m_spin_hour, 10);
    gtk_widget_set_margin_bottom(m_spin_hour, 30);
    gtk_widget_set_margin_start(m_spin_hour, 10);
    gtk_box_pack_start(GTK_BOX(vbox), m_spin_hour, FALSE, FALSE, 0);

    m_spin_minute = gtk_spin_button_new_with_range(.0, 59.0, 1.0);
    g_signal_connect(m_spin_minute, "value-changed", G_CALLBACK(m_value_changed), NULL);
    align = gtk_alignment_new(0, 0, 0, 0);
    gtk_alignment_set_padding(GTK_ALIGNMENT(align), 10, 10, 10, 10);
    gtk_container_add(GTK_CONTAINER(align), m_spin_minute);
    gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("Click me");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    g_timeout_add(1000, m_timeout_cb, NULL);
    m_timeout_cb(NULL);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
