/*
 * auth_wrapper.h
 *
 *  Created on: Feb 5, 2014
 *      Author: gero
 */

#ifndef AUTH_WRAPPER_H_
#define AUTH_WRAPPER_H_

namespace googleapis {

class AuthWrapper {
public:
	AuthWrapper();
	virtual ~AuthWrapper();
	static util::Status Startup();
	util::Status Authorize();
	void Run();
private:
	client::OAuth2Credential credential_;
	static scoped_ptr<google_drive_api::DriveService> service_;
	static scoped_ptr<client::OAuth2AuthorizationFlow> flow_;
	static scoped_ptr<client::HttpTransportLayerConfig> config_;
};

} // namespace googleapis

#endif /* AUTH_WRAPPER_H_ */
