#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#include "dixstruct.h"

#include <X11/X.h>
#include "misc.h"
#include "os.h"
#include "extinit.h"

#include "xwayland-ext.h"
#include "xwayland-screen.h"

#ifdef DEBUG
#define DEBUG_P(x) DebugF(x"\n")
#else
#define DEBUG_P(x) /**/
#endif

static int XwaylandErrorBase;

static int
ProcXwaylandQueryVersion(ClientPtr client)
{
    xXwaylandQueryVersionReply rep = {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .length = 0,
        .majorVersion = XWAYLAND_MAJOR_VERSION,
        .minorVersion = XWAYLAND_MINOR_VERSION
    };

    DEBUG_P("XwaylandQueryVersion");

    REQUEST_SIZE_MATCH(xXwaylandQueryVersionReq);

    if (client->swapped) {
        swaps(&rep.sequenceNumber);
        swapl(&rep.length);
        swaps(&rep.majorVersion);
        swaps(&rep.minorVersion);
    }
    WriteToClient(client, sizeof(xXwaylandQueryVersionReply), &rep);
    return Success;
}

void xwl_screen_set_global_scale( struct xwl_screen *xwl_screen, int32_t scale);

static int
ProcXwaylandSetScale(ClientPtr client)
{
    DEBUG_P("XwaylandSetScale");

    REQUEST(xXwaylandSetScaleReq);
    REQUEST_SIZE_MATCH(xXwaylandSetScaleReq);

    if (stuff->screen >= screenInfo.numScreens)
        return BadValue;
    ScreenPtr pScreen = screenInfo.screens[stuff->screen];

    struct xwl_screen* xwl_screen = xwl_screen_get(pScreen);
    if (xwl_screen == NULL)
        return BadImplementation;

    if(stuff->scale < 1)
        return BadValue;

    xwl_screen_set_global_scale(xwl_screen, stuff->scale);

    return Success;
}

static int
ProcXwaylandDispatch(ClientPtr client)
{
    REQUEST(xReq);
    switch (stuff->data) {
        case X_XwaylandQueryVersion:
            return ProcXwaylandQueryVersion(client);
        case X_XwaylandSetScale:
            return ProcXwaylandSetScale(client);
        default:
            return BadRequest;
    }
}

static int _X_COLD
SProcXwaylandDispatch(ClientPtr client)
{
    REQUEST(xReq);
    switch (stuff->data) {
        default:
            return BadRequest;
    }
}

void
xwlExtensionInit(void)
{
    ExtensionEntry* extEntry;
    if ((extEntry = AddExtension(XWAYLANDNAME,
                                 XwaylandNumberEvents,
                                 XwaylandNumberErrors,
                                 ProcXwaylandDispatch,
                                 SProcXwaylandDispatch,
                                 NULL, StandardMinorOpcode))) {
        XwaylandErrorBase = extEntry->errorBase;
    }
}

