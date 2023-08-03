#include <stdint.h>
#include <sel4cp.h>
#include "timer.h"

static void
put64(uint64_t val) {
    char buffer[20];
    unsigned i = 19;
    buffer[19] = 0;
    do {
        uint8_t c = val % 10;
        buffer[--i] = '0' + c;
        val /= 10;
    } while (val);
    sel4cp_dbg_puts(&buffer[i]);
}

void
notified(sel4cp_channel ch)
{
    /*
     * In this example we only have a single possible channel,
     * so we know it's a notification from the driver telling
     * us that the timeout we set has gone off.
     */
    sel4cp_dbg_puts("CLIENT|INFO: Got a timeout!\n");
    /* Get the current time */
    uint64_t time = time_now();
    sel4cp_dbg_puts("CLIENT|INFO: Now the time is: ");
    put64(time);
    sel4cp_dbg_puts("\n");
    /* Set another timeout */
    set_timeout(NS_IN_S);
}

void
init(void)
{
    // lets get the time!
    uint64_t time = time_now();
    sel4cp_dbg_puts("CLIENT|INFO: The time now is: ");
    put64(time);
    sel4cp_dbg_puts("\n");

    // lets set a timeout
    sel4cp_dbg_puts("CLIENT|INFO: Setting a time out for 1 second\n");
    set_timeout(NS_IN_S);
}
