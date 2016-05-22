/*
 * Packit -- network injection and capture tool
 *
 * Original author: Darren Bounds <dbounds@intrusense.com>
 *
 * Copyright 2002-2004 Darren Bounds <dbounds@intrusense.com>
 * Copyright 2013      Mats Erik Andersson <gnu@gisladisker.se>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 *
 * packit official page at https://github.com/eribertomota/packit
 */

#include "print_arp_hdr.h"

void
print_arp_hdr(u_int8_t *packet)
{
    u_int8_t *arp_t, *arp_hw_t;
    u_int16_t frame_t;

    struct libnet_arp_hdr *ahdr;

#ifdef DEBUG
    fprintf(stdout, "DEBUG: print_arp_hdr()\n");
#endif

    ahdr = (struct libnet_arp_hdr *)(packet + hdr_len);

    arp_t = retrieve_arp_type(htons(ahdr->ar_op));
    arp_hw_t = retrieve_arp_hw_type(htons(ahdr->ar_hrd));

    fprintf(stdout, "ARP header:  Type: %s(%d)\n", arp_t, htons(ahdr->ar_op));
    frame_t = ntohs(*(u_int16_t *)(packet + hdr_len - sizeof(u_int16_t)));

    fprintf(stdout, "%s header:  Type: %s(%d)\n",
            (frame_t == ETHERTYPE_REVARP) ? "RARP": "ARP",
            arp_t, htons(ahdr->ar_op));
    fprintf(stdout, "     Hardware Format: %s  Length: %d\n",
        arp_hw_t,
        ahdr->ar_hln);

    fprintf(stdout, "     Protocol Format: %d  Length: %d\n",
        ahdr->ar_pro,
        ahdr->ar_pln);

    return;
}
