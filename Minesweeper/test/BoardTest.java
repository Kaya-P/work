
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;



public class BoardTest {

    
    @Test 
    public void testFlag() {
        Board br = new Board();
        br.addFlag(1, 2);
        
        assertEquals(1, br.countFlags(), "number of flags:");
    }
    
    @Test 
    public void testMultipleFlag() {
        Board br = new Board();
        br.addFlag(1, 2);
        br.addFlag(2, 2);
        br.addFlag(4, 2);
        br.addFlag(6, 2);
        br.addFlag(7, 2);
   
        assertEquals(5, br.countFlags(), "add multiple flags");
    }
    
    @Test 
    public void testRemoveFlag() {
        Board br = new Board();
        br.addFlag(1, 2);
        br.addFlag(2, 2);
        br.addFlag(2, 2);
        
   
        assertEquals(1, br.countFlags(), "add and then remove flag");
    }

    @Test 
    public void testMineClicked() {
        Board b = new Board();
        Block[] m = b.getMines().toArray(new Block[10]);
        b.state(m[1].getX(), m[1].getY());
    
        assertTrue(b.getClickedMine(), "clicked a mine");
    }
    
    @Test 
    public void testNotMineClickedwhenFlagged() {
        Board b = new Board();
        Block[] m = b.getMines().toArray(new Block[10]);
        b.addFlag(m[1].getX(), m[1].getY());
        b.state(m[1].getX(), m[1].getY());
    
        assertFalse(b.getClickedMine(), "not clicked a mine bc flagged");
    }
    
    
    
    @Test 
    public void testMineNotClicked() {
        Board b = new Board();
        int x = 0;
        int y = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!b.getBlock(i,j).getMine()) {
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        
        b.state(x,y);
        assertFalse(b.getClickedMine(), "did not click a mine");

    }
    @Test
    public void testsrndMines() {
        Board b = new Board();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!b.getBlock(i,j).getMine()) {
                    b.getBlock(i, j).isMine();
                }
            }
        }
        if (b.getBlock(1, 1).getMine()) {
            b.getBlock(1, 1).isMine();
        }
        assertEquals(8,b.srndMines(1, 1), "surrounded by mines");
    
    } 
    
    @Test
    public void testNoSrndMines() {
        Board b = new Board();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b.getBlock(i,j).getMine()) {
                    b.getBlock(i, j).isMine();
                }
            }
        }
        if (b.getBlock(1, 1).getMine()) {
            b.getBlock(1, 1).isMine();
        }
        assertEquals(0,b.srndMines(1, 1), "not surrounded by mines");
    
    } 

    
    @Test 
    public void testNumUncovered() {
        Board b = new Board();
        
        assertEquals(0, b.numUncovered(), "new board so everything is covered");
    }
    @Test
    public void testNumUncoveredAll() {
        Board b = new Board();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                b.getBlock(i, j).setCovered(false);
            }
        }
        
        assertEquals(71, b.numUncovered(), "everything except mines are uncovered");
    }
    

    @Test 
    public void testWon() {
        Board b = new Board();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                b.getBlock(i, j).setCovered(false);
            }
        }
        b.winCondition();
    
        assertTrue(b.getWinCondition(), "won the game");
    }
    
    @Test 
    public void testNotYetWon() {
        Board b = new Board();
        for (int i = 4; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                b.getBlock(i, j).setCovered(false);
            }
        }
        b.winCondition();
    
        assertFalse(b.getWinCondition(), "not yet won the game");
    }
    
    @Test 
    public void testState() {
        Board b = new Board();
        b.state(10, 10);
        assertEquals(0, b.numUncovered(), 
                "mouse click would have been out of bounds so nothing chnaged");
    }

    
}
