#ifndef XWAYLAND_EXT_H
#define XWAYLAND_EXT_H

#include <xwayland-config.h>

#define XWAYLANDNAME "XWAYLAND"
#define XwaylandNumberEvents 0
#define XwaylandNumberErrors 0

#define XWAYLAND_MAJOR_VERSION	1	/* current version numbers */
#define XWAYLAND_MINOR_VERSION	0

#define X_XwaylandQueryVersion	0
#define X_XwaylandSetScale  	1


typedef struct _XwaylandQueryVersion {
    CARD8	reqType;		    /* always XwaylandReqCode */
    CARD8	xwaylandReqType;	/* always X_XwaylandQueryVersion */
    CARD16	length;
} xXwaylandQueryVersionReq;
#define sz_xXwaylandQueryVersionReq	4

typedef struct {
    BYTE	type;			    /* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber;
    CARD32	length;
    CARD16	majorVersion;		/* major version of Xwayland */
    CARD16	minorVersion;		/* minor version of Xwayland */
    CARD32	pad2;
    CARD32	pad3;
    CARD32	pad4;
    CARD32	pad5;
    CARD32	pad6;
} xXwaylandQueryVersionReply;
#define sz_xXwaylandQueryVersionReply	32


typedef struct {
    CARD8	reqType;		    /* always XwaylandReqCode */
    CARD8	xwaylandReqType;	/* always X_XwaylandSetScale */
    CARD16	length;
    CARD16	screen;
    CARD16	scale;
} xXwaylandSetScaleReq;
#define sz_xXwaylandSetScaleReq	8

void xwlExtensionInit(void);

#endif /* XWAYLAND_EXT_H */
