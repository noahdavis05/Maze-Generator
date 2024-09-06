# Maze Generator
A simple C program that generates a maze using the recursive backtracking algorithm. This project serves as a demonstration of algorithm implementation and code structuring for university coursework.
## Table of Contents
- [Overview](#overview)
- [Usage](#usage)
- [Examples](#examples)

## Overview
This project showcases a maze generation algorithm implemented in C using recursive backtracking. The program dynamically generates a random maze on each run and displays it in the terminal and saves the maze to a text file.

## Usage
Use the makefile with the command 'make' to compile.
Then to run the code use the command './mazeGenerator filename width height', to make a maze of a certain width and height and to save it to a certain file.

## Examples
From the command './mazeGenerator file.txt 30 30'
```
                                  #       #           # E # 
  # # # # # # # # # # # # # # #   #   #   #   #   #   #   # 
          #                   #       #   #   #   #   #   # 
  # # #   #   # # #   # # #   # # # # #   # # #   #   #   # 
  #   #   #       #   #               #       #   #   #   # 
  #   #   # # # # #   #   # # # # # # # # #   #   #   #   # 
      #           #   #       #           #   #   #       # 
# #   # # # # #   #   # # #   #   # # #   #   #   # # #   # 
  #   #   #       #   #       #   #   #       #       #   # 
  #   #   #   # # #   #   # # #   #   # # # # # # #   #   # 
          #   #       #       #   #       #           #   # 
  # # # # #   #   # # # # #   #   #   #   # # #   # # #   # 
  #           #           #   #   #   #       #   #       # 
  #   #   # # # # # # #   #   #   #   # # #   #   # # # # # 
  #   #   #           #   #   #       #   #   #           # 
  #   #   #   # # #   #   #   # # # # #   #   #   # # #   # 
  #   #   #       #   #   #   #           #   #   #   #   # 
  #   # # # # #   #   #   #   #   # # #   #   #   #   #   # 
  #               #   #   #   #       #   #   #       #   # 
# # # #   #   # # #   #   # # # #     #   #   # # #   #     
        S     #       #       #               #   #   #   # 
  # # #   #   #   # # #   #   #   # # # # # # #   #   #   # 
      #   #   #   #       #   #       #               #   # 
# #   #   #   #   #     # #   # # #   #   # # # # # # #   # 
      #       #   #       #       #   #           #   #   # 
  # # # # # # #   # # #   # # #   #   # # # #     #   #   # 
  #           #       #       #   #       #           #   # 
  # # #   #   # # #   # # #   #   # # #   # # # # # # #   # 
          #           #       #                           # 
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
```
From the command './mazeGenerator file.txt 10 20'
```
# E                 
#   #   # # # # # # 
#   #               
#   # # # # #   #   
#               #   
# # # # # # # # #   
#           #       
#   # # #   #   # # 
#       #   #       
# # #   #   # # #   
#       #           
#   # # # # # # #   
#   #       #       
#   # # #   #   # # 
#       #       #   
# # #   #   # # #   
#       #           
#   # # # # # # #   
#                 S 
# # # # # # # # #   
```
