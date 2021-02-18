# Projet réalisé dans le cadre du module "IA - Jeux"

Ce projet est constitué de deux parties :

1. Résolution des problèmes Nqueens et Knight
2. Résolution du jeu du taquin

> Le but ici est d'illustrer certains algorithmes de parcourt ainsi que l'utilisation d'arbres de recherche à travers de ces jeux (échecs, jeu du taquin)

---

- [Projet réalisé dans le cadre du module "IA - Jeux"](#projet-réalisé-dans-le-cadre-du-module-ia---jeux)
  - [****NQUEENS***](#nqueens)
  - [Principe](#principe)
    - [Nous avons implémenté les algorithmes suivants pour ce problème](#nous-avons-implémenté-les-algorithmes-suivants-pour-ce-problème)
    - [Structures de données](#structures-de-données)
    - [Structure du code](#structure-du-code)
    - [Compraison des algorithmes](#compraison-des-algorithmes)
  - [****KNIGHTS***](#knights)
  - [Principe (Knights)](#principe-knights)
    - [Nous avons implémenté les trois algorithmes suivants pour ce problème](#nous-avons-implémenté-les-trois-algorithmes-suivants-pour-ce-problème)
    - [Structures de données pour Knights](#structures-de-données-pour-knights)
    - [Structure du code pour Knights](#structure-du-code-pour-knights)
    - [Compraison des algorithmes BFS, DFS et UCS](#compraison-des-algorithmes-bfs-dfs-et-ucs)
  - [Voir aussi : ***Jeu du taquin***](#voir-aussi--jeu-du-taquin)

---

## [****NQUEENS***](https://github.com/nathan-barbier/Nqueens-Knights)

![Wikipedia - 8Queens Minconflict](https://upload.wikimedia.org/wikipedia/commons/b/b0/8queensminconflict.gif)

[Wikipedia - Eight Queens Puzzle](https://en.wikipedia.org/wiki/Eight_queens_puzzle)

## Principe

> Le but de problème est de trouver un ensemble de N emplacements sur notre échiquier de taille N*N tels qu'on pourrait y placer N reines sans qu'elles ne s'éliminent.

### Nous avons implémenté les algorithmes suivants pour ce problème

- **BFS** (Breadth First Search)
- **DFS** (Depth First Search)

### Structures de données

- On utilise un arbre de recherche qui contient les différents états de notre plateau de jeu
- On utilise deux listes chaînées pour faire tourner les algorithmes rappelés plus haut
  
### Structure du code

- La structure des noeuds est gérée dans le fichier **item.h**.
- Toutes les fonctions qui permettent de créer, modifier ou rechercher à l'interieur des listes sont dans le module **list.c**.
- L'initialisation, la vérification et la création de nouveaux états du plateau de jeu sont gérées dans le module **board.c**.
- Les algorithmes sont implémentés dans le module **nqueens.c**.

### Compraison des algorithmes

| Algorithme | Etapes | Noeuds parcourus | Temps             | Taille |
| :--------: | :----: | :--------------: | :---------------: | :----: |
| BFS        |   5    |       3499       | <10<sup>-2</sup> s|  5x5   |
| BFS        |   6    |       60190      |  ~10 s            |  6x6   |
|            |        |                  |                   |        |
| DFS        |   8    |       1970       | <10<sup>-2</sup> s|  8x8   |
|            |        |                  |                   |        |

> Dans ce cas l'algorithme de **parcourt en profondeur (DFS)** est nettement plus rapide.  
> Ces tests ont été réalisés **dans les mêmes conditions**. [1](#foot)

---

## [****KNIGHTS***](https://github.com/nathan-barbier/Nqueens-Knights)

![Wikipedia - Knight's Tour](https://upload.wikimedia.org/wikipedia/commons/d/da/Knight%27s_tour_anim_2.gif)

[Wikipedia - Knight's Tour](https://en.wikipedia.org/wiki/Knight%27s_tour#:~:text=If%20the%20knight%20ends%20on,of%20finding%20a%20knight's%20tour.)

## Principe (Knights)

> Le but de problème est de trouver un chemin le plus court possible pour qu'un cavalier puisse se rendre d'une case A à une case B.

### Nous avons implémenté les trois algorithmes suivants pour ce problème

- **BFS** (Breadth First Search)
- **DFS** (Depth First Search)
- **UCS** (Uniform Cost Search)

### Structures de données pour Knights

- On utilise un arbre de recherche qui contient les différents états de notre plateau de jeu
- On utilise deux listes chaînées pour faire tourner les algorithmes rappelés plus haut
  
### Structure du code pour Knights

- La structure des noeuds est gérée dans le fichier **item.h**.
- Toutes les fonctions qui permettent de créer, modifier ou rechercher à l'interieur des listes sont dans le module **list.c**.
- L'initialisation, la vérification et la création de nouveaux états du plateau de jeu sont gérées dans le module **board_k.c**.
- Les algorithmes sont implémentés dans le module **knights.c**.

### Compraison des algorithmes BFS, DFS et UCS

| Algorithme | Etapes | Noeuds parcourus | Temps              |
| ---------- | :----: | :--------------: | :----------------- |
| BFS        | 6      | 584              | <10<sup>-2</sup> s |
| DFS        | 14     | 15               | 10 s               |
| UCS        | 6      | 73               | 5.10<sup>3</sup> s |

> Dans ce cas l'algorithme **UCS** est le plus efficace.  
> Ces tests ont été réalisés **dans les mêmes conditions**. [1](#foot)

---

## Voir aussi : [***Jeu du taquin***](https://github.com/nathan-barbier/Taquin_IA)

Réalisé en binôme avec [FABRE Mathis](https://github.com/yamana113)

---

<a name="foot"><sup>1</sup></a> Réalisés sur mon ordinateur personnel.
