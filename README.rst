A Monte Carlo Monopoly simulation I wrote in 2005.

Simulates a number of games of Monopoly, considering all movement-related cards
and rules. Always pays to get out of jail.

Example::

    $ ./monopoly -g 10000000
    Playing 10,000,000 games of monopoly (where, in a game, the player passes go 10 times)
                      Go |==================== 2.7%
                land (*) |----------------- 2.3% (-0.5%)
      Mediterranean Ave. |================ 2.2%
         Community Chest |================ 2.2%
             Baltic Ave. |================ 2.2%
              Income Tax |=================== 2.5%
                land (*) |----------------- 2.2% (-0.3%)
              Reading RR |=================== 2.6%
                land (*) |----------------- 2.3% (-0.3%)
           Oriental Ave. |================= 2.3%
                  Chance |=== 0.4%
                land (*) |------------------ 2.4% (+1.9%)
            Vermont Ave. |================= 2.3%
        Connecticut Ave. |================= 2.3%
                    Jail |=========================================== 5.7%
            incarcerated |xxxxxxxxxxxxxxxxxxxxxxx 3.1% (-2.5%)
            visiting (*) |------------------- 2.5% (-3.1%)
       St. Charles Place |======================= 3.1%
                land (*) |---------------- 2.1% (-0.9%)
        Electric Company |======================= 3.0%
                land (*) |---------------- 2.2% (-0.9%)
             States Ave. |================ 2.2%
           Verginia Ave. |================= 2.3%
         Pennsylvania RR |===================== 2.8%
                land (*) |------------------ 2.5% (-0.3%)
         St. James Place |==================== 2.7%
         Community Chest |===================== 2.9%
          Tennessee Ave. |====================== 2.9%
           New York Ave. |======================== 3.2%
                land (*) |---------------------- 2.9% (-0.3%)
            Free Parking |===================== 2.9%
           Kentucky Ave. |===================== 2.8%
                  Chance |==== 0.5%
                land (*) |--------------------- 2.8% (+2.2%)
            Indiana Ave. |==================== 2.7%
           Illinois Ave. |=========================== 3.7%
                land (*) |-------------------- 2.7% (-0.9%)
              B. & O. RR |======================= 3.0%
                land (*) |-------------------- 2.7% (-0.3%)
           Atlantic Ave. |==================== 2.7%
            Ventnor Ave. |==================== 2.7%
             Water Works |======================= 3.1%
                land (*) |------------------- 2.6% (-0.5%)
          Marvin Gardens |=================== 2.6%
                land (*) |-------------------- 2.6% (+2.6%)
            Pacific Ave. |==================== 2.7%
     North Carolina Ave. |==================== 2.7%
         Community Chest |====================== 2.9%
                land (*) |------------------- 2.6% (-0.3%)
       Pennsylvania Ave. |=================== 2.6%
              Short Line |=================== 2.5%
                  Chance |=== 0.4%
                land (*) |------------------ 2.4% (+2.0%)
              Park Place |================= 2.3%
              Luxury Tax |================= 2.3%
               Boardwalk |================= 2.3%

    *: The 'land count' (-) is the total number of times the space was
       landed on 'naturally' (ie, immidiately after rolling the dice).
       This is in contrast with the regular count (=), which shows the
       number of turns which *finished* on a space (ie, after moving.
       because of 'go to jail' or a Chance/CC card).

    Max hits: 34,482,224 (5.3%) Min hits: 6,581,892 (1.0%)
    Each '=' represents 201,650.44 turns where the player finished their turn on the space.


CVS directory included for historical accuracy.

All code is public domain.
