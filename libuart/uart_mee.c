// See LICENSE for license details.

#include <mee/tty.h>
#include <mee/shutdown.h>

int getchar()
{
    return -1;
}

int putchar(int c)
{
    return mee_tty_putc(c);
}

void poweroff()
{
    mee_shutdown(0);
}

/* The MEE is designed for embedded systems, where it might be necessary to
 * relocate the data segment upon entering the program.  In that case, it's
 * expected that the following symbols are defined to inform the C library.
 * While this is nominally part of the C environment so it should really be
 * done in assembly, it's probably safe to do this as it's unlikely that GCC
 * will actually use anything in .data or .bss for init(). */
extern long mee_segment_data_source_start;
extern long mee_segment_data_target_start;
extern long mee_segment_data_target_end;

extern long mee_segment_bss_target_start;
extern long mee_segment_bss_target_end;

void init()
{
    long *dss = &mee_segment_data_source_start;
    long *dts = &mee_segment_data_target_start;
    long *dte = &mee_segment_data_target_end;

    if (dts != dss) {
        while (dts < dte) {
           *dts = *dss;
           dts++;
           dss++;
        }
    }

    long *bts = &mee_segment_bss_target_start;
    long *bte = &mee_segment_bss_target_end;

    while (bts < bte) {
        *bts = 0;
        bts++;
    }
}
