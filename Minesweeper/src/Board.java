
import java.awt.Color;
import java.awt.Graphics2D;
import java.util.Set;
import java.util.TreeSet;


public class Board  {
    
    private Block[][] board = new Block[9][9];
    
    int x;
    int y;
    boolean clickedMine = false;
    boolean flag;
    boolean win = false;
    Set<Block> mines = new TreeSet<>();

    
    public Board() {
        this.flag = false;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = new Block(i,j);
            }
        }
        mines = random();
        for (Block m : mines) {
            board[m.getX()][m.getY()].isMine();
        }
    }
    
    
    public Block getBlock(int x, int y) {
        return board[x][y];
    }
    
    public int getLength() {
        return  board.length;
    }
   
    public boolean isFlag() {
        return this.flag;
    }
    

    public int srndMines(int xCoord, int yCoord) {
        int row = 8;
        int col = 8;
        int count = 0;
        for (int k = xCoord - 1; k <= xCoord + 1; k++) {
            for (int l = yCoord - 1; l <= yCoord + 1; l++) {
                if (k < 0 || l < 0 || k > row || l > col) {
                    count += 0;
                } else {
                    if (board[k][l].getMine()) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
    public int countFlags() {
        int count = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j].getFlagged()) {
                    count++;
                }
            }
        }
        
        return count;
    }
    
    public void addFlag(int xPos, int yPos) {
        if ((board[xPos][yPos].getCovered() || !board[xPos][yPos].getVisited())) {
            board[xPos][yPos].setFlagged();
        }
    }
    
    public void state(int xPos, int yPos) {
        int w = board.length - 1;
        int h = board[0].length - 1;
        //base case
        if (xPos < 0 || yPos < 0 || xPos > w || 
            yPos > h || board[xPos][yPos].getVisited() || board[xPos][yPos].getFlagged())  {
            return;
        } else {
            //if there is a mine, and it is not flagged
            if (board[xPos][yPos].getMine() && !board[xPos][yPos].getFlagged()) {
                board[xPos][yPos].setCovered(false);
                board[xPos][yPos].hasVisited();
                
                clickedMine = true;
            //if has a mine as a neighbour
            //uncover tile and show number
            } else if (srndMines(xPos, yPos) > 0 && !board[xPos][yPos].getFlagged()) {
                board[xPos][yPos].setCovered(false);
                board[xPos][yPos].hasVisited();
              //empty on purpose, it should not change the state of 
              //and already uncovered block or if it is flagged and flag is off  
            } else if (!board[xPos][yPos].getCovered()) {
                return;
            } else {
                board[xPos][yPos].setCovered(false);
                board[xPos][yPos].hasVisited();
                state(xPos, yPos + 1);
                state(xPos, yPos - 1);
                state(xPos - 1, yPos - 1);
                state(xPos - 1, yPos + 1);
                state(xPos + 1, yPos + 1);
                state(xPos + 1, yPos);
                state(xPos - 1, yPos);
                state(xPos + 1, yPos - 1);
            }
        }
    }
    


    public boolean getWinCondition() {
        return win;
    }

    public void winCondition() {
        if (numUncovered() == 71) { 
            win = true;
        }
    }
    
    public boolean getClickedMine() {
        return this.clickedMine;
    }
    

    public int numUncovered() {
        int count = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (!board[i][j].getCovered() && !board[i][j].getMine()) {
                    count++;
                }
            }
        }
        
        return count;
    }

    
    public TreeSet<Block> random() {
        TreeSet<Block> temp = new TreeSet<>();
        while (temp.size() < 10) {
            
            temp.add(new Block((int) (Math.random() * 8), 
                                (int) (Math.random() * 8)));
        }
        return temp; 
 
    }
    
    public Set<Block> getMines() {
        return mines;
    }
    
    public void drawMines(Graphics2D g, Board b) {
        for (Block mine : b.getMines()) {
            g.setColor(Color.red);
            g.fillOval(mine.getX() * 100 + 50, mine.getY() * 100, 99, 99);
        }  
    }

  

    @Override 
    public boolean equals(Object o) {
        boolean result = false;
        if (o == null) { 
            return false; 
        }
        
        if (o instanceof Board) {
            Board that = (Board) o;
            return that == this;
            
            
        }
        return result;
    }


    
 
   
}   
    