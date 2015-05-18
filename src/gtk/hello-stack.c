/* Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <gtk/gtk.h>
#include <string.h>

#include "moses-stackswitcher.h"
#include "moses-iconview.h"

#define ICON_COUNT_LIMIT 256
#define ICON_COUNT_PER_PAGE 28

enum {
    COL_ICON, 
    COL_NAME,
    ICON_COLS
};

enum {
    TARGET_INT32, 
    TARGET_STRING,
};

static GtkTargetEntry target_list[] = {
    { "INTEGER",    0, TARGET_INT32 },
    { "STRING",     0, TARGET_STRING },
};

static guint n_targets = G_N_ELEMENTS(target_list);

static GtkCssProvider *m_provider = NULL;
static GdkScreen *m_screen = NULL;
static GtkListStore *m_store = NULL;
static unsigned int m_store_count = 0;
static GtkWidget *m_stack = NULL;

static void m_destroy_cb(GtkWidget *widget, gpointer user_data) 
{ 
    if (m_store) {
        gtk_list_store_clear(m_store);
        g_object_unref(m_store);
        m_store = NULL;
    }
    
    gtk_main_quit(); 
}

static void m_fill_store() 
{
    GtkIconTheme *icon_theme;
    GList *contexts;
    GtkTreeIter iter;
    char buf[16];
    int l;

    icon_theme = gtk_icon_theme_get_for_screen(m_screen);

    contexts = gtk_icon_theme_list_contexts(icon_theme);
    gtk_list_store_clear(m_store);

    l = ICON_COUNT_LIMIT;
    for (GList *i = contexts; i && l; i = g_list_next(i)) {
        gchar *context = i->data;
        GList *icon_names;

        icon_names = gtk_icon_theme_list_icons(icon_theme, context);
        for (GList *j = icon_names; j && l; j = g_list_next(j), l--) {
            gchar *id = j->data;
            GdkPixbuf *pixbuf = gtk_icon_theme_load_icon(icon_theme, id, 64, 
                GTK_ICON_LOOKUP_FORCE_SIZE, NULL);

            gtk_list_store_append(m_store, &iter);
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf) - 1, "%s", id);
            gtk_list_store_set(m_store, &iter, COL_ICON, pixbuf, COL_NAME, buf, -1);

            m_store_count++;
        }

        g_list_free_full(icon_names, g_free);
    }

    g_list_free_full(contexts, g_free);
}

static gboolean m_drag_motion_cb(MosesIconView *icon_view, 
                                 GdkDragContext *context, 
                                 int x, 
                                 int y, 
                                 guint time,
                                 gpointer user_data) 
{
    gchar *stack_child_name = NULL;
    GtkWidget *stack_child = NULL;
    unsigned int index = 0;
    char buf[16] = {'\0'};
    GtkAllocation allocation;

    gtk_widget_get_allocation(icon_view, &allocation);

    stack_child_name = gtk_stack_get_visible_child_name(m_stack);
    if (stack_child_name == NULL)
        return FALSE;

    if (x < 40)
        index = atoi(stack_child_name) - 1;
    else if (x > allocation.width - 40)
        index = atoi(stack_child_name) + 1;
    
    if (index) {
        snprintf(buf, sizeof(buf) - 1, "%d", index);
        stack_child = gtk_stack_get_child_by_name(m_stack, buf);
        if (stack_child)
            gtk_stack_set_visible_child(m_stack, stack_child);
    }

    return FALSE;
}

static void m_drag_data_get_cb(MosesIconView *icon_view, 
                               GdkDragContext *context, 
                               GtkSelectionData *data, 
                               guint info, 
                               guint time, 
                               gpointer user_data) 
{
    printf("DEBUG: %s %d %d\n", __func__, info, time);
}

static void m_drag_data_received_cb(MosesIconView *icon_view, 
                                    GdkDragContext *context, 
                                    int x, 
                                    int y, 
                                    GtkSelectionData *data, 
                                    guint info, 
                                    guint time, 
                                    gpointer user_data) 
{
    printf("DEBUG: %s %d %d\n", __func__, info, time);
}

int main(int argc, char *argv[]) 
{
    GdkDisplay *display = NULL;
    GtkWidget *window = NULL;
    GtkWidget *overlay = NULL;
    GtkWidget *stack_switcher = NULL;
    char buf[16] = {'\0'};

    gtk_init(&argc, &argv);

    m_provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    m_screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(m_screen, 
        GTK_STYLE_PROVIDER(m_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_path(m_provider, "./moses-stack.css", NULL);

    /* TODO: window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1024, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(m_destroy_cb), NULL);


    /* TODO: overlay */
    overlay = gtk_overlay_new();

    /* TODO: store */
    m_store = gtk_list_store_new(ICON_COLS, GDK_TYPE_PIXBUF, G_TYPE_STRING);
    m_fill_store();
    printf("DEBUG: store count %d\n", m_store_count);

    /* TODO: stack */
    m_stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(m_stack), 
                                  GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    /* TODO: pagenation */
    for (int i = 0; i <= m_store_count / ICON_COUNT_PER_PAGE; i++) {
        GtkWidget *sw = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), 
            GTK_POLICY_NEVER, GTK_POLICY_NEVER);

        GtkListStore *page_store = gtk_list_store_new(ICON_COLS, GDK_TYPE_PIXBUF, 
            G_TYPE_STRING);
        GtkTreeModel *tmp_model = GTK_TREE_MODEL(m_store);
        GtkTreeIter j, k;
        gboolean r = gtk_tree_model_get_iter_first(tmp_model, &j);
        int n;

        n = i * ICON_COUNT_PER_PAGE;
        while (r && n--) 
            r = gtk_tree_model_iter_next(tmp_model, &j);

        n = ICON_COUNT_PER_PAGE;
        while (r && n--) {
            char *name = NULL;
            GdkPixbuf *pixbuf = NULL;

            gtk_tree_model_get(tmp_model, &j, COL_NAME, &name, COL_ICON, &pixbuf, -1);
            gtk_list_store_append(page_store, &k);
            gtk_list_store_set(page_store, &k, COL_ICON, pixbuf, COL_NAME, name, -1);

            r = gtk_tree_model_iter_next(tmp_model, &j);
        }

        GtkWidget *icon_view = moses_icon_view_new_with_model(GTK_TREE_MODEL(page_store));
        gtk_drag_dest_set(icon_view, 
                          GTK_DEST_DEFAULT_ALL, 
                          target_list, 
                          n_targets, 
                          GDK_ACTION_COPY);
        gtk_drag_source_set(icon_view, 
                            GDK_BUTTON1_MASK, 
                            target_list, 
                            n_targets, 
                            GDK_ACTION_COPY);

        g_object_connect(G_OBJECT(icon_view), 
            "signal::drag-motion", m_drag_motion_cb, NULL, 
            "signal::drag-data-get", m_drag_data_get_cb, NULL,
            "signal::drag-data-received", m_drag_data_received_cb, NULL,
            NULL);
        g_object_set(G_OBJECT(icon_view),
            "margin", 10, 
            "column-spacing", 10, "row-spacing", 30, 
            "item-width", 90, "item-padding", 10,
            "activate-on-single-click", FALSE,
            NULL);
        gtk_container_add(GTK_CONTAINER(sw), icon_view);
        moses_icon_view_set_text_column(MOSES_ICON_VIEW(icon_view), COL_NAME);
        moses_icon_view_set_pixbuf_column(MOSES_ICON_VIEW(icon_view), COL_ICON);
        moses_icon_view_set_reorderable(MOSES_ICON_VIEW(icon_view), TRUE);

        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf) - 1, "%d", i + 1);
        gtk_stack_add_titled(GTK_STACK(m_stack), sw, buf, buf);
    }

    /* TODO: stack switcher */
    stack_switcher = moses_stack_switcher_new();
    gtk_widget_set_name(stack_switcher, "moses-stackswitcher");
    gtk_widget_set_halign(stack_switcher, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(stack_switcher, GTK_ALIGN_END);
    moses_stack_switcher_set_stack(MOSES_STACK_SWITCHER(stack_switcher), 
        GTK_STACK(m_stack));

    gtk_container_add(GTK_CONTAINER(overlay), m_stack);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), stack_switcher);

    /* TODO: show */
    gtk_container_add(GTK_CONTAINER(window), overlay);
    gtk_widget_show_all(window);

    /* TODO: main loop */
    gtk_main();

    return 0;
}
