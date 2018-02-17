* to compile: gfortran vol.f
        print*, 'Enter radius'
        read*, r
        pi = acos(-1.)
        v = (4./3.)*pi*r**3
        print*, v
        end
