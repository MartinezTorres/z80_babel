export fn sieve_of_eratosthenes_zig(primes: [*]u16, work: [*]u8, work_size: u16 ) u16 {
    
    {
		var i: u16 = 0;
		while (i < work_size) {
		
			work[i] = 0;
			i = i + 1;
		}
    }
    
    var n_primes: u16 = 0;
    
    primes[n_primes] = 2;
    n_primes = n_primes + 1;
    
    {
		var i: u16 = 3;
		while (i < work_size) {
		
			if (work[i] != 0) {
			
				i = i + 2;
				continue;
			}

			primes[n_primes] = i;
			n_primes = n_primes + 1;
		
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
    
    return n_primes;
    
}

export fn sieve_of_eratosthenes_zig_end() u16 { return 0; }
