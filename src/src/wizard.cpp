#include <iostream>

#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/util/status.h"

#include "auth.h"
#include "wizard.h"

using namespace googleapis;
using namespace googleapis::client;
using namespace googleapis::util;
using namespace Gtk;

Wizard::Wizard (HttpTransport *transport)
: p_auth               (new Auth(transport)),
  p_credential         (new OAuth2Credential),
  p_transport          (transport),
  m_page_intro_label   ("This wizard will help you set up your\n"\
                        "Google Drive account for use with GtkDrive"),
  m_page_account_label ("Please enter your account name"),
  m_page_auth_label    ("Please enter your confirmation code"),
  m_page_confirm_label ("Please confirm your settings")
{
  p_auth->Startup     ();
  p_auth->SetCallback (this);

  set_title ("Wizard example");
  set_default_size (400, 300);

  m_page_intro.add   (m_page_intro_label);
  append_page        (m_page_intro);
  set_page_title     (m_page_intro, "Introduction");
  set_page_type      (m_page_intro, ASSISTANT_PAGE_INTRO);
  set_page_complete  (m_page_intro, true);

  m_page_account.set_orientation (ORIENTATION_VERTICAL);
  m_page_account.add (m_page_account_label);
  m_page_account.add (m_page_account_entry);
  append_page        (m_page_account);
  set_page_title     (m_page_account, "Your account");

  m_page_auth.set_orientation    (ORIENTATION_VERTICAL);
  m_page_auth_url.set_selectable (true);
  m_page_auth_url.set_line_wrap  (true);
  m_page_auth.add    (m_page_auth_label);
  m_page_auth.add    (m_page_auth_url);
  m_page_auth.add    (m_page_auth_entry);
  append_page        (m_page_auth);
  set_page_title     (m_page_auth, "Your authorization");

  m_page_confirm.add (m_page_confirm_label);
  append_page        (m_page_confirm);
  set_page_title     (m_page_confirm, "Please confirm your settings");
  set_page_type      (m_page_confirm, ASSISTANT_PAGE_CONFIRM);
  set_page_complete  (m_page_confirm, true);

  m_page_account_entry.signal_changed ().connect (
        sigc::mem_fun(*this, &Wizard::on_account));
  m_page_auth_entry.signal_changed ().connect (
        sigc::mem_fun(*this, &Wizard::on_auth));

  show_all_children ();
}

Wizard::~Wizard ()
{
  delete p_auth;
}

void
Wizard::on_account ()
{
  Glib::ustring account = m_page_account_entry.get_text();
  m_page_auth_url.set_text (p_auth->GetAuthURL(account));
  set_page_complete (m_page_account, true);
}

void
Wizard::on_auth ()
{
  set_page_complete (m_page_auth, true);
}

void
Wizard::on_cancel ()
{
  std::cout << "Cancel was clicked" << std::endl;
  hide ();
}

void
Wizard::on_apply ()
{
  p_auth->Authorize(p_credential);
  std::cout << "Apply was clicked" << std::endl;
  hide ();
}

Status
Wizard::on_authorization (OAuth2AuthorizationFlow* flow,
                          const OAuth2RequestOptions& options,
                          string* authorization_code)
{
  *authorization_code = m_page_auth_entry.get_text();

  std::cout << "---auth callback---" << std::endl;
  std::cout << *authorization_code << std::endl;

  if (authorization_code->empty())
    return StatusCanceled("Canceled");
  else
    return StatusOk();
}

