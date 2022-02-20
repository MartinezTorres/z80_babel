#![no_std]
#![no_main]

#[no_mangle]
pub unsafe extern "C" fn sieve_of_eratosthenes_rust(primes: *mut u16,
                                                 work: *mut u8,
                                                 work_size: u16)
 -> u16 {
     
    {
        let mut i: u16 = 0;
        while i < work_size {
            *work.offset(i as isize) = 0;
            i = i.wrapping_add(1)
        }
    }
    
    let mut p: *mut u16 = primes;
    *p = 2;
    p = p.offset(1);

    {
        let mut i: u16 = 3;
        while i < work_size {
            
            if !(*work.offset(i as isize) != 0) {

                *p = i;
                p = p.offset(1);
                
                let mut j: u16 = i + i + i;
                while j < work_size {
                    
                    *work.offset(j as isize) = 1;
                    j = j + i + i;
                }
            }
            i = i + 2
        }
    }
    return ((p as u16) - (primes as u16))>>1;
}

#[no_mangle]
pub unsafe extern "C" fn sieve_of_eratosthenes_rust_end() -> u16 { return 0; }




/// This function is called on panic.
use core::panic::PanicInfo;

#[allow(unconditional_recursion)]
#[panic_handler]
extern "C" fn panic_handler_phony(info: &PanicInfo) -> ! { panic_handler_phony(info) }

