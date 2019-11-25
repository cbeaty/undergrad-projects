import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTable;

public class StateGUI extends JFrame {
    private String content;
    private StateCounter state;

    public StateGUI() {
        super("Code Character Results");
        //Creates the JFileChooser and sets the mode to files and directies
        JFileChooser chooser = new JFileChooser();
        chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
        int rc = chooser.showOpenDialog(null);
        //Makes sure the file is a .java file
        while (rc == JFileChooser.APPROVE_OPTION && !chooser.getSelectedFile().getName().endsWith(".java")) {
            JOptionPane.showMessageDialog(null, "The file " + chooser.getSelectedFile() + " is not java source file.",
                    "Open Error", JOptionPane.ERROR_MESSAGE);
            rc = chooser.showOpenDialog(null);
        }
        //Getting the file path
        File file = chooser.getSelectedFile();
        String filePath = file.getAbsolutePath();
        //Trying to convert the file to a byte array, and converting that to a string
        try {
            content = new String(Files.readAllBytes(Paths.get(filePath)), StandardCharsets.ISO_8859_1);
        } catch (IOException e) {
            e.printStackTrace();
        }
        //Running the state on the string array of the .java file
        state = new StateCounter(content);
        //Getting all the data
        String code = Integer.toString(state.getCode());
        String single = Integer.toString(state.getSingle());
        String multi = Integer.toString(state.getMulti());
        String javadoc = Integer.toString(state.getJava());

        String[][] data = { 
            { "Code", code }, 
            { "Single line Comment", single },
            { "Multi-line Comment", multi},
            { "Javadoc Comment", javadoc} 
        }; 
  
        // Column Names 
        String[] columnNames = { "Counter Type", "Number of Characters" }; 
  
        // Initializing the JTable 
        JTable table = new JTable(data, columnNames); 
        table.setBounds(30, 40, 200, 300);
        table.setFillsViewportHeight(true);

        JScrollPane sp = new JScrollPane(table);
        add(sp);
        //Make it visible and whatnot
        setSize(1000, 400);
        setLocation(50, 50);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
}