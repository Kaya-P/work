import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.Timer;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

@SuppressWarnings("serial")
public class GUI extends JComponent implements MouseListener {
    Board b = new Board();
    private boolean flag;
    JLabel stopwatch ;
    JLabel mines;
    //the timer value
    int c = 0;
    Timer timer;
    public static final int X = 100;
    
    int timestep = 0;
    public GUI(JLabel t, JLabel m) {
        stopwatch = t;
        mines = m;
        this.flag = false;
        this.addMouseListener(this);
        
        timer = new Timer(X, new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                //to only increment timer every second
                timestep++;
                tick();
            }
        });
        timer.start(); 
        
       

    }
    void tick() {
        if (timestep % 10 == 0) {
            stopwatch.setText("Timer: " + c++);
        }
        mines.setText("Mines left: " + (10 - b.countFlags()));
    }


    public void mouseClicked(MouseEvent e) {
        int x = (int)((e.getX() - 50) / 100);
        int y = (int)(e.getY() / 100);
        //if user tries to place more than 10 flags
        if (getFlag() && b.countFlags() > 9 && !b.getBlock(x, y).getFlagged()) {
            return;
        
        } else if (getFlag()) {  
            b.addFlag(x, y); 
        } else {
            b.state(x, y);
        
        }
        
        b.winCondition();
        repaint();
        //display messages depending on if they won or lost
        if (b.getClickedMine()) {
            timer.stop();
            JOptionPane.showMessageDialog(this, "awww you lost. Press reset to start again");
            this.setFocusable(false);
        }
        if (b.getWinCondition()) {
            timer.stop();
            JOptionPane.showMessageDialog(this, "YAAAY!! you won. Press reset to try again");
            this.setFocusable(false);
        }
        

    }

    
    public void reset() {
        //create new board, reset timer and flag state must be turned off
        b = new Board();
        this.flag = false; 
        c = 0;
        timer.start();
        
        
    }

    public void setFlag() {
        this.flag = !this.flag; 
    }
    public boolean getFlag() {
        return this.flag;
    }
    
    public Board getBoard() {
        return b;
    }

    
    public void draw(Graphics2D g, Board board) {
        for (int i = 0; i < board.getLength(); i++) {
            for (int j = 0; j < board.getLength(); j++) {
                
                if (board.getBlock(i ,j).getCovered() && !board.getBlock(i ,j).getFlagged()) {    
                    g.setColor(Color.gray);
                    g.fillRect(i * 100 + 50, j * 100, 99, 99);
                } else if (board.getBlock(i ,j).getFlagged() && 
                        board.getBlock(i ,j).getCovered()) { 
                    g.setColor(Color.gray);
                    g.fillRect(i * 100 + 50, j * 100, 99, 99);
                    g.setColor(Color.green);
                    g.fillOval(i * 100 + 50, j * 100, 99, 99);    
                  
                } else if (!board.getBlock(i ,j).getCovered() && board.srndMines(i, j) > 0) {
                    g.setColor(Color.darkGray);
                    g.fillRect(i * 100 + 50, j * 100, 99, 99);
                    g.setColor(Color.black);
                    g.drawString("" + board.srndMines(i, j),i * 100 + 100, j * 100 + 50);
                    
                } else if (!board.getBlock(i ,j).getCovered()) {
                    g.setColor(Color.darkGray);
                    g.fillRect(i * 100 + 50, j * 100, 99, 99);
                
                }
                if (!board.getBlock(i ,j).getCovered() && board.getBlock(i ,j).getMine()) {
                    g.setColor(Color.red);
                    g.fillOval(i * 100 + 50, j * 100, 99, 99);

                }  
            }
        }
    }
    
    


    
    @Override
    public Dimension getPreferredSize() {
        return new Dimension(1000,1000);
    }
    

    

    
    @Override
    public void paintComponent(Graphics gc) {

        super.paintComponent(gc);
 
        draw((Graphics2D)gc, b);

         
        gc.setColor(Color.black);
        if (b.getClickedMine()) {
            b.drawMines((Graphics2D)gc, b);
  
            
        }
         
        if (b.getWinCondition()) {
            draw((Graphics2D)gc, b);
             
        }
         

    }


    @Override
    public void mousePressed(MouseEvent e) {
        // TODO Auto-generated method stub
        
    }


    @Override
    public void mouseReleased(MouseEvent e) {
        // TODO Auto-generated method stub
        
    }


    @Override
    public void mouseEntered(MouseEvent e) {
        // TODO Auto-generated method stub
        
    }


    @Override
    public void mouseExited(MouseEvent e) {
        // TODO Auto-generated method stub
        
    }

}
