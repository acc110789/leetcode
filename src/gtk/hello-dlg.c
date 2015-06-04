/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>

static GtkWidget *m_dialog = NULL;

static void m_destroy_cb(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit(); 
}

static gboolean m_button_press_cb(GtkStatusIcon *status_icon, 
                                  GdkEventButton *event, 
                                  gpointer user_data) 
{
    GtkWidget *window = (GtkWidget *)user_data;
    GtkWidget *content_area = NULL;

    if (m_dialog)
        return TRUE;

    m_dialog = gtk_dialog_new_with_buttons("Dialog", 
            GTK_WINDOW(window), 
            GTK_DIALOG_MODAL | GTK_DIALOG_USE_HEADER_BAR, 
            NULL, NULL, 
            NULL, NULL, 
            NULL);
    gtk_window_set_default_size(GTK_WINDOW(m_dialog), 800, 600);
    //gtk_window_set_resizable(GTK_WINDOW(m_dialog), FALSE);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(m_dialog));
    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Content"));

    gtk_widget_show_all(m_dialog);

    switch (gtk_dialog_run(GTK_DIALOG(m_dialog))) {
    case GTK_RESPONSE_CANCEL:
    default:
        gtk_widget_destroy(m_dialog);
        m_dialog = NULL;
        break;
    }

    return TRUE;
}

int main(int argc, char *argv[]) 
{
    GtkWidget *window = NULL;

    gtk_init(&argc, &argv);

    /* TODO: window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "click me");
    gtk_window_fullscreen(GTK_WINDOW(window));
    /* FIXME: resizable FALSE will influence window size */
    //gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DESKTOP);
    g_object_connect(G_OBJECT(window), 
        "signal::destroy", G_CALLBACK(m_destroy_cb), NULL, 
        "signal::button-press-event", G_CALLBACK(m_button_press_cb), window,
        NULL);

    gtk_widget_show_all(window);

    /* TODO: main loop */
    gtk_main();

    return 0;
}
