# tpZ – Binary Search Tree Transformations

## 📌 Overview

This project explores how Binary Search Trees (BSTs) can be transformed through node rotations based on starting characters. It was developed as a practical application of the **Z programming language**, created by **Professor D.E. Zegour** at **ESI Algiers**.

The program reads words from a file, builds different BST structures (BST0 to BST3), and analyzes how tree behavior changes when nodes are prioritized or deprioritized based on their starting letters (e.g. X, Y, Z).

> **Authors**: Maram Daas & Hibatallah Khadir  
> **Status**: Students at ESI

---

## 🌳 Trees Used

- **BST0** – plain tree, words inserted in file order  
- **BST1** – words starting with **X, Y, Z** are **moved up toward the root**  
- **BST2** – balances special words by **bringing them to the middle**  
- **BST3** – words starting with **X, Y, Z** are **moved down**, away from the root

> The letters X, Y, Z are configurable.

---

## 📂 Files in This Project
`tpZ Daas_Khadir 13 (z-part).alg` (original code in **Z language**)
`tpZ Daas_Khadir 13 (c-part).c` (converted C code) 
`tpZ Daas_Khadir 13 (rapport).pdf` (project report) 

---

## 🧪 Features

- Read or generate word lists
- Build 4 types of BSTs
- Rotate nodes by rules (to root, middle, down)
- Perform traversals and range queries
- Compare access paths and node visits

---

## License

This project is licensed under the [MIT License](./LICENSE).
