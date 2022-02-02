#![no_std]
#![no_main]
#![allow(dead_code, mutable_transmutes, non_camel_case_types, non_snake_case,
         non_upper_case_globals, unused_assignments, unused_mut)]
#![feature(register_tool)]


#[no_mangle]
pub extern "C" fn suma(a: u8, b: u8) -> u8
{
  a + b
}


#[no_mangle]
pub unsafe extern "C" fn sieve_of_eratosthenes_rust(mut out: *mut u16,
                                                 mut work: *mut u8,
                                                 mut max: u16)
 -> u16 {
    let mut i: u16 = 0;
    while i < max {
        *work.offset(i as isize) = 0;
        i = i.wrapping_add(1)
    }
    
    let mut n_primes: u16 = 1;    
    
    let mut p: *mut u16 = out;
    *p = 2;
    p = p.offset(1 as isize);
    
    let mut i_0: u16 = 3;
    while i_0 < max {
        if !(*work.offset(i_0 as isize) != 0) {
            *p = i_0;
            p = p.offset(1 as isize);
            n_primes = n_primes + 1;
            let mut j: u16 = i_0 + i_0 + i_0;
            while j < max {
                *work.offset(j as isize) = 1;
                j = j + i_0 + i_0;
            }
        }
        i_0 = i_0 + 2
    }
    return n_primes;
}





/// This function is called on panic.
use core::panic::PanicInfo;

#[allow(unconditional_recursion)]
#[panic_handler]
extern "C" fn panic_handler_phony(info: &PanicInfo) -> ! { panic_handler_phony(info) }

