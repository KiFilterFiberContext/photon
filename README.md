# photon
Photon is a lightweight hooking engine for the ARM architecture

## Features
The engine supports hooking at the instruction level and allows for modification and inspection of register content in logcat. 
- Instruction Hooking (`softbp::hook_with_entry`)
- Instruction Monitoring (`softbp::midhook_with_entry`)
- LogCat printing (`utils::print` and `utils::debug_print`)

## Implementation
As opposed to trampoline hooking engines, the engine operates by overwriting instructions with the `UDF #1` trap instruction.  This instruction raises a `SIGTRAP` signal and redirects control flow to any registered signal handlers.  When initializing the engine a signal handler is registered with `softbp::setup` with an option to provide a custom signal handler and to catch `SIGSEGV` signals.  It also spawns a watchdog thread for reapplying the trap instruction after dispatch. 

By default, it will register the signal handler for `SIGILL` and `SIGTRAP` signals.  When registering a hook it will retain the overwritten instruction bytes and save the hook routine.  When the signal handler is dispatched to, it will lookup the global list and redirect the instruction pointer to the hook routine and reapply the original bytes.  


## Example
```cpp
#include "photon.h"

//
// hooking a subroutine from the Android game, Geometry Dash
//

using photon::core::softbp;

using photon::utils::debug_print;
using photon::utils::print;

USING_NS_CC;
USING_NS_CC_EXT;

bool ex_callback( LoadingLayer* p, bool useDefault )
{
    debug_print("called from %s", __FUNCTION__ );
    return p->init( useDefault );
}

__attribute__((constructor))
void phsdk_libmain( void )
{
    softbp::setup( softbp::sig_handler, false );
    
    //
    // error checking is recommended
    //
    softbp::hook_with_entry( "libcocos2dcpp.so", "_ZN12LoadingLayer4initEb", (void*) ex_callback );
}
```

## TODO
- GOT/PLT hooking
- Hardware Breakpoints 
- AArch64 support
- Bug Fixing

## License
MIT
