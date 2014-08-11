A Monte Carlo Monopoly simulation I wrote in 2005.

Simulates a number of games of Monopoly, considering all movement-related cards
and rules. Always pays to get out of jail.

Example::

    $ ./monopoly -g 10000
    Playing 10,000 games of monopoly (where, in a game, the player passes go 10 times)
                      Go |++++++++++++++++++++ (2.7%; 17,770)
      Mediterranean Ave. |++++++++++++++++ (2.1%; 14,249)
         Community Chest |++++++++++++++++ (2.2%; 14,349)
             Baltic Ave. |++++++++++++++++ (2.2%; 14,473)
              Income Tax |+++++++++++++++++ (2.2%; 14,857)
              Reading RR |++++++++++++++++++++++++++ (3.4%; 22,633)
           Oriental Ave. |++++++++++++++++++ (2.3%; 15,622)
                  Chance |++++++ (0.8%; 5,213)
            Vermont Ave. |++++++++++++++++++ (2.4%; 15,812)
        Connecticut Ave. |++++++++++++++++++ (2.3%; 15,574)
                    Jail |++++++++++++++++++++++++++++++++++++++++++++ (5.6%; 37,515)
       St. Charles Place |+++++++++++++++++++++ (2.7%; 18,019)
        Electric Company |++++++++++++++++++++++++++ (3.4%; 22,922)
             States Ave. |++++++++++++++++++ (2.3%; 15,417)
           Verginia Ave. |+++++++++++++++++++ (2.4%; 16,266)
         Pennsylvania RR |+++++++++++++++++++++ (2.7%; 17,945)
         St. James Place |+++++++++++++++++++++ (2.8%; 18,480)
         Community Chest |++++++++++++++++++++++ (2.9%; 19,225)
          Tennessee Ave. |+++++++++++++++++++++++ (3.0%; 19,831)
           New York Ave. |+++++++++++++++++++++++ (3.0%; 19,666)
            Free Parking |++++++++++++++++++++++ (2.9%; 19,150)
           Kentucky Ave. |++++++++++++++++++++++ (2.9%; 18,995)
                  Chance |++++++ (0.9%; 5,836)
            Indiana Ave. |+++++++++++++++++++++ (2.8%; 18,661)
           Illinois Ave. |+++++++++++++++++++++ (2.8%; 18,471)
              B. & O. RR |++++++++++++++++++++++ (2.9%; 19,288)
           Atlantic Ave. |+++++++++++++++++++++ (2.7%; 18,121)
            Ventnor Ave. |++++++++++++++++++++ (2.6%; 17,571)
             Water Works |+++++++++++++++++++++++++ (3.3%; 22,021)
          Marvin Gardens |+++++++++++++++++++ (2.5%; 16,525)
          Go To Jail (*) |++++++++++++++++++++ (2.6%; 17,156)
            Pacific Ave. |+++++++++++++++++++ (2.6%; 17,005)
     North Carolina Ave. |++++++++++++++++++++ (2.6%; 17,219)
         Community Chest |+++++++++++++++++++ (2.5%; 16,974)
       Pennsylvania Ave. |+++++++++++++++++++ (2.5%; 16,652)
              Short Line |+++++++++++++++++++ (2.4%; 16,299)
                  Chance |+++++ (0.7%; 4,814)
              Park Place |+++++++++++++++++ (2.2%; 14,564)
              Luxury Tax |+++++++++++++++++ (2.2%; 14,628)
               Boardwalk |++++++++++++++++++++ (2.6%; 17,656)

    *: The Go To Jail space is counted separately because a piece will never
       be on the space at the end of the turn. Instead, this count represents
       the number of times a piece landed on this space.

    Max hits: 37,515 (5.6%) Min hits: 4,814 (0.7%)
    Each '+' represents 852.61 turns where the player finished their turn on the space.


CVS directory included for historical accuracy.

All code is public domain.
