        INTEGER*2 FUNCTION sieve_of_eratosthenes_fortran(r, w, sz)

            INTEGER*2 :: sz
            INTEGER*2 :: r(0:sz-1)
            INTEGER*1 :: w(0:sz-1)
            INTEGER*2 :: i,j,n_primes
            
            i = 0
            do while (i < sz)
                w(i) = 0
                i = i + 1
            end do

            n_primes = 1
            r(0) = 2
            
            i = 3
            do while (i < sz)
            
                if (w(i) == 0) then
                
                    r(n_primes) = i
                    n_primes = n_primes + 1
                    j = i + i + i
                    do while (j < sz)
                        
                        w(j) = j
                        j = j + i + i
                    end do
                end if
                    
                i = i + 2
            end do
            
            sieve_of_eratosthenes_fortran = n_primes
            RETURN
        END FUNCTION

        INTEGER*2 FUNCTION sieve_of_eratosthenes_fortran_end(r, w, sz)

            INTEGER*2 :: sz
            INTEGER*2 :: r(0:sz-1)
            INTEGER*1 :: w(0:sz-1)
            INTEGER*2 :: i,j,n_primes
            
            RETURN
        END FUNCTION
