#ifndef AUTH_H_
#define AUTH_H_

/* Start forward declarations */
class Wizard;
namespace googleapis {
  namespace client {
    class HttpTransport;
    class OAuth2AuthorizationFlow;
    class OAuth2Credential;
    class OAuth2RequestOptions;
  }
}
/* End forward declarations */


namespace googleapis {

class Auth {
public:
  Auth  (client::HttpTransport *transport);
  ~Auth ();

  util::Status Startup          ();
  void         SetCallback      (Wizard *wizard);
  std::string  GetAuthURL       (std::string id = "gerlof.fokkema");
  util::Status Authorize        (client::OAuth2Credential *credential);
private:
  client::HttpTransport           *p_transport;
  client::OAuth2AuthorizationFlow *p_flow;
  client::OAuth2RequestOptions     options;
  const StringPiece                m_client_secret;
};

}

#endif /* AUTH_H_ */
