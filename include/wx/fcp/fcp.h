/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fcp/fcp.h
// Purpose:     central header for fcp implementation
// Author:      saces
// Modified by:
// Created:     14.01.2009
// RCS-ID:      $Id$
// Copyright:   (c) 2009 saces <saces@freenetproject.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _FCP_FCP_H_
#define _FCP_FCP_H_

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#ifndef DEFAULT_FCP_HOST
    #define DEFAULT_FCP_HOST "127.0.0.1"
#endif

#ifndef DEFAULT_FCP_PORT
   #define DEFAULT_FCP_PORT 9481
#endif

#ifndef DEFAULT_FCP_TIMEOUT
   #define DEFAULT_FCP_TIMEOUT 300
#endif

#ifndef FCP_HOST_ENV_NAME
   #define FCP_HOST_ENV_NAME "FCP_HOST"
#endif

#ifndef FCP_PORT_ENV_NAME
   #define FCP_PORT_ENV_NAME "FCP_PORT"
#endif

#ifndef FCP_TIMEOUT_ENV_NAME
   #define FCP_TIMEOUT_ENV_NAME "FCP_TIMEOUT"
#endif

#ifndef REQUIRED_NODE_VERSION
   #define REQUIRED_NODE_VERSION 1197
#endif

#ifndef REQUIRED_NODE_BUILD
   #define REQUIRED_NODE_BUILD 25053
#endif

#ifndef REQUIRED_EXT_VERSION
   #define REQUIRED_EXT_VERSION 26
#endif

#ifndef REQUIRED_EXT_BUILD
   #define REQUIRED_EXT_BUILD 23771
#endif

#include "wx/fcp/connection.h"
#include "wx/fcp/message.h"
#include "wx/fcp/job.h"
#include "wx/fcp/session.h"

#endif // ifndef _FCP_FCP_H_
