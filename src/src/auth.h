#ifndef AUTH_H_
#define AUTH_H_

#include "googleapis/client/auth/oauth2_authorization.h"

/* Start forward declarations */
namespace googleapis {
  namespace client {
    class HttpTransport;
  }
}
/* End forward declarations */


namespace googleapis {

class Auth {
public:
  Auth  (client::HttpTransport *transport);
  ~Auth ();

  util::Status Init                       ();
  util::Status Authorize                  (std::string id = "gerlof.fokkema");
  util::Status Callback                   (const client::OAuth2RequestOptions& options,
                                           string* authorization_code);
  client::OAuth2Credential* GetCredential () { return &m_credential; };
private:
  client::HttpTransport           *p_transport;
  client::OAuth2AuthorizationFlow *p_flow;
  const StringPiece                m_client_secret;
  client::OAuth2Credential         m_credential;
};

}

#endif /* AUTH_H_ */
