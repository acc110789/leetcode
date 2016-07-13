#include <glib.h>
#include <glib/gprintf.h>
#include <libnotify/notify.h>

static NotifyNotification *m_notify = NULL;

static void notify_action_cb(NotifyNotification *notify, 
                             gchar *id, 
                             gpointer user_data) 
{
    g_printf("DEBUG: %s, line %d, %s\n", __func__, __LINE__, id);
}

static void do_notify() 
{
    const gchar *summary = "Hello";
    const gchar *body = "Hello World!";
    const gchar *icon = "gtk3-demo";
    const gchar *action = "test";
    const gchar *label = "Don't show this message again";
    GError *error = NULL;

    m_notify = notify_notification_new(summary, body, icon);
    g_assert(m_notify);

    notify_notification_set_urgency(m_notify, NOTIFY_URGENCY_LOW);
    notify_notification_set_timeout(m_notify, NOTIFY_EXPIRES_DEFAULT);
    notify_notification_add_action(m_notify, action, label, 
                                   notify_action_cb, NULL, NULL);

    if (!notify_notification_show(m_notify, &error)) {
        g_warning("Failed to show notification: %s", 
                  error && error->message ? error->message : "(unknown)");
        g_clear_error(&error);
    }
}

int main(int argc, char *argv[]) 
{
    g_printf("libnotify and notification-XXX-applet testcase\n");

    if (!notify_is_initted())
        notify_init("NotifyTestcase");

    do_notify();

    if (m_notify) {
        //notify_notification_close(m_notify, NULL);
        g_object_unref(m_notify);
        m_notify = NULL;
    }

    return 0;
}
