# Popis hry
Hra bude klasická RPG hra v konzoli. Ve hře bude 1 hrdina, která postupně porazí všechny monstry vyskytující se v mapě. V mapě budou rozvrženy monstry tak, aby hrdina po cestě potkávala od nejméně až po nejvýše silný monstrum. Na mapě se vyskytuje také jednotlivé předměty, které může hrdině pomoc při souboji. Poražením všech monstrů hrdina zvítězí. Prohrává tehdy, když jeho HP klesne na 0.

Mapa je reprezentována pomocí ascii character v konzoli kde:

`@` - reprezentuje hrdinu
`A-Z` - reprezentuje monstrum s rostoucí obtížností
každý item je reprezentována jiným znakem:
Například"
`?` klíč
`h` lektvar
`w` zbraň
`b` boty
Po cestě může hrdina narazit na brány, které může odemykat klíčem vyskytující se na mapě
`+` - reprezentuje brána, která je odemčená
`-` - reprezentuje brána, která je zamčená

`#` - reprezentuje zeď, přes který nemůže hráč projít
`.` - zem po které, může hrdina chodit
Příklad Mapy :

##############################
#@...?..A.#...?.E........b...#
#..h...w..########+###+#######
#...A.....#......D.?#...F....#
#+#########+#########.########
#...C....C......?.#.......Z..#
##############################

# Vlasnosti hry

Hra umožňuje hráč pohybovat hrdinu po mapě a případně otevřít inventář pro prohlédnutí nasbíraného předmětu. Hra přepne hráče do combat modu pokud narazí na nepřítele. Souboj pak probíhá tahovým způsobem. Hráč může při souboji využít různé schopnosti, jehož efektivita bude záležet na vlastnosti dané hrdiny. Po souboji hrdina získá určitý počet zkušenosti k zvýšení své úrovně.
 
# Struktura hry
Interakce s hráčem je pomocí klávesnice, kde každá funkční kláves je zobrazena ve hře.

Nabídky obsahuje např. :

- Načíst rozehranou hru
- Uložit rozehranou hru
- Vytvořit novou hru
- Použít schopnosti
- Otevřít inventář

# Polymorfismus
Polymorfismus je použit u abstraktní třídy `Item`, kde každá jeho podtřída (`Potion` a `Equipment`) má jiné chování při použití metody `use()`. Potion umožňuje hráč zvýšit svůj výkon. Equipment může hráč vzít na sobě, a tak mít dlouhodobě zvýšené vlastnosti.
Dále je polymorfismus využíván ve třídě `Skill`, kde jednotlivé specifické schopnosti (`AttackSkill`, `RegenSkill`) způsobí odlišné efekty při použití.

