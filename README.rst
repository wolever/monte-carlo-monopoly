A Monte Carlo Monopoly simulation I wrote in 2005.

Simulates a number of games of Monopoly, considering all movement-related cards
and rules. Always pays to get out of jail.

Example::

    $ ./monopoly -h
    usage: ./monopoly [-g <games>] [-l <length>] [-t|-T] [-h]
    -t: show only total counts
    -T: show only land counts
    $ ./monopoly -g 10000000
    Playing 10,000,000 games of monopoly (where, in a game, the player passes go 10 times)
                      Go |------------------- 2.2%
      Mediterranean Ave. |------------------- 2.2%
         Community Chest |--------------->>>> 1.8% (+0.4%) 2.2%
             Baltic Ave. |------------------- 2.2%
              Income Tax |-------------------=== 2.2% (+0.4%) 2.6%
              Reading RR |-------------------===== 2.2% (+0.6%) 2.8%
           Oriental Ave. |------------------- 2.2%
                  Chance |--------->>>>>>>>>> 1.0% (+1.2%) 2.3%
            Vermont Ave. |------------------- 2.2%
        Connecticut Ave. |------------------- 2.2%
                    Jail |---------------------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 2.5% (+4.6%) 7.1%
       St. Charles Place |------------------==== 2.1% (+0.5%) 2.6%
        Electric Company |-------------------== 2.2% (+0.3%) 2.5%
             States Ave. |-------------------- 2.3%
           Verginia Ave. |--------------------- 2.4%
         Pennsylvania RR |----------------------== 2.6% (+0.1%) 2.8%
         St. James Place |------------------------ 2.8%
         Community Chest |--------------------->>>>> 2.5% (+0.5%) 3.0%
          Tennessee Ave. |------------------------- 3.0%
           New York Ave. |-------------------------==== 2.9% (+0.5%) 3.5%
            Free Parking |------------------------- 2.9%
           Kentucky Ave. |------------------------ 2.8%
                  Chance |---------->>>>>>>>>>>>>> 1.2% (+1.6%) 2.8%
            Indiana Ave. |----------------------- 2.7%
           Illinois Ave. |-----------------------==== 2.7% (+0.5%) 3.2%
              B. & O. RR |-----------------------== 2.7% (+0.2%) 2.9%
           Atlantic Ave. |------------------------ 2.8%
            Ventnor Ave. |----------------------- 2.7%
             Water Works |-----------------------= 2.7% (+0.2%) 2.9%
          Marvin Gardens |---------------------- 2.6%
              Go To Jail |>>>>>>>>>>>>>>>>>>>>>>> 0.0% (+2.7%) 2.7%
            Pacific Ave. |----------------------- 2.7%
     North Carolina Ave. |---------------------- 2.6%
         Community Chest |---------------------- 2.5% (+0.1%) 2.6%
       Pennsylvania Ave. |---------------------- 2.5%
              Short Line |--------------------- 2.5%
                  Chance |--------->>>>>>>>>>> 1.0% (+1.3%) 2.3%
              Park Place |------------------- 2.2%
              Luxury Tax |------------------- 2.2%
               Boardwalk |------------------- 2.2%

    Legend:
    =: the player ended their turn on this space
    >: the player landed on this space but moved before ending their turn
    -: both of the above
    x: the player was put into jail

    Max hits: 47,151,987 (7.1%) Min hits: 0 (0.0%)
    Each '-' represents 799,186.2 turns

CVS directory included for historical accuracy.

All code is public domain.
