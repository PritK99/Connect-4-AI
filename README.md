# Connect 4 AI

<p align="center">
  <img src="https://miro.medium.com/v2/resize:fit:640/format:webp/0*HqTdkytsHijhlRsd.gif" alt="Connect 4 AI">
</p>

<b>Connect Four</b> is a two-player connection game in which the players first choose a color and then take turns dropping one colored disc from the top into a vertically suspended grid. The objective is to connect four of one's own discs of the same color in a row, either horizontally, vertically, or diagonally, before the opponent does.

<b>Note:</b> Since we try to plan the full decision tree at each move, AI takes a long time to choose its move for  board size greater than ```4 x 4```. An improvement can be to implement ```k-ply lookahead```, where the algorithm generates the decision tree of depth ```k```

## Output

```
PS C:\Users\pritp\OneDrive\Desktop\Bingo-AI> ./a
0 0 0 0 
0 0 0 0
0 0 0 0
0 0 0 0
AI plays....
AI is trying to obtain 0 value
0 0 0 0
0 0 0 0
0 0 0 0
1 0 0 0
Human plays....
Enter your column: 3
0 0 0 0
0 0 0 0
0 0 0 0
1 0 0 2
AI plays....
AI is trying to obtain 0 value
0 0 0 0
0 0 0 0
1 0 0 0
1 0 0 2
Human plays....
Enter your column: 3
0 0 0 0
0 0 0 0
1 0 0 2
1 0 0 2
AI plays....
AI is trying to obtain 0 value
0 0 0 0
1 0 0 0
1 0 0 2
1 0 0 2
Human plays....
Enter your column: 0
2 0 0 0
1 0 0 0
1 0 0 2
1 0 0 2
AI plays....
AI is trying to obtain 0 value
2 0 0 0
1 0 0 0
1 0 0 2
1 1 0 2
Human plays....
Enter your column: 3
2 0 0 0
1 0 0 2
1 0 0 2
1 1 0 2
AI plays....
AI is trying to obtain 0 value
2 0 0 1
1 0 0 2
1 0 0 2
1 1 0 2
Human plays....
Enter your column: 2
2 0 0 1
1 0 0 2
1 0 0 2
1 1 2 2
AI plays....
AI is trying to obtain 0 value
2 0 0 1
1 0 0 2
1 1 0 2
1 1 2 2 
Human plays....
Enter your column: 2
2 0 0 1
1 0 0 2
1 1 2 2
1 1 2 2
AI plays....
AI is trying to obtain 1 value
2 0 0 1
1 1 0 2 
1 1 2 2
1 1 2 2
Human plays....
Enter your column: 2
2 0 0 1
1 1 2 2
1 1 2 2
1 1 2 2
AI plays....
AI is trying to obtain 1 value
2 1 0 1
1 1 2 2
1 1 2 2
1 1 2 2
Bingo! AI wins the game.
PS C:\Users\pritp\OneDrive\Desktop\Bingo-AI>
```
