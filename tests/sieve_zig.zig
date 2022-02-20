export fn sieve_of_eratosthenes_zig(primes_out: [*]u16, work: [*]u8, work_size: u16 ) u16 {
    
    
    {
		var i: u16 = 0;
		while (i < work_size) {
		
			work[i] = 0;
			i = i + 1;
		}
    }
    
    primes_out[0] = 2;
    var primes = primes_out + 1;

    {
		var i: u16 = 3;
		while (i < work_size) {
		
			if (work[i] != 0) {
			
				i = i + 2;
				continue;
			}

			primes[0] = i;
			primes = primes + 1;
		
			{
				var j: u16 = i + i + i;
				while (j < work_size) {
					
					work[j]=1;
					j = j + i + i;
				}
			
			}
		
			i = i + 2;
		}
    }
    
    return ((@ptrToInt(primes) - @ptrToInt(primes_out))>>1);
}

export fn sieve_of_eratosthenes_zig_end() u16 { return 0; }
