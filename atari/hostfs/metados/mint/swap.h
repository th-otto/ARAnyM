/*
 * $Id$
 * 
 * This file belongs to FreeMiNT. It's not in the original MiNT 1.12
 * distribution. See the file CHANGES for a detailed log of changes.
 * 
 * 
 * Copyright 2000 Frank Naumann <fnaumann@freemint.de>
 * All rights reserved.
 * 
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * 
 * Author: Frank Naumann <fnaumann@freemint.de>
 * Started: 2000-04-18
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 */

# ifndef _mint_swap_h
# define _mint_swap_h

typedef unsigned long __u32;
typedef unsigned short __u16;

static inline __u32
__asm_swap32 (register __u32 x)
{
	__asm__
	(
		"swap    %0"
		: "=d" (x)
		: "0" (x)
	);
	
	return x;
}
# define HAVE_ASM_SWAP32

static inline __u32
__const_swap32 (register __u32 x)
{
	register __u32 r;
	
	r  = (x << 16) & 0xffff0000;
	r |= (x >> 16) & 0x0000ffff;
	
	return r;
}


static inline __u32
swap32 (register __u32 x)
{
# ifdef HAVE_ASM_SWAP32
	return (__builtin_constant_p (x) ? __const_swap32 (x) : __asm_swap32 (x));
# else
	return (__const_swap32 (x));
# endif
}


static inline __u16
__const_bswap16 (register __u16 x)
{
	register __u16 r;

	r  = (x << 8) & 0xff00;
	r |= (x >> 8) & 0x00ff;

	return r;
}

#ifndef __mcoldfire__

static inline __u16
__asm_bswap16 (register __u16 x)
{
	__asm__
	(
		"rolw #8, %0"
		: "=d" (x)
		: "0" (x)
	);
	
	return x;
}
# define HAVE_ASM_BSWAP16
#endif

INLINE __u16
bswap16 (register __u16 x)
{
# ifdef HAVE_ASM_BSWAP16
	return (__builtin_constant_p (x) ? __const_bswap16 (x) : __asm_bswap16 (x));
# else
	return (__const_bswap16 (x));
# endif
}

# define BSWAP16(x)	(bswap16 (x))
# define BSWAP32(x)	(bswap32 (x))

# define SWAP16(x)	(BSWAP16 (x))
# define SWAP32(x)	(swap32 (x))


# endif /* _mint_swap_h */
