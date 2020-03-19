#pragma once
#include <cppgit2/libgit2_api.hpp>
#include <cppgit2/ownership.hpp>
#include <git2.h>
#include <string>

// Owned by user, cleaned up in destructor
class credential : public libgit2_api {
public:
  // Create a "default" credential usable for Negotiate mechanisms like NTLM or
  // Kerberos authentication.
  credential();

  // Create a new plain-text username and password credential object. The
  // supplied credential parameter will be internally duplicated.
  credential(const std::string &username, const std::string &password);

  // Create a new passphrase-protected ssh key credential object. The supplied
  // credential parameter will be internally duplicated.
  credential(const std::string &username, const std::string &public_key,
             const std::string &private_key, const std::string &passphrase);

  // Create a new ssh key credential object used for querying an ssh-agent. The
  // supplied credential parameter will be internally duplicated.
  credential(const std::string &username);

  // Cleanup credential object
  ~credential();

  // Supported credential types
  // This represents the various types of authentication methods supported by
  // the library.
  enum class type {
	// a vanilla user/password request
	userpass_plaintext = (1u << 0),

	// an ssh key-based authentication request
	ssh_key = (1u << 1),

	// an ssh key-based authentication request, with a custom signature
	ssh_custom = (1u << 2),

	// an ntlm/negotiate-based authentication request.
	default_ = (1u << 3),

	// an ssh interactive authentication request
	ssh_interactive = (1u << 4),

	// username-only authentication request
	//
	// used as a pre-authentication step if the underlying transport
	// (eg. ssh, with no username in its url) does not know which username
	// to use.
	username = (1u << 5),

	// an ssh key-based authentication request
	//
	// allows credentials to be read from memory instead of files.
	// note that because of differences in crypto backend support, it might
	// not be functional.
	ssh_memory = (1u << 6),
  };

  // Return the username associated with a credential object.
  std::string username() const;

  // Check whether a credential object contains username information.
  bool has_username() const;

private:
  git_credential *c_ptr_;
};