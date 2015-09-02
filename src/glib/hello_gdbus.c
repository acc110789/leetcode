/*************************************************************************************
*  Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>                        *
*                                                                                   *
*  This program is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU General Public License                      *
*  as published by the Free Software Foundation; either version 2                   *
*  of the License, or (at your option) any later version.                           *
*                                                                                   *
*  This program is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
*  GNU General Public License for more details.                                     *
*                                                                                   *
*  You should have received a copy of the GNU General Public License                *
*  along with this program; if not, write to the Free Software                      *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
*************************************************************************************/

#include <glib.h>
#include <gio/gio.h>

static GMainLoop *m_loop = NULL;
static GDBusProxy *m_proxy = NULL;

static void
inhibit_done(GObject *source_object, GAsyncResult *res, gpointer user_data) 
{
    GError *error = NULL;
    int i = 60;
    int fd = -1;

    GVariant *data = g_dbus_proxy_call_finish(source_object, res, &error);
    if (error) {
        g_message("%s, line %d: %s", __func__, __LINE__, error->message);
        goto cleanup;
    }
    g_variant_get(data, "(h)", &fd);

    g_message("Do inhibit...");
    while (i--) {
        sleep(1);
        g_message("Tick... still inhibit");
    }

cleanup:
    if (error) {
        g_error_free(error);
        error = NULL;
    }

    if (data) {
        g_variant_unref(data);
        data = NULL;
    }

    if (fd != -1) {
        g_message("Release inhibit lock");
        close(fd);
        fd = -1;
    }
}

int 
main(int argc, char *argv[]) 
{
    GError *error = NULL;

    m_loop = g_main_loop_new(NULL, FALSE);

    m_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM, 
                                            G_DBUS_PROXY_FLAGS_NONE, 
                                            NULL, 
                                            "org.freedesktop.login1", 
                                            "/org/freedesktop/login1", 
                                            "org.freedesktop.login1.Manager", 
                                            NULL, 
                                            &error);
    if (m_proxy == NULL || error) {
        g_message("ERROR: %s, line %d: %s", __func__, __LINE__, error->message);
        goto cleanup;
    }

    g_dbus_proxy_call(m_proxy, 
                      "Inhibit", 
                      g_variant_new("(ssss)",
                                    "shutdown:handle-power-key:handle-hibernate-key",
                                    "Leslie Zhai", 
                                    "Leslie Zhai in Progress", 
                                    "block"), 
                      G_DBUS_CALL_FLAGS_NONE, 
                      -1, 
                      NULL, 
                      (GAsyncReadyCallback)inhibit_done, 
                      NULL);

    g_main_loop_run(m_loop);

cleanup:
    if (m_loop) {
        g_main_loop_unref(m_loop);
        m_loop = NULL;
    }

    if (m_proxy) {
        g_object_unref(m_proxy);
        m_proxy = NULL;
    }

    if (error) {
        g_error_free(error);
        error = NULL;
    }

    return 0;
}
