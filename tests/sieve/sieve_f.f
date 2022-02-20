        INTEGER*2 FUNCTION sieve_f(primes, work, work_size)

            INTEGER*2 :: work_size
            INTEGER*2 :: primes(0:work_size-1)
            INTEGER*1 :: work(0:work_size-1)
            INTEGER*2 :: i,j,n_primes
            
            i = 0
            do while (i < work_size)
                work(i) = 0
                i = i + 1
            end do

            n_primes = 1
            primes(0) = 2
            
            i = 3
            do while (i < work_size)
            
                if (work(i) == 0) then
                
                    primes(n_primes) = i
                    n_primes = n_primes + 1
                    j = i + i + i
                    do while (j < work_size)
                        
                        work(j) = j
                        j = j + i + i
                    end do
                end if
                    
                i = i + 2
            end do
            
            sieve_f = n_primes
            RETURN
        END FUNCTION

        INTEGER*2 FUNCTION sieve_f_end()

            sieve_fortran_end = 0
            RETURN
        END FUNCTION
