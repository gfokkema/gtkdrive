#ifndef DRIVE_WRAPPER_H_
#define DRIVE_WRAPPER_H_

#include "googleapis/base/scoped_ptr.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/util/status.h"
#include "google/drive_api/drive_api.h"

#include "auth_wrapper.h"

namespace googleapis {

class DriveWrapper {
public:
	DriveWrapper();

	void dir();
private:
	static scoped_ptr<googleapis::AuthWrapper>				auth_;
	static scoped_ptr<client::HttpTransportLayerConfig>		config_;
	static scoped_ptr<google_drive_api::DriveService>		service_;

	client::OAuth2Credential								credential_;
};

} // namespace googleapis

#endif /* DRIVE_WRAPPER_H_ */
