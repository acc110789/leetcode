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
#include <glib/gi18n.h>

typedef struct {
    int num;
    void (*func1)();
} MyData;

static GMainLoop *m_loop = NULL;
static GList *m_list = NULL;
static int m_count = 0;

static void
my_data_func() 
{
    g_message("%s, line %d", __func__, __LINE__);
}

static void *
thread_func(void *arg) 
{
    MyData *data = (MyData *)arg;
    g_message("%s, line %d: %d %d", __func__, __LINE__, data->num, m_count);
    m_list = g_list_append(m_list, g_strdup_printf("arg%d", data->num));
    if (m_count > 10) {
        if (data->func1)
            data->func1();
    }
    m_count++;
    return NULL;
}

int 
main(int argc, char *argv[]) 
{
    GThread *thread = NULL;
    MyData *data = NULL;
    GError *error = NULL;
    for (int i = 0; i < 13; i++) {
        data = g_new0(MyData, 1);
        data->num = i;
        data->func1 = my_data_func;
        thread = g_thread_new(NULL, thread_func, data);
    }
    m_loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(m_loop);
    if (m_loop) {
        g_main_loop_unref(m_loop);
        m_loop = NULL;
    }
    if (error) {
        g_error_free(error);
        error = NULL;
    }
    return 0;
}
