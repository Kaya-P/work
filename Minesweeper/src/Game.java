
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.util.Scanner;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

import javax.swing.SwingUtilities;


public class Game implements Runnable {
    JLabel stopwatch = new JLabel();
    JLabel mines = new JLabel();
    GUI gui = new GUI(stopwatch, mines);

    
    
    public static void main(String[] args) {
        // The proper way to create a top-level window:
        //   - make a class that implements Runnable
        //   - the 'run' method creates the actual window
        //   - SwingUtilities.invokeLater calls the 'run'
        //     method after initializing the program state. 
        SwingUtilities.invokeLater(new Game());
        
    }

    

    @Override 
    public void run() {

        JFrame frame = new JFrame("Minesweeper");
        String instructions = "src/Minesweeper.txt";
        
        
        
        try {
            Reader r = new FileReader(instructions);
            BufferedReader br = new BufferedReader(r);
            StringBuilder message = new StringBuilder();
            
            try (Scanner scanner = new Scanner(br)) {
   
                while (scanner.hasNextLine()) {
                    message.append(scanner.nextLine() + System.lineSeparator());
                }
            
            }  
            JOptionPane.showMessageDialog(null, message.toString());

        
        } catch (IOException e1) {
            System.out.println("file not found");
        }
        
        
        
        JPanel panel = new JPanel();
        JPanel panel2 = new JPanel();
        
        panel.setLayout(new BorderLayout());
        //use grid layout to allow spacing between buttons and labels
        GridLayout layout = new GridLayout(1,0);
        layout.setHgap(25);
        panel2.setLayout(layout);
                
        JButton reset = new JButton("Reset");
        JRadioButton flag = new JRadioButton("Flag");
        

        gui.repaint();
        
        panel2.add(reset);
        panel2.add(flag);
        panel2.add(stopwatch);
        panel2.add(mines);
        

        frame.getContentPane().add(panel);
        panel.add(gui,BorderLayout.CENTER);
        panel.add(panel2,BorderLayout.PAGE_START);
        
        //reset button    
        reset.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                gui.reset();
                gui.repaint();
                flag.setSelected(false);
                

            }
        });
        //flag radio button
        flag.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                gui.setFlag();
                
            }
        });
        

        // pack sets the size of the frame automatically
        // based on the sub-components' preferred sizes
        frame.pack();
        
        
        // tell the frame to display itself
        frame.setVisible(true);
        
        // make sure to end the program when the window is 
        // closed
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        
    }

    
}
