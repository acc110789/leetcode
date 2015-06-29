#include <gio/gio.h>

int main(int argc, char *argv[]) 
{
    GSettings *settings = NULL;
   
    settings = g_settings_new("typo.org.gnome.desktop.background");
    /*
     * settings = g_settings_new("typo.org.gnome.desktop.background");
     *
     * people often typo input wrong schema or such schema has not been 
     * installed by glib-compile-schemas 
     *
     * then it throw GLib-GIO-ERROR **: Settings schema 
     * 'typo.org.gnome.desktop.background' is not installed segfault
     */

#if 0
    /* it needs patch https://bugzilla.gnome.org/show_bug.cgi?id=751627  */
    settings = g_settings_new2();
    g_settings_schema_set_id(settings, "typo.org.gnome.desktop.background");
#endif

    g_message("%x\n", settings);

    if (settings) {
        g_object_unref(settings);
        settings = NULL;
    }

    return 0;
}
