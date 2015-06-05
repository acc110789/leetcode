/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

static GtkWidget *m_window = NULL;
static GtkWidget *m_popup = NULL;
static GtkWidget *m_dialog = NULL;

static void m_destroy_cb(GtkWidget *widget, gpointer user_data) 
{
    gtk_main_quit(); 
}

static GdkRectangle m_get_monitor_geo()
{
    GdkRectangle r;
    GdkDisplay* disp = gdk_display_get_default();
    GdkScreen* screen = gdk_display_get_default_screen(disp);
    gint mon_id = gdk_screen_get_primary_monitor(screen);

    gdk_screen_get_monitor_geometry(screen, mon_id, &r);

    return r;
}

static void m_menu_position(GtkMenu *menu, 
                            gint *x, 
                            gint *y, 
                            gint *push_in, 
                            gpointer user_data) 
{
    GtkWidget *active = gtk_menu_get_active(menu);
    GdkEventButton *event = (GdkEventButton *) user_data;
    int menu_xpos = event->x;
    int menu_ypos = event->y;
    GtkAllocation allocation;
    GdkRectangle display_rect = m_get_monitor_geo();

    if (active) {
        gtk_menu_shell_select_item(GTK_MENU_SHELL(m_popup), active);
        gtk_widget_get_allocation(active, &allocation);
    }

    gtk_widget_get_allocation(GTK_WIDGET(menu), &allocation);
    if (display_rect.height - event->y_root < allocation.height)
        menu_ypos -= allocation.height;

    printf("DEBUG: %s (%d, %d)\n", __func__, menu_xpos, menu_ypos);
    gdk_window_get_root_coords(gtk_widget_get_window(m_window), 
        menu_xpos, menu_ypos, &menu_xpos, &menu_ypos);
    printf("DEBUG: %s (%d, %d)\n", __func__, menu_xpos, menu_ypos);
    *x = menu_xpos;
    *y = menu_ypos;
    *push_in = TRUE;
}

static void m_button_press_cb(GtkStatusIcon *status_icon, 
                              GdkEventButton *event, 
                              gpointer user_data) 
{
    if (event->button != GDK_BUTTON_SECONDARY)
        return;
    
    gtk_widget_show_all(m_popup);
    gtk_menu_popup(GTK_MENU(m_popup), 
        NULL, NULL, 
        m_menu_position/*NULL*/, 
        event, 
        event->button, event->time);
}

static void m_dialog_destroy_cb(GtkDialog *dialog, gpointer user_data) 
{
    printf("DEBUG: %s\n", __func__);
    if (m_dialog) {
        gtk_widget_destroy(m_dialog);
        m_dialog = NULL;
    }
}

static void m_changed_cb(GtkComboBoxText *combo, gpointer user_data) 
{
    GtkWidget *content_area = NULL;

    if (m_dialog)
        return;

    m_dialog = gtk_dialog_new_with_buttons(
            gtk_combo_box_text_get_active_text(combo), 
            GTK_WINDOW(m_window), 
            GTK_DIALOG_MODAL | GTK_DIALOG_USE_HEADER_BAR, 
            NULL, NULL, 
            NULL, NULL, 
            NULL);
    gtk_window_set_default_size(GTK_WINDOW(m_dialog), 800, 600);
    g_object_connect(G_OBJECT(m_dialog), 
        "signal::destroy", G_CALLBACK(m_dialog_destroy_cb), NULL, 
        NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(m_dialog));
    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Content"));

    gtk_widget_show_all(m_dialog);

    /* FIXME: gtk_dialog_run has a side-effect 
     * https://bugzilla.gnome.org/show_bug.cgi?id=750384#c1
    switch (gtk_dialog_run(GTK_DIALOG(m_dialog))) {
    case GTK_RESPONSE_CANCEL:
    default:
        gtk_widget_destroy(m_dialog);
        m_dialog = NULL;
        break;
    }
    */
}

int main(int argc, char *argv[]) 
{
    GtkWidget *vbox = NULL;
    GtkWidget *combo = NULL;
    char buf[16];
    unsigned int menu_size;

    menu_size = argv[1] ? atoi(argv[1]) : 8;

    gtk_init(&argc, &argv);
    
    /* TODO: popup */
    m_popup = gtk_menu_new();
    for (int i = 0; i < menu_size; i++) {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf) - 1, "item %d", i + 1);
        gtk_menu_shell_append(GTK_MENU_SHELL(m_popup), 
            gtk_menu_item_new_with_label(buf));
    }

    /* TODO: window */
    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(m_window), 200, 600);
    gtk_container_set_border_width(GTK_CONTAINER(m_window), 16);
    g_object_connect(G_OBJECT(m_window), 
        "signal::destroy", G_CALLBACK(m_destroy_cb), NULL, 
        "signal::button-press-event", G_CALLBACK(m_button_press_cb), NULL,
        NULL);

    /* TODO: vbox */
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    /* TODO: combo */
    combo = gtk_combo_box_text_new();
    for (int i = 0; i < menu_size; i++) {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf) - 1, "item %d", i + 1);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), buf);
    }
    g_object_connect(G_OBJECT(combo), 
        "signal::changed", G_CALLBACK(m_changed_cb), NULL, 
        NULL);
    gtk_box_pack_start(GTK_BOX(vbox), combo, FALSE, FALSE, 0);

    /* TODO: add */
    gtk_container_add(GTK_CONTAINER(m_window), vbox);

    gtk_widget_show_all(m_window);

    /* TODO: main loop */
    gtk_main();

    return 0;
}
