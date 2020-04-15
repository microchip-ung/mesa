/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <vtss_api.h>
#include <mesa.h>

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_conv2_vtss_ace_t_to_mesa_ace_t(const vtss_ace_t *in, mesa_ace_t *out)
{
    switch (in->type) {
    case VTSS_ACE_TYPE_ANY:
    case VTSS_ACE_TYPE_ETYPE:
        mesa_conv_vtss_ace_frame_etype_t_to_mesa_ace_frame_etype_t(&in->frame.etype, &out->frame.etype);
        break;
    case VTSS_ACE_TYPE_LLC:
        mesa_conv_vtss_ace_frame_llc_t_to_mesa_ace_frame_llc_t(&in->frame.llc, &out->frame.llc);
        break;
    case VTSS_ACE_TYPE_SNAP:
        mesa_conv_vtss_ace_frame_snap_t_to_mesa_ace_frame_snap_t(&in->frame.snap, &out->frame.snap);
        break;
    case VTSS_ACE_TYPE_ARP:
        mesa_conv_vtss_ace_frame_arp_t_to_mesa_ace_frame_arp_t(&in->frame.arp, &out->frame.arp);
        break;
    case VTSS_ACE_TYPE_IPV4:
        mesa_conv_vtss_ace_frame_ipv4_t_to_mesa_ace_frame_ipv4_t(&in->frame.ipv4, &out->frame.ipv4);
        break;
    case VTSS_ACE_TYPE_IPV6:
        mesa_conv_vtss_ace_frame_ipv6_t_to_mesa_ace_frame_ipv6_t(&in->frame.ipv6, &out->frame.ipv6);
        break;
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_ace_t_to_vtss_ace_t(const mesa_ace_t *in, vtss_ace_t *out)
{
    switch (in->type) {
    case MESA_ACE_TYPE_ANY:
    case MESA_ACE_TYPE_ETYPE:
        mesa_conv_mesa_ace_frame_etype_t_to_vtss_ace_frame_etype_t(&in->frame.etype, &out->frame.etype);
        break;
    case MESA_ACE_TYPE_LLC:
        mesa_conv_mesa_ace_frame_llc_t_to_vtss_ace_frame_llc_t(&in->frame.llc, &out->frame.llc);
        break;
    case MESA_ACE_TYPE_SNAP:
        mesa_conv_mesa_ace_frame_snap_t_to_vtss_ace_frame_snap_t(&in->frame.snap, &out->frame.snap);
        break;
    case MESA_ACE_TYPE_ARP:
        mesa_conv_mesa_ace_frame_arp_t_to_vtss_ace_frame_arp_t(&in->frame.arp, &out->frame.arp);
        break;
    case MESA_ACE_TYPE_IPV4:
        mesa_conv_mesa_ace_frame_ipv4_t_to_vtss_ace_frame_ipv4_t(&in->frame.ipv4, &out->frame.ipv4);
        break;
    case MESA_ACE_TYPE_IPV6:
        mesa_conv_mesa_ace_frame_ipv6_t_to_vtss_ace_frame_ipv6_t(&in->frame.ipv6, &out->frame.ipv6);
        break;
    }
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_ACL)

