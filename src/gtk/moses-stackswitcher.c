/*
 * Copyright (c) 2013 Red Hat, Inc.
 * Copyrgith (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "moses-stackswitcher.h"

#define GTK_PARAM_READWRITE G_PARAM_READWRITE|G_PARAM_STATIC_NAME|G_PARAM_STATIC_NICK|G_PARAM_STATIC_BLURB
#define P_(x) (x)

/**
 * SECTION:mosesstackswitcher
 * @Short_description: A controller for GtkStack
 * @Title: MosesStackSwitcher
 * @See_also: #GtkStack
 *
 * The MosesStackSwitcher widget acts as a controller for a
 * #GtkStack; it shows a row of buttons to switch between
 * the various pages of the associated stack widget.
 *
 * All the content for the buttons comes from the child properties
 * of the #GtkStack.
 *
 * It is possible to associate multiple #MosesStackSwitcher widgets
 * with the same stack widget.
 *
 * The MosesStackSwitcher widget was added in 3.10.
 */

typedef struct _MosesStackSwitcherPrivate MosesStackSwitcherPrivate;
struct _MosesStackSwitcherPrivate
{
  GtkStack *stack;
  GHashTable *buttons;
  gboolean in_child_changed;
};

enum {
  PROP_0,
  PROP_STACK
};

G_DEFINE_TYPE_WITH_PRIVATE (MosesStackSwitcher, moses_stack_switcher, GTK_TYPE_BOX)

static void
moses_stack_switcher_init (MosesStackSwitcher *switcher)
{
  GtkStyleContext *context;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (switcher);

  g_resources_register(moses_get_resource());

  priv->stack = NULL;
  priv->buttons = g_hash_table_new (g_direct_hash, g_direct_equal);

  context = gtk_widget_get_style_context (GTK_WIDGET (switcher));
  gtk_style_context_add_class (context, "stack-switcher");
  gtk_style_context_add_class (context, GTK_STYLE_CLASS_LINKED);

  gtk_orientable_set_orientation (GTK_ORIENTABLE (switcher), GTK_ORIENTATION_HORIZONTAL);
}

static void
on_button_clicked (GtkWidget        *widget,
                   MosesStackSwitcher *self)
{
  GtkWidget *child;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);
  if (!priv->in_child_changed)
    {
      child = g_object_get_data (G_OBJECT (widget), "stack-child");
      gtk_stack_set_visible_child (priv->stack, child);
    }
}

static void
rebuild_child (GtkWidget   *self,
               const gchar *icon_name,
               const gchar *title)
{
  GtkStyleContext *context;
  GtkWidget *button_child;

  button_child = gtk_bin_get_child (GTK_BIN (self));
  if (button_child != NULL)
    gtk_widget_destroy (button_child);

  button_child = NULL;
  context = gtk_widget_get_style_context (GTK_WIDGET (self));
#if 0
  if (icon_name != NULL)
    {
#endif
      button_child = gtk_image_new_from_resource("/org/moses/stackswitcher/dot.png");
      if (title != NULL)
        gtk_widget_set_tooltip_text (GTK_WIDGET (self), title);

      gtk_style_context_remove_class (context, "text-button");
      gtk_style_context_add_class (context, "image-button");
#if 0
    }
  else if (title != NULL)
    {
      button_child = gtk_label_new (title);

      gtk_widget_set_tooltip_text (GTK_WIDGET (self), NULL);

      gtk_style_context_remove_class (context, "image-button");
      gtk_style_context_add_class (context, "text-button");
    }
#endif
  if (button_child)
    {
      gtk_widget_set_halign (GTK_WIDGET (button_child), GTK_ALIGN_CENTER);
      gtk_widget_show_all (button_child);
      gtk_container_add (GTK_CONTAINER (self), button_child);
    }
}

static void
update_needs_attention (GtkWidget *widget, GtkWidget *button, gpointer data)
{
  GtkContainer *container;
  gboolean needs_attention;
  GtkStyleContext *context;

  container = GTK_CONTAINER (data);
  gtk_container_child_get (container, widget,
                           "needs-attention", &needs_attention,
                           NULL);

  context = gtk_widget_get_style_context (button);
  if (needs_attention)
    gtk_style_context_add_class (context, GTK_STYLE_CLASS_NEEDS_ATTENTION);
  else
    gtk_style_context_remove_class (context, GTK_STYLE_CLASS_NEEDS_ATTENTION);
}

static void
update_button (MosesStackSwitcher *self,
               GtkWidget        *widget,
               GtkWidget        *button)
{
  gchar *title;
  gchar *icon_name;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);

  gtk_container_child_get (GTK_CONTAINER (priv->stack), widget,
                           "title", &title,
                           "icon-name", &icon_name,
                           NULL);

  rebuild_child (button, icon_name, title);

  gtk_widget_set_visible (button, gtk_widget_get_visible (widget) && (title != NULL || icon_name != NULL));
#if 0
  if (icon_name != NULL)
#endif
    gtk_widget_set_size_request (button, -1, -1);
#if 0
  else
    gtk_widget_set_size_request (button, 100, -1);
#endif
  g_free (title);
  g_free (icon_name);

  update_needs_attention (widget, button, priv->stack);
}

static void
on_title_icon_visible_updated (GtkWidget        *widget,
                               GParamSpec       *pspec,
                               MosesStackSwitcher *self)
{
  GtkWidget *button;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);

  button = g_hash_table_lookup (priv->buttons, widget);
  update_button (self, widget, button);
}

static void
on_position_updated (GtkWidget        *widget,
                     GParamSpec       *pspec,
                     MosesStackSwitcher *self)
{
  GtkWidget *button;
  gint position;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);

  button = g_hash_table_lookup (priv->buttons, widget);

  gtk_container_child_get (GTK_CONTAINER (priv->stack), widget,
                           "position", &position,
                           NULL);

  gtk_box_reorder_child (GTK_BOX (self), button, position);
}

static void
on_needs_attention_updated (GtkWidget        *widget,
                            GParamSpec       *pspec,
                            MosesStackSwitcher *self)
{
  GtkWidget *button;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);

  button = g_hash_table_lookup (priv->buttons, widget);
  update_button (self, widget, button);
}

static void
add_child (GtkWidget        *widget,
           MosesStackSwitcher *self)
{
  GtkWidget *button;
  GList *group;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);

  button = gtk_radio_button_new(NULL);
  gtk_widget_set_events(button, GDK_BUTTON_PRESS_MASK);
  gtk_button_set_focus_on_click (GTK_BUTTON (button), FALSE);
  gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON (button), FALSE);
  update_button (self, widget, button);

  group = gtk_container_get_children (GTK_CONTAINER (self));
  if (group != NULL)
    {
      gtk_radio_button_join_group (GTK_RADIO_BUTTON (button), GTK_RADIO_BUTTON (group->data));
      g_list_free (group);
    }

  gtk_container_add (GTK_CONTAINER (self), button);

  g_object_set_data (G_OBJECT (button), "stack-child", widget);
  g_signal_connect (button, "clicked", G_CALLBACK (on_button_clicked), self);
  g_signal_connect (widget, "notify::visible", G_CALLBACK (on_title_icon_visible_updated), self);
  g_signal_connect (widget, "child-notify::title", G_CALLBACK (on_title_icon_visible_updated), self);
  g_signal_connect (widget, "child-notify::icon-name", G_CALLBACK (on_title_icon_visible_updated), self);
  g_signal_connect (widget, "child-notify::position", G_CALLBACK (on_position_updated), self);
  g_signal_connect (widget, "child-notify::needs-attention", G_CALLBACK (on_needs_attention_updated), self);

  g_hash_table_insert (priv->buttons, widget, button);
}

static void
remove_child (GtkWidget        *widget,
              MosesStackSwitcher *self)
{
  GtkWidget *button;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);

  g_signal_handlers_disconnect_by_func (widget, on_title_icon_visible_updated, self);
  g_signal_handlers_disconnect_by_func (widget, on_position_updated, self);
  g_signal_handlers_disconnect_by_func (widget, on_needs_attention_updated, self);

  button = g_hash_table_lookup (priv->buttons, widget);
  gtk_container_remove (GTK_CONTAINER (self), button);
  g_hash_table_remove (priv->buttons, widget);
}

static void
populate_switcher (MosesStackSwitcher *self)
{
  MosesStackSwitcherPrivate *priv;
  GtkWidget *widget, *button;

  priv = moses_stack_switcher_get_instance_private (self);
  gtk_container_foreach (GTK_CONTAINER (priv->stack), (GtkCallback)add_child, self);

  widget = gtk_stack_get_visible_child (priv->stack);
  if (widget)
    {
      button = g_hash_table_lookup (priv->buttons, widget);
      gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    }
}

static void
clear_switcher (MosesStackSwitcher *self)
{
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);
  gtk_container_foreach (GTK_CONTAINER (priv->stack), (GtkCallback)remove_child, self);
}

static void
on_child_changed (GtkWidget        *widget,
                  GParamSpec       *pspec,
                  MosesStackSwitcher *self)
{
  GtkWidget *child;
  GtkWidget *button;
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (self);

  child = gtk_stack_get_visible_child (GTK_STACK (widget));
  button = g_hash_table_lookup (priv->buttons, child);
  if (button != NULL)
    {
      priv->in_child_changed = TRUE;
      gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
      priv->in_child_changed = FALSE;
    }
}

static void
on_stack_child_added (GtkContainer     *container,
                      GtkWidget        *widget,
                      MosesStackSwitcher *self)
{
  add_child (widget, self);
}

static void
on_stack_child_removed (GtkContainer     *container,
                        GtkWidget        *widget,
                        MosesStackSwitcher *self)
{
  remove_child (widget, self);
}

static void
disconnect_stack_signals (MosesStackSwitcher *switcher)
{
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (switcher);
  g_signal_handlers_disconnect_by_func (priv->stack, on_stack_child_added, switcher);
  g_signal_handlers_disconnect_by_func (priv->stack, on_stack_child_removed, switcher);
  g_signal_handlers_disconnect_by_func (priv->stack, on_child_changed, switcher);
  g_signal_handlers_disconnect_by_func (priv->stack, disconnect_stack_signals, switcher);
}

static void
connect_stack_signals (MosesStackSwitcher *switcher)
{
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (switcher);
  g_signal_connect_after (priv->stack, "add",
                          G_CALLBACK (on_stack_child_added), switcher);
  g_signal_connect_after (priv->stack, "remove",
                          G_CALLBACK (on_stack_child_removed), switcher);
  g_signal_connect (priv->stack, "notify::visible-child",
                    G_CALLBACK (on_child_changed), switcher);
  g_signal_connect_swapped (priv->stack, "destroy",
                            G_CALLBACK (disconnect_stack_signals), switcher);
}

/**
 * moses_stack_switcher_set_stack:
 * @switcher: a #MosesStackSwitcher
 * @stack: (allow-none): a #GtkStack
 *
 * Sets the stack to control.
 *
 * Since: 3.10
 */
void
moses_stack_switcher_set_stack (MosesStackSwitcher *switcher,
                              GtkStack         *stack)
{
  MosesStackSwitcherPrivate *priv;

  g_return_if_fail (MOSES_IS_STACK_SWITCHER (switcher));
  g_return_if_fail (GTK_IS_STACK (stack) || stack == NULL);

  priv = moses_stack_switcher_get_instance_private (switcher);

  if (priv->stack == stack)
    return;

  if (priv->stack)
    {
      disconnect_stack_signals (switcher);
      clear_switcher (switcher);
      g_clear_object (&priv->stack);
    }
  if (stack)
    {
      priv->stack = g_object_ref (stack);
      populate_switcher (switcher);
      connect_stack_signals (switcher);
    }

  gtk_widget_queue_resize (GTK_WIDGET (switcher));

  g_object_notify (G_OBJECT (switcher), "stack");
}

/**
 * moses_stack_switcher_get_stack:
 * @switcher: a #MosesStackSwitcher
 *
 * Retrieves the stack.
 * See moses_stack_switcher_set_stack().
 *
 * Returns: (transfer none): the stack, or %NULL if
 *    none has been set explicitly.
 *
 * Since: 3.10
 */
GtkStack *
moses_stack_switcher_get_stack (MosesStackSwitcher *switcher)
{
  MosesStackSwitcherPrivate *priv;
  g_return_val_if_fail (MOSES_IS_STACK_SWITCHER (switcher), NULL);

  priv = moses_stack_switcher_get_instance_private (switcher);
  return priv->stack;
}

static void
moses_stack_switcher_get_property (GObject      *object,
                                 guint         prop_id,
                                 GValue       *value,
                                 GParamSpec   *pspec)
{
  MosesStackSwitcher *switcher = MOSES_STACK_SWITCHER (object);
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (switcher);
  switch (prop_id)
    {
    case PROP_STACK:
      g_value_set_object (value, priv->stack);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
moses_stack_switcher_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  MosesStackSwitcher *switcher = MOSES_STACK_SWITCHER (object);

  switch (prop_id)
    {
    case PROP_STACK:
      moses_stack_switcher_set_stack (switcher, g_value_get_object (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
moses_stack_switcher_dispose (GObject *object)
{
  MosesStackSwitcher *switcher = MOSES_STACK_SWITCHER (object);

  moses_stack_switcher_set_stack (switcher, NULL);

  G_OBJECT_CLASS (moses_stack_switcher_parent_class)->dispose (object);
}

static void
moses_stack_switcher_finalize (GObject *object)
{
  MosesStackSwitcher *switcher = MOSES_STACK_SWITCHER (object);
  MosesStackSwitcherPrivate *priv;

  priv = moses_stack_switcher_get_instance_private (switcher);

  g_hash_table_destroy (priv->buttons);

  G_OBJECT_CLASS (moses_stack_switcher_parent_class)->finalize (object);
}

static void
moses_stack_switcher_class_init (MosesStackSwitcherClass *class)
{
  GObjectClass *object_class = G_OBJECT_CLASS (class);

  object_class->get_property = moses_stack_switcher_get_property;
  object_class->set_property = moses_stack_switcher_set_property;
  object_class->dispose = moses_stack_switcher_dispose;
  object_class->finalize = moses_stack_switcher_finalize;

  g_object_class_install_property (object_class,
                                   PROP_STACK,
                                   g_param_spec_object ("stack",
                                                        P_("Stack"),
                                                        P_("Stack"),
                                                        GTK_TYPE_STACK,
                                                        GTK_PARAM_READWRITE |
                                                        G_PARAM_CONSTRUCT));
}

/**
 * moses_stack_switcher_new:
 *
 * Create a new #MosesStackSwitcher.
 *
 * Returns: a new #MosesStackSwitcher.
 *
 * Since: 3.10
 */
GtkWidget *
moses_stack_switcher_new (void)
{
  return g_object_new (MOSES_TYPE_STACK_SWITCHER, NULL);
}
