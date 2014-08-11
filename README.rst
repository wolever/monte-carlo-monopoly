A Monte Carlo Monopoly simulation I wrote in 2005.

Simulates a number of games of Monopoly, considering all movement-related cards
and rules (except for "jail after three doubles", it seems).

Example::

    $ ./monopoly  -g 1024 -l 12 
    Playing 1024 games of monopoly (where, in a game, the player passes go 12 times)
                      Go |+ (1804)
      Mediterranean Ave. |+++++++++ (1875)
         Community Chest |++ (1805)
             Baltic Ave. |+++++ (1834)
              Income Tax |++++ (1827)
              Reading RR |+++++++++++ (1889)
           Oriental Ave. |++++++++++++++++++ (1956)
                  Chance |++++++++++++++ (1920)
            Vermont Ave. |+++++++++++++++++++++ (1977)
        Connecticut Ave. |++++++++ (1862)
                    Jail |++++++++++++++++++ (1955)
       St. Charles Place | (1788)
        Electric Company | (1789)
             States Ave. |+++++++++ (1876)
           Verginia Ave. |+++++++++++++++++++++++++++++ (2053)
         Pennsylvania RR |+++++++++++++++++++++++++++++++++++++++++++++ (2193)
         St. James Place |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2313)
         Community Chest |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2494)
          Tennessee Ave. |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2437)
           New York Ave. |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2476)
            Free Parking |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2509)
           Kentucky Ave. |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2371)
                  Chance |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2337)
            Indiana Ave. |+++++++++++++++++++++++++++++++++++++++++++++++++++++ (2272)
           Illinois Ave. |++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2280)
              B. & O. RR |+++++++++++++++++++++++++++++++++++++++++++++++++++ (2254)
           Atlantic Ave. |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2315)
            Ventnor Ave. |++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2281)
             Water Works |++++++++++++++++++++++++++++++++++++++++ (2152)
          Marvin Gardens |+++++++++++++++++++++++++++++++++++ (2109)
              Go To Jail |+++++++++++++++++++++++++++++++++++++++++++++ (2194)
            Pacific Ave. |++++++++++++++++++++++++++++++++++++++++++++++++++++++ (2276)
     North Carolina Ave. |+++++++++++++++++++++++++++++++++++++++++++++++++++ (2249)
         Community Chest |++++++++++++++++++++++++++++++++++++++++ (2149)
       Pennsylvania Ave. |+++++++++++++++++++++++++++++++++ (2088)
              Short Line |++++++++++++++++++++++++++++++++++ (2098)
                  Chance |++++++++++++++ (1920)
              Park Place |+++++ (1833)
              Luxury Tax |++++++++++++++ (1915)
               Boardwalk | (1786)
    Max hits: 2509 Min hits: 1786
    Each '+' represents 9.04 hits (plus an initial correction of 1786)

CVS directory included for historical accuracy.

All code is public domain.
