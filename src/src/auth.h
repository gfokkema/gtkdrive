#ifndef AUTH_H_
#define AUTH_H_

/* Start forward declarations */
class GtkDriveAssistant;
namespace googleapis {
  namespace client {
    class OAuth2AuthorizationFlow;
    class OAuth2Credential;
    class OAuth2RequestOptions;
  }
}
/* End forward declarations */


namespace googleapis {

class Auth {
public:
  Auth (client::HttpTransport *transport);
  ~Auth ();

  util::Status             Startup          ();
  util::Status             Authorize        (client::OAuth2Credential *credential);

  static util::Status      getAuthorization (client::OAuth2AuthorizationFlow *flow,
                                             const client::OAuth2RequestOptions& options,
                                             string *authorization_code);
private:

  const StringPiece                m_client_secret;
  client::OAuth2AuthorizationFlow *p_flow;
  client::HttpTransport           *p_transport;
};

}

#endif /* AUTH_H_ */
