#include "sigchld.h"
#include "sigint.h"
#include "sig_handler.h"

static inline void setSIG(){
	SIGINThandler();
	SIGCHLDhandler();
}