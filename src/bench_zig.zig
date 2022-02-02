


export fn add(a: u8, b: u8) u8 {
return a + b;
}

export fn sieve_of_eratosthenes_zig(result: [*]u16, work: [*]u16, max: u16 ) u16 {
    
    {
		var i: u16 = 0;
		while (i < max) {
		
			work[i] = 0;
			i = i + 1;
		}
    }
    
    var n_primes: u16 = 0;
    
    result[n_primes] = 2;
    n_primes = n_primes + 1;
    
    {
		var i: u16 = 3;
		while (i < max) {
		
			if (work[i] != 0) {
			
				i = i + 2;
				continue;
			}

			result[n_primes] = i;
			n_primes = n_primes + 1;
		
			{
				var j: u16 = i + i + i;
				while (j < max) {
					
					work[j]=1;
					j = j + i + i;
				}
			
			}
		
			i = i + 2;
		}
    }
    
    return n_primes;
    
}
