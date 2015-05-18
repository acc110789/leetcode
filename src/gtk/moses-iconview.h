/* gtkiconview.h
 * Copyright (C) 2002, 2004  Anders Carlsson <andersca@gnome.org>
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MOSES_ICON_VIEW_H__
#define __MOSES_ICON_VIEW_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MOSES_TYPE_ICON_VIEW            (moses_icon_view_get_type ())
#define MOSES_ICON_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MOSES_TYPE_ICON_VIEW, MosesIconView))
#define MOSES_ICON_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), MOSES_TYPE_ICON_VIEW, MosesIconViewClass))
#define MOSES_IS_ICON_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MOSES_TYPE_ICON_VIEW))
#define MOSES_IS_ICON_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MOSES_TYPE_ICON_VIEW))
#define MOSES_ICON_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), MOSES_TYPE_ICON_VIEW, MosesIconViewClass))

typedef struct _MosesIconView           MosesIconView;
typedef struct _MosesIconViewClass      MosesIconViewClass;
typedef struct _MosesIconViewPrivate    MosesIconViewPrivate;

/**
 * MosesIconViewForeachFunc:
 * @icon_view: a #MosesIconView
 * @path: The #GtkTreePath of a selected row
 * @data: (closure): user data
 *
 * A function used by moses_icon_view_selected_foreach() to map all
 * selected rows.  It will be called on every selected row in the view.
 */
typedef void (* MosesIconViewForeachFunc)     (MosesIconView      *icon_view,
					     GtkTreePath      *path,
					     gpointer          data);

/**
 * MosesIconViewDropPosition:
 * @MOSES_ICON_VIEW_NO_DROP: no drop possible
 * @MOSES_ICON_VIEW_DROP_INTO: dropped item replaces the item
 * @MOSES_ICON_VIEW_DROP_LEFT: droppped item is inserted to the left
 * @MOSES_ICON_VIEW_DROP_RIGHT: dropped item is inserted to the right
 * @MOSES_ICON_VIEW_DROP_ABOVE: dropped item is inserted above
 * @MOSES_ICON_VIEW_DROP_BELOW: dropped item is inserted below
 *
 * An enum for determining where a dropped item goes.
 */
typedef enum
{
  MOSES_ICON_VIEW_NO_DROP,
  MOSES_ICON_VIEW_DROP_INTO,
  MOSES_ICON_VIEW_DROP_LEFT,
  MOSES_ICON_VIEW_DROP_RIGHT,
  MOSES_ICON_VIEW_DROP_ABOVE,
  MOSES_ICON_VIEW_DROP_BELOW
} MosesIconViewDropPosition;

typedef enum {
  MOSES_ICON_VIEW_BORDER_LEFT,
  MOSES_ICON_VIEW_BORDER_RIGHT,
} MosesIconViewBorder;

struct _MosesIconView
{
  GtkContainer parent;

  /*< private >*/
  MosesIconViewPrivate *priv;
};

struct _MosesIconViewClass
{
  GtkContainerClass parent_class;

  void    (* item_activated)         (MosesIconView      *icon_view,
				      GtkTreePath      *path);
  void    (* selection_changed)      (MosesIconView      *icon_view);

  /* Key binding signals */
  void    (* select_all)             (MosesIconView      *icon_view);
  void    (* unselect_all)           (MosesIconView      *icon_view);
  void    (* select_cursor_item)     (MosesIconView      *icon_view);
  void    (* toggle_cursor_item)     (MosesIconView      *icon_view);
  gboolean (* move_cursor)           (MosesIconView      *icon_view,
				      GtkMovementStep   step,
				      gint              count);
  gboolean (* activate_cursor_item)  (MosesIconView      *icon_view);

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

GDK_AVAILABLE_IN_ALL
GType          moses_icon_view_get_type          (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GtkWidget *    moses_icon_view_new               (void);
GDK_AVAILABLE_IN_ALL
GtkWidget *    moses_icon_view_new_with_area     (GtkCellArea    *area);
GDK_AVAILABLE_IN_ALL
GtkWidget *    moses_icon_view_new_with_model    (GtkTreeModel   *model);

GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_model         (MosesIconView    *icon_view,
 					        GtkTreeModel   *model);
GDK_AVAILABLE_IN_ALL
GtkTreeModel * moses_icon_view_get_model         (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_text_column   (MosesIconView    *icon_view,
	 	 			        gint            column);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_text_column   (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_markup_column (MosesIconView    *icon_view,
					        gint            column);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_markup_column (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_pixbuf_column (MosesIconView    *icon_view,
					        gint            column);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_pixbuf_column (MosesIconView    *icon_view);

GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_item_orientation (MosesIconView    *icon_view,
                                                   GtkOrientation  orientation);
GDK_AVAILABLE_IN_ALL
GtkOrientation moses_icon_view_get_item_orientation (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_columns       (MosesIconView    *icon_view,
		 			        gint            columns);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_columns       (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_item_width    (MosesIconView    *icon_view,
					        gint            item_width);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_item_width    (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_spacing       (MosesIconView    *icon_view, 
		 			        gint            spacing);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_spacing       (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_row_spacing   (MosesIconView    *icon_view, 
					        gint            row_spacing);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_row_spacing   (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_column_spacing (MosesIconView    *icon_view, 
					        gint            column_spacing);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_column_spacing (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_margin        (MosesIconView    *icon_view, 
					        gint            margin);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_margin        (MosesIconView    *icon_view);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_item_padding  (MosesIconView    *icon_view, 
					        gint            item_padding);
GDK_AVAILABLE_IN_ALL
gint           moses_icon_view_get_item_padding  (MosesIconView    *icon_view);

GDK_AVAILABLE_IN_ALL
GtkTreePath *  moses_icon_view_get_path_at_pos   (MosesIconView     *icon_view,
						gint             x,
						gint             y);
GDK_AVAILABLE_IN_ALL
gboolean       moses_icon_view_get_item_at_pos   (MosesIconView     *icon_view,
						gint              x,
						gint              y,
						GtkTreePath     **path,
						GtkCellRenderer **cell);
GDK_AVAILABLE_IN_ALL
gboolean       moses_icon_view_get_visible_range (MosesIconView      *icon_view,
						GtkTreePath     **start_path,
						GtkTreePath     **end_path);
GDK_AVAILABLE_IN_3_8
void           moses_icon_view_set_activate_on_single_click (MosesIconView  *icon_view,
                                                           gboolean      single);
GDK_AVAILABLE_IN_3_8
gboolean       moses_icon_view_get_activate_on_single_click (MosesIconView  *icon_view);

GDK_AVAILABLE_IN_ALL
void           moses_icon_view_selected_foreach   (MosesIconView            *icon_view,
						 MosesIconViewForeachFunc  func,
						 gpointer                data);
GDK_AVAILABLE_IN_ALL
void           moses_icon_view_set_selection_mode (MosesIconView            *icon_view,
						 GtkSelectionMode        mode);
GDK_AVAILABLE_IN_ALL
GtkSelectionMode moses_icon_view_get_selection_mode (MosesIconView            *icon_view);
GDK_AVAILABLE_IN_ALL
void             moses_icon_view_select_path        (MosesIconView            *icon_view,
						   GtkTreePath            *path);
GDK_AVAILABLE_IN_ALL
void             moses_icon_view_unselect_path      (MosesIconView            *icon_view,
						   GtkTreePath            *path);
GDK_AVAILABLE_IN_ALL
gboolean         moses_icon_view_path_is_selected   (MosesIconView            *icon_view,
						   GtkTreePath            *path);
GDK_AVAILABLE_IN_ALL
gint             moses_icon_view_get_item_row       (MosesIconView            *icon_view,
                                                   GtkTreePath            *path);
GDK_AVAILABLE_IN_ALL
gint             moses_icon_view_get_item_column    (MosesIconView            *icon_view,
                                                   GtkTreePath            *path);
GDK_AVAILABLE_IN_ALL
GList           *moses_icon_view_get_selected_items (MosesIconView            *icon_view);
GDK_AVAILABLE_IN_ALL
void             moses_icon_view_select_all         (MosesIconView            *icon_view);
GDK_AVAILABLE_IN_ALL
void             moses_icon_view_unselect_all       (MosesIconView            *icon_view);
GDK_AVAILABLE_IN_ALL
void             moses_icon_view_item_activated     (MosesIconView            *icon_view,
						   GtkTreePath            *path);
GDK_AVAILABLE_IN_ALL
void             moses_icon_view_set_cursor         (MosesIconView            *icon_view,
						   GtkTreePath            *path,
						   GtkCellRenderer        *cell,
						   gboolean                start_editing);
GDK_AVAILABLE_IN_ALL
gboolean         moses_icon_view_get_cursor         (MosesIconView            *icon_view,
						   GtkTreePath           **path,
						   GtkCellRenderer       **cell);
GDK_AVAILABLE_IN_ALL
void             moses_icon_view_scroll_to_path     (MosesIconView            *icon_view,
                                                   GtkTreePath            *path,
						   gboolean                use_align,
						   gfloat                  row_align,
                                                   gfloat                  col_align);

/* Drag-and-Drop support */
GDK_AVAILABLE_IN_ALL
void                   moses_icon_view_enable_model_drag_source (MosesIconView              *icon_view,
							       GdkModifierType           start_button_mask,
							       const GtkTargetEntry     *targets,
							       gint                      n_targets,
							       GdkDragAction             actions);
GDK_AVAILABLE_IN_ALL
void                   moses_icon_view_enable_model_drag_dest   (MosesIconView              *icon_view,
							       const GtkTargetEntry     *targets,
							       gint                      n_targets,
							       GdkDragAction             actions);
GDK_AVAILABLE_IN_ALL
void                   moses_icon_view_unset_model_drag_source  (MosesIconView              *icon_view);
GDK_AVAILABLE_IN_ALL
void                   moses_icon_view_unset_model_drag_dest    (MosesIconView              *icon_view);
GDK_AVAILABLE_IN_ALL
void                   moses_icon_view_set_reorderable          (MosesIconView              *icon_view,
							       gboolean                  reorderable);
GDK_AVAILABLE_IN_ALL
gboolean               moses_icon_view_get_reorderable          (MosesIconView              *icon_view);


/* These are useful to implement your own custom stuff. */
GDK_AVAILABLE_IN_ALL
void                   moses_icon_view_set_drag_dest_item       (MosesIconView              *icon_view,
							       GtkTreePath              *path,
							       MosesIconViewDropPosition   pos);
GDK_AVAILABLE_IN_ALL
void                   moses_icon_view_get_drag_dest_item       (MosesIconView              *icon_view,
							       GtkTreePath             **path,
							       MosesIconViewDropPosition  *pos);
GDK_AVAILABLE_IN_ALL
gboolean               moses_icon_view_get_dest_item_at_pos     (MosesIconView              *icon_view,
							       gint                      drag_x,
							       gint                      drag_y,
							       GtkTreePath             **path,
							       MosesIconViewDropPosition  *pos);
GDK_AVAILABLE_IN_ALL
cairo_surface_t       *moses_icon_view_create_drag_icon         (MosesIconView              *icon_view,
							       GtkTreePath              *path);

GDK_AVAILABLE_IN_ALL
void    moses_icon_view_convert_widget_to_bin_window_coords     (MosesIconView *icon_view,
                                                               gint         wx,
                                                               gint         wy,
                                                               gint        *bx,
                                                               gint        *by);
GDK_AVAILABLE_IN_3_6
gboolean moses_icon_view_get_cell_rect                          (MosesIconView     *icon_view,
							       GtkTreePath     *path,
							       GtkCellRenderer *cell,
							       GdkRectangle    *rect);


GDK_AVAILABLE_IN_ALL
void    moses_icon_view_set_tooltip_item                        (MosesIconView     *icon_view,
                                                               GtkTooltip      *tooltip,
                                                               GtkTreePath     *path);
GDK_AVAILABLE_IN_ALL
void    moses_icon_view_set_tooltip_cell                        (MosesIconView     *icon_view,
                                                               GtkTooltip      *tooltip,
                                                               GtkTreePath     *path,
                                                               GtkCellRenderer *cell);
GDK_AVAILABLE_IN_ALL
gboolean moses_icon_view_get_tooltip_context                    (MosesIconView       *icon_view,
                                                               gint              *x,
                                                               gint              *y,
                                                               gboolean           keyboard_tip,
                                                               GtkTreeModel     **model,
                                                               GtkTreePath      **path,
                                                               GtkTreeIter       *iter);
GDK_AVAILABLE_IN_ALL
void     moses_icon_view_set_tooltip_column                     (MosesIconView       *icon_view,
                                                               gint               column);
GDK_AVAILABLE_IN_ALL
gint     moses_icon_view_get_tooltip_column                     (MosesIconView       *icon_view);


G_END_DECLS

#endif /* __MOSES_ICON_VIEW_H__ */
