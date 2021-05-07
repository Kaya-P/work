public class Block implements Comparable<Block> {
    private boolean mine;
    private boolean covered;
    private boolean visited;
    private boolean flagged;
    private int x;
    private int y;
 
    
    public Block(int x, int y) {
        this.mine = false;
        this.covered = true;
        this.visited = false;
        this.flagged = false;
        this.x = x;
        this.y = y;
    }
    //getter function for x position
    public int getX() {
        return x; 
    }
    //getter function for y position
    public int getY() {
        return y;
    }
    //changes mine field of block if mine is there
    public void isMine() {
        this.mine = !this.mine;
    }

    //getter function for if mine is there
    public boolean getMine() {
        return mine;
    }
    //getter function for if block is covered
    public boolean getCovered() {
        return covered;
    }
    
    public void setCovered(boolean c) {
        this.covered = c;
    }

    public boolean getVisited() {
        return visited;
    }
    //changes if the block has been visited or not
    public void hasVisited() {
        this.visited = true;
    }
    public boolean getFlagged() {
        return flagged;
    }
    public void setFlagged() {
        this.flagged = !this.flagged;
    }
    
    @Override
    public int compareTo(Block o) {
        if (o == null) { 
            return -1; 
        }
        if (o.getX() < this.getX()) {
            return -1; 
        }
        if (o.getX() == this.getX()) {
            if (o.getY() == this.getY()) {
                return 0;
            } else if (o.getY() < this.getY()) {
                return -1;
            }
        } else {
            return 1;
        } 
        if (o.getX() > this.getX()) {
            return 1;
        }
        return 0;
    }

    
}
