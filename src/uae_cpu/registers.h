/* 2001 MJ */

#ifndef REGISTERS_H
#define REGISTERS_H

#include "sysdeps.h"
#include "spcflags.h"
typedef char flagtype;


struct xttrx {
    uae_u32 log_addr_base : 8;
    uae_u32 log_addr_mask : 8;
    uae_u32 enable : 1;
    uae_u32 s_field : 2;
    uae_u32 : 3;
    uae_u32 usr1 : 1;
    uae_u32 usr0 : 1;
    uae_u32 : 1;
    uae_u32 cmode : 2;
    uae_u32 : 2;
    uae_u32 write : 1;
    uae_u32 : 2;
};

struct mmusr_t {
   uae_u32 phys_addr : 20;
   uae_u32 bus_err : 1;
   uae_u32 global : 1;
   uae_u32 usr1 : 1;
   uae_u32 usr0 : 1;
   uae_u32 super : 1;
   uae_u32 cmode : 2;
   uae_u32 modif : 1;
   uae_u32 : 1;
   uae_u32 write : 1;
   uae_u32 ttrhit : 1;
   uae_u32 resident : 1;
};

struct log_addr4 {
   uae_u32 rif : 7;
   uae_u32 pif : 7;
   uae_u32 paif : 6;
   uae_u32 poff : 12;
};

struct log_addr8 {
  uae_u32 rif : 7;
  uae_u32 pif : 7;
  uae_u32 paif : 5;
  uae_u32 poff : 13;
};

extern struct regstruct
{
    uae_u32 regs[16];
    uaecptr  usp,isp,msp;
    uae_u16 sr;
    flagtype t1;
    flagtype t0;
    flagtype s;
    flagtype m;
    flagtype x;
    flagtype stopped;
    int intmask;

    uae_u32 pc;
    uae_u32 pcp;	//    uae_u8 *pc_p;
    uae_u32 pcoldp;	//    uae_u8 *pc_oldp;

    uae_u32 vbr,sfc,dfc;

    volatile uae_u32 spcflags;

#if 0
    uae_u32 kick_mask;

    /* Fellow sources say this is 4 longwords. That's impossible. It needs
     * to be at least a longword. The HRM has some cryptic comment about two
     * instructions being on the same longword boundary.
     * The way this is implemented now seems like a good compromise.
     */
    uae_u32 prefetch;
#endif

    /* MMU reg*/
    uae_u32 urp,srp;
    uae_u32 tc;

    int mmu_enabled;   /* flagtype tce; */

    int mmu_pagesize; /*  flagtype tcp; */

    uae_u32 dtt0,dtt1,itt0,itt1;
    uae_u32 mmusr;

    uae_u32 mmu_fslw, mmu_fault_addr;
    uae_u16 mmu_ssw;

#if 0
    flagtype atcvali[ATCSIZE];
    flagtype atcvald[ATCSIZE];
    flagtype atcu0d[ATCSIZE];
    flagtype atcu0i[ATCSIZE];
    flagtype atcu1d[ATCSIZE];
    flagtype atcu1i[ATCSIZE];
    flagtype atcsuperd[ATCSIZE];
    flagtype atcsuperi[ATCSIZE];
    int atccmd[ATCSIZE];
    int atccmi[ATCSIZE];
    flagtype atcmodifd[ATCSIZE];
    flagtype atcmodifi[ATCSIZE];
    flagtype atcwritepd[ATCSIZE];
    flagtype atcwritepi[ATCSIZE];
    flagtype atcresidd[ATCSIZE];
    flagtype atcresidi[ATCSIZE];
    flagtype atcglobald[ATCSIZE];
    flagtype atcglobali[ATCSIZE];
    flagtype atcfc2d[ATCSIZE];
    flagtype atcfc2i[ATCSIZE];
    uaecptr atcind[ATCSIZE];
    uaecptr atcini[ATCSIZE];
    uaecptr atcoutd[ATCSIZE];
    uaecptr atcouti[ATCSIZE];
#endif

    /* Cache reg*/
    uae_u32 cacr,caar;
} regs, lastint_regs;

#endif
