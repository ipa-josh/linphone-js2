
#include "lock.h"

#define IN_LINPHONE // This is a dirty hack for linphone to include files from actal 
	// directory and not from system header location, and thus we dont need to install it and mess with the system
#include <linphonecore.h>
//#include "private.h" /*coreapi/private.h, needed for LINPHONE_VERSION */

// Core
class linphone;
FB_FORWARD_PTR(linphone);

class linphoneAPI;
typedef boost::shared_ptr<linphoneAPI> linphoneAPIPtr;
typedef boost::weak_ptr<linphoneAPI> linphoneAPIWeakPtr;

// Call
class CallAPI;
typedef boost::shared_ptr<CallAPI> CallAPIPtr;
typedef boost::weak_ptr<CallAPI> CallAPIWeakPtr;

// Address
class AddressAPI;
typedef boost::shared_ptr<AddressAPI> AddressAPIPtr;
typedef boost::weak_ptr<AddressAPI> AddressAPIWeakPtr;

// Sample
class SampleAPI;
typedef boost::shared_ptr<SampleAPI> SampleAPIPtr;
typedef boost::weak_ptr<SampleAPI> SampleAPIWeakPtr;
