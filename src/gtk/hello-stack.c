/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>

#include "moses-stackswitcher.h"
#include "moses-iconview.h"

static GtkCssProvider *m_provider = NULL;

static void m_destroy_cb(GtkWidget *widget, gpointer user_data) 
{ 
    gtk_main_quit(); 
}

int main(int argc, char *argv[]) 
{
    GdkDisplay *display = NULL;
    GdkScreen *screen = NULL;
    GtkWidget *window = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *stack_switcher = NULL;
    GtkWidget *stack = NULL;
    GtkWidget *icon_view = NULL;
    GtkWidget *calendar = NULL;
    GtkWidget *entry = NULL;
    GtkWidget *label = NULL;

    gtk_init(&argc, &argv);

    m_provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, 
        GTK_STYLE_PROVIDER(m_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_path(m_provider, "./moses-stack.css", NULL);

    /* TODO: window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(m_destroy_cb), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

    stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), 
                                  GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    //gtk_stack_set_transition_duration(GTK_STACK(stack), 1000);

    /* page 1 */
    icon_view = moses_icon_view_new();
    gtk_stack_add_titled(GTK_STACK(stack), icon_view, "icon_view", "Page1");

    /* page 2 */
    gtk_stack_add_titled(GTK_STACK(stack), 
        gtk_radio_button_new_with_label(NULL, "I`m radio"), "radio", "Page2");

    /* page 3 */
    entry = gtk_entry_new();
    gtk_stack_add_titled(GTK_STACK(stack), entry, "entry", "Page3");

    /* page 4 */
    label = gtk_label_new("Hello");
    gtk_stack_add_titled(GTK_STACK(stack), label, "label", "Page4");

    stack_switcher = moses_stack_switcher_new();
    gtk_widget_set_name(stack_switcher, "moses-stackswitcher");
    gtk_widget_set_halign(stack_switcher, GTK_ALIGN_CENTER);
    moses_stack_switcher_set_stack(MOSES_STACK_SWITCHER(stack_switcher), GTK_STACK(stack));

    gtk_box_pack_start(GTK_BOX(vbox), stack, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), stack_switcher, FALSE, FALSE, 0);

    /* TODO: add */
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    gtk_widget_show_all(window);

    /* TODO: main loop */
    gtk_main();

    return 0;
}
