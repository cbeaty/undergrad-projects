import pixel.Pixel;
import javax.swing.JOptionPane;
import icon.Icon;

public class Driver {
    public static void main(String[] args) {
        String value = JOptionPane.showInputDialog("Enter Number of Rows");
        int rows = Integer.parseInt(value);
        value = JOptionPane.showInputDialog("Enter Number of Cols");
        int cols = Integer.parseInt(value);
        PixelClassGUI gui = new PixelClassGUI(rows, cols);
    }
}