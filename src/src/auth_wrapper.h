#ifndef AUTH_WRAPPER_H_
#define AUTH_WRAPPER_H_

#include "googleapis/base/scoped_ptr.h"
#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/util/status.h"

namespace googleapis {

class AuthWrapper {
public:
	static util::Status									Startup(client::HttpTransport *transport_);

	util::Status										Authorize(client::OAuth2Credential *credential_);
	client::OAuth2Credential							getCredentials();
private:
	static scoped_ptr<client::OAuth2AuthorizationFlow>	flow_;
};

}

#endif /* AUTH_WRAPPER_H_ */
