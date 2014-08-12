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
                      Go |----------------------========= 2.1% (+0.9%) 3.1%
      Mediterranean Ave. |---------------------- 2.1%
         Community Chest |-------------------->> 1.9% (+0.3%) 2.2%
             Baltic Ave. |----------------------- 2.2%
              Income Tax |-----------------------== 2.3% (+0.2%) 2.4%
              Reading RR |------------------------======= 2.3% (+0.8%) 3.1%
           Oriental Ave. |------------------------ 2.4%
                  Chance |---------->>>>>>>>>>>>>>> 0.9% (+1.5%) 2.4%
            Vermont Ave. |------------------------- 2.4%
        Connecticut Ave. |------------------------ 2.3%
                    Jail |---------------------------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 2.6% (+3.6%) 6.2%
       St. Charles Place |-----------------------===== 2.2% (+0.5%) 2.7%
        Electric Company |------------------------== 2.3% (+0.3%) 2.6%
             States Ave. |------------------------ 2.3%
           Verginia Ave. |------------------------- 2.4%
         Pennsylvania RR |---------------------------=== 2.6% (+0.3%) 2.9%
         St. James Place |---------------------------- 2.8%
         Community Chest |-------------------------->>>> 2.6% (+0.4%) 2.9%
          Tennessee Ave. |------------------------------ 2.9%
           New York Ave. |------------------------------= 2.9% (+0.2%) 3.1%
            Free Parking |----------------------------- 2.9%
           Kentucky Ave. |----------------------------- 2.8%
                  Chance |----------->>>>>>>>>>>>>>>>> 1.0% (+1.7%) 2.8%
            Indiana Ave. |---------------------------- 2.7%
           Illinois Ave. |----------------------------==== 2.7% (+0.5%) 3.2%
              B. & O. RR |----------------------------=== 2.7% (+0.3%) 3.0%
           Atlantic Ave. |---------------------------- 2.7%
            Ventnor Ave. |--------------------------- 2.7%
             Water Works |---------------------------== 2.6% (+0.2%) 2.8%
          Marvin Gardens |-------------------------- 2.6%
              Go To Jail |>>>>>>>>>>>>>>>>>>>>>>>>>>> 0.0% (+2.6%) 2.6%
            Pacific Ave. |--------------------------- 2.7%
     North Carolina Ave. |--------------------------- 2.6%
         Community Chest |------------------------>> 2.4% (+0.2%) 2.5%
       Pennsylvania Ave. |------------------------- 2.5%
              Short Line |------------------------- 2.4%
                  Chance |--------->>>>>>>>>>>>>>> 0.9% (+1.4%) 2.3%
              Park Place |---------------------- 2.2%
              Luxury Tax |---------------------- 2.2%
               Boardwalk |----------------------===== 2.2% (+0.5%) 2.6%

    Legend:
    -: player landed and finished their turn on this space
    >: player landed but did not finish their turn on this space
    =: player finished their but did not land on this space (ie, they were moved to it)
    x: the player was put into jail

    Max hits: 41,240,704 (6.2%) Min hits: 0 (0.0%)
    Each '-' represents 665,172.6 turns

CVS directory included for historical accuracy.

All code is public domain.
