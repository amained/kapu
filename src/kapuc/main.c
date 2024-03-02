#include <stdlib.h>
#include "lib/log.h"

#include "helper.h"

#define STB_DS_IMPLEMENTATION

#include "lib/stb_ds.h"
#include "lex.h"

int main(const int argc, char **argv) {
    log_set_level(1);
    if (argc != 2) {
        log_error("Usage: %s <file>", argv[0]);
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        log_error("Cannot open %s, exiting", argv[1]);
        exit(1);
    }
    log_debug("lexing started");
    BENCH_TIMER_HELPER(
            struct TOK *tokens = lex(f);
    )
    log_debug("lexing finished: got %d tokens", arrlen(tokens));
    fclose(f);
}
