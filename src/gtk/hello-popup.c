/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>

static GtkWidget *event_box = NULL;

static void window_destroy(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit(); 
}

static gboolean on_popup_focus_out(GtkWidget *widget,
                                   GdkEventFocus *event,
                                   gpointer user_data)
{
    gtk_widget_hide(widget);
    
    return TRUE;
}

static GtkWidget *popup_window_new() 
{ 
    GtkWidget *popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(popup_window), FALSE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popup_window), TRUE);
    gtk_window_set_skip_pager_hint(GTK_WINDOW(popup_window), TRUE);
    gtk_widget_set_size_request(popup_window, 150, 150);
    gtk_widget_set_events(popup_window, GDK_FOCUS_CHANGE_MASK);
    g_object_connect(G_OBJECT(popup_window),
        "signal::focus-out-event", G_CALLBACK(on_popup_focus_out), NULL,
        NULL);

    gtk_widget_grab_focus(popup_window);

    return popup_window;
}

static void event_box_button_press(GtkWidget *event_box, 
                                   GdkEventButton *event, 
                                   gpointer user_data) 
{
    GtkWidget *popup_window = (GtkWidget *) user_data;
    
    gtk_window_move(GTK_WINDOW(popup_window), event->x_root, event->y_root);
    gtk_widget_show_all(popup_window);
}

int main(int argc, char *argv[]) 
{
    GtkWidget *window = NULL;
    GtkWidget *icon = NULL;
    GtkWidget *popup_window = NULL;

    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_resize(GTK_WINDOW(window), 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(window_destroy), NULL);
    
    popup_window = popup_window_new();

    event_box = gtk_event_box_new();
    g_signal_connect(event_box, 
                     "button-press-event", 
                     G_CALLBACK(event_box_button_press), 
                     popup_window);

    icon = gtk_image_new_from_icon_name("system-users", GTK_ICON_SIZE_SMALL_TOOLBAR);
    gtk_container_add(GTK_CONTAINER(event_box), icon);

    gtk_container_add(GTK_CONTAINER(window), event_box);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
