# C / C++ Projects by Bashar Rashed

This repository contains a collection of C and C++ projects I've built to explore various domains such as cryptography, sorting algorithms, natural language processing, and machine learning.

## 🔐 Cypher / Decypher (C)
A simple encryption and decryption tool that demonstrates basic principles of cryptography using substitution or Caesar-style ciphers. 
The program can encrypt messages into unreadable text and decrypt them back into their original form.

Skills: C programming, string manipulation, file I/O

---

## 🚌 Bus Station Sorting (C)
A console-based program that reads bus line data from an input (File) and sorts them by various criteria such as name, distance, or duration. 
The project involves input parsing, structured data storage using `structs`, and sorting algorithms such as Quick-sort and Merge-sort.

Skills: Data structures, struct usage, multi-criteria sorting, user input handling

---

## 🧠 Markov Chain Tweet Generator / Snakes and Ladder (C)
A Markov chain-based text generator trained on tweet-like inputs. It generates pseudo-random text based on the probabilistic transitions between words or characters.
it is first used based on String format, then afterwards turned into a generic MarkovChain that works for any datatype such as in the game Snakes and Ladders, 
which also prints out in a similar fashion to the tweets generator, it prints out an entire simulation of a snakes and ladders game where it shows each step until the finish.
Skills: Markov chains, randomness, linked lists , text parsing , generic C programming

---

## 🎬 Movie Recommendation System (C++)
An intelligent movie recommendation system written in C++ that leverages content-based filtering and collaborative filtering (CF) algorithms. The system analyzes user preferences and movie feature vectors to suggest the most suitable movie for each user. Key components include custom smart pointers, similarity metrics (cosine similarity), and dynamic memory management using STL containers.

Key Features:

Recommends movies using content similarity and collaborative filtering (k-nearest neighbors)

User/movie data is loaded from files

Designed with modular C++ classes (Movie, User, RecommendationSystem, etc.)

Heavy focus on performance and memory safety

Skills: OOP in C++, algorithm design, smart pointers, STL, cosine similarity, matrix/vector math
---

## 🤖 Machine Learning Project (C++)
A basic implementation of a fully connected feedforward neural network in C++ designed to classify handwritten digits (0–9). The model includes four layers with ReLU and Softmax activation functions. It takes grayscale 28×28 images as input and predicts the digit with over 96% accuracy on pre-trained weights. The project focuses on linear algebra operations, custom matrix implementation, and activation function logic.

Architecture:

Input: 784 (28×28) grayscale pixel values

Layers: 128 → 64 → 20 → 10 neurons

Activations: ReLU (for hidden layers), Softmax (for output)

Skills: Matrix operations in C++, neural networks, numerical computation, file I/O, custom class design

---

## 🚀 Getting Started
To run any of the C/C++ projects:
```bash
# Compile (example for cypher project)
gcc cypher.c -o cypher
./cypher
