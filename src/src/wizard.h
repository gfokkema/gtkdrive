#ifndef WIZARD_H_
#define WIZARD_H_

#include <gtkmm.h>

/* Start forward declarations */
namespace googleapis {
  class Auth;
  namespace client {
    class HttpTransport;
    class OAuth2AuthorizationFlow;
    class OAuth2RequestOptions;
  }
}
/* End forward declarations */

class Wizard : public Gtk::Assistant
{
public:
  /* Constructor */
  Wizard  (googleapis::client::HttpTransport *transport);
  ~Wizard ();

  /* Members */
  googleapis::util::Status on_authorization (googleapis::client::OAuth2AuthorizationFlow    *flow,
                                             const googleapis::client::OAuth2RequestOptions &options,
                                             std::string                                    *authcode);
private:
  /* Signals */
  void on_account ();
  void on_auth    ();

  void on_apply  ();
  void on_cancel ();

  googleapis::Auth                     *p_auth;
  googleapis::client::OAuth2Credential *p_credential;
  googleapis::client::HttpTransport    *p_transport;

  Gtk::Grid  m_page_intro;
  Gtk::Label m_page_intro_label;
  Gtk::Grid  m_page_account;
  Gtk::Label m_page_account_label;
  Gtk::Entry m_page_account_entry;
  Gtk::Grid  m_page_auth;
  Gtk::Label m_page_auth_label;
  Gtk::Label m_page_auth_url;
  Gtk::Entry m_page_auth_entry;
  Gtk::Grid  m_page_confirm;
  Gtk::Label m_page_confirm_label;
};

#endif /* WIZARD_H_ */
