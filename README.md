1. Identification:
# Group 124
# Poker Game of Five Card Draw
# Contributed by Lam Wu, Kevin
# And by

2. Description:
# The game we choese to design is a poker game of five card draw. In which, each player would be dealt five cards from a deck of 52. The winner is determined based on the ranks of the five hands. A primary program handles the courses of a game, including but not limited to asking the number of players, initializing the deck, annoucing the winner. A secondary program is required to generate a text file, called "ranks.txt" which ranks all 2,598,960 distinct combinations of hands, in descending order of ranks to return a corresponding index.

3. Features:
# Random - an array of cards denotation is randomized. The n-th card belongs to player ((n modulo m) + 1), where m is the number of player.
# Data Structure - a class of player, which includes the name of the player, players' wealth, sorted hands, and an index returned by search in rank.txt, for storing game status and facilitating hands comparison.
# Dynamic Memory - a vector of the player class, supporting a varying number of player from at least 1 to at most 10.
# File Manipulation - writing of rank.txt, reading content of rank.txt into array to make comparison between hands.
# Mulitple Codes - a primary (main) and seconday (text file) program, and makefile for compilation.
# File Input/Output - read user input about player's name, his original wealth as well as number of players and rounds (less original wealth, more players and rounds implies greater difficulty for victory and even survival up till the last round)
