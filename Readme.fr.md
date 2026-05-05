# push_swap

[English](README.md)

*Lire une ligne, un buffer à la fois... attendez, mauvais projet.*

---

## Description

`push_swap` est un projet d'algorithme de tri où on trie une pile d'entiers en utilisant seulement deux piles et un ensemble limité d'opérations. L'objectif est de trier les nombres avec le moins de mouvements possible.

**Ce que j'ai appris :** Optimisation d'algorithmes, heuristiques gloutonnes, calcul de coûts, et pourquoi choisir le bon algorithme compte beaucoup plus que je ne le pensais.

**Le défi :** Trier 500 nombres aléatoires en moins de 5 500 opérations. Ça a l'air facile jusqu'à ce qu'on réalise que chaque rotation compte.

---

## Comment l'utiliser

### Compilation

```bash
make
```

### Exécution

```bash
# Trier quelques nombres
./push_swap 3 2 1 5 4

# Fonctionne aussi avec des guillemets
./push_swap "3 2 1 5 4"

# Tester avec checker (si vous l'avez)
./push_swap 3 2 1 | ./checker 3 2 1
```

### Ce que ça affiche

Une série d'opérations comme :
```
pb
pb
sa
pa
pa
```

Ces opérations, appliquées à la pile d'origine, vont la trier.

---

## Les opérations

| Opération | Ce qu'elle fait |
|-----------|-----------------|
| `sa` | Échange les 2 premiers éléments de la pile A |
| `sb` | Échange les 2 premiers éléments de la pile B |
| `pa` | Pousse le sommet de B vers A |
| `pb` | Pousse le sommet de A vers B |
| `ra` | Rotation de A vers le haut (le premier devient dernier) |
| `rb` | Rotation de B vers le haut |
| `rr` | Rotation de A et B en même temps |
| `rra` | Rotation inverse de A (le dernier devient premier) |
| `rrb` | Rotation inverse de B |
| `rrr` | Rotation inverse de A et B en même temps |

---

## Mon approche

### Pour les petites piles (2-3 nombres)

J'ai juste hardcodé les mouvements optimaux. Pas la peine de trop réfléchir.

- 2 nombres : Échanger si nécessaire. Terminé.
- 3 nombres : Maximum 2 opérations. Facile.

### Pour les grandes piles (100-500 nombres) : L'algorithme Turk

C'est là que ça devient intéressant.

**Étape 1 : Donner un rang à chaque nombre**

Au lieu de comparer des valeurs comme `42 < 100`, j'assigne des rangs (0, 1, 2...) basés sur leur position triée. Beaucoup plus rapide.

**Étape 2 : Pousser presque tout vers la pile B**

Laisser 3 nombres dans A, pousser le reste vers B. Maintenant A est facile à trier.

**Étape 3 : Trier les 3 nombres dans A**

Solution optimale hardcodée.

**Étape 4 : Ramener tout de B vers A (intelligemment)**

C'est là que la magie opère. Pour chaque nombre dans B :

1. Trouver sa **cible** dans A (où il doit aller)
2. Calculer le **coût** pour le déplacer (combien de rotations nécessaires)
3. Choisir le **moins cher** et le déplacer en premier

**L'optimisation :** Quand le nombre dans B et sa cible dans A sont du même côté (tous deux au-dessus ou en-dessous de la médiane), je peux faire tourner les deux piles en même temps avec `rr` ou `rrr`. Ça économise énormément d'opérations.

**Étape 5 : Rotation finale**

Faire tourner A jusqu'à ce que le plus petit nombre soit en haut. Terminé.

---

## Pourquoi ça marche

L'insight clé : **tous les mouvements n'ont pas le même coût.**

Si j'ai besoin de faire tourner A 5 fois et B 3 fois, et qu'ils tournent tous les deux dans la même direction, je peux faire 3 opérations `rr` (simultanées) + 2 opérations `ra` = **5 opérations au total au lieu de 8**.

Cette petite optimisation a fait baisser ma moyenne de ~5 700 opérations à ~5 160 pour 500 nombres.

---

## Ma structure de données

J'ai utilisé une liste doublement chaînée pour chaque pile :

```c
typedef struct s_stack
{
    int             value;          // Le nombre actuel
    int             rank;           // Sa position triée
    int             index;          // Position actuelle dans la pile
    int             push_cost;      // Coût pour déplacer ce nœud
    bool            above_median;   // Est-il dans la moitié supérieure ?
    bool            cheapest;       // Est-ce le moins cher à déplacer ?
    struct s_stack  *target_node;   // Où il doit aller dans l'autre pile
    struct s_stack  *next;
    struct s_stack  *prev;
}                   t_stack;
```

Pourquoi doublement chaînée ? Pour pouvoir faire des rotations dans les deux directions efficacement.

---

## Performance

| Test | Mon résultat | Objectif | Note |
|------|--------------|----------|------|
| 3 nombres | ≤ 3 ops | ≤ 3 | ✅ |
| 5 nombres | ≤ 12 ops | ≤ 12 | ✅ |
| 100 nombres | ~608 ops | < 700 | ✅ |
| 500 nombres | ~5 160 ops | < 5 500 | ✅ |

**Note finale : 30/30**

---

## Gestion des erreurs

Le programme affiche `Error` et quitte si :

- L'entrée contient des doublons (`1 2 2 3`)
- L'entrée contient des valeurs non numériques (`1 deux 3`)
- Les nombres dépassent `INT_MIN` ou `INT_MAX`
- Chaînes vides ou format invalide

Si la pile est déjà triée, le programme quitte simplement (pas de sortie nécessaire).

---

## Ce qui n'a pas marché (et comment je l'ai corrigé)

### Tentative 1 : Tri Radix

Ma première implémentation utilisait le tri radix. Propre, simple, facile à comprendre.

**Problème :** ~6 700 opérations pour 500 nombres. Test échoué.

J'ai dû tout recommencer et apprendre un meilleur algorithme.

### Tentative 2 : Algorithme Turk (première version)

J'ai implémenté l'algorithme Turk à partir d'un tutoriel vidéo.

**Problème :** Toujours ~5 700 opérations. Réussissait de justesse parfois, échouait d'autres fois.

### Tentative 3 : Optimisation du coût

J'ai réalisé que je calculais mal les coûts. J'**additionnais** les coûts de rotation des deux piles, même quand elles pouvaient tourner simultanément.

**La correction :**
```c
// Avant (faux)
cost = cost_a + cost_b;  // Toujours additionner

// Après (correct)
if (same_side)
    cost = max(cost_a, cost_b);  // Peuvent tourner ensemble
else
    cost = cost_a + cost_b;  // Doivent tourner séparément
```

Ce **seul changement** m'a fait descendre à ~5 160 opérations. Taux de réussite constant de 100%.

---

## Structure du projet

```
.
├── Makefile
├── README.md
├── README.fr.md
├── includes/
│   └── push_swap.h
├── srcs/
│   ├── main.c
│   ├── stack_utils.c
│   ├── validation.c
│   ├── stack_init.c
│   ├── parsing/
│   │   ├── parser.c
│   │   └── parse_helpers.c
│   ├── sort/
│   │   ├── sort_small.c
│   │   ├── sort_utils.c
│   │   ├── turk_init.c
│   |   ├── turk_cost.c
│   │   ├── turk_move.c
│   │   └── turk_sort.c
│   └── operations/
│       ├── push.c
│       ├── swap.c
│       ├── rotate.c
│       └── rev_rotate.c
├── libft/
└── ft_printf/
```

À l'origine, tout était dans le répertoire racine avec des noms comme `turk.c`, `turk2.c`, `turk3.c`. J'ai nettoyé ça à la fin.

---

## Tests

```bash
# Tests basiques
./push_swap 3 2 1
./push_swap 5 4 3 2 1

# Cas d'erreur
./push_swap 1 2 1          # Doublons
./push_swap 2147483648     # Dépassement
./push_swap "a b c"        # Non numérique

# Tests de performance (nécessite push_swap_tester)
./complexity 100 100 700 ./push_swap
./complexity 500 20 5500 ./push_swap

# Fuites mémoire
valgrind --leak-check=full ./push_swap 5 4 3 2 1
```

---

## Ressources utilisées

**Tutoriels :**
- Regardé plusieurs vidéos YouTube sur les approches de push_swap
- Lu des exemples d'implémentation (pas copié, juste compris la logique)

**Documentation :**
- `man malloc`, `man free`, `man write`
- Notation Big O et théorie de la complexité algorithmique

**Outils :**
- Utilisé `push_swap_tester` pour benchmarker les performances
- Utilisé `valgrind` pour détecter les fuites mémoire
- Utilisé NotebookLM pour analyser une transcription vidéo et extraire les détails d'optimisation

**Usage de l'IA :**
- Commencé avec le tri radix (simple mais lent)
- L'IA a expliqué pourquoi ce n'était pas assez bon pour 500 éléments
- Appris l'algorithme Turk et les heuristiques gloutonnes
- Obtenu de l'aide pour débugger le calcul de coût (l'optimisation clé)
- Corrigé les violations de la norminette (nombre de lignes, nombre de variables)
- Réorganisé la structure du projet pour plus de clarté

J'ai écrit chaque ligne de code moi-même. L'IA était mon mentor et réviseur de code, pas mon générateur de solutions.

---

## Ce que j'ai vraiment appris

1. **Le choix de l'algorithme compte plus que je ne le pensais.** Radix était élégant mais trop lent. Turk était plus compliqué mais beaucoup plus rapide.
2. **Les petites optimisations s'accumulent.** L'optimisation `rr` / `rrr` a économisé ~500 opérations sur 500 nombres. C'est la différence entre réussir et échouer.
3. **Le glouton marche étonnamment bien.** Toujours choisir le mouvement le "moins cher" n'est pas optimal, mais c'est assez proche et beaucoup plus rapide que de calculer la solution parfaite.
4. **L'organisation du code en vaut la peine.** Refactoriser d'une structure plate vers des dossiers organisés a rendu le débogage beaucoup plus facile.
5. **Les tests révèlent tout.** Les cas limites auxquels je n'avais jamais pensé (chaînes vides, dépassements, doublons) sont tous apparus pendant les tests.

---

**Ce projet m'a appris à penser en termes d'efficacité, pas seulement de correction.**
