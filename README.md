Team Name: Project 2 22

Team Members: Angela Acquista, Eva Chacin, and Julie Wang

Project Title:

Problem: The problem we are trying to solve is in the U.S. There are many different restaurants in the world and are rated based on their quality. However, the person who is interested would have to manually do research on multiple sites to find ratings on all the different restaurants and also find the types of food these restaurants offer.

Motivation: This is a problem because having to manually research in multiple places to find ratings of different restaurants and such can be extremely time consuming and exhausting.

Features: We know that we have solved the problem when we have one program that filters by ratings and also the types of food the user likes to eat for all the U.S. restaurants.

Data: The dataset we will use is from kaggle: U.S. Restaurants: https://www.kaggle.com/datasets/kwxdata/380k-restaurants-mostly-usa-based 

Tools: C++, SFML

Visuals: We will be creating a CLI (Command Line Interface) which will be made up of questions for the users that will be used to find the right restaurant for their cravings. These questions include things like where are you located? What kind of food are you looking for? And many more to make sure that the user finds the perfect restaurant with the perfect ranking in their area. Additionally, to make the program more visually appealing we will be integrating the SFML graphics library with the CLI.  

Strategy: We will use a hashtable where each type of food has a corresponding list of restaurants that offer these dishes. The second data structure will be a heap, specifically a max heap that will find the restaurants with the highest ratings.

Distribution of Responsibility and Roles: 
Angela is responsible for implementing the other data structure which is the heap(max) to find the restaurants with the highest ratings. 
Julie is responsible for implementing one of the data structures, which is the hashtable to efficiently filter the restaurants the user will be interested in. 
Eva is responsible for the visuals of the program, creating the CLI and integrating the SFML graphics into the program.

References:
https://www.kaggle.com/datasets/kwxdata/380k-restaurants-mostly-usa-based 
