A Monte Carlo Monopoly simulation I wrote in 2005.

Simulates a number of games of Monopoly, considering all movement-related cards
and rules. Always pays to get out of jail.

Example::

    $ ./monopoly -g 10000000
    Playing 10,000,000 games of monopoly (where, in a game, the player passes go 10 times)
                      Go |=============================== 2.7%
                land (*) |------------------------- 2.2% (-0.5%)
      Mediterranean Ave. |========================= 2.2%
         Community Chest |======================== 2.1%
                land (*) |------------------------- 2.2% (+0.1%)
             Baltic Ave. |========================== 2.2%
              Income Tax |============================= 2.6%
                land (*) |-------------------------- 2.3% (-0.3%)
              Reading RR |================================= 2.9%
                land (*) |-------------------------- 2.3% (-0.6%)
           Oriental Ave. |=========================== 2.3%
                  Chance |============= 1.1%
                land (*) |--------------------------- 2.4% (+1.3%)
            Vermont Ave. |=========================== 2.4%
        Connecticut Ave. |=========================== 2.3%
                    Jail |================================================================= 5.7%
            incarcerated |xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 3.1% (-2.6%)
            visiting (*) |------------------------------ 2.6% (-3.1%)
       St. Charles Place |=============================== 2.7%
                land (*) |-------------------------- 2.2% (-0.5%)
        Electric Company |================================ 2.8%
                land (*) |-------------------------- 2.3% (-0.6%)
             States Ave. |========================== 2.3%
           Verginia Ave. |============================ 2.4%
         Pennsylvania RR |=============================== 2.7%
                land (*) |----------------------------- 2.6% (-0.2%)
         St. James Place |=============================== 2.7%
         Community Chest |=============================== 2.7%
                land (*) |--------------------------------- 2.9% (+0.2%)
          Tennessee Ave. |================================= 2.9%
           New York Ave. |==================================== 3.2%
                land (*) |--------------------------------- 2.9% (-0.3%)
            Free Parking |================================ 2.8%
           Kentucky Ave. |================================ 2.8%
                  Chance |============== 1.2%
                land (*) |------------------------------- 2.8% (+1.6%)
            Indiana Ave. |=============================== 2.7%
           Illinois Ave. |==================================== 3.2%
                land (*) |------------------------------- 2.7% (-0.5%)
              B. & O. RR |================================= 2.9%
                land (*) |------------------------------- 2.7% (-0.2%)
           Atlantic Ave. |=============================== 2.7%
            Ventnor Ave. |=============================== 2.7%
             Water Works |================================== 3.0%
                land (*) |------------------------------ 2.6% (-0.4%)
          Marvin Gardens |============================= 2.6%
              Go To Jail |------------------------------ 2.6%
            Pacific Ave. |============================== 2.7%
     North Carolina Ave. |============================== 2.6%
         Community Chest |=============================== 2.7%
                land (*) |----------------------------- 2.6% (-0.1%)
       Pennsylvania Ave. |============================= 2.5%
              Short Line |============================ 2.5%
                  Chance |============ 1.0%
                land (*) |--------------------------- 2.3% (+1.3%)
              Park Place |========================== 2.2%
              Luxury Tax |========================== 2.2%
               Boardwalk |========================= 2.2%

    *: The 'land count' (-) is the total number of times the space was
       landed on 'naturally' (ie, immediately after rolling the dice).
       This is in contrast with the regular count (=), which shows the
       number of turns which *finished* on a space (ie, after moving.
       because of 'go to jail' or a Chance/CC card).

    Max hits: 37,840,174 (5.7%) Min hits: 0 (0.0%)
    Each '=' represents 591,252.8 turns where the player finished their turn on the space.


CVS directory included for historical accuracy.

All code is public domain.
