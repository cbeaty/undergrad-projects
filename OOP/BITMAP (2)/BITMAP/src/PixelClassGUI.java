import java.awt.Color;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.awt.*;
import javax.imageio.ImageIO;
import javax.swing.filechooser.FileSystemView;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JOptionPane;

import icon.*;

public class PixelClassGUI extends JFrame implements ActionListener {
    private PixelClassGUI THIS = this;
    private JPanel buttonPanel;
    private JPanel colorPanel;
    private JCheckBox advanced;
    private JButton createBITMAP;
    private JTabbedPane advancedPanes;
    private JSlider red;
    private JSlider green;
    private JSlider blue;
    private JTextField previewColor;
    private JPanel pastColorPanel;
    private ArrayList<JButton> pastColor;
    private ArrayList<ArrayList<JButton>> allButtons;
    private BufferedImage img;
    private JFileChooser saver;
    private Icon icon;

    public PixelClassGUI(int rows, int cols) {
        super("One GUI to Rule Them All");
        JPanel container = new JPanel(); // The overall JPanel that holds the smaller ones
        container.setLayout(new GridBagLayout()); //GridbBagLayout for more customization.. kind of. 
        GridBagConstraints c = new GridBagConstraints();
        buttonPanel = new JPanel(); //THis panel hold all the buttons that are used to create the icon
        previewColor = new JTextField(); //A simple text field that shows the color the user is about to choose
        buttonPanel.setLayout(new GridLayout(rows, cols)); // Make a grid of pixel buttons
        icon = new Icon(rows, cols); // Make a grid of pixels
        pastColorPanel = new JPanel(); //THe panel that is used to hold previous colors
        advanced = new JCheckBox("Advanced");
        pastColor = new ArrayList<JButton>(); //Arraylist that holds the previous colors
        allButtons = new ArrayList<ArrayList<JButton>>(); //Used for manipulating the buttons in the advanced panel
        pastColorPanel.setLayout(new BoxLayout(pastColorPanel, BoxLayout.X_AXIS)); //Just buttons along the x axis
        /*THis for loop goes for the 5 steps (max amount of previous colors) and creates a button
        for each index and gets the background from the backgroud of the button (one of the previous colors). 
        THere is a function below that deals with the duplicate cases. This then sets the slider values to 
        that previous color.
        */
        for (int i = 0; i < 5; i++) {
            JButton temp = new JButton();
            temp.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int r = temp.getBackground().getRed();
                    int b = temp.getBackground().getBlue();
                    int g = temp.getBackground().getGreen();
                    red.setValue(r);
                    blue.setValue(b);
                    green.setValue(g);
                }
            });
            pastColorPanel.add(temp);
            pastColor.add(temp);
        }
        //Don't need the action listener now, but maybe later for something.
        advanced.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                JCheckBox cb = (JCheckBox) event.getSource();
                if (cb.isSelected()) {
                    // System.out.println("Got it.");
                }
            }
        });
        //This nested for loop creates the pixelbuttons and handles the many cases that require action
        for (int i = 0; i < rows; i++) {
            ArrayList<JButton> rowButton = new ArrayList<JButton>(); //All the rows that are to be stored
            for (int j = 0; j < cols; j++) {
                PixelButton b = new PixelButton(i, j); //create pixelbutton at current location.
                rowButton.add(b); //Add to the rowButton that will later be stored in the allbuttons for the whole grid
                b.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        //This is for when the advanced button is selected to deal with that case.
                        if (advanced.isSelected()) { 
                            // create a new JDialog
                            JDialog newDialog = new JDialog(PixelClassGUI.this, "Advanced Menu", true);
                            //Create the panes and tabs
                            advancedPanes = new JTabbedPane();
                            JPanel tab1 = new JPanel();
                            tab1.setLayout(new BoxLayout(tab1, BoxLayout.Y_AXIS));
                            //Creating ways for user input for rows and columns
                            JLabel labelr = new JLabel("Rows:");
                            JTextField userRows = new JTextField();
                            userRows.setBounds(50, 100, 200, 30);
                            JTextField userCols = new JTextField();
                            userCols.setBounds(50, 150, 200, 30);
                            JLabel labelc = new JLabel("Columns:");
                            //THe ok button executes the user input
                            JButton block = new JButton("OK");
                            block.addActionListener(new ActionListener() {
                                @Override
                                public void actionPerformed(ActionEvent event) {
                                    //Get the pixelbutton location so that we can change the icon from the Icon class
                                    //This is because we can easily create a bitmap from the Icon class
                                    int x = ((PixelButton) e.getSource()).getXCoord();
                                    int y = ((PixelButton) e.getSource()).getYCoord();
                                    //converting the string to int (SHould probably put some logic in to handle exceptions)
                                    String rowS = userRows.getText();
                                    String colS = userCols.getText();
                                    int r = Integer.parseInt(rowS);
                                    int c = Integer.parseInt(colS);
                                    /*This for loop gets the this instance of the PixelGUI (so that we have full access
                                    to the grid of buttons and icon pixels) and sets their color to whatever the user
                                    set the sliders to before.*/
                                    for (int i = 0; i < r; i++) {
                                        for (int j = 0; j < c; j++) {
                                            //Handles any out of bounds EX: 5x5 grid and user asks for 40x40 filler color
                                            if (i + x < rows && j + y < cols) { 
                                                THIS.allButtons.get(x + i).get(y + j).setBackground(
                                                        new Color(red.getValue(), green.getValue(), blue.getValue()));
                                                THIS.icon.setRGB(x + i, y + j, red.getValue(), green.getValue(),
                                                        blue.getValue());
                                                checkPrevColors(b);
                                            }
                                        }
                                    }
                                }
                            });
                            //adding all the labels to the first tab
                            tab1.add(labelr);
                            tab1.add(userRows);
                            tab1.add(labelc);
                            tab1.add(userCols);
                            tab1.add(block);
                            //Add the first tab to the panes
                            advancedPanes.addTab("Block", tab1);
                            //Now for the second tab
                            JPanel tab2 = new JPanel();
                            tab2.setLayout(new BoxLayout(tab2, BoxLayout.Y_AXIS));
                            JLabel label = new JLabel("Choose a Bitmap");
                            JButton chooseFile = new JButton("Choose File");
                            chooseFile.addActionListener(new ActionListener() {
                                @Override
                                public void actionPerformed(ActionEvent e) {
                                    //Used to find files in the users directory
                                    JFileChooser jfc = new JFileChooser(
                                            FileSystemView.getFileSystemView().getHomeDirectory());

                                    int returnValue = jfc.showOpenDialog(null);

                                    if (returnValue == JFileChooser.APPROVE_OPTION) {
                                        File bmpFile = jfc.getSelectedFile(); 
                                        img = null;
                                        try {
                                            img = ImageIO.read(bmpFile); //Makes sure it is a bitmap file
                                        } catch (IOException e1) {
                                            e1.printStackTrace();
                                        }
                                    }
                                }
                            });
                            JButton ok = new JButton("OK");
                            ok.addActionListener(new ActionListener() {
                                @Override
                                public void actionPerformed(ActionEvent event) {
                                    int x = ((PixelButton) e.getSource()).getXCoord();
                                    int y = ((PixelButton) e.getSource()).getYCoord();
                                    //This is used to go through the image and get and set the colors
                                    marchThroughImage(img, x, y, rows, cols);
                                }
                            });
                            JButton preview = new JButton("Preview Image.");
                            preview.addActionListener(new ActionListener() {
                                @Override
                                public void actionPerformed(ActionEvent event) {
                                    //Goes through to set up a preview image of the image the user wants
                                    marchThroughImage(img);
                                }
                            });
                            //Add stuff to the second tab
                            tab2.add(label);
                            tab2.add(chooseFile);
                            tab2.add(ok);
                            tab2.add(preview);
                        
                            advancedPanes.addTab("Pic", tab2);
                            //Get everything in the JDialog
                            newDialog.add(advancedPanes);
                            //set the size and location of the JDialog and make it visible
                            newDialog.setSize(400, 300);
                            newDialog.setLocation(400, 400);
                            newDialog.setVisible(true);
                        }
                        //If the button is unselected, we need to just change the pixel one at a time
                        else {
                            //Get the position of the pixelbutton
                            int x = ((PixelButton)e.getSource()).getXCoord();
                            int y = ((PixelButton)e.getSource()).getYCoord();
                            //Set the background of that pixel to whatever the sliders are
                            b.setBackground(new Color(red.getValue(),green.getValue(),blue.getValue()));
                            //Set the background of the preview color to whater the sliders are
                            previewColor.setBackground(new Color(red.getValue(),green.getValue(),blue.getValue()));
                            //Checks to make sure we aren't adding the same color over and over again to the
                            //previous color panel. Also handles deletions when the the panel is full
                            checkPrevColors(b);
                            //make sure the icon is a correct representation of the grid the user sees
                            icon.setRGB(x, y, red.getValue(),green.getValue(),blue.getValue());
                        }
                    }
                });
                //Add the pixelbuttons to the button panel
                buttonPanel.add(b);
            }
            //Add the rows of buttons to the arraylist<arraylist<buttons>>
            allButtons.add(rowButton);
        }
        //Make the buttons fill the panel better
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1.0; 
        c.weighty = 1.0;
        c.gridx = 0; //first row and first column
        c.gridy = 0;
        c.gridwidth = 3; //Make it take up the entire top row
        container.add(buttonPanel, c);
        colorPanel = new JPanel();
        //Setting the layout such that the labels are on top of the color sliders
        colorPanel.setLayout(new GridLayout(6, 1));
        //Creating the Labels
        JLabel rLabel = new JLabel("Red");
        JLabel gLabel = new JLabel("Green");
        JLabel bLabel = new JLabel("Blue");
        //Creating the Sliders
        red = createSlider(red);
        green = createSlider(green);
        blue = createSlider(blue);
        //Adding the labels
        colorPanel.add(rLabel);
        colorPanel.add(red);
        colorPanel.add(gLabel);
        colorPanel.add(green);
        colorPanel.add(bLabel);
        colorPanel.add(blue);
        c.gridwidth = 2; //Want the panel to take up two rows so it looks better
        c.gridx = 0; //First row
        c.gridy = 1; //Second column
        c.gridheight = 1; //Take up 2 more columns so it looks better
        container.add(colorPanel, c);
        c.gridheight = 2; //Greater height for the preview of the color
        c.gridwidth = 1; //Resetting the grid width
        c.gridx = 2; //Over one column from the sliders
        c.gridy = 1; //Still one below the button grid
        container.add(previewColor, c);
        c.gridx = 2; //Same row as preview color, but
        c.gridy = 2; //Under the preview color
        container.add(pastColorPanel, c);
        createBITMAP = new JButton("Create BITMAP Image");
        createBITMAP.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //icon.makeFile(); //Can be used to create one where this program is stored
                saver = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory()); //Get home directory
                byte[] contentInBytes = icon.FileHeader(); //Need to get the byte[] so that we can save as a bitmap
                switch (saver.showSaveDialog(PixelClassGUI.this)) {
                    case JFileChooser.APPROVE_OPTION: //When you save it
                    try(FileOutputStream fop = new FileOutputStream(saver.getSelectedFile()+".bmp")) { //Allow for user to set name, always a .bmp
                        fop.write(contentInBytes); //Write it
                        fop.flush();
			            fop.close();    
                    }
                    catch (Exception ex) {
                        ex.printStackTrace();
                    }
                    //Let's you know where you selected the file to go
                    JOptionPane.showMessageDialog(PixelClassGUI.this, "Selected: "+
                                                     saver.getSelectedFile(),
                                                     "BITMAP",
                                                     JOptionPane.OK_OPTION);
                       break;

                    case JFileChooser.CANCEL_OPTION:
                        //When you cancel
                       JOptionPane.showMessageDialog(PixelClassGUI.this, "Cancelled",
                                                     "BITMAP",
                                                     JOptionPane.OK_OPTION);
                       break;
                    //yeah, something whent wrong
                    case JFileChooser.ERROR_OPTION:
                       JOptionPane.showMessageDialog(PixelClassGUI.this, "Error",
                                                     "BITMAP",
                                                     JOptionPane.OK_OPTION);
                 }
            }
        });
        c.fill = GridBagConstraints.HORIZONTAL; //Looks better to me
        c.gridx = 0;
        c.gridy = 2; //Under the sliders
        container.add(createBITMAP, c);
        c.gridx = 1; //Next to the create bitmap button
        c.gridy = 2; 
        container.add(advanced, c);
        //Add the container to the JFrame
        add(container);
        setSize(500, 500);
        setLocation(50, 50);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    private JSlider createSlider(JSlider color) {
        color = new JSlider(JSlider.HORIZONTAL,0, 255, 0);
        color.setMajorTickSpacing(25);
        color.setMinorTickSpacing(5); //Every 5 looked the best, could maybe add a value tracker next to it later
        color.setPaintTicks(true);
        color.setPaintLabels(true);
        color.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent ce) { //Makes so the color is constantly changing on the preview
               previewColor.setBackground(new Color(red.getValue(),green.getValue(),blue.getValue()));
            }
         });
        return color;
    }
    private void checkPrevColors(PixelButton b) {
        for (int i = 0; i < 5; i++) {
            //Create temporary button
            JButton temp = new JButton();
            //Run the colorPrev on the pastColor list and see if it is the same as the default button
            boolean colorPrev = previousColor(pastColor, b.getBackground());
            //Check to see if all 5 spots are filled
            boolean full = colorFull(pastColor);
            //If not the same as the background or it is a previous color
            if (!pastColor.get(i).getBackground().equals(temp.getBackground()) || colorPrev == true) {
                if (full != true) {
                    continue; //We want to add it because it is unique
                }
                else if (colorPrev == true) {
                    continue; //Don't want to remove the last element if it is now the newest color 
                }
                else {
                    pastColor = removeColor(pastColor); //Failed the rest which means the previous color panel is full
                }
            }
            else if (full == false) { //Unique color and not full so add it!
                pastColor.get(i).setBackground(b.getBackground());
                break; //Don't want to fill the previous color panel with just one color!
            }
        }
        for (JButton bu : pastColor) {
            pastColorPanel.add(bu); //Add all the buttons to the pastColor panel
        }
    }
    private void marchThroughImage(BufferedImage image) { //Used specifically for the preview window
        if (image == null) { //In case the user presses the button when no image is selected (avoids crash)
            JDialog newDialog = new JDialog(PixelClassGUI.this, "Image Preview.", true);
            newDialog.setSize(400, 300);
            newDialog.setLocation(400, 400);
            newDialog.setVisible(false); //Window will pop up but won't be seen
        }
        else { //User has successfully added a bitmap file!
            //get the dimensions of the image
            int w = image.getWidth();
            int h = image.getHeight();
            //New window to display the image
            JDialog newDialog = new JDialog(PixelClassGUI.this, "Image Preview.", true);
            JPanel screen = new JPanel();
            screen.setLayout(new GridLayout(h, w));
            //Go through the elements of the image
            for (int i = 0; i < h; i++) {
              for (int j = 0; j < w; j++) {
                JButton b = new JButton();
                int pixel = image.getRGB(j, i); //Get the pixel
                int red = (pixel >> 16) & 0xff; //get the red portion and make it an int
                int green = (pixel >> 8) & 0xff; //get the green portion and make it an int
                int blue = (pixel) & 0xff; //get the blue portion and make it an int
                b.setBackground(new Color(red, green, blue)); //Set the temp button to the rgb value
                screen.add(b); //add to the panel
              } 
            }
            newDialog.add(screen); //Add it to the dialog
            newDialog.setSize(400, 300);
            newDialog.setLocation(400, 400);
            newDialog.setVisible(true);
        }
    }
    //Used to set the grid that the user sees to the bitmap that they added
    private void marchThroughImage(BufferedImage image, int x, int y, int rows, int cols) {
        //Get image dimensions
        int w = image.getWidth();
        int h = image.getHeight();
    
        for (int i = 0; i < h; i++) {
          for (int j = 0; j < w; j++) {
            //Same as before, just getting the color values from the pixel 
            int pixel = image.getRGB(j, i);
            int red = (pixel >> 16) & 0xff;
            int green = (pixel >> 8) & 0xff;
            int blue = (pixel) & 0xff;
            if (x + i < rows && y + j < cols) { //This so it doesn't go out of bounds
                //Setting the grid that the user sees, wherever they selected the image to appear
                THIS.allButtons.get(i+x).get(j+y).setBackground(new Color(red, green, blue));
                //Doing the same for the background icon
                THIS.icon.setRGB(i+x, j+y, red, green, blue);
            }
          }
        }
    }
    public boolean previousColor(ArrayList<JButton> list, Color c) {
        boolean retVal = false;
        for (JButton b : list) { //Search the list
            if (b.getBackground().equals(c)) {
                retVal = true; //This means that the color is already apart of the list
            }
        }
        return retVal;
    }
    public boolean colorFull(ArrayList<JButton> list) {
        boolean retVal = true; //Assume it is full
        JButton temp = new JButton();
        for (JButton b : list) { //Search through the list
            if (b.getBackground().equals(temp.getBackground())) {
                retVal = false; //If one of the elements has the default color background, it is empty
                break;
            }
        }
        return retVal;
    }
    public ArrayList<JButton> removeColor(ArrayList<JButton> list) {
        JButton temp = new JButton();
        for (int i = 0; i < list.size(); i++) { //Go through the list
            if (i + 1 < list.size()) { //Don't step out of bounds
                list.get(i).setBackground(list.get(i+1).getBackground()); //Shift all the colors over
            }
            else {
                list.get(i).setBackground(temp.getBackground()); //Reset the next value to the default so a new one can be added
            }
        }
        return list;
    }
    //I get an error if this isn't here, but the program works with it empty
    @Override
    public void actionPerformed(ActionEvent e) {

    }
}