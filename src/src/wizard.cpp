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
  p_transport          (transport),
  m_page_intro_label   ("This wizard will help you set up your\n"\
                        "Google Drive account for use with GtkDrive"),
  m_page_account_label ("Please enter your account name"),
  m_page_auth_label    ("Please enter your confirmation code"),
  m_page_confirm_label ("Please confirm your settings")
{
  p_auth->Startup     ();
  p_auth->SetCallback (this);

  // TODO: call this when we have a user ID
  // p_auth->Authorize   (&m_credential);

  set_title ("Wizard example");
  set_default_size (400, 300);

  m_page_intro.add   (m_page_intro_label);
  append_page        (m_page_intro);
  set_page_title     (m_page_intro, "Introduction");
  set_page_type      (m_page_intro, ASSISTANT_PAGE_INTRO);
  set_page_complete  (m_page_intro, true);

  m_page_account.set_orientation(ORIENTATION_VERTICAL);
  m_page_account.add (m_page_account_label);
  m_page_account.add (m_page_account_entry);
  append_page        (m_page_account);
  set_page_title     (m_page_account, "Your account");

  m_page_auth.set_orientation(ORIENTATION_VERTICAL);
  m_page_auth_url.set_selectable(true);
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
  Glib::ustring::size_type atindex  = account.find_first_of ('@');
  Glib::ustring::size_type dotindex = account.find_last_of ('.');
  if (atindex  != account.npos &&
      dotindex != account.npos &&
      dotindex >  atindex &&
      dotindex <  account.length() - 2)
  {
    set_page_complete (m_page_account, true);
  }
  else
  {
    set_page_complete (m_page_account, false);
  }
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
  std::cout << "Apply was clicked" << std::endl;
  hide ();
}

Status
Wizard::on_authorization (OAuth2AuthorizationFlow* flow,
                          const OAuth2RequestOptions& options,
                          string* authorization_code)
{
  string url = flow->GenerateAuthorizationCodeRequestUrlWithOptions(options);
  std::cout << "Enter the following URL into a browser:\n" << url << std::endl;
  std::cout << std::endl;
  std::cout << "Enter the browser's response to confirm authorization: ";

  authorization_code->clear();
  std::cin >> *authorization_code;
  if (authorization_code->empty())
  {
    return StatusCanceled("Canceled");
  } else {
    return StatusOk();
  }
}

