import javax.swing.JButton;
import pixel.*;


public class PixelButton extends JButton {
    private int x;
    private int y;
    private Pixel pixel;

    public PixelButton(int x, int y) {
        this.x = x;
        this.y = y;
        pixel = new Pixel();
    }

    public int getXCoord() {
        return this.x;
    }

    public void setXCoord(int x) {
        if(x >= 0) {
            this.x = x;
        }
        else {
            this.x = 0;
        }
    }

    public int getYCoord() {
        return this.y;
    }

    public void setYCoord(int y) {
        if(y >= 0) {
            this.y = y;
        }
        else {
            this.y = 0;
        }
    }
}