/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>
#include <string.h>

#define MENU_SIZE 128

static GtkWidget *m_window = NULL;
static GtkWidget *m_popup = NULL;

static void m_destroy_cb(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit(); 
}

static void m_menu_position(GtkMenu *menu, 
                            gint *x, 
                            gint *y, 
                            gint *push_in, 
                            gpointer user_data) 
{
    GdkEventButton *event = (GdkEventButton *) user_data;
    int menu_xpos = event->x;
    int menu_ypos = event->y;

    printf("DEBUG: %s, (%d, %d)\n", __func__, menu_xpos, menu_ypos);
    gdk_window_get_root_coords(gtk_widget_get_window(m_window), 
        menu_xpos, menu_ypos, &menu_xpos, &menu_ypos);
    printf("DEBUG: %s, (%d, %d)\n", __func__, menu_xpos, menu_ypos);
    *x = menu_xpos;
    *y = menu_ypos;
    *push_in = TRUE;
}

static void m_button_press_cb(GtkStatusIcon *status_icon, 
                              GdkEventButton *event, 
                              gpointer user_data) 
{
    if (event->button != 3)
        return;

    gtk_widget_show_all(m_popup);
    gtk_menu_popup(GTK_MENU(m_popup), 
        NULL, NULL, 
        m_menu_position/*NULL*/, 
        event, 
        event->button, event->time);
}

int main(int argc, char *argv[]) 
{
    GtkWidget *vbox = NULL;
    GtkWidget *combo = NULL;
    char buf[16];

    gtk_init(&argc, &argv);
    
    /* TODO: popup */
    m_popup = gtk_menu_new();
    for (int i = 0; i < MENU_SIZE; i++) {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf) - 1, "item %d", i + 1);
        gtk_menu_shell_append(GTK_MENU_SHELL(m_popup), 
            gtk_menu_item_new_with_label(buf));
    }

    /* TODO: window */
    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(m_window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(m_window), 16);
    g_object_connect(G_OBJECT(m_window), 
        "signal::destroy", G_CALLBACK(m_destroy_cb), NULL, 
        "signal::button-press-event", G_CALLBACK(m_button_press_cb), NULL,
        NULL);

    /* TODO: vbox */
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    /* TODO: combo */
    combo = gtk_combo_box_text_new();
    for (int i = 0; i < MENU_SIZE; i++) {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf) - 1, "item %d", i + 1);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), buf);
    }
    gtk_box_pack_start(GTK_BOX(vbox), combo, FALSE, FALSE, 0);

    /* TODO: add */
    gtk_container_add(GTK_CONTAINER(m_window), vbox);

    gtk_widget_show_all(m_window);

    /* TODO: main loop */
    gtk_main();

    return 0;
}
