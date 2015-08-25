/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <rpm/rpmlib.h>
#include <rpm/rpmcli.h>
#include <rpm/rpmts.h>
#include <glib/gi18n.h>

enum modes {
    MODE_QUERY      = (1 <<  0),
    MODE_VERIFY     = (1 <<  3),
#define MODES_QV (MODE_QUERY | MODE_VERIFY)

    MODE_INSTALL    = (1 <<  1),
    MODE_ERASE      = (1 <<  2),
#define MODES_IE (MODE_INSTALL | MODE_ERASE)

    MODE_UNKNOWN    = 0
};

#define MODES_FOR_NODEPS    (MODES_IE | MODE_VERIFY)
#define MODES_FOR_TEST      (MODES_IE)

static int quiet;

static struct poptOption optionsTable[] = {
    {NULL, '\0', POPT_ARG_INCLUDE_TABLE, rpmQVSourcePoptTable, 0,
     N_("Query/Verify package selection options:"),
     NULL},
    {NULL, '\0', POPT_ARG_INCLUDE_TABLE, rpmQueryPoptTable, 0,
     N_("Query options (with -q or --query):"),
     NULL},
    {NULL, '\0', POPT_ARG_INCLUDE_TABLE, rpmVerifyPoptTable, 0,
     N_("Verify options (with -V or --verify):"),
     NULL},
    {NULL, '\0', POPT_ARG_INCLUDE_TABLE, rpmInstallPoptTable, 0,
     N_("Install/Upgrade/Erase options:"),
     NULL},
    {"quiet", '\0', POPT_ARGFLAG_DOC_HIDDEN, &quiet, 0, NULL, NULL},
    {NULL, '\0', POPT_ARG_INCLUDE_TABLE, rpmcliAllPoptTable, 0,
     N_("Common options for all rpm modes and executables:"),
     NULL},
    POPT_AUTOALIAS
    POPT_AUTOHELP
    POPT_TABLEEND
};

int main(int argc, char *argv[]) 
{
    rpmts ts = NULL;
    enum modes bigMode = MODE_UNKNOWN;
    QVA_t qva = &rpmQVKArgs;
    struct rpmInstallArguments_s *ia = &rpmIArgs;
    poptContext optCon;
    int ec = 0;
    int i;

    int c = 3;
    char **arg = malloc(sizeof(char *) * c);
    memset(arg, 3, sizeof(char *) * c);
    for (int i = 0; i < c; i++) {
        arg[i] = malloc(sizeof(char) * PATH_MAX);
        memset(arg[i], 0, sizeof(char) * PATH_MAX);
    }
#if 0
    char *arg[3] = {"hello_rpm", 
                    "-ivh", 
                    "/data/download/firefox-40.0-12.x86_64.rpm"};
#endif
    snprintf(arg[0], strlen(arg[0]) - 1, "hello_rpm");
    snprintf(arg[1], strlen(arg[1]) - 1, "-ivh");
    snprintf(arg[2], strlen(arg[2]) - 1, "/data/download/firefox-40.0-12.x86_64.rpm");
    optCon = rpmcliInit(3, arg, optionsTable);

    switch (bigMode) {
    case MODE_QUERY:
        qva->qva_mode = 'q';
        break;
    case MODE_VERIFY:
        qva->qva_mode = 'V';
        break;
    default:
        break;
    }

    if (bigMode == MODE_UNKNOWN || (bigMode & MODES_QV)) {
        switch (qva->qva_mode) {
        case 'q':
            bigMode = MODE_QUERY;
            break;
        case 'V':
            bigMode = MODE_VERIFY;
            break;
        default:
            break;
        }
    }

    if (bigMode == MODE_UNKNOWN || (bigMode & MODES_IE)) {
        int iflags = (ia->installInterfaceFlags & 
            (INSTALL_UPGRADE | INSTALL_FRESHEN | INSTALL_INSTALL | INSTALL_REINSTALL));
        int eflags = (ia->installInterfaceFlags & INSTALL_ERASE);
    
        if (iflags & eflags)
            g_error("only one major mode may be specified");
        else if (iflags)
            bigMode = MODE_INSTALL;
        else if (eflags)
            bigMode = MODE_ERASE;
    }

    ts = rpmtsCreate();
    rpmtsSetRootDir(ts, rpmcliRootDir);

    switch (bigMode) {
    case MODE_INSTALL:
        if (!ia->incldocs) {
            if (rpmExpandNumeric("%{_excludedocs}"))
                ia->transFlags |= RPMTRANS_FLAG_NODOCS;
        }

        if (ia->noDeps) 
            ia->installInterfaceFlags |= INSTALL_NODEPS;

        if (ia->prefix) {
            ia->relocations = malloc(2 * sizeof(*ia->relocations));
            ia->relocations[0].oldPath = NULL;   /* special case magic */
            ia->relocations[0].newPath = ia->prefix;
            ia->relocations[1].oldPath = NULL;
            ia->relocations[1].newPath = NULL;
        } else if (ia->relocations) {
            ia->relocations = realloc(ia->relocations, 
                sizeof(*ia->relocations) * (ia->numRelocations + 1));
            ia->relocations[ia->numRelocations].oldPath = NULL;
            ia->relocations[ia->numRelocations].newPath = NULL;
        }

        if (!poptPeekArg(optCon))
            g_error(_("no packages given for install"));
        else
            ec += rpmInstall(ts, ia, (ARGV_t) poptGetArgs(optCon));

        break;
    case MODE_QUERY:
        ec = rpmcliQuery(ts, qva, (ARGV_const_t) poptGetArgs(optCon));
        break;
    default:
        break;
    }

    rpmtsFree(ts);
    ts = NULL;

    free(qva->qva_queryFormat);
    qva->qva_queryFormat = NULL;

    rpmcliFini(optCon);

    return 0;
}
