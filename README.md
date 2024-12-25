CSCI 0300 Project 1 - Snake
===========================

## Design Overview:

For this project, the principle design was creating the classic game Snake, where the snake is represented as a linked list where each node of the linked list stores an index corresponding to its position within a cells array. The user can move the snake across the board by using the arrow keys, which insert and remove nodes from the snake to create movement. Additionally, when the snake encounters certain obstacles or features (i.e. food, walls, or itself), it can either grow (and increment the score by 1) or die, causing the game to terminate.

The main methods of this project were the `update()` method, which keeps track of the movement of the snake and handles these obstacles/features, and `initialize_game()` which takes care of rendering, placing food, and setting up the game board. Another cool design aspect of this project involved creating custom boards through decompressed board strings, allowing the user to play on other boards that are not the default 10 by 20 cell board. The assigning of cells via this decompressed board string was handled by a helper function called `populate_board()`.

Lastly, the user is able to type in their name and have it be displayed when the game is over, along with the score. This is handled in `read_name()` in the `game.c` file and additionally, the `mbslen()` method allows the user to type in names involving any Unicode character, allowing for more flexibility and inclusion within the game.

## Collaborators:
Josh Benzon, Aaron Wang, Alex Choi, Angela Li

## Responsible Computing:
Partner CS login: ali190

## Extra Credit attempted:
No

## How long did it take to complete Snake?
~25 hours

<!-- Enter an approximate number of hours that you spent actively working on the project. -->

## SRC Component:

### Who founded the Consortium? Who is responsible among the current members, and how might that affect decisions being made for Unicode?

The Unicode Consortium was founded by Joe Becker, Lee Collins, and Mark Davis. Becker was a computer scientist, Collins was a software engineer, and Davis was a specialist in internationalization and specialization of software who eventually became the first president of the organization. Members of the corporation include major computer corporations, software producers, database vendors, government ministries, research institutions, and more. Because the consortium is mainly composed of large companies and institutions, this might make it difficult for individuals from more underrepresented backgrounds to have their voices heard within the organization. As a result, certain less popular languages may not have characters included in the Unicode standard since the main people making decisions are those who are heading these large companies.

### Find a language that is not yet in Unicode, has only recently been supported (e.g. in the last 10 years), or is/was missing important characters. What is/was missing, and how does this affect the users of the language?

- One language that is not yet in Unicode is the Ranjana script, a Brahmic script developed around 1100 CE that was used in India and is still used today by the Newar people who live in parts of Nepal. 
- A few documents have been submitted for encoding the Ranjana script in the Unicode standard but no characters have been introduced yet. 
- Although this doesn’t affect a huge number of people around the world, those of Newar descent who reside in certain areas of Nepal and India who practice these linguistic and cultural traditions in modern society might find it difficult to maintain this language, especially if it is not supported by computers.

### For this question, you will need to work with a classmate! Make sure to coordinate so that you outline opposing positions for Part A (e.g. if you outline the ‘for’ position, your partner defends the ‘against’ position). Then, come together and discuss Part B!

### My Conclusion (A)
- For my discussion about the Han unification, I was on the side of supporting the unification. 
- The main point that I outlined in my argument was that many of the glyphs that are similar within the languages have virtually no difference and therefore, they should be consolidated into one encoding. 
- Another point that I considered in my rationale was that bringing these characters together would limit the size of Unicode and allow for other less common languages to have their characters represented in the encoding when they didn’t have any representation to begin with.

- For this part of the question, I learned that Unicode has a section of their encodings called CJK Unified Ideographs which contains almost 21,000 Chinese characters within the block. 
- This block not only includes characters used in the Chinese writing system but also kanji used in the Japanese writing system and hanja (whose use is diminishing in Korea). 
- I think that in some ways, Unicode did a good job preserving some of these traditional characters but in the same vein, this took up a lot of space when it came to allowing others to be represented. 
- In some ways, I think that this overall method is positive but when semantically, many of these characters are the same, it shouldn’t make a difference when it comes to having every single character of the three languages included. 
- Another concern that was brought up by my partner was that languages such as Chinese and Japanese don’t have too many differences when it comes to the legibility of the text, but in regards to textbooks, this could be problematic when interchanging characters.

### Partner Discussion (B)
- My partner made the following claims against unification. She argued that it is simply not an accurate representation of each language and that each language has its own different glyphs, therefore making it impossible for one unified version to accurately represent a language. 
- She also claimed that the Han unification merged characters that users of each language found disparate, producing many inaccuracies. 
- The cultural effects of this unification with distinct languages is also harmful because it creates generalizations that can be made about the groups that are not true, altering the public's perceptions about them.
