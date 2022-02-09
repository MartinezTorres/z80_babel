#![no_std]
#![no_main]

#[no_mangle]
pub extern fn main() {
}


/// This function is called on panic.
use core::panic::PanicInfo;

#[allow(unconditional_recursion)]
#[panic_handler]
extern "C" fn panic_handler_phony(info: &PanicInfo) -> ! { panic_handler_phony(info) }

