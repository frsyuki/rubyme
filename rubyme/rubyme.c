#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char REPLACE_MAGIC[] = "@@59914b974c7eaa89e346eeb5abe3f571@@";

static void
update_args(int *r_argc, char ***r_argv)
{
    long binsz, allsz, scriptsz;
    FILE* fp;
    char* script;
    char** argv2;
    int i;

    int argc = *r_argc;
    char **argv = *r_argv;

    binsz = atol(REPLACE_MAGIC);
    if(binsz == 0) {
        return;
    }

    /* FIXME error handilng */
    fp = fopen(argv[0], "rb");
    fseek(fp, 0, SEEK_END);
    allsz = ftell(fp);

    scriptsz = allsz - binsz;

    script = malloc(scriptsz);
    fseek(fp, binsz, SEEK_SET);

    fread(script, scriptsz, 1, fp);

    argv2 = calloc(argc+3, sizeof(char*));

    argv2[0] = argv[0];
    argv2[1] = strdup("-e");
    argv2[2] = script;
    for(i=1; i < argc; i++) {
        argv2[2+i] = argv[i];
    }

    *r_argv = argv2;
    *r_argc += 2;
}

/**********************************************************************

  main.c -

  $Author: shyouhei $
  created at: Fri Aug 19 13:19:58 JST 1994

  Copyright (C) 1993-2007 Yukihiro Matsumoto

**********************************************************************/

#undef RUBY_EXPORT
#include "ruby.h"
#include "debug.h"
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif
#ifdef RUBY_DEBUG_ENV
#include <stdlib.h>
#endif

RUBY_GLOBAL_SETUP

int
main(int argc, char **argv)
{
    update_args(&argc, &argv);

#ifdef RUBY_DEBUG_ENV
    ruby_set_debug_option(getenv("RUBY_DEBUG"));
#endif
#ifdef HAVE_LOCALE_H
    setlocale(LC_CTYPE, "");
#endif

    ruby_sysinit(&argc, &argv);
    {
	RUBY_INIT_STACK;
	ruby_init();
	return ruby_run_node(ruby_options(argc, argv));
    }
}

