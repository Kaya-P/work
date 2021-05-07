=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
CIS 120 Game Project README
PennKey: kayap_______
=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=

===================
=: Core Concepts :=
===================

- List the three core concepts, the features they implement, and why each feature
  is an appropriate use of the concept. Incorporate the feedback you got after
  submitting your proposal.

  1. Double Array

  2. Recursion 

  3. JUnit 

=========================
=: Your Implementation :=
=========================

- Provide an overview of each of the classes in your code, and what their
  function is in the overall game.
	Block - this refers to each block on the board, it can be flagged, or registered as a mine or uncovered.
	Board - this creates a double array of blocks and initializes each of them. Then it creates a random set of mines and updates those blocks. Here is where the recursion takes place for the flooding and updating the state of each block after it has been pressed.
	GUI - here is where the board is drawn and the graphics are updated. There is an mouselistener for the users clicks on the board, and then the coordinates are recorded and the board is updated.  There is also a timer that measure the length of each game. And the number of mines button updates depending on how many flags the user has used to mark probable mines. The user cannot place more than ten flags as there are only ten mines. 
	Game - this is where the game is run and the window is produced. There is an instructions window that is displayed the first time the game is opened and then once you click okay the game is drawn and ready to play, There is a reset button that allows you to start again, even misplay. There is a radio button to signal if you are drawing flags or uncovering blocks. There is the timer and the number of mines left.  



- Were there any significant stumbling blocks while you were implementing your
  game (related to your design, or otherwise)?
I did struggle to implement to actionlistner at first but once I figured that out, the rest was pretty fine.


- Evaluate your design. Is there a good separation of functionality? How well is
  private state encapsulated? What would you refactor, if given the chance?
I think the game is pretty well done. I would change my organization to allow my to have different difficulties so when I choose a difficulty the size or the board and number of mines is can be changed automatically and it would remain functional. 



========================
=: External Resources :=
========================

- Cite any external resources (libraries, images, tutorials, etc.) that you may
  have used while implementing your game.
Java docs
Youtube tutorial on using JOptionsPane

