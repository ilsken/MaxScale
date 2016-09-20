/*
 * Copyright (c) 2016 MariaDB Corporation Ab
 *
 * Use of this software is governed by the Business Source License included
 * in the LICENSE.TXT file and at www.mariadb.com/bsl.
 *
 * Change Date: 2019-07-01
 *
 * On the date above, in accordance with the Business Source License, use
 * of this software will be governed by version 2 or later of the General
 * Public License.
 */

#include <gw_authenticator.h>
#include <dcb.h>
#include <listener.h>
#include <maxscale/alloc.h>
#include <mysql_client_server_protocol.h>

static int gssapi_auth_set_protocol_data(DCB *dcb, GWBUF *buffer)
{
    if (dcb->data == NULL)
    {
        MYSQL_session *client_data = (MYSQL_session *)MXS_CALLOC(1, sizeof(MYSQL_session));
    }
    return MXS_AUTH_SUCCEEDED;
}

static int gssapi_auth_authenticate(DCB *dcb)
{
    return MXS_AUTH_SUCCEEDED;
}

static void gssapi_auth_free(DCB *dcb)
{

}

static int gssapi_auth_load_users(SERV_LISTENER *listener)
{
    return MXS_AUTH_LOADUSERS_OK;
}

static bool gssapi_auth_is_client_ssl_capable(DCB *dcb)
{
    return false;
}

/*
 * The "module object" for mysql client authenticator module.
 */
static GWAUTHENTICATOR MyObject =
{
    gssapi_auth_set_protocol_data, /* Extract data into structure   */
    gssapi_auth_is_client_ssl_capable, /* Check if client supports SSL  */
    gssapi_auth_authenticate,   /* Authenticate user credentials */
    gssapi_auth_free,           /* Free the client data held in DCB */
    gssapi_auth_load_users,     /* Load users from backend databases */
    "auth_gssapi_client"
};

static char *version_str = "1.0.0";

/*lint -e14 */
MODULE_INFO info =
{
    MODULE_API_AUTHENTICATOR,
    MODULE_GA,
    GWAUTHENTICATOR_VERSION,
    "The MySQL client to MaxScale authenticator implementation"
};
/*lint +e14 */
